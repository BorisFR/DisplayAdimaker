#include "TheScreen.hpp"

TheScreen::TheScreen() {}

void TheScreen::setup()
{
    // Custom pin mapping for all pins
    // HUB75_I2S_CFG::i2s_pins _pins = {RL1, GL1, BL1, RL2, GL2, BL2, CH_A, CH_B, CH_C, CH_D, CH_E, LAT, OE, CLK};
    HUB75_I2S_CFG::i2s_pins _pins = {R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN};
    HUB75_I2S_CFG mxconfig(
        MATRIX_WIDTH,  // width
        MATRIX_HEIGHT, // height
        CHAIN_LENGTH,  // chain length
        _pins          // pin mapping
    );

    mxconfig.i2sspeed = HUB75_I2S_CFG::HZ_10M; // I2S clock speed, better leave as-is unless you want to experiment.
                                               // mxconfig.i2sspeed = HUB75_I2S_CFG::HZ_20M;
    // mxconfig.clkphase = false;
    // mxconfig.double_buff = true;
    dma_display = new MatrixPanel_I2S_DMA(mxconfig);
    dma_display->begin();
    dma_display->setBrightness8(DEFAULT_BRIGHT); // 0-255
    dma_display->setTextWrap(false);
    dma_display->clearScreen();

    fadingText("DisplayLED", 2, false, colorRGB(240, 107, 66), colorRGB(63, 42, 86), DEFAULT_BRIGHT, 3500, 2500, 250);
}

void TheScreen::loop()
{
    // dma_display->flipDMABuffer();
}

/// fct pour effacer l'ecran dans le code principal
void TheScreen::clear()
{
    dma_display->clearScreen();
}

void TheScreen::clear(uint16_t fillColor)
{
    dma_display->fillScreen(fillColor);
}

/// fct pour formater la couleur (à pour seul but de prendre peu de place)
uint16_t TheScreen::colorRGB(uint16_t r, uint16_t g, uint16_t b)
{
    return dma_display->color565(r, g, b);
}

void TheScreen::drawPixel(uint16_t x, uint16_t y, uint16_t color)
{
    dma_display->drawPixel(x, y, color);
}

/*
uint16_t TheScreen::colorWheel(uint16_t WheelPos)
{
    WheelPos = 65535 - WheelPos;
    if (WheelPos < 21845)
    {
        return colorRGB(65535 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 43690)
    {
        WheelPos -= 21845;
        return colorRGB(0, WheelPos * 3, 65535 - WheelPos * 3);
    }
    WheelPos -= 43690;
    return colorRGB(WheelPos * 3, 65535 - WheelPos * 3, 0);
}
*/

uint16_t TheScreen::rgb888ToRgb565(uint8_t red, uint8_t green, uint8_t blue)
{
    // return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    red >>= 3;
    green >>= 2;
    blue >>= 3;
    return (red << 11) | (green << 5) | blue;
    // return (((31 * (red + 4)) / 255) << 11) |
    //        (((63 * (green + 2)) / 255) << 5) |
    //        ((31 * (blue + 4)) / 255);
}

uint8_t TheScreen::nextWheelIndex(uint8_t value)
{
    value++;
    if (value < 94)
        return value;
    return value % 95;
}

uint16_t TheScreen::myColorWheel(uint8_t wheelPos)
{
    uint8_t pos = wheelPos;
    uint8_t red, green, blue;
    if (pos < 32) // red to blue
    {
        red = 31 - pos;
        green = 0;
        blue = pos;
    }
    else
    {
        if (pos < 64) // blue to green
        {
            red = 0;
            green = 2 * pos - 63; // => 64-(64-pos)*2
            blue = 63 - pos;
        }
        else // green to red
        {
            red = pos - 63;
            green = 1 + 2 * (94 - pos);
            blue = 0;
        }
    }
    return rgb888ToRgb565(red, green, blue);
}

uint16_t TheScreen::colorWheel(uint8_t wheelPos)
{
    wheelPos = 255 - wheelPos;
    uint8_t r, g, b;

    if (wheelPos < 85)
    {
        r = 255 - wheelPos * 3;
        g = 0;
        b = wheelPos * 3;
    }
    else if (wheelPos < 170)
    {
        wheelPos -= 85;
        r = 0;
        g = wheelPos * 3;
        b = 255 - wheelPos * 3;
    }
    else
    {
        wheelPos -= 170;
        r = wheelPos * 3;
        g = 255 - wheelPos * 3;
        b = 0;
    }

    return rgb888ToRgb565(r, g, b);
    /*WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
        return colorRGB(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170)
    {
        WheelPos -= 85;
        return colorRGB(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return colorRGB(WheelPos * 3, 255 - WheelPos * 3, 0);*/
}

