// food.cpp
// Resubmitted after revert
#include "food.h"
#include <cstdlib>   
#include <windows.h> 
#include <iostream>
using namespace std;

void gotoxy(int column, int line); // Đã declare trong main.cpp


Food::Food() {
    spawn();
}

void Food::spawn() {
    moi.x = rand() % 70 + 1; 
    moi.y = rand() % 20 + 1;
}

void Food::draw() {
    gotoxy(moi.x, moi.y);
    cout << "O";
}


