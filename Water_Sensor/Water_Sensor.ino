//just placeholder code to initialize with github
//testing 


const int SENSOR_PIN = A0; //defining pin sensor will read from

int sensValue = 0; //for the value read by the temp sensor


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  sensValue = analogRead(SENSOR_PIN); //will be more useful later
  delay(1000);
  Serial.println(sensValue);

}
