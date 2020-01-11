
long extractRfidTagSerial2() {
  uint8_t buffer[14];
  bool callGetTag = false;
  int bufferIndex = 0;
  int currentValue;
  delay(1000);
  while ((Serial2.available() > 0)) {
    currentValue = Serial2.read();
    if (currentValue == 2) {
      bufferIndex = 0;
    }
    if (currentValue == 3) {
      callGetTag = true;
    }
    buffer[bufferIndex++] = currentValue;
    if (callGetTag == true) {
      if (bufferIndex == 14) {
        long tag = extract_tag(buffer);
        return tag;
      }
      else {
        // Something is wrong
        bufferIndex = 0;
      }
    }
  }
  return 0; 
}

void clearSerial2() {
  while (Serial2.available() > 0) {
    char symbol = Serial2.read();
  }
}

long extractRfidTagSerial3() {
  uint8_t buffer[14];
  bool callGetTag = false;
  int bufferIndex = 0;
  int currentValue;
  delay(1000);
  while ((Serial3.available() > 0)) {
    currentValue = Serial3.read();
    if (currentValue == 2) {
      bufferIndex = 0;
    }
    if (currentValue == 3) {
      callGetTag = true;
    }
    buffer[bufferIndex++] = currentValue;
    if (callGetTag == true) {
      if (bufferIndex == 14) {
        long tag = extract_tag(buffer);
        return tag;
      }
      else {
        // Something is wrong
        bufferIndex = 0;
      }
    }
  }
  return 0;
}

void clearSerial3() {
  while (Serial3.available() > 0) {
    char symbol = Serial3.read();
  }
}
