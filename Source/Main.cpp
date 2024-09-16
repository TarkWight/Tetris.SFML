#include <SFML/Graphics.hpp>
#include <iostream>
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    sf::RectangleShape rectangle(sf::Vector2f(120.f, 60.f));
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition(340.f, 270.f);

     while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        window.draw(rectangle);

        window.display();
    }

    return 0;
}
