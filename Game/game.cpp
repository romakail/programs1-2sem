#include <SFML/Graphics.hpp>

const int WINDOW_HEIGHT = 900;
const int WINDOW_LENGHT = 900;


int game ();

class gameObject
{
private:

    double x;
    double y;
    double v;


public:


};



int game()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_LENGHT), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    //sf::Vector2f rightVector

    double x = 0;
    double y = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Right))
        {
            x += 0.1;
            shape.setPosition(sf::Vector2f(x, y));
        }

        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Left))
        {
            x -= 0.1;
            shape.setPosition(sf::Vector2f(x, y));
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}













