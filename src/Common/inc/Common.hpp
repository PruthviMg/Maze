#ifndef COMMON_HPP
#define COMMON_HPP

#include <SFML/Graphics.hpp>
#include "ConfigParser.hpp"
#include <vector>
#include <unordered_map>
#include "Utility.hpp"
#include <stack>

#define Log(args, ...) Maze::Trace::Logger::Logging(args, __VA_ARGS__)
using Log = Maze::Trace::LogLevel;

namespace Maze::Common
{
    constexpr auto WINDOW_NAME = "Maze";
    constexpr auto HEIGHT = 800;
    constexpr auto WIDTH = 800;

}

#endif