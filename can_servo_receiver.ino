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

void moveServoSmoothly(int targetAngle) {
  if (targetAngle < 0) targetAngle = 0;
  if (targetAngle > 180) targetAngle = 180;

  if (targetAngle == currentAngle) return;

  int step = (targetAngle > currentAngle) ? 1 : -1;
  for (int angle = currentAngle; angle != targetAngle; angle += step) {
    roboticArmServo.write(angle);
    delay(10); // Adjust for smoother/faster movement
  }
  roboticArmServo.write(targetAngle); // Final adjustment
  currentAngle = targetAngle;
}

void loop() {
  CANMessage msg;
  if (ACAN_ESP32::can.receive(msg)) {
    if (msg.id == roboticArmCANID && msg.len == 1) {
      uint8_t targetAngle = msg.data[0];
      Serial.print("Received angle: ");
      Serial.println(targetAngle);
      moveServoSmoothly(targetAngle);
    }
  }
}