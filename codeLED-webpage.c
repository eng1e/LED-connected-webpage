#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const String url = "https://s-m.com.sa/s.html";
String payload = "";
void setup() 
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(27, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(12, OUTPUT);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());

  Serial.print("Fetching " + url + "... ");
}

void loop() {
  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0)
   {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println();
    Serial.println(payload);
    if( payload == "forward" )
    {
      digitalWrite(27, HIGH);
    }
    if( payload == "backward" )
    {
      digitalWrite(12, HIGH);
    }
    if( payload == "right" )
    {
      digitalWrite(33, HIGH);
    }
    if( payload == "left" )
    {
      digitalWrite(25, HIGH);
    }
    
  }
  else 
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    Serial.println(":-(");
  }
}