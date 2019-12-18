//Hewitt McGaughey
const int SENSOR_PIN = A0; //defining pin sensor will read from

int sensValue = 0; //for the value read by the temp sensor


void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT);

}

void loop() {
  sensValue = analogRead(SENSOR_PIN); //will be more useful later
  delay(1000);
  Serial.println(sensValue);

}
