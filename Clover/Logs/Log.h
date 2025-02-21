#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include <string>

enum LogLevel { INFO, WARN, CRITICAL };

void Log(const std::string& message, LogLevel level = INFO);


#endif // LOGGER_H