void TheScreen::externalRainbowRectangle(uint16_t decal, uint8_t border)
{
    for (uint16_t y = 0; y < PANEL_SIZE_HEIGHT; y++)
    {
        byte startWheel = decal + y + 1;
        for (uint16_t x = 0; x < PANEL_SIZE_WIDTH; x++)
        {
            if (y < border || y >= PANEL_SIZE_HEIGHT - border ||
                x < border || x >= PANEL_SIZE_WIDTH - border)
            {
                dma_display->drawPixel(x, y, colorWheel(startWheel));
                // dma_display->drawPixel(x, y, myColorWheel(startWheel));
                // startWheel = nextWheelIndex(startWheel);
            }
            // startWheel = nextWheelIndex(startWheel);
        }
    }
}

void TheScreen::drawFillRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
    dma_display->fillRect(x, y, width, height, color);
}

void TheScreen::drawFillRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t red, uint8_t green, uint8_t blue)
{
    dma_display->fillRect(x, y, width, height, red, green, blue);
}

/// renvoie la largeur en led d'un texte
uint16_t TheScreen::getTextWidth(const char *text)
{
    int16_t x1, y1;
    uint16_t w, h;
    dma_display->getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    return w;
}

/// affiche du texe sans animation, il ne fait qu'apparaitre
void TheScreen::printText(const char *text, uint8_t size, int posX, bool centered, uint16_t color, uint8_t lumin)
{
    dma_display->setTextSize(size);
    dma_display->setBrightness8(lumin);
    if (centered)
        posX = ((PANEL_SIZE_WIDTH)-getTextWidth(text)) / 2;
    int posY = (-7 * size + 32) / 2;
    dma_display->setCursor(posX, posY);
    dma_display->setTextColor(color);
    dma_display->print(text);
}

void TheScreen::printText(const char *text, uint8_t size, int posX, bool centered, uint16_t textColor, uint16_t backgroundColor, uint8_t lumin)
{
    dma_display->setTextSize(size);
    dma_display->setBrightness8(lumin);
    if (centered)
        posX = ((PANEL_SIZE_WIDTH)-getTextWidth(text)) / 2;
    int posY = (-7 * size + 32) / 2;
    dma_display->setCursor(posX, posY);
    dma_display->setTextColor(textColor, backgroundColor);
    dma_display->print(text);
}

/// affiche un texte avec un fondu d'entrée et de sortie
void TheScreen::fadingText(const char *text, uint8_t size, bool isRGB, uint16_t color, uint16_t fillColor, uint8_t lumin, int delais, int fadeInTime, int fadeOutTime)
{
    dma_display->clearScreen();
    dma_display->fillScreen(fillColor);
    if (!isRGB)
    {
        printText(text, size, 0, true, color, 0);
    }

    int timeRef = millis();
    int timeDelay = 2;
    float fadeVal = 0;
    int rgb = 0;
    int r = 0, g = 255, b = 0;
    bool sign = 1;
    int pas = 2;

    while (millis() <= timeRef + delais)
    {
        if (millis() >= timeDelay)
        {
            if (millis() <= timeRef + fadeInTime && fadeInTime != 0)
            {
                // Serial.print("("+String(millis())+"-"+String(timeRef)+")*("+String(lumin)+"/"+String(fadeInTime)+") = ");
                fadeVal = (millis() - timeRef) * lumin / fadeInTime;
                // Serial.println(fadeVal);
                dma_display->setBrightness8(fadeVal);
            }

            if (isRGB)
            {
                if (rgb <= 0)
                {
                    if (sign)
                    {
                        r += pas;
                        if (r > 255)
                            r = 255;
                    }
                    else
                    {
                        r -= pas;
                        if (r < 0)
                            r = 0;
                    }
                    if (r >= 255 || r <= 0)
                    {
                        rgb++;
                        sign = 1 - sign;
                    }
                }
                if (rgb == 1)
                {
                    if (sign)
                    {
                        g += pas;
                        if (g > 255)
                            g = 255;
                    }
                    else
                    {
                        g -= pas;
                        if (g < 0)
                            g = 0;
                    }
                    if (g >= 255 || g <= 0)
                    {
                        rgb++;
                        sign = 1 - sign;
                    }
                }
                if (rgb >= 2)
                {
                    if (sign)
                    {
                        b += pas;
                        if (b > 255)
                            b = 255;
                    }
                    else
                    {
                        b -= pas;
                        if (b < 0)
                            b = 0;
                    }
                    if (b >= 255 || b <= 0)
                    {
                        rgb = 0;
                        sign = 1 - sign;
                    }
                }
                // dma_display->clearScreen();
                // Serial.print(r); Serial.print(" "); Serial.print(g); Serial.print(" "); Serial.println(b);
                printText(text, size, 0, true, colorRGB(r, g, b), fadeVal);
            }

            if (millis() >= timeRef + delais - fadeOutTime && fadeOutTime != 0)
            {
                // Serial.print("("+String(millis())+"-"+String(timeRef+delais-fadeOutTime)+")*("+String(lumin)+"/"+String(fadeOutTime)+") = ");
                fadeVal = lumin - ((millis() - (timeRef + delais - fadeOutTime)) * lumin / fadeOutTime);
                // Serial.println(fadeVal);
                dma_display->setBrightness8(fadeVal);
            }
            timeDelay = millis() + 7;
        }
    }
    dma_display->clearScreen();
}
