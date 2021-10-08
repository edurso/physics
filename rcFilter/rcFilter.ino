const int inPin = 3;
const int outPin = 5;
const float speedReducer = 0.25;
const String sep = " ";

/**
 * Initialization.
 */
void setup() {

  /* Setup Serial Port For Logging */
  Serial.begin(9600);

  /* Configure Pins */
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
  
}

/**
 * Periodic Function.
 */
void loop() {

  /* Read Input */
  unsigned long ontime = pulseIn(inPin, HIGH); // length (microseconds) of high pulse
  unsigned long offtime = pulseIn(inPin, LOW); // length (microseconds) of low pulse
  unsigned long period = ontime + offtime; // period (total time in microseconds for each complete pulse)
  float freq = 1000000.0 / (float) period; // frequency (Hz)
  float duty = ((float) ontime / period); // duty cycle ratio of ontime to total period (value between 0.0 and 1.0)
  Serial.println(duty); // duty cycle

  /* Check Duty Cycle */
  if(duty < 0.05) {
    duty = 0.0;
  } else if(duty > 1.0) {
    duty = 1.0;
  }
  
  /* Change Duty Cycle */
  duty *= speedReducer;

  /* Format Duty Cycle */
  float outDuty = duty * 255;

  /* Write Duty Cycle */
  analogWrite(outPin, (int) outDuty);
  
}
