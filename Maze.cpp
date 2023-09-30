#include "Manager.hpp"

using namespace Maze::Trace;
using namespace Maze::Manager;

void InitializeLogging()
{
    ConfigParser::GetInstance().LoadConfig();
    std::ofstream fs;

    if (ConfigParser::GetInstance().LoggingType() == "File")
    {
        fs.open(ConfigParser::GetInstance().LogFilePath());

        Logger::init<std::ofstream>(ConfigParser::GetInstance().LoggingLevel(), &fs);
    }
    else if (ConfigParser::GetInstance().LoggingType() == "Console")
    {
        Logger::init<std::ostream>(ConfigParser::GetInstance().LoggingLevel());
    }
    else if (ConfigParser::GetInstance().LoggingType() == "SStream")
    {
        Logger::init<std::stringstream>(ConfigParser::GetInstance().LoggingLevel());
    }
}

void run()
{
    Manager manager;
    manager.Init();
    manager.RunMainLoop();
}

void test()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Lines");
    // Create a vertex array for the rectangle
    sf::VertexArray rectangle(sf::Lines);

    // Define the four corner points of the rectangle
    sf::Vector2f topLeft(100, 100);
    sf::Vector2f topRight(300, 100);
    sf::Vector2f bottomRight(300, 200);
    sf::Vector2f bottomLeft(100, 200);

    // Add lines connecting the points to form a rectangle
    rectangle.append(sf::Vertex(topLeft, sf::Color::Red));
    rectangle.append(sf::Vertex(topRight, sf::Color::Red));

    rectangle.append(sf::Vertex(topRight, sf::Color::Green));
    rectangle.append(sf::Vertex(bottomRight, sf::Color::Green));

    rectangle.append(sf::Vertex(bottomRight, sf::Color::Blue));
    rectangle.append(sf::Vertex(bottomLeft, sf::Color::Blue));

    rectangle.append(sf::Vertex(bottomLeft, sf::Color::Yellow));
    rectangle.append(sf::Vertex(topLeft, sf::Color::Yellow));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(rectangle); // Draw the lines
        window.display();
    }
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    InitializeLogging();

    run();
    // test();

    return 0;
}