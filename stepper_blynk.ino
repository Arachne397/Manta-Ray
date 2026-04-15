// SEKCE 1
#define BLYNK_PRINT Serial

// Blynk Device Info here
#define BLYNK_TEMPLATE_ID           "BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME         "BLYNK_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN            "BLYNK_AUTH_TOKEN"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <AccelStepper.h>

// steps per revolution
const int stepsPerRevolution = 2048;
int target = 1.5*stepsPerRevolution;

// ULN2003 Motor Driver Pins
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4

// initialize the stepper library
AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);


// WiFi credentials.
char ssid[] = "SSID";
char pass[] = "PASSWORD";
int buttonOnOff;
int buttonUP;
int buttonDOWN;
int buttonPosition;

// SEKCE 2
BLYNK_WRITE(V0) {

  buttonOnOff = param.asInt();

  if (buttonOnOff == HIGH) {
    stepper.enableOutputs();

    // set the speed and acceleration
    stepper.setMaxSpeed(500);
    stepper.setAcceleration(100);
    Serial.println("Motor On");
  
  } else {
    stepper.setMaxSpeed(0);
    stepper.setAcceleration(0);
    stepper.disableOutputs();  // Disable motor outputs
    Serial.println("Motor Stopped");
  }
}


BLYNK_WRITE(V1) {

  buttonUP = param.asInt();
  stepper.stop();

  if (buttonUP == HIGH) {
    stepper.enableOutputs();

    // set the max speed and speed
    stepper.setMaxSpeed(500);
    stepper.setSpeed(500);
    Serial.println("Move UP");
  
  } else {
    stepper.setSpeed(0);
    stepper.disableOutputs();  // Disable motor outputs
    Serial.println("Motor Stopped");
  }
}


BLYNK_WRITE(V2) {

  buttonDOWN = param.asInt();
  stepper.stop();

  if (buttonDOWN == HIGH) {
    stepper.enableOutputs();

    // set the max speed and speed
    stepper.setMaxSpeed(500);
    stepper.setSpeed(-500);
    Serial.println("Move DOWN");
  
  } else {
    stepper.setSpeed(0);
    stepper.disableOutputs();  // Disable motor outputs
    Serial.println("Motor Stopped");
  }
}


BLYNK_WRITE(V3) {

  buttonPosition = param.asInt();

  if (buttonPosition == HIGH) {
    stepper.setCurrentPosition(1.5*stepsPerRevolution);
  }
}


// SEKCE 3
void setup() {
  // Debug console
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}


void loop() {
  Blynk.run();

  if (buttonOnOff == HIGH) {
    stepper.enableOutputs();

    if (stepper.distanceToGo() == 0){
      target = target*(-1);
      Serial.println("Changing direction");
    }

    stepper.moveTo(target);
    stepper.run(); // move the stepper motor (one step at a time)
  }

  if (buttonUP == HIGH || buttonDOWN == HIGH) {
    stepper.enableOutputs();
    stepper.runSpeed();
  }
  
}


