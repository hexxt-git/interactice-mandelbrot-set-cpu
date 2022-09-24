#include "raylib.h"
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main(void) {
    const int width = 400;
    const int height = 300;
    const float maxN = 100; // max itterations ditermines the quality of the image when you zoom far in
    const float scroll = 0.3;

    InitWindow(width, height, "mandel");

    float cameraX = 0;
    float cameraY = 0;
    float cameraZ = 0.02;
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
            cameraZ *= 1 + scroll;
        }

        //cameraZ *= .9;

        ClearBackground(WHITE);

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                //float initial_real = (float) x / width * 2 - 1;
                //float initial_imaginary = (float) y / height * 2 - 1;
                float initial_real = (float)(x - width / 2.0) * cameraZ + cameraX;
                float initial_imaginary = (float)(y - height / 2.0) * cameraZ + cameraY;

                float current_real = initial_real;
                float current_imaginary = initial_imaginary;

                int n = 0;
                int final = 0;
                while (n < maxN) {
                    n++;

                    float next_real = powf(current_real, 2) - powf(current_imaginary, 2);
                    float next_imaginary = 2 * current_real * current_imaginary;

                    current_real = next_real + initial_real;
                    current_imaginary = next_imaginary + initial_imaginary;

                    final = abs(current_real + current_imaginary);

                    if (final > 100) {
                        break;
                    }
                }


                /*
                float h = fmod(powf((n / maxN) * 360, 1.5f), 360);
                float s = 80;
                float v = (n / maxN) * 100;

                Color c = ColorFromHSV(h, s, v);
                DrawPixel(x, y, c);
                */
                //cout << (int)(n/maxN*200) << endl;
                //Color c = { (int)(n / maxN * 200 * 30), (int)(n / maxN * 30 * 30), (int)(n / maxN * 80 * 30), 255};

                Color c = { (int)(n / maxN * 190), (int)(n / maxN * 70) % 190, (int)(n / maxN * 100) % 190, 255 };

                DrawPixel(x, y, c);
                if (n == maxN) {
                    DrawPixel(x, y, BLACK);
                }
            }
        }
        /*
            DrawPixel(int(width / 2), int(height / 2), WHITE);
            DrawPixel(int(width / 2) + 2, int(height / 2), WHITE);
            DrawPixel(int(width / 2) - 2, int(height / 2), WHITE);
            DrawPixel(int(width / 2), int(height / 2)+1, WHITE);
            DrawPixel(int(width / 2), int(height / 2)-1, WHITE);
        */

        EndDrawing();
    }
    CloseWindow();
    return 0;
}