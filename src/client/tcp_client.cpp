
#include "../../include/client/player_controller.hpp"
#include "../../include/client/tcp_client.hpp"
#include <sockpp/exception.h>

sockpp::tcp_connector*  net::TCP_Client::_connection = nullptr;

bool  net::TCP_Client::_connectionSuccess = false;
bool  net::TCP_Client::_failedToConnect = false;



void net::TCP_Client::init(const std::string& host, const uint16_t port) {

    // initialize sockpp framework
    sockpp::socket_initializer sockInit;
    // reset connection status
    net::TCP_Client::_connectionSuccess = false;
    net::TCP_Client::_failedToConnect = false;

    // delete exiting connection and create new one
    if( net::TCP_Client::_connection != nullptr) {
         net::TCP_Client::_connection->shutdown();
        delete  net::TCP_Client::_connection;
    }
     net::TCP_Client::_connection = new sockpp::tcp_connector();

    // try to connect to server
    if( net::TCP_Client::connect(host, port)) {
        //GameController::showStatus("Connected to " + host + ":" + std::to_string(port));
        player_controller::showStatus("Connected to " + host + ":" + std::to_string(port));
	net::TCP_Client::_connectionSuccess = true;

        // start network thread
	 net::ResponseListenerThread* responseListenerThread = new net::ResponseListenerThread(net::TCP_Client::_connection);
        if(responseListenerThread->Run() != wxTHREAD_NO_ERROR) {
            //GameController::showError("Connection error", "Could not create client network thread");
	    player_controller::showError("Connection error", "Could not create client network thread");

        }

    } else {
        net::TCP_Client::_failedToConnect = true;
        //GameController::showStatus("Not connected");
	player_controller::showStatus("Not connected");	
    }
}


bool  net::TCP_Client::connect(const std::string& host, const uint16_t port) {

    // create sockpp address and catch any errors
    sockpp::inet_address address;
    try {
        address = sockpp::inet_address(host, port);
    } catch (const sockpp::getaddrinfo_error& e) {
        //GameController::showError("Connection error", "Failed to resolve address " + e.hostname());
	player_controller::showError("Connection error", "Failed to resolve address " + e.hostname());
        return false;
    }

    // establish connection to given address
    if (!net::TCP_Client::_connection->connect(address)) {
        //GameController::showError("Connection error", "Failed to connect to server " + address.to_string());
	player_controller::showError("Connection error", "Failed to connect to server " + address.to_string());

        return false;
    }

    return true;
}


void net::TCP_Client::send(const std::string& msg) {

    // wait until network is connected (max. 5 seconds)
    int connectionCheckCounter = 0;
    while(!net::TCP_Client::_connectionSuccess
          && !net::TCP_Client::_failedToConnect
          && connectionCheckCounter < 200) {
        wxMilliSleep(25);
        connectionCheckCounter++;
    }

    // do not continue if failed to connect to server
    if(net::TCP_Client::_failedToConnect) {
        return;
    }

    if( net::TCP_Client::_connectionSuccess &&  net::TCP_Client::_connection->is_connected()) {
        // serialize request into JSON string
        //rapidjson::Document* jsonDocument = request.to_json();
        //std::string message = json_utils::to_string(jsonDocument);
        //delete jsonDocument;

        // turn message into stream and prepend message length
        //std::stringstream messageStream;
        //messageStream << std::to_string(msg.size()) << ':' << msg;
	//std::string message = messageStream.str();
	std::string message = msg;

        // output message for debugging purposes
#ifdef PRINT_NETWORK_MESSAGES
        std::cout << "Sending request : " << message << std::endl;
#endif

        // send message to server
        ssize_t bytesSent =  net::TCP_Client::_connection->write(message);
        // if the number of bytes sent does not match the length of the message, probably something went wrong
        if (bytesSent != ssize_t(message.length())) {
            //GameController::showError("Network error", "Error writing to the TCP stream: " + ClientNetworkManager::_connection->last_error_str());
	    player_controller::showError("Network error", "Error writing to the TCP stream: " + net::TCP_Client::_connection->last_error_str());

        }

    } else {
        //GameController::showError("Network error", "Lost connection to server");
	player_controller::showError("Network error", "Lost connection to server");
    }
}


