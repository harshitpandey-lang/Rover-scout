# Rover Scout — Wiring

## Arduino Pinout

| Arduino | Connection | Function |
|---|---|---|
| D2 | FlySky CH1 | Steering |
| D3 | Servo Signal | Sensor servo |
| D4 | FlySky CH2 | Throttle |
| D5 | L298N ENA | Left PWM |
| D6 | L298N ENB | Right PWM |
| D7 | L298N IN1 | Left direction |
| D8 | L298N IN2 | Left direction |
| D9 | L298N IN3 | Right direction |
| D10 | L298N IN4 | Right direction |
| A0 | HC-SR04 TRIG | Trigger |
| A1 | HC-SR04 ECHO | Echo |
| A2 | FlySky CH3 | Servo control |

## FlySky Receiver


CH1 → D2  → Steering
CH2 → D4  → Throttle
CH3 → A2  → Servo
GND → Arduino GND
VCC → 5V



HC-SR04
VCC  → 5V
GND  → GND
TRIG → A0
ECHO → A1
Servo
Signal → D3
VCC    → Suitable 5V supply
GND    → Common GND
L298N
ENA → D5
IN1 → D7
IN2 → D8


ENB → D6
IN3 → D9
IN4 → D10


GND → Common GND
VM  → Motor battery

The left and right motor groups are controlled as two sides of the 6×6 drivetrain.

Power
3S LiPo
   │
   ▼
Power Switch
   │
   ├──→ L298N motor power
   │
   └──→ Appropriate regulator/BEC → Arduino / Servo / Receiver
