#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "common.hpp"

#include <sockpp/tcp_socket.h>
#include <sockpp/tcp_acceptor.h>

namespace net {
    namespace detail {
        class TCPException : public std::exception {
            const std::string msg;
        public:
            TCPException(const std::string& _msg) noexcept : msg(_msg) {}
            const char* what() const noexcept override { return msg.data(); }
        };
    }  // namespace detail
}  // namespace net

#endif /* NETWORK_HPP */