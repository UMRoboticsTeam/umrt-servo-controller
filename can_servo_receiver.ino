#include <ACAN_ESP32.h>
#include <ESP32Servo.h>

Servo roboticArmServo;

const int servoPin = 18;
const uint32_t roboticArmCANID = 0x100;

void setup () {
  Serial.begin(115200);

  roboticArmServo.setPeriodHertz(50);
  roboticArmServo.attach(servoPin, 500, 2400);

  ACAN_ESP32_Settings settings(500 * 1000); // 500 kbps
  const uint32_t error = ACAN_ESP32::can.begin(settings);
  if (error == 0) {
    Serial.println("CAN initialized successfully.");
  } else {
    Serial.print("CAN init failed. Error code: ");
    Serial.println(error, HEX);
  }
}

void loop () {
  CANMessage msg;
  if (ACAN_ESP32::can.receive(msg)) {
    if (msg.id == roboticArmCANID && msg.len == 1) {
      uint8_t angle = msg.data[0];
      Serial.print("Received angle: ");
      Serial.println(angle);
      roboticArmServo.write(angle);
    }
  }
}
