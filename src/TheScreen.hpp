#ifndef THE_SCREEN_hpp
#define THE_SCREEN_hpp

#define PIXEL_COLOR_DEPTH_BITS 8
#define MATRIX_WIDTH 64
#define MATRIX_HEIGHT 32 // Panel height of 64 will required PIN_E to be defined.
#define CHAIN_LENGTH 4   // Number of chained panels, if just a single panel, obviously set to 1
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

#define PANEL_SIZE_WIDTH MATRIX_WIDTH *CHAIN_LENGTH
#define PANEL_SIZE_HEIGHT MATRIX_HEIGHT

///////////////////////////////////////////////// Définition des pins pour connecter la matrice
#define R1_PIN 19
#define G1_PIN 13
#define B1_PIN 18
#define R2_PIN 5
#define G2_PIN 12
#define B2_PIN 17

#define A_PIN 16
#define B_PIN 14
#define C_PIN 4
#define D_PIN 27
#define E_PIN -1

#define LAT_PIN 26
#define OE_PIN 15
#define CLK_PIN 2

class TheScreen
{
public:
    TheScreen();
    void setup();
    void loop();

    uint16_t colorRGB(uint16_t r, uint16_t g, uint16_t b);
    // uint16_t colorWheel(uint16_t WheelPos);
    uint16_t colorWheel(uint8_t WheelPos);
    uint16_t rgb888ToRgb565(uint8_t r, uint8_t g, uint8_t b);
    void clear();
    void clear(uint16_t fillColor);
    void drawPixel(uint16_t x, uint16_t y, uint16_t color);
    void printText(const char *text, uint8_t size, int posX, bool centered, uint16_t color, uint8_t lumin);
    void printText(const char *text, uint8_t size, int posX, bool centered, uint16_t textColor, uint16_t backgroundColor, uint8_t lumin);
    void fadingText(const char *text, uint8_t size, bool isRGB, uint16_t color, uint16_t fillColor, uint8_t lumin, int delais, int fadeInTime, int fadeOutTime);
    void externalRainbowRectangle(uint16_t decal = 0, uint8_t border = 4);
    void drawFillRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
    void drawFillRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t red, uint8_t green, uint8_t blue);

private:
    MatrixPanel_I2S_DMA *dma_display;
    uint16_t getTextWidth(const char *text);
};

#endif