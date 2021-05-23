#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include "../common/common.hpp"
#include "../common/utils.hpp"

#include <sockpp/tcp_socket.h>
#include <sockpp/tcp_connector.h>
#include <sockpp/inet_address.h>
#include <sockpp/tcp_acceptor.h>


namespace net {

    class TCP_Client {
        std::future<void> listener;
	std::unique_ptr<util::BlockQueue<std::string>> toSend;
	util::BlockQueue<std::string> cbQueue;
        std::mutex mutex;
        std::future<void> connection;
        bool connected;
	    std::atomic<bool> shutdown = false;
        bool isInit = false;

        static TCP_Client* instance;

        TCP_Client() noexcept;
	
	//from other
	static bool connect(const std::string& host, const uint16_t port);
    	static sockpp::tcp_connector* _connection;
    	static bool _connectionSuccess;
    	static bool _failedToConnect;
	
	std::function<void(const std::string&)> cb = 0;



    public:

        static void send(const std::string&) noexcept;
        static void terminate() noexcept;
        static void barrier() noexcept;

        template<class Port, class Callback>
        static void connect(const std::string& _adress, Port _port, Callback _callback){
            if(instance->isInit) throw new ckException("TCP_Client already initialised");
            instance->isInit = true;
            instance->cb = _callback;
	    auto logger = Logger::create("client_main");

           
	    //auto logger = Logger::create("client_thread");
            logger->info("Welcome. Initializing client...");
	    instance->connection = std::async(std::launch::async, [/*coptr = std::move(coptr),*/ adress = _adress, port = _port, cb = _callback]() mutable {
                               //logge//instance->cb = _callback;r->info("connected to {} on port {}", adress, port);
		auto logger = Logger::create("client_connection");
		sockpp::socket_initializer sockInit;
		sockpp::tcp_acceptor acc(port);
		if(!acc){
			logger->error("Error opening acceptor: {}", acc.last_error_str());
			throw new ckException(acc.last_error_str());
		}
		logger->info("Socket open and listening on port {}",port);
		while (!instance->shutdown) {
                    sockpp::tcp_socket sock = acc.accept();
                    sock.read_timeout(0.25s);
                    sock.write_timeout(0.25s);
                    sock.set_non_blocking(true);

                    if (!sock) {
                        logger->error("Error accepting incoming connection: {}", acc.last_error_str());
                    } else {
                        bool er = true;
                        /*for (size_t i = 0; i < 4; ++i) {
                            if (instance->connection != NULL) continue;*/
                            er = false;
                            instance->connection = {std::async(std::launch::async, [instance = instance, sock = std::move(sock)]() mutable {
                                char buf[1024];
                                std::queue<char> msg;
                                std::queue<char> curMsg;

                                using clock = std::chrono::high_resolution_clock;
                                std::stringstream ss;
                                ss << "server_player_";
                                auto logger = Logger::create(ss.str());

                                //notify the connection of a new player
                                /*
                                nlohmann::json cmsg;
                                cmsg["type"] = "new_player";
                                cmsg["id"] = id + 1;
                                instance-> cbQueue.push({static_cast<Player_id>(id+1), cmsg.dump()});
                                */

		while(!instance->shutdown){
		  auto now = clock::now();

                                    //send
                                    {
                                        auto& q = instance->toSend;
                                        while (!q->empty()) {
                                            std::string msg_ = q->front();
                                            msg_.push_back(static_cast<char>(3));
                                            if(sock.write(msg_) == 1)
                                                logger->error("Send failed: {}", msg_);
                                            else{
                                                logger->debug("Sent: {}", msg_);
                                                q->pop();
                                            }                                     
                                        }
                                    }

                                    //recieve
                                    {
                                        ssize_t n;
                                        
                                        while ((n = sock.read(buf, sizeof(buf))) > 0) {
                                            for (size_t i = 0; i < n; ++i)
                                                msg.push(buf[i]);
                                        }
                                        if (!msg.empty()) {
                                            //parse all containing messages in the buffer
                                            while(!msg.empty()){
                                                const char c = msg.front();
                                                msg.pop();
                                                //reached end of message
                                                if(c == static_cast<char>(3)){
                                                    std::string message;
                                                    message.reserve(curMsg.size());
                                                    while(!curMsg.empty()){
                                                        message.push_back(curMsg.front());
                                                        curMsg.pop();
                                                    }
                                                    logger->debug("Received: {}", message);
                                                    //callback(static_cast<Player>(id+1),message);
                                                    instance->cbQueue.push(message);
                                                } else
                                                    curMsg.push(c);                                                
                                            }                                   
                                        }
                                    }
                                    //max 60 fps
                                    const auto delta = 16ms - std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - now);
                                    if(delta > 0ms) std::this_thread::sleep_for(delta);
                                }

                                sock.shutdown();
                                //instance->connection.reset();
			})};
 
                //nlohmann::json msg;
                            //msg["id"] = i+1;
                            //TCP_Server::sendToPlayer(static_cast<Player_id>(i+1), msg.dump());
                            break;
		
 		if (er)
                            logger->error("cannot accept more connections");

	}
}
            });
        }

      
    };

}

#endif /* TCP_CLIENT_HPP */
