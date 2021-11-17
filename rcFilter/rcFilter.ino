/*
 * Program to Read & Filter PWM Signal from RC Controller
 */

#include <Servo.h>

/* Hardware Objects */
Servo throttle;

/* Declare Constants */
const int throttleIn = 5;
const int throttleOut = 10;
const int neutral = 90;
const float limit = 0.25;

/* Placeholders */
int rcIn;
int rx;
int target = 90;

/**
 * Initialization.
 */
void setup() {

  /* Configure Pins */
  pinMode(throttleIn, INPUT);
  throttle.attach(throttleOut);
  setThrottle(90);

  /* Setup Serial Port For Logging */
  Serial.begin(9600);
  
}

/**
 * Periodic Function.
 */
void loop() {

  /* Read & Map Input */
  rcIn = pulseIn(throttleIn, HIGH);
  rx = map(rcIn, 890, 2053, 0, 180);

  /* Filter Input */
  target = neutral + (int) ((rx - neutral) * limit);

  /* Set Output */
  Serial.println(target);
  setThrottle(target);
  
}

void setThrottle(int speed) {
  throttle.write(speed);
}
