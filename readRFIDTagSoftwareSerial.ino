
long extractRfidTag(SoftwareSerial &softwareSerialRfid) {
  uint8_t buffer[14];
  bool callGetTag = false;
  int bufferIndex = 0;
  int currentValue;
  softwareSerialRfid.listen();
  delay(1000);
  while ((softwareSerialRfid.available() > 0)) {
    currentValue = softwareSerialRfid.read();
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

long extract_tag(uint8_t buffer []) {
  uint8_t *msg_data = buffer + 1;
  uint8_t *msg_data_tag = msg_data + 2;
  uint8_t *msg_checksum = buffer + 11;
  long tag = getTagValue(msg_data_tag, 8);
  long checksum = 0;
  for (int i = 0; i < 10; i += 2) {
    long val = getTagValue(msg_data + i, 2);
    checksum ^= val;
  }
  if (checksum == getTagValue(msg_checksum, 2)) {
    return tag;
  }
  else {
    Serial.println("Error!");
    return 0;
  }
}

long getTagValue(char *str, unsigned int length) {
  char* copy = malloc((sizeof(char) * length) + 1);
  memcpy(copy, str, sizeof(char) * length);
  copy[length] = '\0';
  long value = strtol(copy, NULL, 16);
  free(copy);
  return value;
}

void clearSerial(SoftwareSerial &softwareSerialRfid) {
  while ((softwareSerialRfid.available() > 0)) {
    softwareSerialRfid.read();
  }
}
