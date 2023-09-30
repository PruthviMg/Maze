#include "Manager.hpp"

namespace Maze::Manager
{
    Manager::Manager() : m_window{sf::VideoMode(Common::WIDTH, Common::HEIGHT), Common::WINDOW_NAME}
    {
        // m_window.setFramerateLimit(10);
    }

    Manager::~Manager()
    {
    }

    void Manager::Init()
    {
        m_platform.Init(Common::WIDTH, Common::HEIGHT);
    }

    void Manager::RunMainLoop()
    {
        Log(Log::DEBUG, __func__);
        while (m_window.isOpen())
        {
            m_window.clear(sf::Color::Black);
            while (m_window.pollEvent(m_event))
            {
                if (m_event.type == sf::Event::Closed)
                {
                    m_window.close();
                }
                if (m_event.type == sf::Event::KeyPressed)
                {
                    if (m_event.key.code == sf::Keyboard::Escape)
                    {
                        m_window.close();
                    }
                }
                if (m_event.type == sf::Event::MouseButtonPressed)
                {
                    if (m_event.mouseButton.button == sf::Mouse::Button::Left)
                    {
                    }

                    if (m_event.mouseButton.button == sf::Mouse::Button::Right)
                    {
                    }
                }
            }

            m_platform.Solve(std::ref(m_window));

            m_window.display();
        }
    }
}