#ifndef IPLATFORM_HPP
#define IPLATFORM_HPP

#include "Common.hpp"

namespace Maze::Platform
{
    using EntityId = int32_t;
    using Position = sf::Vector2f;

    class IPlatform
    {
    public:
        virtual ~IPlatform() = default;

        /**
         * To define the dimensions of the platform
         * @param width
         * @param height
         * */
        virtual void Init(const int32_t &, const int32_t &) = 0;
        /**
         * To define the dimensions of the platform
         * @param window object for drawing
         * */
        virtual void Solve(std::reference_wrapper<sf::RenderWindow>) = 0;
    };
}

#endif
