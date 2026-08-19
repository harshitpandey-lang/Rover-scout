/*
  ============================================================
                       ROVER SCOUT
                6×6 RC Exploration Rover
  ============================================================

  Controller:
    Arduino Uno

  Radio:
    FlySky Receiver

  Drive:
    Differential drive
    Left motors  -> L298N left channel
    Right motors -> L298N right channel

  Sensors:
    HC-SR04 Ultrasonic Sensor
    Servo-mounted sensor head

  RC Channels:
    CH1 -> Steering
    CH2 -> Throttle
    CH3 -> Sensor-head servo

  Serial:
    9600 baud

  ============================================================
*/

// ============================================================
//                     LIBRARIES
// ============================================================

#include <Servo.h>


// ============================================================
//                     MOTOR DRIVER
// ============================================================

// LEFT MOTOR SIDE
#define ENA 5
#define IN1 7
#define IN2 8

// RIGHT MOTOR SIDE
#define ENB 6
#define IN3 9
#define IN4 10


// ============================================================
//                     FLYSKY RECEIVER
// ============================================================

#define CH1 2       // Steering
#define CH2 4       // Throttle
#define CH3 A2      // Servo control


// ============================================================
//                     SERVO
// ============================================================

#define SERVO_PIN 3

Servo sensorServo;


// ============================================================
//                     ULTRASONIC SENSOR
// ============================================================

#define TRIG_PIN A0
#define ECHO_PIN A1


// ============================================================
//                     SETTINGS
// ============================================================

#define DEADZONE 60

// Valid RC pulse range
#define RC_MIN 900
#define RC_MAX 2100

// Servo limits
#define SERVO_MIN 0
#define SERVO_MAX 180


// ============================================================
//                     SETUP
// ============================================================

void setup() {

  // ----------------------------------------------------------
  // Motor pins
  // ----------------------------------------------------------

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);


  // ----------------------------------------------------------
  // FlySky receiver
  // ----------------------------------------------------------

  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);


  // ----------------------------------------------------------
  // Ultrasonic sensor
  // ----------------------------------------------------------

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);


  // ----------------------------------------------------------
  // Servo
  // ----------------------------------------------------------

  sensorServo.attach(SERVO_PIN);
  sensorServo.write(90);


  // ----------------------------------------------------------
  // Serial communication
  // ----------------------------------------------------------

  Serial.begin(9600);


  // ----------------------------------------------------------
  // Start with motors stopped
  // ----------------------------------------------------------

  stopMotors();

  Serial.println();
  Serial.println("=================================");
  Serial.println("        ROVER SCOUT ONLINE");
  Serial.println("=================================");
}


// ============================================================
//                       MAIN LOOP
// ============================================================

