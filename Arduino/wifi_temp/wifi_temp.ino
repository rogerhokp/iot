//Arduino sketch created by Nikos Georgousis
//Dec 2014
//Based on http://rayshobby.net/?p=9592 example
//Wireless temperature sensor with LM-35 and HlK-RM04

#include <DHT.h>
#define tempSensorPower 7
#define tempSensorPin 6
#define DHTTYPE DHT11
DHT dht(tempSensorPin, DHTTYPE);

float analogVal;
float temp;
float referenceVoltage;
void setup() {
  Serial.begin(57600);
  analogReference(INTERNAL);
  referenceVoltage = 2.00; //Set to 5, 3.3, 2.56 or 1.1 depending on analogReference Setting


  pinMode(tempSensorPin, INPUT);
  pinMode(tempSensorPower, OUTPUT);
  digitalWrite(tempSensorPower, HIGH);
  dht.begin();
}

void loop() {
  boolean has_request = false;
  if (Serial.available()) {
    while (Serial.available()) {
      char c = Serial.read();
    }
    has_request = true;
  }
  if (has_request) {
    Serial.println("HTTP/1.1 200 OK");
    Serial.println("Content-Type: text/html");
    Serial.println("Connection: close");  // the connection will be closed after completion of the response
    Serial.println("Refresh: 5");  // refresh the page automatically every 5 sec

    String sr = "<!DOCTYPE HTML>\n";
    sr += "<html>\n";

    analogVal = 0;
    temp = getHeatIndexInC();


    sr += "<center>";

    sr += "<h1 style=color:blue>";
    sr += temp;

    sr += "</h1>";

    sr += "</center>";

    sr += "</html>";
    Serial.print("Content-Length: ");
    Serial.print(sr.length());
    Serial.print("\r\n\r\n");
    Serial.print(sr);
    has_request = false;
  }

}


float getHeatIndexInC() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  return dht.computeHeatIndex(t, h, false);
}

