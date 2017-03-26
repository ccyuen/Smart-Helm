void initializeBluetooth() {
  Serial1.begin(9600); // ble def. baud
  Serial1.print("AT+CLEAR"); // clear
  Serial1.print("AT+ROLE0"); //edison as slave
  Serial.print("AT+SAVE1"); // proper connection ensurance
}
void listenForBleData() { // updates bluetooth string
  char bData;
  
  if (Serial.available()) {
      bData = Serial.read();
      Serial1.print(bData);
  }

  if (Serial1.available()) {
      bData = Serial1.read();
      Serial.print(bData);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  initializeBluetooth();

}

void loop() {

  listenForBleData();

  delay(50);

}
