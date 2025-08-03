# ESP32 CAN Servo Receiver

This file receives angle values over the CAN bus using ESP32 and rotates a servo motor accordingly.

## Wiring Summary
- CAN RX: GPIO 4
- CAN TX: GPIO 5
- Servo signal pin: GPIO 18

## Required Libraries
See `libraries.txt` for setup instructions.

## How it works
The receiver listens for CAN messages containing a single byte (0–180) representing the servo angle. Upon receiving a new value, the servo gradually moves to the target angle and holds it.

## ID
roboticArmCANID = 0x100
