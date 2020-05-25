void connectToMQTTClient() {
  while (!mqttClient.connected())
  {

    String clientName = "Thingspeak-889998";
    Serial.print("Connecting to ");
    Serial.print(server);
    Serial.print(" as ");
    Serial.println(clientName);

    if (mqttClient.connect((char*) clientName.c_str())) {
      Serial.println("Connected to MQTT broker.");
      Serial.print("Topic is: ");
      Serial.println(topic);
    }
    else {
      Serial.println("MQTT connect failed");
      abort();
    }
  }
}

void publishData() {

  Serial.println(row1);
  Serial.println(row2);
  Serial.println(row3);
  Serial.println(row4);
  Serial.println(row5);
  Serial.println(row6);
  Serial.println(row7);
  Serial.println(row8);

  if (!mqttClient.connected())
  {
    connectToMQTTClient();
  }
  String data;
  data += "&field1=";
  data += row1;
  data += "&field2=";
  data += row2;
  data += "&field3=";
  data += row3;
  data += "&field4=";
  data += row4;
  data += "&field5=";
  data += row5;
  data += "&field6=";
  data += row6;
  data += "&field7=";
  data += row7;
  data += "&field8=";
  data += row8;
  data += "&status=MQTTPUBLISH";

  if (mqttClient.connected()) {
    Serial.print("Publishing data: ");
    Serial.println(data);

    if (mqttClient.publish(topic, (char*) data.c_str())) {
      Serial.println("Successfully published.");
    }
    else {
      Serial.println("Publish failed.");
      Serial.print(mqttClient.state());
    }
  }
}
