#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "IPlatform.hpp"

namespace Maze::Platform
{
    constexpr auto MIN_WIDTH = 20;
    constexpr auto MIN_HEIGHT = 20;

    enum class Quadrant : uint8_t
    {
        Top,
        Right,
        Bottom,
        Left
    };

    class Block
    {
        std::unordered_map<Quadrant, sf::VertexArray> lines;
        std::unordered_map<Quadrant, bool> m_walls;
        std::vector<sf::Color> m_colors{sf::Color::Green, sf::Color::Blue, sf::Color::White, sf::Color::Red, sf::Color::Magenta};

    public:
        Position m_position;
        bool m_visited{false}, m_pathTraversered{false};
        int32_t m_id;

        Block(Position position, int32_t id) : m_position(position), m_id(id)
        {
            auto ch = Common::Utility::GetRandom<int>(0, m_colors.size() - 1);

            // sf::Color color = sf::Color(0, 0, 0);
            sf::Color color(sf::Color::Red);
            // sf::Color color = m_colors[ch];

            // Top
            sf::VertexArray top(sf::Lines);
            top.append(sf::Vertex({position.x, position.y}, color));             // x,y
            top.append(sf::Vertex({position.x + MIN_WIDTH, position.y}, color)); // x+w, y
            lines[Quadrant::Top] = top;
            m_walls[Quadrant::Top] = true;

            // Right
            sf::VertexArray right(sf::Lines);
            right.append(sf::Vertex({position.x + MIN_WIDTH, position.y}, color));             // x+w, y
            right.append(sf::Vertex({position.x + MIN_WIDTH, position.y + MIN_WIDTH}, color)); // x+w, y+w
            lines[Quadrant::Right] = right;
            m_walls[Quadrant::Right] = true;

            // Bottom
            sf::VertexArray bottom(sf::Lines);
            bottom.append(sf::Vertex({position.x + MIN_WIDTH, position.y + MIN_WIDTH}, color)); // x+w, y+w
            bottom.append(sf::Vertex({position.x, position.y + MIN_WIDTH}, color));             // x, y+w
            lines[Quadrant::Bottom] = bottom;
            m_walls[Quadrant::Bottom] = true;

            // Left
            sf::VertexArray left(sf::Lines);
            left.append(sf::Vertex({position.x, position.y + MIN_WIDTH}, color)); // x, y+w
            left.append(sf::Vertex({position.x, position.y}, color));             // x, y
            lines[Quadrant::Left] = left;
            m_walls[Quadrant::Left] = true;
        }

        void draw(std::reference_wrapper<sf::RenderWindow> window)
        {
            // Log(Log::DEBUG, __func__);

            if (m_walls[Quadrant::Top])
                window.get().draw(lines[Quadrant::Top]);

            if (m_walls[Quadrant::Right])
                window.get().draw(lines[Quadrant::Right]);

            if (m_walls[Quadrant::Bottom])
                window.get().draw(lines[Quadrant::Bottom]);

            if (m_walls[Quadrant::Left])
                window.get().draw(lines[Quadrant::Left]);

            if (m_visited)
            {
                sf::RectangleShape rectangle(Position(MIN_WIDTH, MIN_WIDTH));
                rectangle.setPosition(m_position);
                // rectangle.setFillColor(sf::Color::Green);
                rectangle.setFillColor(sf::Color(7, 67, 147));

                // window.get().draw(rectangle);
            }
        }

        void RemoveWall(Quadrant quadrant)
        {
            m_walls[quadrant] = false;
        }

        void HighLight(std::reference_wrapper<sf::RenderWindow> window)
        {
            sf::RectangleShape rectangle(Position(MIN_WIDTH / 10, MIN_WIDTH / 10));
            rectangle.setPosition(sf::Vector2f(m_position.x + MIN_WIDTH / 2, m_position.y + MIN_WIDTH / 2));
            // rectangle.setPosition(m_position);

            rectangle.setFillColor(sf::Color::Green);
            // rectangle.setFillColor(sf::Color(7, 67, 147));

            window.get().draw(rectangle);
        }

        bool WallPresent(Quadrant quadrant)
        {
            return m_walls[quadrant];
        }
    };
} // namespace Maze::Platform

#endif