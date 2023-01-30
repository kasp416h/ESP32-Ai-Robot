#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

const int SWITCH_PIN = 23;

const int X_AXIS_PIN = 32;
const int Y_AXIS_PIN = 33;

int mapAndAdjustJoystickDeadBandValues(int value, bool reverse) {
  if (value >= 2200) {
    value = map(value, 2200, 4095, 127, 254);
  }
  else if (value <= 1800) {
    value = map(value, 1800, 0, 127, 0);  
  }
  else {
    value = 127;
  }
  if (reverse) {
    value = 254 - value;
  }
  return value;
}

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32master", true); //Bluetooth device name
  Serial.println("Connecting...");
  bool connected = SerialBT.connect("ESP32slave");
  if (connected) {
    Serial.println("Connected!");
  } else {
    Serial.println("NOT Connected!");
  }
  pinMode(SWITCH_PIN, INPUT);
}

void loop() {
  byte xAxisValue = mapAndAdjustJoystickDeadBandValues(analogRead(X_AXIS_PIN), false);
  byte yAxisValue = mapAndAdjustJoystickDeadBandValues(analogRead(Y_AXIS_PIN), false);
  int switchState = digitalRead(SWITCH_PIN);


  if (switchState == 1) {
    SerialBT.println("H");
    Serial.println(switchState);
    delay(100);
  }
  if (xAxisValue == 0) {
    SerialBT.println("F");
    Serial.println(xAxisValue);
    delay(100);
  }
  if (xAxisValue == 254) {
    SerialBT.println("B");
    Serial.println(xAxisValue);
    delay(100);
  }
  if (yAxisValue == 254) {
    SerialBT.println("L");
    Serial.println(yAxisValue);
    delay(100);
  }
  if (yAxisValue == 0) {
    SerialBT.println("R");
    Serial.println(yAxisValue);
    delay(100);
  }
}


