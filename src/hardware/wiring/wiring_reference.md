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
