//Hewitt McGaughey
//Wifi Test
//Try resetting WiFi hotspot if it doesn't work at first
//Seems like connections are spotty if there are spaces in the ssid

#include <ESP8266WiFi.h>
const int SENSOR_PIN = A0; //defining pin sensor will read from
int sensValue = 0; //for the value read by the temp sensor
const int threshValue = 300; //threshold for the sensor value

const char* ssid = "hewitt";
const char* pass = "tuif6528";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  Serial.println();
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected to IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(SENSOR_PIN, INPUT); //not sure if needed

}

void loop() {
  /*sensValue = analogRead(SENSOR_PIN); //will be more useful later
  delay(1000);
  Serial.println(sensValue);
  if(sensValue > threshValue)
  {
    Serial.println("Water level too low!");
  }
  */

}
