
#include <iostream>
#include "PongGame.h"

sf::Mutex mutex;

void GenerateHostPacket(float * buf, const sf::Vector2f padCord,  const sf::Vector2f ballCoord)
{
    buf[0] = padCord.x;
    buf[1] = padCord.y;
    buf[2] = ballCoord.x;
    buf[3] = ballCoord.y;
}

void GenerateClientPacket(float * buf, const sf::Vector2f padCord)
{
    buf[0] = padCord.x;
    buf[1] = padCord.y;
}

struct args{
    PongNetworking* network;
    float* buf;
    size_t length;
};

void RecvFunc(args& arg)
{
    sf::SocketSelector selector;
    selector.add(arg.network->GetUDPSock());
    while(true)
    {
        if(selector.wait(sf::seconds(0)))
        {
            mutex.lock();
            arg.network->RecieveData(arg.buf, arg.length);
            //std::cout << arg.buf[0] << " " << arg.buf[1] << std::endl;
            mutex.unlock();
        }

    }
}

PongGame::PongGame(sf::RenderWindow& window)
: window(window)
{
    
    int screen_width = 1024, screen_height = 768;
    int pad_width = screen_width/30, pad_height = screen_height /4;
    paddle1 = new Paddle(pad_width, pad_height);
    paddle2 = new Paddle(pad_width, pad_height, screen_width - pad_width);
    ball = new Ball(screen_width, screen_width/2, screen_height/2);
    
    Ball::InitSound();
    mGameOver = false;
    
}

PongGame::~PongGame()
{
    delete paddle1;
    delete paddle2;
    delete ball;
    Ball::DeleteSound();
}

void PongGame::Run()
{
    
    while (!mGameOver)
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    mGameOver = true;
                    break;
                case sf::Event::KeyPressed:
                    SetPaddleMovement(event.key, true);
                    break;
                case sf::Event::KeyReleased:
                    
                    SetPaddleMovement(event.key, false);
                    break;
                default:
                    break;
                    
            }
        }
        
        
        paddle1->Move(window.getSize().y);
        paddle2->Move(window.getSize().y);
        ball->Move();
        HandleCollision(window.getSize().x, window.getSize().y, paddle1, paddle2, ball);
        
        
        
        Update();
        
        if(mPlayerOneScore == mWinCondition || mPlayerTwoScore == mWinCondition)
        {
            mGameOver = true;
        }
    }
    
    
}

void PongGame::RunHost(PongNetworking& network)
{
    float recvBuff[4], sendBuff[4];
    
    
    args arg;
    arg.network = &network;
    arg.buf = recvBuff;
    arg.length = 4 * sizeof(float);
    sf::Thread thread(&RecvFunc, arg);
    thread.launch();
    while (!mGameOver)
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    mGameOver = true;
                    break;
                case sf::Event::KeyPressed:
                    SetPaddleMovement(event.key, true);
                    break;
                case sf::Event::KeyReleased:
                    
                    SetPaddleMovement(event.key, false);
                    break;
                default:
                    break;
                    
            }
        }
        
        paddle1->Move(window.getSize().y);
        
        ball->Move();
        mutex.lock();
        paddle2->SetPosition(recvBuff[0], recvBuff[1]);
        GenerateHostPacket(sendBuff, paddle1->GetPaddle().getPosition(), ball->GetBall().getPosition());
        network.SendData(sendBuff, 4*sizeof(float));
        mutex.unlock();
        HandleCollision(window.getSize().x, window.getSize().y, paddle1, paddle2, ball);
        
        Update();
        
        if(mPlayerOneScore == mWinCondition || mPlayerTwoScore == mWinCondition)
        {
            mGameOver = true;
        }
    }
    
    thread.terminate();
}





void PongGame::RunClient(PongNetworking& network)
{
    float recvBuff[4] = {0,0,50,50}, sendBuff[4];
    
    args arg;
    arg.network = &network;
    arg.buf = recvBuff;
    arg.length = 4* sizeof(float);
    sf::Thread thread(&RecvFunc, arg);
    thread.launch();
    ball->SetMove(0,0);
    while (!mGameOver)
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    mGameOver = true;
                    break;
                case sf::Event::KeyPressed:
                    SetPaddleMovement(event.key, true);
                    break;
                case sf::Event::KeyReleased:
                    
                    SetPaddleMovement(event.key, false);
                    break;
                default:
                    break;
                    
            }
        }
        
        paddle2->Move(window.getSize().y);

        mutex.lock();
        paddle1->SetPosition(recvBuff[0], recvBuff[1]);
        ball->SetPosition(recvBuff[2], recvBuff[3]);

        GenerateClientPacket(sendBuff, paddle2->GetPaddle().getPosition());
        network.SendData(sendBuff, 2*sizeof(float));
        mutex.unlock();
        HandleCollision(window.getSize().x, window.getSize().y, paddle1, paddle2, ball);
        Update();
        
        if(mPlayerOneScore == mWinCondition || mPlayerTwoScore == mWinCondition)
        {
            mGameOver = true;
        }
    }
    thread.terminate();
}
    
    
void PongGame::Update()
{
    window.clear();
    window.draw((*paddle1).GetPaddle());
    window.draw((*paddle2).GetPaddle());
    window.draw((*ball).GetBall());
    window.display();
}


void PongGame::SetPaddleMovement( sf::Event::KeyEvent key , bool status)
{
    if (key.code == sf::Keyboard::W)
    {
        paddle1->SetUpMove(status);
    }
    if (key.code == sf::Keyboard::S)
    {
        paddle1->SetDownMove(status);
    }
    
    if (key.code == sf::Keyboard::Up)
    {
        paddle2->SetUpMove(status);
    }
    
    if (key.code == sf::Keyboard::Down)
    {
        paddle2->SetDownMove(status);
    }
}



void PongGame::HandleCollision(int width, int height, const Paddle* paddle1, const Paddle* paddle2, Ball* pBall)
{
    
    const sf::FloatRect ballBound = pBall->GetBall().getGlobalBounds();
    const sf::Vector2f ballPos = pBall->GetBall().getPosition();
    if(ballBound.intersects(paddle1->GetPaddle().getGlobalBounds())
       || ballBound.intersects(paddle2->GetPaddle().getGlobalBounds()))
    {
        pBall->ReverseHorizontal();
        Ball::PlaySound();
    }
    
    if (ballPos.y <= 0 || ballPos.y >= height - pBall->GetBall().getSize().y)
    {
        pBall->ReverseVertical();
        Ball::PlaySound();
    }
    
    if (ballPos.x <= 0 )
    {
        pBall->SetPosition(width/2, height/2);
        pBall->ReverseHorizontal();
        mPlayerTwoScore++;
        
    }
    
    if(ballPos.x >= width - pBall->GetBall().getSize().x)
    {
        pBall->SetPosition(width/2, height/2);
        pBall->ReverseHorizontal();
        mPlayerOneScore++;
    }
    
    
}
