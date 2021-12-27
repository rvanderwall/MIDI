#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "led.h"

//
// OLED Display screen
//
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// https://arduinogetstarted.com/tutorials/arduino-oled
// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void init_display() {
    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      Serial.println(F("SSD1306 allocation failed"));
      blink_error(3);
    }
}

void display_big_text(String line1) {
    oled.clearDisplay();
    oled.setTextSize(2);
    oled.setTextColor(WHITE);
    oled.setCursor(0, 2);
    oled.println(line1);
    oled.display();
}

void display_text(String line1, String line2, String line3) {
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.setCursor(0, 2);   //  Offest a bit for better look
    oled.println(line1);
    oled.setCursor(0, 12);
    oled.println(line2);
    oled.setCursor(0, 22);
    oled.println(line3);
    oled.display();
}

#endif
