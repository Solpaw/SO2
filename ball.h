#ifndef _BALL_H_
#define _BALL_H_
#include <mutex>
using namespace std;

mutex mu;

class Ball {
    int x, y, maxX, maxY, directionX, directionY;
    char sign;
    
    void collision();
    void display();
public:
    void moveRandom();
    Ball(int xx,int yy,int maxXx,int maxYy,int dX,int dY);
};

Ball::Ball(int xx,int yy,int maxXx,int maxYy,int dX,int dY) {
    x = xx;
    y = yy;
    maxX = maxXx;
    maxY = maxYy;
    sign = 'O';
    directionX = dX;
    directionY = dY;
}

void Ball::collision() {
    if(y+directionY==0||y+directionY==maxY-1) {
        directionY = -directionY;
    }
    if(x+directionX==0||x+directionX==maxX-1) {
        directionX = -directionX;
    }
}

void Ball::moveRandom() {
    collision();
    display();
}

void Ball::display() {
    lock_guard<mutex> guard(mu);
    mvaddch(y,x,' ');
    x+=directionX;
    y+=directionY;
    mvaddch(y,x,sign);
    refresh();
}

#endif