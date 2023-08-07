#include <Arduino.h>
#include "TFTLCDST7789V.h"

TFTLCDST7789V* lcd = new TFTLCDST7789V();

// Функция для рисования 3D куба
const int screenWidth = HEIGHT;
const int screenHeight = WIDTH;

// Функция для рисования 3D куба
void draw3DCube(float angleX, float angleY, float angleZ) {
    // Вершины куба
    int vertices[8][3] = {
        {-50, -50, -50},
        {50, -50, -50},
        {50, 50, -50},
        {-50, 50, -50},
        {-50, -50, 50},
        {50, -50, 50},
        {50, 50, 50},
        {-50, 50, 50}
    };

    //     Угол поворота куба на 45 градусов по оси X
    //    float angleX = 45.0 * PI / 180.0;
    //    float angleY = 45.0 * PI / 180.0;
    //    float angleZ = 45.0 * PI / 180.0;


    // Матрицы поворота вокруг осей X, Y и Z
    float cosX = cos(angleX);
    float sinX = sin(angleX);
    float cosY = cos(angleY);
    float sinY = sin(angleY);
    float cosZ = cos(angleZ);
    float sinZ = sin(angleZ);
    for (int i = 0; i < 8; i++) {
        int x = vertices[i][0];
        int y = vertices[i][1];
        int z = vertices[i][2];

        // Поворот вокруг оси X
        int newY = y * cosX - z * sinX;
        int newZ = y * sinX + z * cosX;
        y = newY;
        z = newZ;

        // Поворот вокруг оси Y
        int newX = x * cosY + z * sinY;
        newZ = -x * sinY + z * cosY;
        x = newX;
        z = newZ;

        // Поворот вокруг оси Z
        newX = x * cosZ - y * sinZ;
        newY = x * sinZ + y * cosZ;
        x = newX;
        y = newY;

        vertices[i][0] = x;
        vertices[i][1] = y;
        vertices[i][2] = z;
    }


    // Рисуем ребра куба
    lcd->drawLine(vertices[0][0] + screenWidth / 2, vertices[0][1] + screenHeight / 2, vertices[1][0] + screenWidth / 2, vertices[1][1] + screenHeight / 2);
    lcd->drawLine(vertices[1][0] + screenWidth / 2, vertices[1][1] + screenHeight / 2, vertices[2][0] + screenWidth / 2, vertices[2][1] + screenHeight / 2);
    lcd->drawLine(vertices[2][0] + screenWidth / 2, vertices[2][1] + screenHeight / 2, vertices[3][0] + screenWidth / 2, vertices[3][1] + screenHeight / 2);
    lcd->drawLine(vertices[3][0] + screenWidth / 2, vertices[3][1] + screenHeight / 2, vertices[0][0] + screenWidth / 2, vertices[0][1] + screenHeight / 2);

    lcd->drawLine(vertices[4][0] + screenWidth / 2, vertices[4][1] + screenHeight / 2, vertices[5][0] + screenWidth / 2, vertices[5][1] + screenHeight / 2);
    lcd->drawLine(vertices[5][0] + screenWidth / 2, vertices[5][1] + screenHeight / 2, vertices[6][0] + screenWidth / 2, vertices[6][1] + screenHeight / 2);
    lcd->drawLine(vertices[6][0] + screenWidth / 2, vertices[6][1] + screenHeight / 2, vertices[7][0] + screenWidth / 2, vertices[7][1] + screenHeight / 2);
    lcd->drawLine(vertices[7][0] + screenWidth / 2, vertices[7][1] + screenHeight / 2, vertices[4][0] + screenWidth / 2, vertices[4][1] + screenHeight / 2);

    lcd->drawLine(vertices[0][0] + screenWidth / 2, vertices[0][1] + screenHeight / 2, vertices[4][0] + screenWidth / 2, vertices[4][1] + screenHeight / 2);
    lcd->drawLine(vertices[1][0] + screenWidth / 2, vertices[1][1] + screenHeight / 2, vertices[5][0] + screenWidth / 2, vertices[5][1] + screenHeight / 2);
    lcd->drawLine(vertices[2][0] + screenWidth / 2, vertices[2][1] + screenHeight / 2, vertices[6][0] + screenWidth / 2, vertices[6][1] + screenHeight / 2);
    lcd->drawLine(vertices[3][0] + screenWidth / 2, vertices[3][1] + screenHeight / 2, vertices[7][0] + screenWidth / 2, vertices[7][1] + screenHeight / 2);
}

void setup() {
    Serial.begin(115200);
    Serial.println("TFTLCDST7789V");
    lcd->init();
    lcd->setLineWidth(2);
    lcd->setColor(255, 0, 0);
    //    lcd->fillRect(0, 0, HEIGHT, WIDTH);

    // Углы поворота куба
    float angleX = 0.0;
    float angleY = 0.0;
    float angleZ = 0.0;

    while (true) {
        lcd->clearRectBlack(0, 0, HEIGHT, WIDTH);

        // Рисуем 3D куб и вращаем его вокруг осей X, Y и Z
        draw3DCube(angleX, angleY, angleZ);
        // Отображаем кадр на экране или дисплее
        // Здесь должна быть логика отображения кадра на экране или дисплее

        angleX += 0.07;
        angleY += 0.07;
        angleZ += 0.07;
    }
}
