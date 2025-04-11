#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include "LiquidCrystal_I2C.h"
// Matrix Declaration
ArduinoLEDMatrix matrix;
//  LCD Declaration
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Joystick Int
const int joyXPfar = A0;
const int joyYPfar = A2;
const int buttonPinPfar = 8;

bool buttonPressedPfar = false;

int valJoyXPfar = 0;
int valJoyYPfar = 0;
int buttonState = 0;

int mappedValJoyX = 0;
int mappedValJoyY = 0;

int keyWPfar = 0;
int keyAPfar = 0;
int keySPfar = 0;
int keyDPfar = 0;

int counter = 1;

// LCD Int
unsigned long lastMillis;
//int reply;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonPinPfar, INPUT_PULLUP); // use pullup since there is no resistor but you can use resistors
  // Matrix SetUp
  matrix.begin();

  const char textPfar[] = "625";
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(textPfar);
  matrix.endText();

  matrix.endDraw();

  // LCD SetUp
  lcd.init();
  lcd.backlight();
}

void loop() {
unsigned long currentMillis = millis();

  // put your main code here, to run repeatedly:
  // Matrix Loop
  if(buttonPressedPfar == true && (currentMillis - lastMillis >= 300)) 
  {
    
    matrix.endText();
    matrix.endDraw();

    // JoyStick Loop
    valJoyXPfar = analogRead(joyXPfar);
    valJoyYPfar = analogRead(joyYPfar);

    // Converting movement JoyStick
    keyAPfar = map(valJoyXPfar, 0, 500, 100, 0);
    keyDPfar = map(valJoyXPfar, 510, 1023, 0, 100);
    keyWPfar = map(valJoyYPfar, 0, 500, 100, 0);
    keySPfar = map(valJoyYPfar, 500, 1023, 0, 100);


    if(keyWPfar <= 500) 
    {
      if (keyWPfar < 0)
      {keyWPfar = 0;}
      counter = 0;
      Serial.println("Up");
        lcd.setCursor(0, 0);
        lcd.print("                "); // clear
        lcd.setCursor(0, 0);
        lcd.print("UP - ");
        lcd.print(keyWPfar);
        lcd.print("%    ");
    }
    if(keyAPfar <= 500) 
    {
      if (keyAPfar < 0)
      {keyAPfar = 0;}
      counter = 0;
      Serial.println("Left");
        lcd.setCursor(0, 1);
        lcd.print("                "); // clear
        lcd.setCursor(0, 1);
        lcd.print("Left - ");
        lcd.print(keyAPfar);
        lcd.print("%    ");
    }
    if(keySPfar <= 500) 
    {
      if (keySPfar < 0)
      {keySPfar = 0;}
      counter = 0;
      Serial.println("Down");
        lcd.setCursor(0, 2);
        lcd.print("                "); // clear
        lcd.setCursor(0, 2);
        lcd.print("Down - ");
        lcd.print(keySPfar);
        lcd.print("%    ");
    }
    if(keyDPfar <= 500) 
    {
      if (keyDPfar < 0)
      {keyDPfar = 0;}
      counter = 0;
      Serial.println("Right");
        lcd.setCursor(0, 3);
        lcd.print("                "); // clear
        lcd.setCursor(0, 3);
        lcd.print("Right - ");
        lcd.print(keyDPfar);
        lcd.print("%    ");
    }

    if(keyWPfar == 100 && keyAPfar == 100 && keySPfar == 100 && keyDPfar == 100) 
    {
    	if(counter == 0) 
      {
        counter = 1;
        Serial.println("STOP");
        lcd.print("STOP");
      }
    }
    lastMillis = currentMillis;
  }
  if(buttonPressedPfar == false)
  {
    matrix.beginDraw();

    matrix.stroke(0xFFFFFFFF);
    matrix.textScrollSpeed(100);

    const char textPfar[] = "625 - Patricia - BPO3";
    matrix.textFont(Font_5x7);
    matrix.beginText(0, 1, 0xFFFFFF);
    matrix.println(textPfar);
    matrix.endText(SCROLL_LEFT);
    matrix.endDraw();
    delay(500);

    buttonState = digitalRead(buttonPinPfar);
      if(buttonState == LOW){
        buttonPressedPfar = true;
      }
  }
  
}
