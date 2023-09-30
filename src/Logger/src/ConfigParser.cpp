#include "ConfigParser.hpp"

namespace Maze::Trace
{
    ConfigParser &ConfigParser::GetInstance()
    {
        static ConfigParser obj;
        return obj;
    }

    bool ConfigParser::LoadConfig()
    {
        std::ifstream config;
        config.open(ConfigPath);

        if (config.is_open())
        {
            m_jsonData = nlohmann::json::parse(config);
            config.close();
            return true;
        }
        else
        {
            return false;
        }
    }

    float ConfigParser::GetVersion()
    {
        return m_jsonData["Version"];
    }
    LogLevel ConfigParser::LoggingLevel()
    {
        // Fetching Log level
        LogLevel level = LogLevel::DISABLE;
        uint8_t val = m_jsonData["LoggingLevel"];
        switch (val)
        {
        case 1:
            level = LogLevel::FATAL;
            break;
        case 2:
            level = LogLevel::WARN;
            break;
        case 3:
            level = LogLevel::ERROR;
            break;
        case 4:
            level = LogLevel::INFO;
            break;
        case 5:
            level = LogLevel::DEBUG;
            break;
        case 6:
            level = LogLevel::VERBOSE;
            break;
        }

        return level;
    }
    std::string ConfigParser::LoggingType()
    {
        return m_jsonData["LoggingType"];
    }
    std::string ConfigParser::LogFilePath()
    {
        return m_jsonData["LogFilePath"];
    }

}