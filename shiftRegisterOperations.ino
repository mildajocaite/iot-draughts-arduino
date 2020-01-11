
const byte COL_COUNT = 32;
unsigned int sequence[COL_COUNT] = {0B0000000000000001, 0B0000000000000010, 0B0000000000000100, 0B0000000000001000,
                                    0B0000000000010000, 0B0000000000100000, 0B0000000001000000, 0B0000000010000000,
                                    0B0000000100000000, 0B0000001000000000, 0B0000010000000000, 0B0000100000000000,
                                    0B0001000000000000, 0B0010000000000000, 0B0100000000000000, 0B1000000000000000
                                   };

void updateFirstShiftRegister(int value) {
  digitalWrite(latchFirstShiftRegister, LOW);
  shiftOut(dataFirstShiftRegister, clockFirstShiftRegister, MSBFIRST, value);
  digitalWrite(latchFirstShiftRegister, HIGH);
}

void changePowerStateFirstShiftRegister(int rfidNumber, int state) {
  digitalWrite(latchFirstShiftRegister, LOW);
  shiftOut(dataFirstShiftRegister, clockFirstShiftRegister, MSBFIRST, (sequence[rfidNumber] >> 8));
  shiftOut(dataFirstShiftRegister, clockFirstShiftRegister, MSBFIRST, sequence[rfidNumber]);
  digitalWrite(latchFirstShiftRegister, HIGH);
}

void turnOffAllFirstRegister() {
  digitalWrite(latchFirstShiftRegister, LOW);
  shiftOut(dataFirstShiftRegister, clockFirstShiftRegister, MSBFIRST, (0B0000000000000000 >> 8));
  shiftOut(dataFirstShiftRegister, clockFirstShiftRegister, MSBFIRST, 0B0000000000000000);
  digitalWrite(latchFirstShiftRegister, HIGH);
}

void updateSecondShiftRegister(int value) {
  digitalWrite(latch2, LOW);
  shiftOut(data2, clock2, MSBFIRST, value);
  digitalWrite(latch2, HIGH);
}

void changePowerStateSecondShiftRegister(int rfidNumber, int state) {
  digitalWrite(latch2, LOW);
  shiftOut(data2, clock2, MSBFIRST, (sequence[rfidNumber] >> 8));
  shiftOut(data2, clock2, MSBFIRST, sequence[rfidNumber]);
  digitalWrite(latch2, HIGH);
}

void turnOffAllSecondShiftRegister() {
  digitalWrite(latch2, LOW);
  shiftOut(data2, clock2, MSBFIRST, (0B0000000000000000 >> 8));
  shiftOut(data2, clock2, MSBFIRST, 0B0000000000000000);
  digitalWrite(latch2, HIGH);
}
