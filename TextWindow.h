

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
class TextWindow
{
public:
    TextWindow();
    sf::String GetDestinationIP(sf::Font&);
    
private:
    sf::RenderWindow window;
    sf::String ipaddr;
};
