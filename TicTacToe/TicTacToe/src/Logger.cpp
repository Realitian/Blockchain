#include "Logger.h"

Logger::Logger(const std::string& name)
{
    flux.open(name);
}

void Logger::write(const std::string& refference)
{
    flux << refference << std::endl;
}
Logger::~Logger()
{
    flux.close();
}
