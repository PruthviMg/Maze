#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "Common.hpp"
#include "PlatformHandler.hpp"
#include "Grid.hpp"
#include <random>

namespace Maze::Manager
{
    class Manager
    {
    public:
        Manager();
        ~Manager();

        void Init();
        void RunMainLoop();

    private:
        sf::RenderWindow m_window;
        sf::Event m_event;

        Platform::PlatformHandler<Platform::Grid> m_platform;
    };
}

#endif