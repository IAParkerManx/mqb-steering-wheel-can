void canInit() {
  chassisCAN.setRX(pinCAN_RX);
  chassisCAN.setTX(pinCAN_TX);
  chassisCAN.begin();
  chassisCAN.setBaudRate(500000);
  chassisCAN.onReceive(onBodyRX);
}

void onBodyRX(const CAN_message_t& frame) {
#if ChassisCANDebug
  Serial.print("Length Recv: ");
  Serial.print(frame.len);
  Serial.print(" CAN ID: ");
  Serial.print(frame.id, HEX);
  Serial.print(" Buffer: ");
  for (uint8_t i = 0; i < frame.len; i++) {
    Serial.print(frame.buf[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
#endif
}

void broadcastButtonsCAN() {
  CAN_message_t broadcastCAN;
  broadcastCAN.id = canButtonID;
  broadcastCAN.len = 8;

  if (transButtonDataCAN[1] != 0) {
    broadcastCAN.buf[1] = transButtonDataCAN[1];
  }

  if (!chassisCAN.write(broadcastCAN)) {
    Serial.println(F("Chassis CAN Write TX Fail!"));
  }
}

void sendPaddleUpFrame() {
  CAN_message_t paddlesUp;
  paddlesUp.id = GRA_ID;
  paddlesUp.len = 8;
  paddlesUp.buf[0] = 0xB7;
  paddlesUp.buf[2] = 0x34;
  paddlesUp.buf[3] = 0x02;

  bitSet(paddlesUp.buf[3], 1);
  if (!chassisCAN.write(paddlesUp)) {
    Serial.println("Upshift Trigger Failed");
  }

  delay(100);

  bitClear(paddlesUp.buf[3], 1);
  if (!chassisCAN.write(paddlesUp)) {
    Serial.println("Upshift Clear Failed");
  }

  dsgPaddleUp = false;
  Serial.println("Sent shift up message");
}

void sendPaddleDownFrame() {
  CAN_message_t paddlesDown;
  paddlesDown.id = GRA_ID;
  paddlesDown.len = 8;
  paddlesDown.buf[0] = 0xB4;
  paddlesDown.buf[2] = 0x34;
  paddlesDown.buf[3] = 0x01;

  bitSet(paddlesDown.buf[3], 1);
  if (!chassisCAN.write(paddlesDown)) {
    Serial.println("Downshift Trigger Failed");
  }

  delay(100);

  bitClear(paddlesDown.buf[3], 1);
  if (!chassisCAN.write(paddlesDown)) {
    Serial.println("Downshift Clear Failed");
  }

  dsgPaddleDown = false;
  Serial.println("Sent shift down message");
}
