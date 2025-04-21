// food.h
#pragma once
#include <iostream>
using namespace std;

struct Point {
    int x, y;
};

class Food {
public:
    Point moi;

    Food();
    void spawn();   
    void draw();    
};
