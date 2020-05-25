
#include "WiFiEsp.h"
#include "SoftwareSerial.h"
#include "PubSubClient.h"

#ifndef HAVE_HWSERIAL1
//HardwareSerial pins for RFID readers
SoftwareSerial Serial1(18, 19); // RX, TX
SoftwareSerial Serial2(17, 16); // RX, TX
SoftwareSerial Serial3(15, 14); // RX, TX
#endif

//Pins for RFID readers
SoftwareSerial Ser1 = SoftwareSerial(10, 22);
SoftwareSerial Ser2 = SoftwareSerial(11, 22);
SoftwareSerial Ser3 = SoftwareSerial(12, 22);
SoftwareSerial Ser4 = SoftwareSerial(13, 22);
SoftwareSerial Ser5 = SoftwareSerial(62, 22);
SoftwareSerial Ser6 = SoftwareSerial(63, 22);
SoftwareSerial Ser7 = SoftwareSerial(64, 22);
SoftwareSerial Ser8 = SoftwareSerial(65, 22);
SoftwareSerial Ser9 = SoftwareSerial(66, 22);
SoftwareSerial Ser10 = SoftwareSerial(67, 22);
SoftwareSerial Ser11 = SoftwareSerial(68, 22);
SoftwareSerial Ser12 = SoftwareSerial(69, 22);
SoftwareSerial Ser13 = SoftwareSerial(50, 22);
SoftwareSerial Ser14 = SoftwareSerial(51, 22);
SoftwareSerial Ser15 = SoftwareSerial(52, 22);
SoftwareSerial Ser16 = SoftwareSerial(53, 22);

WiFiEspClient client;
PubSubClient mqttClient(client);

//First Shift Register pins
int dataFirstShiftRegister = 22;
int clockFirstShiftRegister = 24;
int latchFirstShiftRegister = 26;

//Second Shift Register pins
int data2 = 23;
int clock2 = 27;
int latch2 = 29;

// First Mux  pins
int firstMuxPin0 = 28;
int firstMuxPin1 = 30;
int firstMuxPin2 = 32;
int firstMuxPin3 = 34;

// Second Mux control pins
int secondMuxPin0 = 31;
int secondMuxPin1 = 33;
int secondMuxPin2 = 35;
int secondMuxPin3 = 37;

//Constants for shift register (turn on and turn off)
const int ON = HIGH;
const int OFF = LOW;

int powerState = 0;
const int BUFFER_SIZE = 14; // RFID DATA FRAME FORMAT: 1byte head (value: 2), 10byte data (2byte version + 8byte tag), 2byte checksum, 1byte tail (value: 3)
const int DATA_SIZE = 10; // 10byte data (2byte version + 8byte tag)
const int DATA_VERSION_SIZE = 2; // 2byte version (actual meaning of these two bytes may vary)
const int DATA_TAG_SIZE = 8; // 8byte tag
const int CHECKSUM_SIZE = 2; // 2byte checksum
uint8_t buffer[BUFFER_SIZE]; // used to store an incoming data frame
int buffer_index = 0;

char* topic = "channels/889998/publish/1KCIJE0V56IGASY6";
char* server = "mqtt.thingspeak.com";

