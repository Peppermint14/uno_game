#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Logger {
    [[nodiscard]] std::shared_ptr<spdlog::logger> create(const std::string& /*name*/) noexcept;
    [[nodiscard]] std::shared_ptr<spdlog::logger> get(const std::string& /*name*/) noexcept;
    void drop(const std::string& /*_name*/) noexcept;
};

#endif /*LOGGER_HPP*/