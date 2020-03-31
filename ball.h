#ifndef _BALL_H_
#define _BALL_H_

class Ball {
    int x, y, maxX, maxY, directionX, directionY;
    char sign;
    
    void collision();
    
public:
    void moveRandom();
    Ball(int xx,int yy,int maxXx,int maxYy,int dX,int dY);
    int getX();
    int getY();
    void display(bool move);
};

#endif