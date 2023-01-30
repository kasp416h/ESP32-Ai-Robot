#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

char receivedChar;
bool btConnected = false;
long previousMillis = 0;
int timeout = 1000;

// MOTOR 1 : VENSTRE
int enA = 35;
int in1 = 33;
int in2 = 25;

// MOTOR 2 : Højre
int enB = 14;
int in3 = 26;
int in4 = 27;

int sensor = 34;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32slave");
  Serial.println("The device started in master mode, make sure remote BT device is on!");
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  analogWrite(enB, 200);
}

void loop() {
  int sensorValue = analogRead(sensor);
  if (sensorValue < 3000) {
    digitalWrite(in3, HIGH);
  } else {
    digitalWrite(in3, LOW);
  }

  if (SerialBT.available()) {
    previousMillis = millis();

    receivedChar =(char)SerialBT.read();

    if (btConnected == false) {
      btConnected = true;
      Serial.println("Bluetooth connected.");
    }
    
    if (receivedChar == 'H') {
      Serial.println(receivedChar);
      delay(5000);
    }
    if (receivedChar == 'F') {
      digitalWrite(in3, HIGH);
      Serial.println(receivedChar);
      delay(100);
    }
    if (receivedChar == 'B') {
      Serial.println(receivedChar);
      delay(100);
    }
    if (receivedChar == 'L') {
      Serial.println(receivedChar);
      delay(100);
    }
    if (receivedChar == 'R') {
      Serial.println(receivedChar);
      delay(100);
    }
  }
  if (millis() - previousMillis > timeout && btConnected == true) {

    Serial.println("Bluetooth disconnected.");
    btConnected = false;
    }
}