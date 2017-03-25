
//Check later for error with slave
void setup() {
  Serial.begin(9600);

  Serial1.begin(9600);// ble default baud
  Serial1.print("AT+CLEAR"); //clear
  Serial1.print("AT+ROLE0"); // edison as slave
  Serial.print("AT+SAVE1"); // make sure connection settings are proper

}

char rev;

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available()) {
    rev = Serial.read();
    Serial1.print(rev);
  }

  if (Serial1.available()) {
    rev = Serial1.read();
    Serial.print(rev);
  }

}
