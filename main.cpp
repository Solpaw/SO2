#include <ncurses.h>
#include <unistd.h>
#include <thread>
#include "ball.h"
#include <random>
using namespace std;

void newBall(int maxX,int maxY, bool &end,int x,int y, int speed) {
    Ball *ball = new Ball(maxX/2,maxY/2,maxX,maxY,x,y);
    while(!end) {
        ball->moveRandom();
        usleep(speed);
    }
}

int rollDirection() {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(-1,1);
    return dist(mt);
}

int rollSpeed() {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(10000,30000);
    return dist(mt);
}


int main (){

    const int nrOfBalls = 15;

    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr,true);
    const int maxX = getmaxx(stdscr);
    const int maxY = getmaxy(stdscr);
    box(stdscr,0,0);
    refresh();
    bool end = false;

    vector<thread> threads;

    for(int i =0 ;i<nrOfBalls;i++) {
        threads.push_back(thread(newBall,maxX,maxY,ref(end),rollDirection(),rollDirection(),rollSpeed()));
    }

    int c;
    while(c!='e') {
        c = getch();
    }
    end = true;
    for(int i=0;i<threads.size();i++) {
        threads[i].join();
    }
    endwin();
    return 0;
}