void loop() {

  // ----------------------------------------------------------
  // Read RC channels
  // ----------------------------------------------------------

  unsigned long steeringSignal =
    pulseIn(CH1, HIGH, 25000);

  unsigned long throttleSignal =
    pulseIn(CH2, HIGH, 25000);

  unsigned long servoSignal =
    pulseIn(CH3, HIGH, 25000);


  // ----------------------------------------------------------
  // FAILSAFE
  //
  // If steering or throttle signals are invalid,
  // immediately stop the rover.
  // ----------------------------------------------------------

  if (
    steeringSignal < RC_MIN ||
    steeringSignal > RC_MAX ||
    throttleSignal < RC_MIN ||
    throttleSignal > RC_MAX
  ) {

    stopMotors();

    Serial.println("FAILSAFE: Invalid RC signal");

    delay(20);

    return;
  }


  // ----------------------------------------------------------
  // STEERING
  // ----------------------------------------------------------

  int steering =
    map(steeringSignal, 1000, 2000, -255, 255);

  steering =
    constrain(steering, -255, 255);


  // ----------------------------------------------------------
  // THROTTLE
  // ----------------------------------------------------------

  int throttle =
    map(throttleSignal, 1000, 2000, -255, 255);

  throttle =
    constrain(throttle, -255, 255);


  // ----------------------------------------------------------
  // APPLY DEADZONE
  // ----------------------------------------------------------

  if (abs(throttle) < DEADZONE) {
    throttle = 0;
  }

  if (abs(steering) < DEADZONE) {
    steering = 0;
  }


  // ----------------------------------------------------------
  // DIFFERENTIAL DRIVE
  //
  // Steering modifies the speed of each side.
  //
  // throttle + steering
  //          ↓
  //     LEFT / RIGHT
  // ----------------------------------------------------------

  int leftSpeed =
    throttle + steering;

  int rightSpeed =
    throttle - steering;


  leftSpeed =
    constrain(leftSpeed, -255, 255);

  rightSpeed =
    constrain(rightSpeed, -255, 255);


  // ----------------------------------------------------------
  // DRIVE MOTORS
  // ----------------------------------------------------------

  setLeftMotor(leftSpeed);
  setRightMotor(rightSpeed);


  // ----------------------------------------------------------
  // SERVO CONTROL
  // ----------------------------------------------------------

  if (
    servoSignal >= RC_MIN &&
    servoSignal <= RC_MAX
  ) {

    int servoAngle =
      map(
        servoSignal,
        1000,
        2000,
        SERVO_MIN,
        SERVO_MAX
      );

    servoAngle =
      constrain(
        servoAngle,
        SERVO_MIN,
        SERVO_MAX
      );

    sensorServo.write(servoAngle);
  }


  // ----------------------------------------------------------
  // ULTRASONIC DISTANCE
  // ----------------------------------------------------------

  long distance =
    readDistance();


  // ----------------------------------------------------------
  // SERIAL TELEMETRY
  // ----------------------------------------------------------

  Serial.print("CH1: ");
  Serial.print(steeringSignal);

  Serial.print("  CH2: ");
  Serial.print(throttleSignal);

  Serial.print("  CH3: ");
  Serial.print(servoSignal);

  Serial.print("  Distance: ");

  if (distance == -1) {
    Serial.print("OUT_OF_RANGE");
  }
  else {
    Serial.print(distance);
    Serial.print(" cm");
  }

  Serial.print("  L: ");
  Serial.print(leftSpeed);

  Serial.print("  R: ");
  Serial.println(rightSpeed);


  delay(20);
}


// ============================================================
//                  LEFT MOTOR CONTROL
// ============================================================

void setLeftMotor(int speed) {

  speed =
    constrain(speed, -255, 255);


  // STOP
  if (speed == 0) {

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    analogWrite(ENA, 0);

    return;
  }


  // FORWARD
  if (speed > 0) {

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    analogWrite(
      ENA,
      speed
    );

    return;
  }


  // REVERSE
  speed = abs(speed);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(
    ENA,
    speed
  );
}


// ============================================================
//                 RIGHT MOTOR CONTROL
// ============================================================

void setRightMotor(int speed) {

  speed =
    constrain(speed, -255, 255);


  // STOP
  if (speed == 0) {

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    analogWrite(ENB, 0);

    return;
  }


  // FORWARD
  if (speed > 0) {

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    analogWrite(
      ENB,
      speed
    );

    return;
  }


  // REVERSE
  speed = abs(speed);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(
    ENB,
    speed
  );
}


// ============================================================
//                       STOP MOTORS
// ============================================================

void stopMotors() {

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


// ============================================================
//                 ULTRASONIC DISTANCE
// ============================================================

long readDistance() {

  // Make sure trigger starts LOW
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);


  // Send 10 µs trigger pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);


  // Measure echo pulse
  unsigned long duration =
    pulseIn(
      ECHO_PIN,
      HIGH,
      30000
    );


  // No echo received
  if (duration == 0) {
    return -1;
  }


  // Speed of sound:
  // approximately 0.034 cm/µs
  //
  // Divide by 2 because the sound travels:
  // sensor → object → sensor

  long distance =
    duration * 0.034 / 2;


  return distance;
}
