/*
 Contains the definition of the Ball class
 */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifdef _WIN32
#include "ResourcePath.h"
#elif __APPLE__
#include "ResourcePath.hpp"
#endif

class Ball
{
public:
	Ball(int screen_width, float x, float y);
	~Ball();

	void Move();
    void ReverseVertical();
    void ReverseHorizontal();
    void SetPosition(float x, float y);
    void SetMove(int xMove, int yMove);
	sf::RectangleShape GetBall() const;
    int GetWidth() const;
	
	const static int INITIAL_SIZE = 15;
    
    
    static sf::SoundBuffer* ballSound;
    static sf::Sound* sound;
    
    static void InitSound();
    static void DeleteSound();
    static void PlaySound();
    
private:
	sf::RectangleShape *mBall;
    int mWidth;
	int mXMove;
	int mYMove;

};
