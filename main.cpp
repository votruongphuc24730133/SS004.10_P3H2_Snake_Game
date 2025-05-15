#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <time.h>

#define MINX 2
#define MINY 2
#define MAXX 35
#define MAXY 20

using namespace std;

void gotoxy(int column, int line);

// Cấu trúc điểm tọa độ
struct Point {
    int x, y;
};

// Lớp con rắn
class CONRAN {
public:
    Point A[100];
    int DoDai;

    CONRAN() {
        DoDai = 3;
        A[0] = {10, 10};
        A[1] = {11, 10};
        A[2] = {12, 10};
    }

    void Ve(Point Qua) {
        // Vẽ đầu rắn
        gotoxy(A[0].x, A[0].y);
        cout << "O";  // Dùng ký tự O để làm đầu rắn
    
        // Vẽ thân rắn
        for (int i = 1; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            cout << "x";  // Ký tự cho thân rắn
        }
    
        // Vẽ quả
        gotoxy(Qua.x, Qua.y);
        cout << "*";
    
        // Ghi điểm ở góc
        gotoxy(1, 1);
        cout << "Diem: " << DoDai - 3;
    }

    void DiChuyen(int Huong, Point& Qua) {
        for (int i = DoDai - 1; i > 0; i--) {
            A[i] = A[i - 1];
        }

        switch (Huong) {
            case 0: A[0].x += 1; break; // Phải
            case 1: A[0].y += 1; break; // Xuống
            case 2: A[0].x -= 1; break; // Trái
            case 3: A[0].y -= 1; break; // Lên
        }

        // Ăn quả
        if (A[0].x == Qua.x && A[0].y == Qua.y) {
            DoDai++;
            Qua.x = rand() % (MAXX - MINX) + MINX;
            Qua.y = rand() % (MAXY - MINY) + MINY;
        }
    }
};

// Vẽ khung
void VeKhung() {
    for (int i = MINX; i <= MAXX; i++) {
        for (int j = MINY; j <= MAXY; j++) {
            if (i == MINX || i == MAXX || j == MINY || j == MAXY) {
                gotoxy(i, j);
                cout << "+";
            }
        }
    }
}
void Ve(Point Qua){
        gotoxy(A[0].x,A[0].y);
            cout<<"O";                         //vẽ đầu rắn trước
        for (int i = 1; i < DoDai; i++){
            gotoxy(A[i].x,A[i].y);
            cout<<"x";                          //vẽ thân rắn
        }
        gotoxy(Qua.x, Qua.y); cout<<"*";
        gotoxy( 1,1);
         cout<<"Diem : ";                            //di chuyển con trỏ về tọa độ (1;1) để ghi điểm 
    }

bool RanDungTuong(const Point& dauRan) {
    return (dauRan.x <= MINX || dauRan.x >= MAXX || dauRan.y <= MINY || dauRan.y >= MAXY);
}

// Hàm chính
int main() {
    CONRAN r;
    int Huong = 0;
    char t;
    Point Qua;

    srand((int)time(0));
    Qua.x = rand() % (MAXX - MINX) + MINX;
    Qua.y = rand() % (MAXY - MINY) + MINY;

    while (1) {
        if (kbhit()) {
            t = getch();
            if (t == -32 || t == 224) { // Phím mũi tên
                t = getch();
                if (t == 75 ) Huong = 2; // Trái
                if (t == 72) Huong = 3; // Lên
                if (t == 77) Huong = 0; // Phải
                if (t == 80) Huong = 1; // Xuống
            } else {
                // Phím thường
                if (t == 'a' || t == 'A') Huong = 2;
                if (t == 'w' || t == 'W') Huong = 3;
                if (t == 'd' || t == 'D') Huong = 0;
                if (t == 's' || t == 'S') Huong = 1;
            }
        }

        system("cls");
        r.Ve(Qua);
        r.DiChuyen(Huong, Qua);
        VeKhung();

        if (RanDungTuong(r.A[0])) {
            gotoxy(10, MAXY + 2);
            cout << "Game Over! Ran da dung tuong.";
            break;
        }
        
        Sleep(300);
    }

    return 0;
}

// Đặt vị trí con trỏ trong console
void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
