#include "SoftPWM.h"

int inPin = 3;
int outPin = 5;

void setup() {
  SoftPWMBegin();
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float dutyCycle = readInput();
  int pwr = (dutyCycle * 100) / 4;
  set(pwr);
}

void set(int pwr) {
  //pwr 0-100%
  SoftPWMSetPercent(outPin, pwr);
}

float readInput() {
  unsigned long highTime = pulseIn(inPin, HIGH);
  unsigned long lowTime = pulseIn(inPin, LOW);
  unsigned long cycleTime = highTime + lowTime;
  float dutyCycle = (float) highTime / (float) cycleTime;
  Serial.println(dutyCycle);
  return dutyCycle;
}
