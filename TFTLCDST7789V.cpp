/* 
 * File:   TFTLCDST7789V.cpp
 * Author: LWJGL2
 * 
 * Created on 4 августа 2023 г., 20:21
 */

#include "TFTLCDST7789V.h"

TFTLCDST7789V::TFTLCDST7789V() {
}

TFTLCDST7789V::TFTLCDST7789V(const TFTLCDST7789V& orig) {
}

TFTLCDST7789V::~TFTLCDST7789V() {
}

void TFTLCDST7789V::sendCommand(uint8_t command) {
    RS_B; // Устанавливаем RS в 0 для команды
    CS_B; // Устанавливаем CS в 0 (включаем дисплей)

    // Устанавливаем биты данных на шине
    if ((command >> 0) & 0x01) {
        DB_0A;
    } else {
        DB_0B;
    }
    if ((command >> 1) & 0x01) {
        DB_1A;
    } else {
        DB_1B;
    }
    if ((command >> 2) & 0x01) {
        DB_2A;
    } else {
        DB_2B;
    }
    if ((command >> 3) & 0x01) {
        DB_3A;
    } else {
        DB_3B;
    }
    if ((command >> 4) & 0x01) {
        DB_4A;
    } else {
        DB_4B;
    }
    if ((command >> 5) & 0x01) {
        DB_5A;
    } else {
        DB_5B;
    }
    if ((command >> 6) & 0x01) {
        DB_6A;
    } else {
        DB_6B;
    }
    if ((command >> 7) & 0x01) {
        DB_7A;
    } else {
        DB_7B;
    }

    // Записываем команду на дисплей
    WR_B; // Сигнал WR в 0
    delayMicroseconds(10); // Минимальная задержка записи
    WR_A; // Сигнал WR в 1
    delayMicroseconds(10); // Минимальная задержка записи
    CS_A; // Выключаем дисплей
}

// Функция для отправки данных на дисплей

void TFTLCDST7789V::sendData(uint8_t data) {
    RS_A; // Устанавливаем RS в 1 для данных
    CS_B; // Устанавливаем CS в 0 (включаем дисплей)

    // Устанавливаем биты данных на шине
    if ((data >> 0) & 0x01) {
        DB_0A;
    } else {
        DB_0B;
    }
    if ((data >> 1) & 0x01) {
        DB_1A;
    } else {
        DB_1B;
    }
    if ((data >> 2) & 0x01) {
        DB_2A;
    } else {
        DB_2B;
    }
    if ((data >> 3) & 0x01) {
        DB_3A;
    } else {
        DB_3B;
    }
    if ((data >> 4) & 0x01) {
        DB_4A;
    } else {
        DB_4B;
    }
    if ((data >> 5) & 0x01) {
        DB_5A;
    } else {
        DB_5B;
    }
    if ((data >> 6) & 0x01) {
        DB_6A;
    } else {
        DB_6B;
    }
    if ((data >> 7) & 0x01) {
        DB_7A;
    } else {
        DB_7B;
    }
    // Записываем команду на дисплей
    WR_B; // Сигнал WR в 0
    WR_A; // Сигнал WR в 1
    CS_A; // Выключаем дисплей
}

void TFTLCDST7789V::resetLCD() {
    digitalWrite(pinRESET, HIGH);
    delayMicroseconds(100);
    digitalWrite(pinRESET, LOW);
    delayMicroseconds(100);
    digitalWrite(pinRESET, HIGH);
}

void TFTLCDST7789V::setOrientation(bool horizontal) {
    // Выбираем соответствующую ориентацию в зависимости от параметра
    uint8_t orientation;
    if (horizontal) {
        // Горизонтальная ориентация
        orientation = MADCTL_MX | MADCTL_RGB;
    } else {
        // Вертикальная ориентация
        orientation = MADCTL_MV | MADCTL_RGB;
    }
    // Отправляем команду MADCTL с выбранной ориентацией
    setMADCTL(orientation);
}

void TFTLCDST7789V::setAddress(uint16_t start, uint16_t end) {
    sendData(start >> 8);
    sendData(start & 0xFF);
    sendData(end >> 8);
    sendData(end & 0xFF);
}

void TFTLCDST7789V::setMADCTL(uint8_t data) {
    sendCommand(0x36); // MADCTL (Memory Access Control) команда
    sendData(data);
}

void TFTLCDST7789V::init() {
    // Устанавливаем все пины в качестве выходов
    pinMode(pinCS, OUTPUT);
    pinMode(pinRS, OUTPUT);
    pinMode(pinWR, OUTPUT);
    pinMode(pinRD, OUTPUT);
    pinMode(pinRESET, OUTPUT);

    pinMode(DB_RAW_0, OUTPUT);
    pinMode(DB_RAW_1, OUTPUT);
    pinMode(DB_RAW_2, OUTPUT);
    pinMode(DB_RAW_3, OUTPUT);
    pinMode(DB_RAW_4, OUTPUT);
    pinMode(DB_RAW_5, OUTPUT);
    pinMode(DB_RAW_6, OUTPUT);
    pinMode(DB_RAW_7, OUTPUT);

    digitalWrite(pinRESET, HIGH);
    resetLCD();
    sendCommand(0x01); // Сброс дисплея
    delay(10);
    sendCommand(0x11); // Выход из режима сна
    delay(10);
    sendCommand(0x29); // Включение дисплея
    setOrientation(false);

    CS_A;
    RS_A;
    WR_A;
    digitalWrite(pinRD, HIGH); // Устанавливаем RD в HIGH для окончания чтения
}

void TFTLCDST7789V::begin(int x, int y, int w, int h) {
    int endX = x + w - 1;
    int endY = y + h - 1;

    sendCommand(0x2A); // CASET (Column Address Set)    
    setAddress(x, endX);

    sendCommand(0x2B); // RASET (Row Address Set)  
    setAddress(y, endY);

    sendCommand(0x2C); // RAMWR (Memory Write) команда

    CS_B; // Включаем дисплей
}

void TFTLCDST7789V::end() {
    CS_A; // Выключаем дисплей
}

void TFTLCDST7789V::sendRGB(uint8_t r, uint8_t g, uint8_t b) {
    sendData(b);
    sendData(g);
    sendData(r);
}

void TFTLCDST7789V::setColor(uint8_t r, uint8_t g, uint8_t b) {
    this->currentR = r;
    this->currentG = g;
    this->currentB = b;
}

void TFTLCDST7789V::setLineWidth(uint8_t lineWidth) {
    this->lineWidth = lineWidth;
}

void TFTLCDST7789V::drawPixel(int x, int y) {
    begin(x, y, lineWidth, lineWidth);
    {
        if (lineWidth == 1) {
            sendRGB(currentR, currentG, currentB);
        } else {
            for (int i = 0; i < lineWidth * lineWidth; i++) {
                sendRGB(currentR, currentG, currentB);
            }
        }
    }
    end();
}

void TFTLCDST7789V::drawLine(int x1, int y1, int x2, int y2) {
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    drawPixel(x2, y2);
    while (x1 != x2 || y1 != y2) {
        drawPixel(x1, y1);
        int error2 = error * 2;
        if (error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
}

void TFTLCDST7789V::fillRect(int x, int y, int w, int h) {
    begin(x, y, w, h);
    {
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                sendRGB(currentR, currentG, currentB);
            }
        }
    }
    end();
}
