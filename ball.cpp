#include "ball.h"
#include <ncurses.h>
#include <mutex>
using namespace std;

mutex mu;

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
    display(true);
}

void Ball::display(bool move) {
    lock_guard<mutex> guard(mu);
    mvaddch(y,x,' ');
    if(move) {
        x+=directionX;
        y+=directionY;
    }
    mvaddch(y,x,sign);
    refresh();
}

int Ball::getX() {
    return x;
}

int Ball::getY() {
    return y;
}
