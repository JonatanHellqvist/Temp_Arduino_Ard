#include <ArduinoHttpClient.h>
#include <WiFiS3.h>
#include "settings.h"
#include <dht11.h>
#define DHT11PIN 8

dht11 DHT11;

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASSWORD;
 
char serverAdress[] = "orca-app-il7tk.ondigitalocean.app";

int port = 443;

//temp sensor////
// int sensePin = A0;
// int sensorInput;
// double temp;
// double voltage;
/////////////////

WiFiSSLClient wifi;
HttpClient client = HttpClient(wifi, serverAdress, port);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("Ansluter till wifi");
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    
    delay(500);
  }

  Serial.println("Ansluten till WiFi");
}

void loop() {
  int chk = DHT11.read(DHT11PIN);
  // // put your main code here, to run repeatedly:
  
  // String postData = "{\"celsius\":" + String(temp, 1) + "}"; //1 decimal
  String postData = "{\"humidity\":" + String((float)DHT11.humidity, 1) + ", \"celsius\":" + String((float)DHT11.temperature, 1) + "}";
  Serial.print("JSON som skickas: ");
  Serial.println(postData);

  Serial.println("Skickar POST");

  client.beginRequest();
  client.post("/post-dht11-sensor-data");

  client.sendHeader("Content-Type", "application/json");
  client.sendHeader("Content-Length", postData.length());

  client.beginBody();
  client.print(postData);
  client.endRequest();

  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  
  if (statusCode == 200) {
    Serial.print("Status code: ");
    Serial.println(statusCode);
    Serial.print("Response: ");
    Serial.println(response);

    Serial.println();

    Serial.print("Humidity (%): ");
    Serial.println((float)DHT11.humidity, 1);

    Serial.print("Temperature  (C): ");
    Serial.println((float)DHT11.temperature, 1);

    // delay(1800000); //30 min
    delay(900000); //15min
 
  } else if (statusCode == -3) {
    
    Serial.print("Status code: ");
    Serial.println(statusCode);
    Serial.print("Response: ");
    Serial.println(response);
  }
}