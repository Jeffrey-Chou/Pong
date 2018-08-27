#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "PongGame.h"
#include "TextWindow.h"
#include "PongNetworking.h"

#ifdef _WIN32
#include "ResourcePath.h"
#elif __APPLE__
#include "ResourcePath.hpp"
#endif

void SetMenuText(sf::Text& menuText, const sf::Font& font, const char* text, const unsigned int size, const float x, const float y)
{
    menuText.setFont(font);
    menuText.setString(text);
    menuText.setCharacterSize(size);
    menuText.setFillColor(sf::Color::White);
    sf::FloatRect bounds = menuText.getGlobalBounds();
    menuText.setPosition(x - bounds.width/2, y);
}

void StartPongGame(sf::RenderWindow& window, int selection, sf::Font& font)
{
    switch(selection)
    {
        case 0:
        {
            window.clear();
            PongGame game(window);
            game.Run();
            break;
        }
        case 1:
        {
            window.clear();
            PongNetworking host;
            host.WaitForClient();
            PongGame game(window);
            game.RunHost(host);
            break;
        }
        case 2:
        {
            sf::String str = TextWindow().GetDestinationIP(font);
            PongNetworking client(42070);
            client.SetDest(str);
            client.ConnectToHost();
            window.clear();
            PongGame game(window);
            game.RunClient(client);
            break;
        }
    }

}

int main(void)
{
    
    int screen_width = 1024, screen_height = 768;
    int pad_width = screen_width/30, pad_height = screen_height /4;
	sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Pong");
    sf::Font font;
    
    font.loadFromFile( resourcePath() + "sansation.ttf");
    sf::Text title;
    sf::Text subMenu[3];
    SetMenuText(title, font, "Pong", 100, screen_width/2, screen_height/3);

    sf::Vector2f titlePos = title.getPosition();
    sf::FloatRect titleBounds = title.getGlobalBounds();
    
    SetMenuText(subMenu[0], font, "Local", 50, titlePos.x - 150, titlePos.y * 2);
    SetMenuText(subMenu[1], font, "Host", 50, titlePos.x + titleBounds.width/2, titlePos.y * 2);
    SetMenuText(subMenu[2], font, "Join", 50, titlePos.x + titleBounds.width + 150, titlePos.y * 2);
    
    
    int selection = 0;
    subMenu[selection].setStyle(sf::Text::Style::Underlined);
    
	
	window.setFramerateLimit(60);
	
	
	while (window.isOpen())
	{
		sf::Event event;
		
		while (window.pollEvent(event))
		{
			
			switch (event.type)
			{
                case sf::Event::Closed:
                    window.close();
                    
                    break;
                case sf::Event::KeyPressed:
                    
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Left:
                            if(selection == 0)
                            {
                                break;
                            }
                            subMenu[selection--].setStyle(0);
                            subMenu[selection].setStyle(sf::Text::Style::Underlined);
                            break;
                        case sf::Keyboard::Right:
                            if(selection == 2)
                            {
                                break;
                            }
                            subMenu[selection++].setStyle(0);
                            subMenu[selection].setStyle(sf::Text::Style::Underlined);
                            break;
                            
                        case sf::Keyboard::Enter:
                            StartPongGame(window, selection, font);
                            break;
                        default:
                            break;
                    }
                
                    break;
                    
                default:
                    break;
                
			}
        
		}

        window.clear();
        window.draw(title);
        window.draw(subMenu[0]);
        window.draw(subMenu[1]);
        window.draw(subMenu[2]);
        window.display();
	}
    
	return 0;
}
