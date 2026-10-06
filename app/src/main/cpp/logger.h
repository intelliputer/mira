//
// Created by sf on 6/28/17.
//

#ifndef XPLATDEV_LOGGER_H
#define XPLATDEV_LOGGER_H

#include <iostream>
#include <sstream>

namespace _Logger {
    enum Severity {
        LOG_DEBUG = 0,
        LOG_INFO,
        LOG_WARN,
        LOG_ERROR,
        LOG_FATAL
    };

    class Logger {
    private:
        std::stringstream logbuf;
        Severity severity;

        std::string sevStr()
        {
            switch(severity){
                case LOG_DEBUG:
                    return "[DEBUG] ";
                case LOG_INFO:
                    return "[INFO] ";
                case LOG_WARN:
                    return "[WARN] ";
                case LOG_ERROR:
                    return "[ERROR] ";
                case LOG_FATAL:
                    return "[FATAL] ";
                default:
                    return "default";
            }
        }

        static std::ostream& getStream(Severity s)
        {
            if (s < LOG_ERROR)
            {
                return std::cout;
            }
            else
            {
                return std::cerr;
            }
        }

    public:
        static Severity& minSeverity()
        {
            static Severity minSeverity = LOG_DEBUG;
            return minSeverity;
        }

        Logger(Severity s) : severity(s)
        {

        }
        ~Logger()
        {
            getStream(severity) << sevStr() << logbuf.str() << std::endl;
        }
        std::stringstream& log()
        {
            return logbuf;
        }

    };
};

#define Log(LOGLEVEL) _Logger::Logger(_Logger::LOGLEVEL).log()

#endif // XPLATDEV_LOGGER_H
