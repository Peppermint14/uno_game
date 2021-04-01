
#include "../../include/common/logger.hpp"

#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Logger::create(const std::string& _name) noexcept{
    static auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto logger = std::make_shared<spdlog::async_logger>(_name, stdout_sink, spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    logger->set_level(spdlog::level::trace);
    spdlog::register_logger(logger);
    return spdlog::get(_name);
}

std::shared_ptr<spdlog::logger> Logger::get(const std::string& _name) noexcept{
    return spdlog::get(_name);
}

void Logger::drop(const std::string& _name) noexcept{
    spdlog::drop(_name);
}