void  net::TCP_Client::parseResponse(const std::string& message) {

    // output message for debugging purposes
#ifdef PRINT_NETWORK_MESSAGES
    std::cout << "Received response : " << message << std::endl;
#endif

    //rapidjson::Document json = rapidjson::Document(rapidjson::kObjectType);
    //json.Parse(message.c_str());

    try {
        //server_response* res = server_response::from_json(json);
        //res->Process();
	player_controller::eval_response(message);

    } catch (std::exception e) {
        //GameController::showError("JSON parsing error", "Failed to parse message from server:\n" + message + "\n" + (std::string) e.what());
	player_controller::showError("JSON parsing error", "Failed to parse message from server:\n" + message + "\n" + (std::string) e.what());

    }
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//

net::ResponseListenerThread::ResponseListenerThread(sockpp::tcp_connector* connection) {
    this->_connection = connection;
}


net::ResponseListenerThread::~ResponseListenerThread() {
    this->_connection->shutdown();
}


wxThread::ExitCode net::ResponseListenerThread::Entry() {
    try {
        char buffer[512]; // 512 bytes
        ssize_t count = 0;

        while ((count = this->_connection->read(buffer, sizeof(buffer))) > 0) {
            try {
                int pos = 0;

                // extract length of message in bytes (which is sent at the start of the message, and is separated by a ":")
                std::stringstream messageLengthStream;
                while (buffer[pos] != ':' && pos < count) {
                    messageLengthStream << buffer[pos];
                    pos++;
                }
                ssize_t messageLength = std::stoi(messageLengthStream.str());

                // initialize a stream for the message
                std::stringstream messageStream;

                // copy everything following the message length declaration into a stringstream
                messageStream.write(&buffer[pos + 1], count - (pos + 1));
                ssize_t bytesReadSoFar = count - (pos + 1);

                // read remaining packages until full message length is reached
                while (bytesReadSoFar < messageLength && count != 0) {
                    count = this->_connection->read(buffer, sizeof(buffer));
                    messageStream.write(buffer, count);
                    bytesReadSoFar += count;
                }

                // process message (if we've received entire message)
                if (bytesReadSoFar == messageLength) {
                    std::string message = messageStream.str();
                    player_controller::getMainThreadEventHandler()->CallAfter([message]{
                       net::TCP_Client::parseResponse(message);
                    });

                } else {
                    this->outputError("Network error", "Could not read entire message. TCP stream ended early. Difference is " + std::to_string(messageLength - bytesReadSoFar) + " bytes");
                }

            } catch (std::exception& e) {
                // Make sure the connection isn't terminated only because of a read error
                this->outputError("Network error", "Error while reading message: " + (std::string) e.what());
            }
        }

        if (count <= 0) {
            this->outputError("Network error", "Read error [" + std::to_string(this->_connection->last_error()) + "]: " + this->_connection->last_error_str());
        }

    } catch(const std::exception& e) {
        this->outputError("Network error", "Error in listener thread: " + (std::string) e.what());
    }

    this->_connection->shutdown();

    return (wxThread::ExitCode) 0; // everything okay
}


void net::ResponseListenerThread::outputError(std::string title, std::string message) {
    //GameController::getMainThreadEventHandler()->CallAfter([title, message]{
      //  GameController::showError(title, message);
    //});
}

/*
net::TCP_Client* net::TCP_Client::instance = new net::TCP_Client();


net::TCP_Client::TCP_Client() noexcept {
 	toSend = std::make_unique<util::BlockQueue<std::string>>();   
 	shutdown = false;
}

/*net::TCP_Client::~TCP_Client() noexcept{
        shutdown = true; 
}


void net::TCP_Client::send(const std::string& _msg) noexcept {
    std::lock_guard<std::mutex> lock(instance->mutex);
    instance->toSend->push(_msg);
}

void net::TCP_Client::terminate() noexcept {
    auto log = Logger::get("client_main");
    log->info("Shutdown recieved.");
    instance->shutdown = true;
}

//use for debug and test purpose only
void net::TCP_Client::barrier() noexcept {
    auto logger = Logger::get("client_main");
    logger->info("Waiting for shutdown...");
    char i;
    std::cin >> i;
    terminate();
    logger->info("Waiting for threads to shut down...");

    logger->info("Goodbye!");
}

*/
//from other



