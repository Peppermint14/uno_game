#include <gtest/gtest.h>
#include <vector>
#include <thread>
#include <chrono>
#include <future>

#include "../../include/common/common.hpp"
#include "../../include/client/tcp_client.hpp"
#include "../../include/server/tcp_server.hpp"


TEST(TCP_Connection_Test, ResponseTest) {

    Logger::init();
    auto future = std::async(std::launch::async, [&]{

        try {
            net::TCP_Server::init(8080, [&](Player_id _id, const std::string& _msg){
                if(_msg == "{\"id\":1}") return;

                //auto log = Logger::get("server_main");
                //log->debug("[cb] {}", _msg);
                size_t in = std::stoull(_msg);
                net::TCP_Server::broadcast(std::to_string(in + 1));
            });
            net::TCP_Server::barrier();
        } catch(const std::exception& _e){
            auto logger = Logger::get("server_main");
            logger->error( _e.what());
            return;
        }
    });
    
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);

    std::vector<size_t> vals;
    for(size_t i = 0; i < 100; ++i)
        vals.push_back(i);

    std::vector<size_t> result;

    std::mutex mutex;

    try {
        net::TCP_Client::connect("localhost", 8080, [&](const std::string& _msg){
            if(_msg == "{\"id\":1}") return;
            //auto log = Logger::get("client_main");
            //log->debug("[cb] {}", _msg);
            std::lock_guard<std::mutex> lock(mutex);
            result.push_back(std::stoull(_msg));
        });
    } catch(const std::exception& _e){
        auto logger = Logger::get("client_main");
        logger->error(_e.what());      
    }

    for(size_t i = 0; i < vals.size(); ++i)
        net::TCP_Client::send(std::to_string(vals[i]));

    while(true){
        std::this_thread::sleep_for(0.25s);
        std::lock_guard<std::mutex> lock(mutex);
        if(result.size() == vals.size()) break;
    }

    for(size_t i = 0; i < vals.size(); ++i)
        ASSERT_EQ(vals[i] + 1, result[i]);

    net::TCP_Client::terminate();
    std::this_thread::sleep_for(1s);
    net::TCP_Server::terminate();
    std::this_thread::sleep_for(1s);
    future.wait();
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}