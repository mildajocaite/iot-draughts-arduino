void connectToWifi(){
  char network_name[] = "MW40V_47BC";
  char password[] = "04667337"; 
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to wifi: ");
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(network_name, password); 
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
}
