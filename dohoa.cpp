#include <iostream>
#include <string>
#include "mylib.h"
#include <conio.h>

#define ngang 196
#define doc 179
#define traitren 218
#define phaitren 191
#define traiduoi 192
#define phaiduoi 217
#define MAX 100
using namespace std;
int x = 50; int y = 5;

//===============
void box(int x, int y, int w, int h, int t_color, int b_color, string nd);
void n_box(int x, int y, int w, int h, int t_color, int b_color, string nd[], int sl);
void menu();
void thanh_sang(int x, int y, int w, int h, int b_color, string nd);
void main()
{
    menu();
    _getch();
}

void menu() {
    ShowCur(0);
    int w = 30;
    int h = 2;
    int t_color = 11;
    int b_color = 0;
    int b_color_sang = 70;
    string nd[] = { "Quan ly lop tin chi", "Quan ly sinh vien", "Quan ly mon hoc", "Quan ly dang ky", "Quan ly diem" };
    int sl = 5;
    n_box(x, y, w, h, t_color, b_color, nd, sl);

    int xp = x; int yp = y;
    int x_cu = xp; int y_cu = yp;
    bool kt = true;
    while (true) {
        if (kt == true) {
            gotoxy(x_cu, y_cu);
            thanh_sang(x_cu, y_cu, w, h, b_color, nd[(y_cu - y) / 2]);
            x_cu = xp; y_cu = yp;
            thanh_sang(xp, yp, w, h, b_color_sang, nd[(yp - y) / 2]);
            kt = false;
        }

        if (_kbhit()) {
            char c = _getch();
            if (c == -32) {
                kt = true;
                c = _getch();
                if (c == 72) {  // Phím mũi tên lên
                    if (yp != y) yp -= 2;
                    else yp = y + h * (sl - 1);
                }
                else if (c == 80) {  // Phím mũi tên xuống
                    if (yp != y + h * (sl - 1))
                        yp += 2;
                    else yp = y;
                }
            }
        }
    }
}

void thanh_sang(int x, int y, int w, int h, int b_color, string nd) {
    SetBGColor(b_color);
    for (int iy = y + 1; iy <= y + h - 1; iy++) {
        for (int ix = x + 1; ix <= x + w - 1; ix++) {
            gotoxy(ix, iy); cout << " ";
        }
    }
    SetColor(5);
    gotoxy(x + 1, y + 1);
    cout << nd;
}

void box(int x, int y, int w, int h, int t_color, int b_color, string nd) {
    SetBGColor(b_color);
    for (int iy = y + 1; iy <= y + h - 1; iy++) {
        for (int ix = x + 1; ix <= x + w - 1; ix++) {
            gotoxy(ix, iy); cout << " ";
        }
    }
    SetColor(5);
    gotoxy(x + 1, y + 1);
    cout << nd;
    SetBGColor(0);
    SetColor(t_color);
    if (h <= 1 || w <= 1) return;
    for (int ix = x; ix <= x + w; ix++) {
        gotoxy(ix, y); cout << char(ngang);
        gotoxy(ix, y + h); cout << char(ngang);
    }
    for (int iy = y; iy <= y + h; iy++) {
        gotoxy(x, iy); cout << char(179);
        gotoxy(x + w, iy); cout << char(179);
    }
    gotoxy(x, y); cout << char(218);
    gotoxy(x + w, y); cout << char(191);
    gotoxy(x, y + h); cout << char(192);
    gotoxy(x + w, y + h); cout << char(217);
}

void n_box(int x, int y, int w, int h, int t_color, int b_color, string nd[], int sl) {
    for (int i = 0; i < sl; i++) {
        box(x, y + (i * 2), w, h, t_color, b_color, nd[i]);
        if (i != 0) {
            gotoxy(x, y + (i * 2)); cout << char(195);
            gotoxy(x + w, y + (i * 2)); cout << char(180);
        }
    }
}
