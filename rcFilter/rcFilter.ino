/*
 * Program to Read & Filter PWM Signal from RC Controller
 */

/* Libraries */
#include <Servo.h>

/* Pinout */
#define port 9600
#define throttleIn 5
#define throttleOut 10
#define steerIn 9
#define steerOut 11
#define echoPin 2
#define trigPin 3

/* Hardware Objects */
Servo throttle;
Servo steer;

/* Constants */
const int neutral = 90;
const float throttleLimit = 0.15;

/* Define Variables */
int throttleInput;
int steerInput;
int throttleTarget = neutral;
int steerTarget = neutral;
int distance;
long duration;

/**
 * Initialization.
 */
void setup() {

  /* Initialize Components */
  initCar();
//  initUltrasonicSensor();
  
  /* Setup Serial Port For Logging */
  Serial.begin(port);
  
}

/**
 * Periodic Function.
 */
void loop() {

  /* Make The Car Move */
  rcDrive();

  /* Read Distance From Sensor */
//  distance = getDistance();
//  Serial.print("Distance: ");
//  Serial.print(distance);
//  Serial.print(" meters\n");
  
}

/**
 * Initializes RC Car Driving Hardware
 */
void initCar() {
  
  /* Configure Pins */
  pinMode(throttleIn, INPUT);
  pinMode(steerIn, INPUT);
  throttle.attach(throttleOut);
  steer.attach(steerOut);

  /* Set Initial PWM Signal */
  setThrottle(neutral);
  setSteer(neutral);

}

void initUltrasonicSensor() {
  
  /* Configure Pins */ 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = (duration * 0.034 / 2) * 100; // m
  return distance;
}

/**
 * Gets, Filters, & Sets The Car's Wheel Speed & Steer From RC Controller
 */
void rcDrive() {
  
  /* Read & Map Input */
  throttleInput = getInput(throttleIn);
  steerInput = getInput(steerIn);

  /* Filter Input */
  throttleTarget = neutral + (int) ((throttleInput - neutral) * throttleLimit);

  /* Set Output */
  Serial.println(steerTarget);
  setThrottle(throttleTarget);
  setSteer(steerInput);
  
}

/**
 * Returns Input From RC Controller
 */
int getInput(int pin) {
  return map(pulseIn(pin, HIGH), 890, 2053, 0, 180);
}

/**
 * Writes PWM Signal To Throttle
 */
void setThrottle(int speed) {
  throttle.write(speed);
}

/**
 * Writes PWM Signal To Servo
 */
void setSteer(int signal) {
  steer.write(signal);
}
