# ESP32 CAN Servo Receiver

This file receives angle values over the CAN bus using ESP32 and rotates a servo motor accordingly.

## Wiring Summary
- CAN RX: GPIO 4
- CAN TX: GPIO 5
- Servo signal pin: GPIO 18

## Required Libraries
Required Libraries:

1. ACAN_ESP32 by Pierre Molinaro
   Installation:
   - Download from: https://github.com/pierremolinaro/ACAN_ESP32
   - Open Arduino IDE
   - Go to Sketch -> include libraries -> add zip file and select the downloaded file.

2. ESP32Servo by Kevin Harrington, John K. Bennett
   Installation:
   - Search for "ESP32Servo" in Arduino Library Manager and install.


## How it works
The receiver listens for CAN messages containing a single byte (0–180) representing the servo angle. Upon receiving a new value, the servo gradually moves to the target angle and holds it.

## ID
roboticArmCANID = 0x100