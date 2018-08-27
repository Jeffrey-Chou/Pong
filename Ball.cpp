#include "Ball.h"

sf::SoundBuffer* Ball::ballSound;
sf::Sound* Ball::sound;

Ball::Ball(int screen_width, float x, float y)
{
    mWidth = screen_width/50;
	mBall = new sf::RectangleShape(sf::Vector2f(mWidth, mWidth));
	mBall->setFillColor(sf::Color::White);
	mBall->setPosition(sf::Vector2f(x, y));
	mXMove = 3;
	mYMove = -3;
}

Ball::~Ball()
{
	delete mBall;
}

void Ball::Move()
{
	mBall->move(mXMove, mYMove);
}

void Ball::ReverseVertical()
{
    mYMove = -mYMove;
}

void Ball::ReverseHorizontal()
{
    mXMove = -mXMove;
}

void Ball::SetPosition(float x, float y)
{
    mBall->setPosition(x, y);
}

void Ball::SetMove(int xMove, int yMove)
{
    mXMove = xMove;
    mYMove = yMove;
}

sf::RectangleShape Ball::GetBall() const
{
	return *mBall;
}

int Ball::GetWidth() const
{
    return mWidth;
}

void Ball::InitSound()
{
    ballSound = new sf::SoundBuffer();
    sound = new sf::Sound();
    ballSound->loadFromFile(resourcePath() + "beep.wav");
    sound->setBuffer(*ballSound);
}

void Ball::DeleteSound()
{
    delete ballSound;
    delete sound;
}

void Ball::PlaySound()
{

    sound->play();
}


