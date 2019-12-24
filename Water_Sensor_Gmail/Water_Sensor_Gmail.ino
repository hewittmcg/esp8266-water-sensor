//Hewitt McGaughey
//Dec 10, 2019
//Modified general template

//Try resetting WiFi hotspot if it doesn't work at first
//Seems like connections are spotty if there are spaces in the ssid
//If using SMTP2GO, this will throw an Error: 550 unless you contact support and ask them to set up your account to send emails without a sender domain connected to it

#include <ESP8266WiFi.h>

const int SENSOR_PIN = A0; //defining pin sensor will read from
int sensValue = 0; //for the value read by the temp sensor
const int threshValue = 300;

char server[] = "mail.smtp2go.com"; //server used to send emails

const char* ssid = "YOUR SSID"; //enter wifi ssid
const char* pass = "YOUR PASSWORD"; //enter password

WiFiClient espClient; //creates new client to be used with server

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  Serial.println();
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected to IP address: ");
  Serial.println(WiFi.localIP());
  //byte ret = sendEmail(); debugging only
  delay(5000);
  Serial.println("Starting email send test...");
  sensValue = analogRead(SENSOR_PIN); 
  Serial.println(sensValue);
  if(sensValue > threshValue)
  {
    sendEmail();
   
  }

}

void loop() {
 //code will be added here with delays between emails later
}

//below functions taken from https://www.electronicshub.org/send-an-email-using-esp8266/.
//they've been modified slightly to work with this use case and condensed in some cases
//I've also added some more info to make these easier to understand in the future

byte sendEmail() //sends an email with a pre-generated message notifying the user of the water level

{

  if (espClient.connect(server, 2525) == 1) //connecting to port 2525.  
  //note: 8025, 587, 80, 25 (TLS); 443, 465, 8456 (SSL) should work as well
  {
    Serial.println(F("Connected to SMTP Server"));
  }
  else
  {
    Serial.println(F("Connection to SMTP Server Failed"));
    return 0;
  }

  if (!serverResp())
    return 0;

  Serial.println(F("Sending EHLO"));
  espClient.println("EHLO www.example.com");

  if (!serverResp())
    return 0;

  Serial.println(F("Sending auth login"));
  espClient.println("AUTH LOGIN");

  if (!serverResp())
    return 0;

  Serial.println(F("Sending User"));
  espClient.println("YOUR USERNAME"); // username for smtp2go account IN BASE 64

  if (!serverResp())
    return 0;

  Serial.println(F("Sending Password"));
  espClient.println("YOUR PASSWORD");// Password for smtp2go account IN BASE 64

  if (!serverResp())
    return 0;

  Serial.println(F("Sending From"));
  espClient.println(F("MAIL From: SENDER_EMAIL_HERE")); // Enter Sender Mail Id

  if (!serverResp())
    return 0;

  Serial.println(F("Sending To"));
  espClient.println(F("RCPT To: RECEIVER_EMAIL_HERE")); // Enter Receiver Mail Id

  if (!serverResp())
    return 0;
    
  Serial.println(F("Sending DATA"));
  espClient.println(F("DATA"));
  
  if (!serverResp())
    return 0;
    
  Serial.println(F("Sending email"));

  espClient.println(F("To:  RECEIVER_EMAIL_HERE")); // Enter Receiver Mail Id

  espClient.println(F("From: SENDER_MAIL_HERE")); // Enter Sender Mail Id

  espClient.println(F("Subject: Water Level Warning\r\n"));

  espClient.println(F("The water level has been measured as being below the given threshold.\n"));
  //
  espClient.println(F(".")); //to end email text
  if (!serverResp())
    return 0;
  //
  Serial.println(F("Sending QUIT"));
  espClient.println(F("QUIT"));
  if (!serverResp())
    return 0;
  //
  espClient.stop();
  Serial.println(F("Disconnected"));
  return 1;
}
byte serverResp() //checks connection to server, returns any responses
{
  byte responseCode, readByte;
  int loopCount = 0;
  
  while (!espClient.available()) //waiting for server to be available
  {
    delay(1);
    loopCount++;
    if (loopCount > 20000)
    {
      espClient.stop();
      Serial.println(F("\r\nTimeout"));
      return 0;
    }
  }
  
  responseCode = espClient.peek();
  while (espClient.available())
  {
    readByte = espClient.read();
    Serial.write(readByte);
  }
  
  if (responseCode >= '4')
    return 0;
  return 1;
}
