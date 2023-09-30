#ifndef PLATFORM_HANDLER_HPP
#define PLATFORM_HANDLER_HPP

#include "IPlatform.hpp"

namespace Maze::Platform
{
    template <typename Platform, typename SFINAE_PlaceHolder = std::void_t<>>
    class PlatformHandler
    {
    };

    template <typename Platform>
    class PlatformHandler<Platform, std::enable_if_t<std::is_base_of<IPlatform, Platform>::value>>
    {
    public:
        PlatformHandler() : m_platform(std::make_shared<Platform>())
        {
        }
        ~PlatformHandler()
        {
            m_platform.reset();
        }
        void Init(const int32_t &width, const int32_t &height)
        {
            m_platform->Init(width, height);
        }
        void Solve(std::reference_wrapper<sf::RenderWindow> window)
        {
            m_platform->Solve(window);
        }

    private:
        std::shared_ptr<Platform> m_platform;
    };
}

#endif
