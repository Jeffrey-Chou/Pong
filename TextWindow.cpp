

#include "TextWindow.h"

TextWindow::TextWindow()
{
    window.create(sf::VideoMode(700,200), "Pong");
}

sf::String TextWindow::GetDestinationIP(sf::Font& font)
{
    sf::Text prompt;
    prompt.setFont(font);
    prompt.setString("Enter an IP Address: ");
    prompt.setCharacterSize(40);
    
    sf::Text addr;
    addr.setFont(font);
    addr.setCharacterSize(40);
    addr.setPosition(prompt.getGlobalBounds().width, 0);
    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    
                    return "";
                    
                case sf::Event::TextEntered:
                    if (event.text.unicode >= 46 && event.text.unicode <=57)
                    {
                        ipaddr += static_cast<char>(event.key.code);
                        
                    }
                    else if(event.text.unicode == 8)
                    {
                        ipaddr.erase(ipaddr.getSize()-1);
                    }
                    
                    else if(event.text.unicode == 10)
                    {
                        window.close();
                    }
                    addr.setString(ipaddr);
                    break;
            }
        }
        
        window.clear();
        window.draw(prompt);
        window.draw(addr);
        window.display();
    }
    return ipaddr;
}
