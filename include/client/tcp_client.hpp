#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include "../common/common.hpp"
#include "../common/network.hpp"

namespace net {

    using namespace std::literals::chrono_literals;
    using Logger = std::shared_ptr<spdlog::logger>;

    class TCP_Client {

    public:
        static void connect(Logger /*_logger*/, const std::string& /*adress*/);
    };

}

#endif /* TCP_CLIENT_HPP */