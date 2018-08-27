/*
 Contains the definition of a Paddle in a Pong game
 */

#pragma once
#include <SFML/Graphics.hpp>

class Paddle
{
public:

	Paddle(float width = 0 , float height = 0, float xcoord = 0, float ycoord = 0);
	~Paddle();

	void Move(int max);
	void SetUpMove(bool status);
	void SetDownMove(bool status);
    void SetPosition(float x, float y);
	sf::RectangleShape GetPaddle() const;
    float GetWidth() const;
    float GetHeight() const;
	const static int INITIAL_VELOCITY = 5;

private:
	sf::RectangleShape* mPaddle;
	bool mUpMove;
	bool mDownMove;
    float mWidth;
    float mHeight;
	int mVelocity;

};
