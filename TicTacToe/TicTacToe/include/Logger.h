#ifndef LOGGER_H
#define LOGGER_H
#include <ostream>
#include <fstream>
#include <string>

class Logger
{
public:
    Logger(const std::string&);
    virtual ~Logger();
    void write(const std::string &);
protected:
private:
    std::string name;
    std::ofstream flux;
};

#endif // LOGGER_H
