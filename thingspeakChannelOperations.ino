void updateThingspeakChannel() {
  
  Serial.println(row1);
  Serial.println(row2);
  Serial.println(row3);
  Serial.println(row4);
  Serial.println(row5);
  Serial.println(row6);
  Serial.println(row7);
  Serial.println(row8);
  //Set the fields
  ThingSpeak.setField(1, row1);
  ThingSpeak.setField(2, row2);
  ThingSpeak.setField(3, row3);
  ThingSpeak.setField(4, row4);
  ThingSpeak.setField(5, row5);
  ThingSpeak.setField(6, row6);
  ThingSpeak.setField(7, row7);
  ThingSpeak.setField(8, row8);
  ThingSpeak.setStatus("Board position");

  int responseCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (responseCode == 200) {
    Serial.println("Channel update successful.");
  }
  else {
    Serial.println("Problem updating channel. HTTP error code " + String(responseCode));
  }
}
