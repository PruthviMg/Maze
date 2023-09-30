#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <random>

namespace Maze::Common
{
    class Utility
    {
    public:
        template <typename T>
        static T GetRandom(T low, T high)
        {
            std::random_device rd;
            std::mt19937 generator(rd());
            std::uniform_int_distribution<T> distribution(low, high);

            return distribution(generator);
        }

    private:
    };
}

#endif