long row1;
long row2;
long row3;
long row4;
long row5;
long row6;
long row7;
long row8;

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial2.begin(9600);
  Serial3.begin(9600);

  WiFi.init(&Serial1);
  Serial.print("Searching for ESP8266...");
  WiFi.init(&Serial1);
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }
  Serial.println("WiFi shield exists.");
  mqttClient.setServer(server, 1883);

  //Initiate RFID readers
  Ser1.begin(9600);
  Ser2.begin(9600);
  Ser3.begin(9600);
  Ser4.begin(9600);
  Ser5.begin(9600);
  Ser6.begin(9600);
  Ser7.begin(9600);
  Ser8.begin(9600);
  Ser9.begin(9600);
  Ser10.begin(9600);
  Ser11.begin(9600);
  Ser12.begin(9600);
  Ser13.begin(9600);
  Ser14.begin(9600);
  Ser15.begin(9600);
  Ser16.begin(9600);

  //First Shift Register
  pinMode(dataFirstShiftRegister, OUTPUT);
  pinMode(clockFirstShiftRegister, OUTPUT);
  pinMode(latchFirstShiftRegister, OUTPUT);

  //Second Shift Register
  pinMode(data2, OUTPUT);
  pinMode(clock2, OUTPUT);
  pinMode(latch2, OUTPUT);

  //First Mux
  pinMode(firstMuxPin0, OUTPUT);
  pinMode(firstMuxPin1, OUTPUT);
  pinMode(firstMuxPin2, OUTPUT);
  pinMode(firstMuxPin3, OUTPUT);
  digitalWrite(firstMuxPin0, LOW);
  digitalWrite(firstMuxPin1, LOW);
  digitalWrite(firstMuxPin2, LOW);
  digitalWrite(firstMuxPin3, LOW);

  //Second Mux
  pinMode(secondMuxPin0, OUTPUT);
  pinMode(secondMuxPin1, OUTPUT);
  pinMode(secondMuxPin2, OUTPUT);
  pinMode(secondMuxPin3, OUTPUT);
  digitalWrite(secondMuxPin0, LOW);
  digitalWrite(secondMuxPin1, LOW);
  digitalWrite(secondMuxPin2, LOW);
  digitalWrite(secondMuxPin3, LOW);
}

