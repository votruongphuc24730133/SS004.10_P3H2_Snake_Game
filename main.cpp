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




        gotoxy(15,1);                                   
        cout<<"DIEM : "<<DoDai-3;                   //Hiển thị điểm số người chơi = độ dài hiện tại - độ dài ban đầu.

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
            Qua.x = rand() % (MAXX - MINX-4) + MINX+2;              //Vị trí random sẽ nằm trong khung. và cách khung ít nhất 1 dòng (cột). 
            Qua.y = rand() % (MAXY - MINY-4) + MINY+2;
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

bool RanDungTuong(const Point& dauRan) {
    return (dauRan.x <= MINX || dauRan.x >= MAXX || dauRan.y <= MINY || dauRan.y >= MAXY);
}
bool RanCanThan(const CONRAN& r) {
    for (int i = 1; i < r.DoDai; i++) {
        if (r.A[0].x == r.A[i].x && r.A[0].y == r.A[i].y) {
            return true; // Đầu rắn trùng vị trí với thân
        }
    }
    return false;
}
void welcome()
{
    gotoxy(5,2);
    cout<<"DO AN CUOI KY - MON KY NANG NGHE NGHIEP";
    gotoxy(15,4);
    cout<<"GAME SNAKE";
    gotoxy(11,8);
    cout<<"NHOM 5: Vo Truong Phuc";
    gotoxy(19,9);
    cout<<"Pham Tran Tien Phat";
    gotoxy(19,10);
    cout<<"Vo Xuan Huu";
    gotoxy(19,11);
    cout<<"Pham Van Hieu";
    gotoxy(19,12);
    cout<<"Pham Duc Hai";
    Sleep(5000);
    system("cls");

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
    welcome();
    VeKhung();               //đặt hàm vẽ khung ra ngoài vòng lặp While(1), chỉ vẽ khung 1 lần duy nhất.
    while (1) {
        if (kbhit()) {
            int HuongCu = Huong;
            t = getch();

            if (t == -32 || t == 224) { // Phím mũi tên
                t = getch(); // Lấy mã phím thực
                if (t == 75) Huong = 2; // Trái
                if (t == 72) Huong = 3; // Lên
                if (t == 77) Huong = 0; // Phải
                if (t == 80) Huong = 1; // Xuống
            } else { // Phím thường
                if (t == 'a') Huong = 2;
                if (t == 'w') Huong = 3;
                if (t == 'd') Huong = 0;
                if (t == 's') Huong = 1;
            }

            // Ngăn không cho quay ngược đầu
            if (abs(HuongCu - Huong) == 2)
                Huong = HuongCu;
        }

        for (int i = 0; i < r.DoDai; i++)           // xóa rắn bằng cách thay thế thành ký tự khoảng trắng " " 
        {
            gotoxy(r.A[i].x, r.A[i].y);
            cout << " "; 
        }
        
        r.DiChuyen(Huong, Qua);                       //đổi thử tự chạy hàm, cho hàm di chuyển chạy trước, vẽ chạy sau.
        r.Ve(Qua);                                 // nếu để hàm vẽ chạy trước, sau khi xóa thân rắn, hàm vẽ nó lại vẽ lại toàn bộ những thứ đã xóa (giá trị cũ) . rồi hàm di chuyển tịnh tiến toàn bộ, nên con rắn đi để lại cái đuôi kéo dài.  
        

        // Kiểm tra va chạm thân (chỉ kiểm tra khi rắn dài >= 4)
        if (r.DoDai >= 4 && RanCanThan(r)) {
            gotoxy(10, MAXY + 2);
            cout << "Game Over! Ran da can than.";
            break;
        }


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
