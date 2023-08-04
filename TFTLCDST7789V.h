/* 
 * File:   TFTLCDST7789V.h
 * Author: LWJGL2
 *
 * Created on 4 августа 2023 г., 20:21
 */
#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef TFTLCDST7789V_H
#define TFTLCDST7789V_H

// Пин для сигнала CS
#define pinCS 10  
// Пин для сигнала RS
#define pinRS 9  
// Пин для сигнала WR
#define pinWR 8  
// Пин для сигнала RD
#define pinRD 7  
// Пин для сигнала /RSTB
#define pinRESET A0 

#define CS_A PORTB |= B00000100
#define RS_A PORTB |= B00000010
#define WR_A PORTB |= B00000001

#define CS_B PORTB &= B11111011
#define RS_B PORTB &= B11111101
#define WR_B PORTB &= B11111110

/*
============ DATA BUS ============ 
 */
// enable
#define DB_0A PORTB |= B00100000 // pin 13
#define DB_1A PORTB |= B00010000 // pin 12
#define DB_2A PORTB |= B00001000 // pin 11
#define DB_3A PORTD |= B01000000 // pin 6
#define DB_4A PORTD |= B00100000 // pin 5

#define DB_5A PORTD |= B00010000 // pin 4
#define DB_6A PORTD |= B00001000 // pin 3
#define DB_7A PORTD |= B00000100 // pin 2

// disable
#define DB_0B PORTB &= B11011111 // pin 13
#define DB_1B PORTB &= B11101111 // pin 12
#define DB_2B PORTB &= B11110111 // pin 11
#define DB_3B PORTD &= B10111111 // pin 6
#define DB_4B PORTD &= B11011111 // pin 5

#define DB_5B PORTD &= B11101111 // pin 4
#define DB_6B PORTD &= B11110111 // pin 3
#define DB_7B PORTD &= B11111011 // pin 2

#define DB_RAW_0 13
#define DB_RAW_1 12
#define DB_RAW_2 11
#define DB_RAW_3 6
#define DB_RAW_4 5
#define DB_RAW_5 4
#define DB_RAW_6 3
#define DB_RAW_7 2

// Определяем биты для горизонтальной и вертикальной ориентации
#define MADCTL_MY 0x80 /* Ориентация по вертикали (mirror Y axis) */
#define MADCTL_MX 0x40 /* Ориентация по горизонтали (mirror X axis) */

// Определяем биты для переключения лево-право и верх-низ
#define MADCTL_MV 0x20 /* Верх-низ (swap X-Y axes) */

// Определяем биты для управления порядком цветовых компонентов
#define MADCTL_RGB 0x00 /* RGB порядок */
#define MADCTL_BGR 0x08 /* BGR порядок */

/* 240 */
#define WIDTH 240
/* 320 */
#define HEIGHT 320

/* WIDTH / 2 */
#define HALF_WIDTH 120
/* HEIGHT / 2 */
#define HALF_HEIGHT 160

class TFTLCDST7789V {
private:
    uint8_t currentR = 0xFF, currentG = 0xFF, currentB = 0xFF, lineWidth = 1;
public:
    TFTLCDST7789V();
    TFTLCDST7789V(const TFTLCDST7789V& orig);
    virtual ~TFTLCDST7789V();
    void init();
    void resetLCD();

    void sendCommand(uint8_t command);
    void sendData(uint8_t data);

    void setOrientation(bool horizontal);
    void setMADCTL(uint8_t data);

    void setAddress(uint16_t start, uint16_t end);
    void begin(int x, int y, int w, int h);
    void end();
    void sendRGB(uint8_t r, uint8_t g, uint8_t b);


    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setLineWidth(uint8_t lineWidth);
    
    void drawPixel(int x, int y);
    void drawLine(int x1, int y1, int x2, int y2);

    void fillRect(int x, int y, int w, int h);
};

#endif /* TFTLCDST7789V_H */

