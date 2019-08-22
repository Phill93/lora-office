/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x32 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "battery.cpp"
#include <avr/dtostrf.h>
#include <Adafruit_seesaw.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_seesaw ss;

void setup() {
  asm(".global _printf_float");
  Serial.begin(115200);

  delay(20); // Needed for Heltec Display without RESET Pin
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(WHITE);
  display.setTextSize(1);

  display.println("Bootup!!");
  display.println("Display inititated");
  display.println("Trying to initiate Soil Sensor");
  display.display();

  if (!ss.begin(0x36)) {
    display.println("ERROR! seesaw not found");
    display.println("!!looping for ever!!");
    display.display();
    while(1);
  } else {
    display.print("seesaw started! version: ");
    display.println(ss.getVersion(), HEX);
    display.display();
  }

  display.println("Soil Sensor inititated");
  display.display();
  delay(2000);
  display.clearDisplay();
}


void loop() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(WHITE);
  display.setTextSize(1);

  char str_bat[4];
  dtostrf(getBatteryVoltage(), 4, 2, str_bat);
  display.printf("Bat: %sV\n", str_bat);

  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

  display.printf("Temp: %f°C\n", tempC);
  display.printf("Cap: %d\n", capread);

  display.display();
  delay(1000);
}