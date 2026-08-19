# Rover Scout — Wiring Reference

This document describes the electrical connections used by Rover Scout.

> ⚠️ **Important:** Always disconnect the LiPo battery before changing wiring.

---

# 1. System Overview

```text
                         ┌─────────────────────┐
                         │   FlySky Transmitter│
                         └──────────┬──────────┘
                                    │
                                 2.4 GHz
                                    │
                                    ▼
                         ┌─────────────────────┐
                         │   FlySky Receiver   │
                         │                     │
                         │ CH1 → Steering      │
                         │ CH2 → Throttle      │
                         │ CH3 → Servo         │
                         └──────────┬──────────┘
                                    │
                                    ▼
                         ┌─────────────────────┐
                         │     Arduino Uno     │
                         │                     │
                         │  Control + Logic    │
                         └──────┬───────┬──────┘
                                │       │
                    ┌───────────┘       └────────────┐
                    ▼                                ▼
             ┌──────────────┐                ┌──────────────┐
             │ L298N Drivers│                │ Sensor System│
             │              │                │              │
             │ Motor Control│                │ HC-SR04      │
             └───────┬──────┘                │ + Servo      │
                     │                       └──────────────┘
                     ▼
              ┌─────────────┐
              │ 6×6 Motors  │
              │ ● ● ● ● ● ● │
              └─────────────┘

2. Arduino Pinout
Arduino Pin	Connected Component	Function
D2	FlySky CH1	Steering
D3	Servo signal	Sensor-head servo
D4	FlySky CH2	Throttle
D5	L298N ENA	Left motor PWM
D6	L298N ENB	Right motor PWM
D7	L298N IN1	Left motor direction
D8	L298N IN2	Left motor direction
D9	L298N IN3	Right motor direction
D10	L298N IN4	Right motor direction
A0	HC-SR04 TRIG	Ultrasonic trigger
A1	HC-SR04 ECHO	Ultrasonic echo
A2	FlySky CH3	Servo control
3. FlySky Receiver

The receiver provides RC pulse signals to the Arduino.

CH1 — Steering
FlySky Receiver CH1
        │
        ▼
Arduino D2

Expected behavior:

~1000 µs  → Left
~1500 µs  → Center
~2000 µs  → Right
CH2 — Throttle
FlySky Receiver CH2
        │
        ▼
Arduino D4

Expected behavior:

~1000 µs  → Reverse
~1500 µs  → Stop
~2000 µs  → Forward
CH3 — Servo
FlySky Receiver CH3
        │
        ▼
Arduino A2

The firmware converts CH3 into a servo position.

~1000 µs → 0°
~1500 µs → 90°
~2000 µs → 180°
4. L298N Motor Control

The current firmware provides two logical motor groups:

LEFT SIDE
    │
    ├── ENA
    ├── IN1
    └── IN2


RIGHT SIDE
    │
    ├── ENB
    ├── IN3
    └── IN4
Left side
L298N Pin	Arduino
ENA	D5
IN1	D7
IN2	D8

The left-side motors should be wired so that they operate together.

Right side
L298N Pin	Arduino
ENB	D6
IN3	D9
IN4	D10

The right-side motors should be wired so that they operate together.

5. Important 6×6 Motor Note

Rover Scout physically has six motors, but the current firmware controls:

LEFT MOTOR GROUP
RIGHT MOTOR GROUP

It does not provide six independent motor outputs.

Therefore, the exact arrangement of the six motors must be designed around the available motor-driver channels.

Do not connect multiple motors in parallel without checking:

Motor current
Driver current capability
Startup current
Stall current
Wire gauge
Connector rating
Driver temperature
6. HC-SR04

The ultrasonic sensor uses two signal connections.

HC-SR04	Arduino
VCC	5V
GND	GND
TRIG	A0
ECHO	A1

Signal path:

Arduino A0
    │
    ▼
HC-SR04 TRIG
    │
    │ ultrasonic pulse
    ▼
      Object
    │
    │ reflected pulse
    ▼
HC-SR04 ECHO
    │
    ▼
Arduino A1
7. Servo

The servo has three basic connections:

Servo Wire	Connection
Signal	Arduino D3
VCC	Appropriate regulated supply
GND	Common GND
Important

Do not assume that the Arduino 5V pin can safely supply every servo.

A servo can produce current spikes when:

starting
changing direction
reaching a mechanical limit
carrying a load

Use an appropriate 5V regulator/BEC when necessary.

8. Power Architecture

Rover Scout uses a:

3S LiPo
11.1V nominal
3000mAh

Recommended high-level architecture:

                  3S LiPo
                     │
                     ▼
              ┌─────────────┐
              │ Power Switch│
              └──────┬──────┘
                     │
          ┌──────────┴──────────┐
          │                     │
          ▼                     ▼
   Motor Driver Supply     5V Regulator/BEC
          │                     │
          │              ┌──────┼───────┐
          │              │      │       │
          ▼              ▼      ▼       ▼
       Motors         Arduino Receiver Servo
9. Common Ground

The signal systems need a common electrical reference.

                 Arduino GND
                      │
          ┌───────────┼────────────┐
          │           │            │
          ▼           ▼            ▼
      Receiver     HC-SR04       Servo
          │
          ▼
      Motor Driver

Make sure the grounds are connected correctly.

10. Battery Connection

The battery should connect through the main power switch.

LiPo +
  │
  ▼
Power Switch
  │
  ▼
Motor Driver VM+

Battery negative should connect to the appropriate power ground.

Never reverse battery polarity.

11. L298N Power

Typical L298N terminals:

┌───────────────────────────────┐
│             L298N             │
│                               │
│  +12V / VM  ← Motor Battery   │
│  GND        ← Battery GND     │
│                               │
│  ENA        ← Arduino D5      │
│  IN1        ← Arduino D7      │
│  IN2        ← Arduino D8      │
│                               │
│  ENB        ← Arduino D6      │
│  IN3        ← Arduino D9      │
│  IN4        ← Arduino D10     │
│                               │
│  OUT1/OUT2 → Left motors      │
│  OUT3/OUT4 → Right motors     │
└───────────────────────────────┘

The exact power-terminal labeling can vary between L298N modules, so verify the markings on your physical board.

12. Wiring Checklist

Before connecting the battery:

 Battery polarity checked
 Power switch installed
 Motor-driver polarity checked
 Arduino GND connected correctly
 Receiver GND connected
 HC-SR04 GND connected
 Servo GND connected
 CH1 connected to D2
 CH2 connected to D4
 CH3 connected to A2
 Servo signal connected to D3
 TRIG connected to A0
 ECHO connected to A1
 ENA connected to D5
 ENB connected to D6
 IN1 connected to D7
 IN2 connected to D8
 IN3 connected to D9
 IN4 connected to D10
 No loose motor wires
 No exposed battery terminals
 Wheels lifted for first powered test
13. First Power-Up Procedure

Do not immediately place Rover Scout on the ground.

Step 1

Remove the wheels from contact with the ground.

Step 2

Turn on the FlySky transmitter.

Step 3

Turn on Rover Scout.

Step 4

Open Serial Monitor:

9600 baud
Step 5

Check that CH1, CH2 and CH3 values are being received.

Step 6

Keep the throttle centered.

The motors should remain stopped.

Step 7

Move the throttle slightly forward.

Verify motor direction.

Step 8

Test steering.

Step 9

Move CH3 and verify the sensor servo.

Step 10

Verify the ultrasonic distance readings.

14. Electrical Safety

⚠️ Never make wiring changes while the LiPo is connected.

⚠️ Never short the LiPo battery.

⚠️ Do not power motors from Arduino 5V.

⚠️ Do not exceed the practical current capability of the L298N.

⚠️ Keep the rover lifted during the first motor test.

15. Future Wiring Expansion

Future versions of Rover Scout may add:

             Rover Scout
                  │
       ┌──────────┼───────────┐
       ▼          ▼           ▼
    Encoders      IMU       Battery
       │          │        Monitor
       └──────────┼───────────┘
                  ▼
            Main Controller
                  │
                  ▼
              ROS 2 / PC

Potential future hardware:

Wheel encoders
IMU
ESP32
Camera
Battery voltage sensor
Higher-current motor drivers
Raspberry Pi
ROS 2 computer
