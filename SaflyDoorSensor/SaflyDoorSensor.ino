#include <ESP8266WiFi.h>

unsigned long previousMillis = 0;
const unsigned long interval = 1000L; // Interval in milliseconds

const char* ssid = "CodeMI5";
const char* password = "inioluwa900";
const char* host = "maker.ifttt.com";

int x = 1;
int flag=0;





void setup()
{
  Serial.begin(115200);
  //Blynk.begin(auth, ssid, pass);
  pinMode(D1,INPUT_PULLUP);

    Serial.println("Email from node mcu");
    delay(100);

    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
//timer.setInterval(16000L,notifyOnButtonPress); 
}

void loop(){
  
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {  
                  Serial.println("connection failed");  
    return;} 
    
  // Check if the interval has elapsed
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the current time


  int isButtonPressed = digitalRead(D1);
  if (isButtonPressed==1 && flag==0) {
    Serial.println("Someone Opened the door");
//    delay(100);
    
        String url = "/trigger/Alert/with/key/g7peItsO1uA_7x17GURH6nlk1rFw0dYXi0SAV0jZP3";
      
      
        Serial.print("Requesting URL: ");
        Serial.println(url);
        
        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +  
                "Connection: close\r\n\r\n");

      flag=1;
  } else if (isButtonPressed==0){
    flag=0;
  } 
 
  
}
delay(500);
} 
