# IoT-Based EV Battery Management System

## Overview

This project implements an IoT-based Battery Management System (BMS) for an Electric Vehicle (EV) battery pack using ESP32.

The system monitors individual cell conditions and provides visual and IoT-based status monitoring.

## Features

- Monitoring of multiple battery cells
- Cell voltage condition detection
- LCD-based status display
- LED indication for battery condition
- ESP32-based control
- IoT monitoring using Blynk
- Wokwi simulation
- PlatformIO development environment

## Hardware / Components

- ESP32
- 16×2 I2C LCD
- Battery cell voltage inputs
- LEDs
- Resistors
- Wi-Fi

## Software

- Arduino framework
- PlatformIO
- Wokwi
- Blynk IoT

## Project Structure

```text
IoT-Based-EV-Battery-Management-System/
│
├── src/
│   └── main.cpp
│
├── diagram.json
├── platformio.ini
├── wokwi.toml
├── .gitignore
└── README.md
