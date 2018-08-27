#include "Paddle.h"

Paddle::Paddle(float width, float height, float xcoord, float ycoord)
{
	mPaddle = new sf::RectangleShape(sf::Vector2f(width, height));
    mWidth = width;
    mHeight = height;
	mPaddle->setFillColor(sf::Color::White);
	mPaddle->setPosition(sf::Vector2f(xcoord, ycoord));
	mVelocity = INITIAL_VELOCITY;
	mUpMove = mDownMove = false;
}

Paddle::~Paddle()
{
	delete mPaddle;
}

void Paddle::Move(int max)
{
	float curry = mPaddle->getPosition().y;
	
	if (mUpMove)
	{
		if (curry <= 0)
		{
			return;
		}
		mPaddle->move(0, -mVelocity);
	}

	if (mDownMove)
	{
		if (curry >= max - mPaddle->getSize().y)
		{
			return;
		}

		mPaddle->move(0, mVelocity);
	}
}

void Paddle::SetUpMove(bool status)
{
	mUpMove = status;
}

void Paddle::SetDownMove(bool status)
{
	mDownMove = status;
}

void Paddle::SetPosition(float x, float y)
{
    mPaddle->setPosition(x, y);
}

sf::RectangleShape Paddle::GetPaddle() const
{
	return *mPaddle;
}

float Paddle::GetWidth() const
{
    return mWidth;
}

float Paddle::GetHeight() const
{
    return mHeight;
}
