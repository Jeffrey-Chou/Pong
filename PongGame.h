

#pragma once

#include "Paddle.h"
#include "Ball.h"
#include "PongNetworking.h"

class PongGame
{
public:
    
    PongGame(sf::RenderWindow&);
    ~PongGame();
    void Run();
    void RunHost(PongNetworking& network);
    void RunClient(PongNetworking& network);
    
    
    void Update();
    void SetPaddleMovement(sf::Event::KeyEvent key , bool status);
    void HandleCollision(int width, int height, const Paddle* paddle1, const Paddle* paddle2, Ball* pBall);
    
    //void RecvFunc(PongNetworking&, float*, size_t length );
    
private:
    int mPlayerOneScore = 0;
    int mPlayerTwoScore = 0;
    
    int mWinCondition = 1;
    sf::RenderWindow& window;
    bool mGameOver;
    Paddle* paddle1;
    Paddle* paddle2;
    Ball* ball;
};

