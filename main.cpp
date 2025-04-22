#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;

void gotoxy(int column, int line);

struct Point {
    int x, y;
};

// ===== Snake Class =====
class CONRAN {
public:
    Point A[100];  // Snake body
    int DoDai;

    CONRAN() {
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 12; A[2].y = 10;
    }

    void Ve() {
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            cout << "X";
        }
    }

    void DiChuyen(int Huong) {
        for (int i = DoDai - 1; i > 0; i--)
            A[i] = A[i - 1];

        if (Huong == 0) A[0].x = A[0].x + 1;     // Right
        if (Huong == 1) A[0].y = A[0].y + 1;     // Down
        if (Huong == 2) A[0].x = A[0].x - 1;     // Left
        if (Huong == 3) A[0].y = A[0].y - 1;     // Up
    }

    bool AnMoi(Point moi) {
        return A[0].x == moi.x && A[0].y == moi.y;
    }
};

// ===== Ăn mồi =====
Point TaoMoi() {
    Point moi;
    moi.x = rand() % 70 + 1;
    moi.y = rand() % 20 + 1;
    return moi;
}

void VeMoi(Point moi) {
    gotoxy(moi.x, moi.y);
    cout << "O";
}


int main() {
    CONRAN r;
    Point moi = TaoMoi();  // Sinh mồi đầu tiên

    int Huong = 0;
    char t;

    while (1) {
        if (kbhit()) {
            t = getch();
            if (t == 'a') Huong = 2;
            if (t == 'w') Huong = 3;
            if (t == 'd') Huong = 0;
            if (t == 'x') Huong = 1;
        }

        system("cls");

        VeMoi(moi);  
        r.Ve();       

        //logic ăn mồi
        if (r.AnMoi(moi)) {
            r.DoDai++;       
            moi = TaoMoi();  
        }

        r.DiChuyen(Huong);
        Sleep(300);
    }

    return 0;
}

// ===== gotoxy() =====
void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}
