#include "raylib.h"
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

long double* complexMulitplication(double real1, double img1, double real2, double img2) {
    long double  newReal = (real1 * real2 - img1 * img2);
    long double  newImg = (real1 * img2 + real2 * img1);

    long double  arr[2] = { newReal, newImg };
    return arr;
}

int main(void) {
    const int width = 250;
    const int height = 250;
    const double maxN = 5000; // max itterations ditermines the quality of the image when you zoom far in
    const double scroll = 0.3;

    InitWindow(width, height, "mandel");

    long double cameraX = 0;
    long double cameraY = 0;
    long double cameraZ = 0.02;
    int shift = 0;

    while (!WindowShouldClose()) {
        shift += 1;
        BeginDrawing();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            cameraX -= GetMouseDelta().x * cameraZ;
            cameraY -= GetMouseDelta().y * cameraZ;
        }
        if (GetMouseWheelMove() == 1) {
            cameraZ *= 1 - scroll;
        }
        if (GetMouseWheelMove() == -1) {
            cameraZ *= 1 + scroll * 2;
        }

        //cameraZ *= .9;

        ClearBackground(WHITE);

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                //float initial_real = (float) x / width * 2 - 1;
                //float initial_imaginary = (float) y / height * 2 - 1;
                long double initial_real = (long double)(x - width / 2.0) * cameraZ + cameraX;
                long double initial_imaginary = (long double)(y - height / 2.0) * cameraZ + cameraY;

                long double current_real = initial_real;
                long double current_imaginary = initial_imaginary;

                long int n = 0;
                long int final = 0;
                while (n < maxN) {
                    n++;

                    long double* next = complexMulitplication(current_real, current_imaginary, current_real, current_imaginary);
                    long double  next_real = next[0] + initial_real;
                    long double  next_imaginary = next[1] + initial_imaginary;

                    current_real = next_real;
                    current_imaginary = next_imaginary;

                    final = abs(current_real + current_imaginary);

                    if (final > 10) {
                        break;
                    }

                }

                //double h = (n / maxN) * .9;
                //double s = .6;
                //double v = (n / maxN) * .5;

                //Color c = ColorFromHSV(h, s, v);
                
                //Color c = { (int)(n / maxN * 200 * 20), (int)(n / maxN * 30 * 20), (int)(n / maxN * 80 * 20), 255};

                //Color c = { (int)(n / maxN * 220), (int)(n / maxN * 180), (int)(n / maxN * 100), 255 };

                long double l = powf(n , 0.7);
                Color c = { (int)(l*3.5)%200, (int)(l*2.4)%200, (int)(l*1.5)%200, 255 };



                DrawPixel(x, y, c);
                if (n == maxN) {
                    DrawPixel(x, y, BLACK);
                }
            }
        }
            DrawPixel(int(width / 2), int(height / 2), WHITE);
            DrawPixel(int(width / 2) + 2, int(height / 2), WHITE);
            DrawPixel(int(width / 2) - 2, int(height / 2), WHITE);
            DrawPixel(int(width / 2), int(height / 2)+1, WHITE);
            DrawPixel(int(width / 2), int(height / 2)-1, WHITE);


        EndDrawing();
    }
    CloseWindow();
    return 0;
}