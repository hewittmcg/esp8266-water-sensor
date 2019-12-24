//Hewitt McGaughey
//For use with arduino currently
const int SENSOR_PIN = A0; //defining pin sensor will read from
int sensValue = 0; //for the value read by the temp sensor
const int threshValue = 300; //threshold for the sensor value

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT); //not sure if needed

}

void loop() {
  sensValue = analogRead(SENSOR_PIN); //will be more useful later
  delay(1000);
  Serial.println(sensValue);
  if(sensValue > threshValue)
  {
    Serial.println("Water level too low!");
  }

}
