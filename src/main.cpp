#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#include "Keyboard.h"

const int DIN_PIN = 6;    // D6
const int LED_COUNT = 2;  // LED の数
const int KEY_DIN_PIN = 4;
const int COLOR_COUNTS = 9;
const int COLOR_LIST[COLOR_COUNTS][3] = {
    // red
    {255, 0, 0},
    // orange
    {255, 128, 0},
    // yellow
    {255, 255, 0},
    // green
    {0, 255, 0},
    // emeraldo
    {0, 255, 128},
    // blue
    {0, 0, 255},
    // blue_purple
    {64, 0, 255},
    // purple
    {128, 0, 255},
    // pink
    {255, 0, 128}};

Adafruit_NeoPixel pixels(LED_COUNT, DIN_PIN, NEO_GRB + NEO_KHZ800);
int colorLeft = 0;
int colorRight = 5;
int beforeInput = 1;
int keyHoldTIick = 0;
void setup() {
    pixels.begin();
    pinMode(KEY_DIN_PIN, INPUT_PULLUP);
    Serial.begin(9600);
    Keyboard.begin();
}

void onKeyDown() {
    Keyboard.print("Chura");
    // 色の変化
    colorLeft = (colorLeft + 1) % COLOR_COUNTS;
    colorRight = (colorRight + 1) % COLOR_COUNTS;
    pixels.setPixelColor(
        0, pixels.Color(COLOR_LIST[colorLeft][0], COLOR_LIST[colorLeft][1],
                        COLOR_LIST[colorLeft][2]));  // 0 番目の色を変える
    pixels.setPixelColor(
        1, pixels.Color(COLOR_LIST[colorRight][0], COLOR_LIST[colorRight][1],
                        COLOR_LIST[colorRight][2]));  // 1 番目の色を変える
    pixels.show();
}

void onKeyUp() {
    Keyboard.print("DATA");
    Keyboard.releaseAll();
    // ちゅら太郎の目から光を奪う
    pixels.clear();
    pixels.show();
}

void loop() {
    int value = digitalRead(KEY_DIN_PIN);
    Serial.println(value);
    if (value == 0) {
        if (beforeInput != value) {
            onKeyDown();
        }
    } else {
        if (beforeInput != value) {
            onKeyUp();
        }
    }
    beforeInput = value;
}
