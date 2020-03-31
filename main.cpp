#include <ncurses.h>
#include <unistd.h>
#include <thread>
#include "ball.h"
#include <random>
#include <stdlib.h>
using namespace std;

random_device rd;
mt19937 mt(rd());

void newBall(int maxX,int maxY, bool &end,int x,int y, int speed,vector<pair<int,int>> &ballPosition,int index,vector<bool> &hits,vector<bool> &ready) {
    int collisionDelay = 0;
    Ball *ball = new Ball(maxX/2,maxY-2,maxX,maxY,x,y);
    while(!end) {
        ballPosition[index].first = ball->getY();
        ballPosition[index].second = ball->getX();
        for(int i=0;i<ballPosition.size();i++) {
            if(collisionDelay) break;
            if(i==index) continue;
            if(!ready[i]) continue;
            if(abs(ballPosition[i].first-ballPosition[index].first)<=1 && abs(ballPosition[i].second-ballPosition[index].second)<1) {
                for(int i=0;i<hits.size();i++) {
                    hits[i] = false;
                }
                hits[index] = true;
                hits[i]=true;
                ready[i] = false;
                ready[index] = false;
                collisionDelay = 3;
            }
        }
        if(hits[index]){
            for(int i=0;i<1000;i++) {
                usleep(1000);
                ball->display(false);
            }
            ready[index] = true;
            while(hits[index] && !end) {
                usleep(100);
                ball->display(false);
            }
        }
        ball->moveRandom();
        if(collisionDelay>0)collisionDelay--;
        usleep(speed);
    }
}

pair<int,int> rollDirection() {
    uniform_int_distribution<int> dist(-1,1);
    int y = dist(mt);
    int x;
    if(y == 0) {
        x = dist(mt);
        while (x==0) {
            x = dist(mt);
        }
    } else {
        x = dist(mt);
    }
    
    return make_pair(x,y);
}

int rollSpeed() {
    uniform_int_distribution<int> dist(20000,30000);
    return dist(mt);
}

void finish(bool &end) {
    int c;
    while(c!='e') {
        c = getch();
    }
    end = true;
}

int main (){

    const int nrOfBalls = 10;
    uniform_int_distribution<int> delay(500000,1500000);
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
    vector<pair<int,int>> ballPosition;
    vector<bool> hits;
    vector<bool> ready;
    

    threads.push_back(thread(finish,ref(end)));
    for(int i =0 ;i<nrOfBalls;i++) {
        usleep(delay(mt));
        if(end) break;
        hits.push_back(false);
        ready.push_back(true);
        ballPosition.push_back(make_pair(i+1,20));
        pair<int,int> direction = rollDirection();
        threads.push_back(thread(newBall,maxX,maxY,ref(end),direction.first,direction.second,rollSpeed(),ref(ballPosition),i,ref(hits),ref(ready)));
    }

    for(int i=0;i<threads.size();i++) {
        threads[i].join();
    }
    endwin();
    return 0;
}