void loop() {

  connectToWifi();
  row1 = 0;
  row2 = 0;
  row3 = 0;
  row4 = 0;
  row5 = 0;
  row6 = 0;
  row7 = 0;
  row8 = 0;

  //Turn off all rfid readers
  turnOffAllFirstRegister();
  turnOffAllSecondShiftRegister();

  changePowerStateFirstShiftRegister(0, ON);
  long a1 = extractRfidTag(Ser1);
  Serial.print("A1 tag: ");
  Serial.println(a1);
  row1 += returnDraughtType(a1) * 1000;
  turnOffAllFirstRegister();
  clearSerial(Ser1);

  changePowerStateFirstShiftRegister(1, ON);
  long c1 = extractRfidTag(Ser2);
  Serial.print("C1 tag: ");
  Serial.println(c1);
  row1 += returnDraughtType(c1) * 100;
  turnOffAllFirstRegister();
  clearSerial(Ser2);

  changePowerStateFirstShiftRegister(2, ON);
  long e1 = extractRfidTag(Ser3);
  Serial.print("E1 tag: ");
  Serial.println(e1);
  row1 += returnDraughtType(e1) * 10;
  turnOffAllFirstRegister();
  clearSerial(Ser3);

  changePowerStateFirstShiftRegister(3, ON);
  long g1 = extractRfidTag(Ser4);
  Serial.print("G1 tag: ");
  Serial.println(g1);
  row1 += returnDraughtType(g1);
  turnOffAllFirstRegister();
  clearSerial(Ser4);

  changePowerStateFirstShiftRegister(4, ON);
  long h2 = extractRfidTag(Ser5);
  Serial.print("H2 tag: ");
  Serial.println(h2);
  row2 += returnDraughtType(h2);
  turnOffAllFirstRegister();
  clearSerial(Ser5);

  changePowerStateFirstShiftRegister(5, ON);
  long f2 = extractRfidTag(Ser6);
  Serial.print("F2 tag: ");
  Serial.println(f2);
  row2 += returnDraughtType(f2) * 10;
  turnOffAllFirstRegister();
  clearSerial(Ser6);

  changePowerStateFirstShiftRegister(6, ON);
  long d2 = extractRfidTag(Ser7);
  Serial.print("D2 tag: ");
  Serial.println(d2);
  row2 += returnDraughtType(d2) * 100;
  turnOffAllFirstRegister();
  clearSerial(Ser7);

  changePowerStateFirstShiftRegister(7, ON);
  long b2 = extractRfidTag(Ser8);
  Serial.print("B2 tag: ");
  Serial.println(b2);
  row2 += returnDraughtType(b2) * 1000;
  turnOffAllFirstRegister();
  clearSerial(Ser8);

  changePowerStateFirstShiftRegister(8, ON);
  long g3 = extractRfidTag(Ser9);
  Serial.print("G3 tag: ");
  Serial.println(g3);
  row3 += returnDraughtType(g3);
  turnOffAllFirstRegister();
  clearSerial(Ser9);

  changePowerStateFirstShiftRegister(9, ON);
  long e3 = extractRfidTag(Ser10);
  Serial.print("E3 tag: ");
  Serial.println(e3);
  row3 += returnDraughtType(e3) * 10;
  turnOffAllFirstRegister();
  clearSerial(Ser10);

  changePowerStateFirstShiftRegister(10, ON);
  long c3 = extractRfidTag(Ser11);
  Serial.print("C3 tag: ");
  Serial.println(c3);
  row3 += returnDraughtType(c3) * 100;
  turnOffAllFirstRegister();
  clearSerial(Ser11);

  changePowerStateFirstShiftRegister(11, ON);
  long a3 = extractRfidTag(Ser12);
  Serial.print("A3 tag:");
  Serial.println(a3);
  row3 += returnDraughtType(a3) * 1000;
  turnOffAllFirstRegister();
  clearSerial(Ser12);

  setFirstMux(0);
  changePowerStateFirstShiftRegister(12, ON);
  long h4 = extractRfidTagSerial2();
  Serial.print("H4 tag:");
  Serial.println(h4);
  row4 += returnDraughtType(h4);
  turnOffAllFirstRegister();
  clearSerial2();

  setFirstMux(1);
  changePowerStateFirstShiftRegister(13, ON);
  long f4 = extractRfidTagSerial2();
  Serial.print("F4 tag:");
  Serial.println(f4);
  row4 += returnDraughtType(f4) * 10;
  turnOffAllFirstRegister();
  clearSerial2();


  setFirstMux(2);
  changePowerStateFirstShiftRegister(14, ON);
  long c4 = extractRfidTagSerial2();
  Serial.print("C4 tag:");
  Serial.println(c4);
  row4 += returnDraughtType(c4) * 100;
  turnOffAllFirstRegister();
  clearSerial2();


  setFirstMux(3);
  changePowerStateFirstShiftRegister(15, ON);
  long b4 = extractRfidTagSerial2();
  Serial.print("B4 tag:");
  Serial.println(b4);
  row4 += returnDraughtType(b4) * 1000;
  turnOffAllFirstRegister();
  clearSerial2();


  setFirstMux(4);
  changePowerStateSecondShiftRegister(0, ON);
  long g5 = extractRfidTagSerial2();
  Serial.print("G5 tag:");
  Serial.println(g5);
  row5 += returnDraughtType(g5);
  turnOffAllSecondShiftRegister();
  clearSerial2();


  setFirstMux(5);
  changePowerStateSecondShiftRegister(1, ON);
  long e5 = extractRfidTagSerial2();
  Serial.print("E5 tag:");
  Serial.println(e5);
  row5 += returnDraughtType(e5) * 10;
  turnOffAllSecondShiftRegister();
  clearSerial2();


  setFirstMux(6);
  changePowerStateSecondShiftRegister(2, ON);
  long c5 = extractRfidTagSerial2();
  Serial.print("C5 tag:");
  Serial.println(c5);
  row5 += returnDraughtType(c5) * 100;
  turnOffAllSecondShiftRegister();
  clearSerial2();

  setFirstMux(7);
  changePowerStateSecondShiftRegister(3, ON);
  long a5 = extractRfidTagSerial2();
  Serial.print("A5 tag:");
  Serial.println(a5);
  row5 += returnDraughtType(a5) * 1000;
  turnOffAllSecondShiftRegister();
  clearSerial2();

  setSecondMux(0);
  changePowerStateSecondShiftRegister(4, ON);
  long h6 = extractRfidTagSerial3();
  Serial.print("H6 tag:");
  Serial.println(h6);
  row6 += returnDraughtType(h6);
  turnOffAllSecondShiftRegister();
  clearSerial3();

  setSecondMux(1);
  changePowerStateSecondShiftRegister(5, ON);
  long f6 = extractRfidTagSerial3();
  Serial.print("F6 tag:");
  Serial.println(f6);
  row6 += returnDraughtType(f6) * 10;
  turnOffAllSecondShiftRegister();
  clearSerial3();

  setSecondMux(2);
  changePowerStateSecondShiftRegister(6, ON);
  long d6 = extractRfidTagSerial3();
  Serial.print("D6 tag:");
  Serial.println(d6);
  row6 += returnDraughtType(d6) * 100;
  turnOffAllSecondShiftRegister();
  clearSerial3();

  setSecondMux(3);
  changePowerStateSecondShiftRegister(7, ON);
  long b6 = extractRfidTagSerial3();
  Serial.print("B6 tag:");
  Serial.println(b6);
  row6 += returnDraughtType(b6) * 1000;
  turnOffAllSecondShiftRegister();
  clearSerial3();

  setSecondMux(4);
  changePowerStateSecondShiftRegister(8, ON);
  long g7 = extractRfidTagSerial3();
  Serial.print("G7 tag:");
  Serial.println(g7);
  row7 += returnDraughtType(g7);
  turnOffAllSecondShiftRegister();
  clearSerial3();

  changePowerStateSecondShiftRegister(9, ON);
  long e7 = extractRfidTag(Ser14);
  Serial.print("E7 tag:");
  Serial.println(e7);
  row7 += returnDraughtType(e7) * 10;
  turnOffAllSecondShiftRegister();
  extractRfidTag(Ser14);
  clearSerial(Ser14);

  setSecondMux(5);
  turnOffAllSecondShiftRegister();
  changePowerStateSecondShiftRegister(10, ON);
  long c7 =  extractRfidTagSerial3();
  Serial.print("C7 tag:");
  Serial.println(c7);
  row7 += returnDraughtType(c7) * 100;
  turnOffAllSecondShiftRegister();
  clearSerial3();

  setSecondMux(6);
  changePowerStateSecondShiftRegister(11, ON);
  long a7 = extractRfidTagSerial3();
  Serial.print("A7 tag:");
  Serial.println(a7);
  row7 += returnDraughtType(a7) * 1000;
  turnOffAllSecondShiftRegister();
  clearSerial3();

  setSecondMux(7);
  changePowerStateSecondShiftRegister(12, ON);
  long h8 = extractRfidTagSerial3();
  Serial.print("H8 tag:");
  Serial.println(h8);
  row8 += returnDraughtType(h8);
  turnOffAllSecondShiftRegister();
  clearSerial3();

  changePowerStateSecondShiftRegister(13, ON);
  long f8 = extractRfidTag(Ser13);
  Serial.print("F8 tag:");
  Serial.println(f8);
  row8 += returnDraughtType(f8) * 10;
  turnOffAllSecondShiftRegister();
  extractRfidTag(Ser13);
  clearSerial(Ser13);

  changePowerStateSecondShiftRegister(14, ON);
  long d8 = extractRfidTag(Ser15);
  Serial.print("D8 tag:");
  Serial.println(d8);
  row8 += returnDraughtType(d8) * 100;
  turnOffAllSecondShiftRegister();
  clearSerial(Ser15);

  changePowerStateSecondShiftRegister(15, ON);
  long b8 = extractRfidTag(Ser16);
  Serial.print("B8 tag:");
  Serial.println(b8);
  row8 += returnDraughtType(b8) * 1000;
  turnOffAllSecondShiftRegister();
  clearSerial(Ser16);

  publishData();
}
