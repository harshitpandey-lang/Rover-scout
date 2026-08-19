
# 🤖 Rover Scout

### 6×6 RC Exploration Rover

![Arduino](https://img.shields.io/badge/Arduino-Uno-00979D?style=for-the-badge\&logo=arduino)
![C++](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge\&logo=cplusplus)
![Drive](https://img.shields.io/badge/Drive-6×6-orange?style=for-the-badge)
![Control](https://img.shields.io/badge/Control-FlySky-blue?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Working-success?style=for-the-badge)

> **Rover Scout** is a 6×6 Arduino-powered exploration rover designed to explore the fundamentals of robotics, embedded systems, RC control, motor control and distance sensing.

---

## 🚀 About the Project

**Rover Scout** is a six-wheel robotic rover built around an **Arduino Uno**.

The rover uses a **FlySky RC transmitter and receiver** for wireless control and a pair of **L298N motor drivers** for controlling its drivetrain.

A servo-mounted **HC-SR04 ultrasonic sensor** acts as the rover's scanning head, allowing Rover Scout to measure the distance to objects in front of it.

The project is designed to be modular so that it can evolve from a simple RC rover into a more advanced autonomous robotics platform.

### Current capabilities

* 🎮 FlySky wireless RC control
* 🛞 6-wheel drivetrain
* ↔️ Differential drive
* ⚡ PWM motor-speed control
* 📡 HC-SR04 ultrasonic distance sensing
* 🔄 Servo-controlled sensor head
* 📊 Serial telemetry
* 🛑 Basic RC signal failsafe
* 🔧 Arduino-based architecture

---

# 🧠 How Rover Scout Works

```text
                     ┌─────────────────────┐
                     │   FlySky Transmitter│
                     └──────────┬──────────┘
                                │
                                │ Radio
                                ▼
                     ┌─────────────────────┐
                     │   FlySky Receiver   │
                     │                     │
                     │ CH1 → Steering      │
                     │ CH2 → Throttle      │
                     │ CH3 → Sensor Servo  │
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
       ┌─────────────────┐              ┌─────────────────┐
       │ Motor Drivers   │              │  Sensor System  │
       │                 │              │                 │
       │   L298N ×2      │              │ HC-SR04 + Servo  │
       └────────┬────────┘              └─────────────────┘
                │
                ▼
       ┌─────────────────┐
       │   6×6 Drive     │
       │                 │
       │  ● ● ●  ● ● ●  │
       └─────────────────┘
```

---

# ✨ Features

## 🎮 RC Control

Rover Scout is controlled using a FlySky radio system.

| Channel | Function          |
| ------- | ----------------- |
| CH1     | Steering          |
| CH2     | Throttle          |
| CH3     | Sensor-head servo |

The Arduino reads the RC pulse widths and converts them into motor and servo commands.

---

## 🛞 6×6 Differential Drive

Rover Scout uses differential steering.

Instead of a traditional steering mechanism, the rover changes direction by varying the movement of the left and right sides.

```text
             FRONT

       LEFT             RIGHT
        │                 │
        ▼                 ▼

      ● ● ●             ● ● ●
      │ │ │             │ │ │
      └─┴─┴─────────────┴─┴─┘

       LEFT SIDE       RIGHT SIDE
```

Basic movement:

```text
FORWARD

LEFT  → Forward
RIGHT → Forward
```

```text
REVERSE

LEFT  → Reverse
RIGHT → Reverse
```

```text
TURN LEFT

LEFT  → Stop / Slow
RIGHT → Forward
```

```text
TURN RIGHT

LEFT  → Forward
RIGHT → Stop / Slow
```

---

# 📡 Ultrasonic Sensor

Rover Scout uses an **HC-SR04 ultrasonic sensor** to measure distance.

The sensor works by:

1. Sending an ultrasonic pulse.
2. Waiting for the reflected echo.
3. Measuring the return time.
4. Converting the time into distance.

```text
Rover Scout
     │
     │  ultrasonic pulse
     ▼
     ───────────────────────►
                              │
                              │ Object
                              ▼
     ◄───────────────────────
          reflected echo
```

The calculated distance is displayed through the Serial Monitor.

---

# 🔄 Sensor Scanning

The HC-SR04 is mounted on a servo.

This allows the sensor head to rotate.

```text
          90°
           │
           ▲
           │
      45°  │  135°
        \  │  /
         \ │ /
          \│/
      ┌─────────┐
      │  ROVER  │
      └─────────┘
```

The servo position is controlled using **FlySky CH3**.

This creates the foundation for future autonomous obstacle-scanning functionality.

---

# 🔌 Pin Configuration

| Arduino Pin | Component  | Function        |
| ----------- | ---------- | --------------- |
| D2          | FlySky CH1 | Steering        |
| D3          | Servo      | Sensor head     |
| D4          | FlySky CH2 | Throttle        |
| D5          | L298N      | Left PWM        |
| D6          | L298N      | Right PWM       |
| D7          | L298N      | Left direction  |
| D8          | L298N      | Left direction  |
| D9          | L298N      | Right direction |
| D10         | L298N      | Right direction |
| A0          | HC-SR04    | TRIG            |
| A1          | HC-SR04    | ECHO            |
| A2          | FlySky CH3 | Servo control   |

---

# 🧰 Bill of Materials

| Qty | Component                            |
| --: | ------------------------------------ |
|   1 | Arduino Uno                          |
|   2 | L298N Motor Driver                   |
|   6 | BO Geared DC Motors                  |
|   6 | Wheels                               |
|   1 | 6×6 Rover Chassis                    |
|   1 | FlySky Transmitter                   |
|   1 | FlySky Receiver                      |
|   1 | HC-SR04 Ultrasonic Sensor            |
|   1 | Servo Motor                          |
|   1 | HC-05 Bluetooth Module               |
|   1 | 11.1V 3S LiPo Battery                |
|   1 | Power Switch                         |
|   1 | Breadboard                           |
|   — | Jumper Wires                         |
|   — | Motor connectors / mounting hardware |

A machine-readable BOM is available here:

```text
BOM.csv
```

---

# 🔋 Power Architecture

The rover uses an **11.1V 3S LiPo battery**.

A simplified power architecture is:

```text
                 3S LiPo
              11.1V nominal
                    │
                    ▼
              Power Switch
                    │
          ┌─────────┴─────────┐
          │                   │
          ▼                   ▼
     Motor Drivers       Regulated Supply
          │                   │
          ▼                   ├── Arduino
       Motors                 ├── Receiver
                              ├── Servo
                              └── HC-SR04
```

⚠️ **Do not power the motors directly from the Arduino 5V pin.**

The servo can also draw significant current, so its supply should be designed appropriately.

---

# ⚠️ Important Hardware Note

The project uses **L298N motor drivers**.

The L298N is inexpensive and easy to use, but it has relatively high voltage losses and limited practical current capability.

Because Rover Scout has six motors, motor startup and stall current can become significant.

For a future high-performance version, consider replacing the L298N with a modern **MOSFET-based motor driver** sized according to measured motor current.

---

# 💻 Software

The firmware is written in **Arduino C++**.

Main source:

```text
src/
└── rover_scout.ino
```

The project uses the Arduino **Servo** library.

No additional external libraries are required for the basic motor, RC and ultrasonic functionality.

---

# 📊 Serial Telemetry

Rover Scout continuously outputs useful debugging information.

Example:

```text
CH1: 1502
CH2: 1510
CH3: 1498
Distance: 47 cm
```

This allows you to monitor:

* steering input
* throttle input
* servo input
* ultrasonic distance
* motor PWM values

Open:

**Arduino IDE → Serial Monitor → 9600 baud**

---

# 🛑 Failsafe

Rover Scout contains a basic receiver-signal failsafe.

If the steering or throttle pulse becomes invalid, the firmware stops the motors.

Conceptually:

```text
Valid RC signal
       │
       ▼
   Drive rover
       │
       │
Signal lost?
       │
       ▼
   STOP MOTORS
```

This is an additional software safety layer.

It should **not** replace:

* transmitter failsafe configuration
* physical power switch
* proper battery protection
* safe testing procedures

---

# 📁 Repository Structure

```text
rover-scout-6x6/
│
├── README.md
├── LICENSE
├── .gitignore
├── BOM.csv
│
├── src/
│   └── rover_scout.ino
│
├── hardware/
│   ├── BOM.csv
│   └── wiring/
│       └── wiring_reference.md
│
├── docs/
│   ├── WIRING.md
│   ├── CALIBRATION.md
│   ├── TESTING.md
│   ├── SAFETY.md
│   │
│   └── diagrams/
│       └── wiring.svg
│
├── examples/
│   └── serial_plotter_notes.md
│
├── tests/
│   └── test_plan.md
│
└── media/
    └── README.md
```

---

# 🔧 Building Rover Scout

## 1. Build the chassis

Install:

* six motors
* six wheels
* motor brackets
* chassis
* electronics mounting points

## 2. Install electronics

Mount:

* Arduino Uno
* L298N drivers
* FlySky receiver
* servo
* HC-SR04
* battery
* power switch

## 3. Connect the wiring

Follow:

```text
docs/WIRING.md
```

and the reference diagram:

```text
docs/diagrams/wiring.svg
```

## 4. Upload the firmware

Open:

```text
src/rover_scout.ino
```

in Arduino IDE.

Select:

```text
Board: Arduino Uno
```

Select the correct COM port and upload.

## 5. Test without the rover touching the ground

Before the first drive:

* verify receiver signals
* verify motor direction
* verify throttle center
* verify steering
* verify servo
* verify ultrasonic readings

---

# 🧪 Testing

The project contains a complete test checklist:

```text
tests/test_plan.md
```

The recommended testing sequence is:

```text
Electronics
     ↓
Receiver
     ↓
Motor Driver
     ↓
Individual Motor Groups
     ↓
Servo
     ↓
Ultrasonic
     ↓
Wheels Raised
     ↓
Low-Speed Floor Test
     ↓
Full Rover Test
```

---

# 🗺️ Roadmap

Rover Scout is designed to grow into a more capable robotics platform.

### Version 1 — RC Rover

* [x] Arduino control
* [x] FlySky RC
* [x] 6×6 drivetrain
* [x] Differential drive
* [x] Ultrasonic sensor
* [x] Servo sensor mount
* [x] Serial telemetry

### Version 2 — Smart Rover

* [ ] Automatic obstacle detection
* [ ] Servo scanning
* [ ] Obstacle avoidance
* [ ] Smooth acceleration
* [ ] Configurable steering
* [ ] Battery voltage monitoring
* [ ] Improved telemetry

### Version 3 — Autonomous Rover

* [ ] Wheel encoders
* [ ] Odometry
* [ ] IMU
* [ ] Autonomous navigation
* [ ] Mapping
* [ ] Wireless telemetry

### Version 4 — Advanced Robotics Platform

* [ ] ESP32 / more powerful controller
* [ ] ROS 2 integration
* [ ] Camera
* [ ] Computer vision
* [ ] SLAM
* [ ] Autonomous navigation

---

# 🧩 Future Architecture

The long-term goal is to evolve Rover Scout from:

```text
RC CAR
```

into:

```text
RC ROVER
    ↓
SMART ROVER
    ↓
AUTONOMOUS ROVER
    ↓
ROBOTICS PLATFORM
```

Possible future architecture:

```text
                  Camera
                    │
                    ▼
             ┌──────────────┐
             │   Computer   │
             │ Raspberry Pi │
             │ / Jetson     │
             └──────┬───────┘
                    │
                  ROS 2
                    │
             ┌──────▼───────┐
             │ Microcontroller│
             │ ESP32 / MCU    │
             └──────┬─────────┘
                    │
          ┌─────────┼─────────┐
          ▼         ▼         ▼
       Motors     Sensors    Servo
```

---

# 🛡️ Safety

Rover Scout uses a LiPo battery and powerful moving motors.

Always:

* inspect the battery before use
* use an appropriate LiPo charger
* avoid short circuits
* use suitable wiring
* keep hands away from moving wheels
* test with wheels raised initially
* configure RC failsafe
* use a physical power switch
* never leave a LiPo charging unattended

Read:

```text
docs/SAFETY.md
```

for the complete safety notes.

---

# 📸 Project Media

Project photographs and videos should be placed inside:

```text
media/
```

Recommended documentation:

```text
01-chassis.jpg
02-electronics.jpg
03-wiring.jpg
04-sensor-head.jpg
05-rover-scout.jpg
06-field-test.jpg
```

A final project README can feature the best photograph at the top.

---

# 🤝 Contributing

Contributions and improvements are welcome.

If you modify Rover Scout:

1. Document the hardware change.
2. Update the BOM.
3. Update the wiring documentation.
4. Update the firmware.
5. Test the physical rover.
6. Document the result.

---

# 📜 License

This project is released under the **MIT License**.

See:

```text
LICENSE
```

for details.

---

# 👨‍💻 Project

## Rover Scout

**6×6 RC Exploration Rover**

Built as a hands-on project in:

* Robotics
* Embedded Systems
* Arduino
* Electronics
* Motor Control
* RC Systems
* Sensors
* Mechanical Design

---

<p align="center">

### 🤖 Rover Scout

**Explore. Build. Test. Improve.**

</p>
