#ifndef CONFIG_PARSER
#define CONFIG_PARSER

#include "nlohmann/json.hpp"
#include "Logger.hpp"

namespace Maze::Trace
{
    constexpr auto ConfigPath = "../config/Application.json";

    class ConfigParser
    {
    public:
        static ConfigParser &GetInstance();
        bool LoadConfig();

        [[nodiscard]] float GetVersion();
        [[nodiscard]] LogLevel LoggingLevel();
        [[nodiscard]] std::string LoggingType();
        [[nodiscard]] std::string LogFilePath();

    private:
        ConfigParser() = default;
        ~ConfigParser() = default;

        nlohmann::json m_jsonData;
    };
} // namespace Maze::Trace

#endif