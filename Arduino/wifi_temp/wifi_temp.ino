//Arduino sketch created by Nikos Georgousis
//Dec 2014
//Based on http://rayshobby.net/?p=9592 example
//Wireless temperature sensor with LM-35 and HlK-RM04


#include <DHT.h>
#define highLightPin 2
#define normalLightPin 3
#define lowLightPin 4
#define switchPin 8
#define switchNoti 9
#define tempSensorPower 7
#define tempSensorPin 6
#define DHTTYPE DHT11
DHT dht(tempSensorPin, DHTTYPE);

float analogVal;
float temp;
float referenceVoltage;
void setup() {
  Serial.begin(57600);
  sprintln("starting....");

  referenceVoltage = 2.00; //Set to 5, 3.3, 2.56 or 1.1 depending on analogReference Setting

  pinMode(switchPin, INPUT);
  pinMode(switchNoti, OUTPUT);
  pinMode(tempSensorPin, INPUT);
  pinMode(tempSensorPower, OUTPUT);
  pinMode(highLightPin, OUTPUT);
  pinMode(normalLightPin, OUTPUT);
  pinMode(lowLightPin, OUTPUT);
  digitalWrite(tempSensorPower, HIGH);
  dht.begin();
  sprintln("setup finished");
}

boolean sendOn = true;
long count = 0L;
long sendInterval = 60000L;
int delayMs = 100;

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float hi = dht.computeHeatIndex(t, h, false);

  if (sendOn && count == sendInterval && Serial) {
    postToServer(
      "/temperature",
      "iot-rogerhokp.rhcloud.com",
      "{\"humidity\": " + String(h) + ", \"temperature\":" + String(t) + ", \"heat_index\":" + String(hi) + "}",
      "application/json; charset=utf-8"
    );
  }
  if (count == sendInterval) {
    count = 0L;
  }


  if (digitalRead(switchPin) == HIGH) {
    sendOn = !sendOn;
    sprintln("switch");
    delay(900);
    count = 0L;
  }

  if (sendOn) {
    digitalWrite(switchNoti, HIGH);
  } else {
    digitalWrite(switchNoti, LOW);
  }

  if (hi > 32 ) {
    digitalWrite(highLightPin, HIGH);
    digitalWrite(normalLightPin, LOW);
    digitalWrite(lowLightPin, LOW);
  } else if (hi > 25) {
    digitalWrite(highLightPin, LOW);
    digitalWrite(normalLightPin, HIGH);
    digitalWrite(lowLightPin, LOW);
  } else {
    digitalWrite(highLightPin, LOW);
    digitalWrite(normalLightPin, LOW);
    digitalWrite(lowLightPin, HIGH);
  }



  count += delayMs;

  delay(delayMs);

  //  if (Serial.available()) {
  //
  //    sprintln("send to Server");
  //
  //    sprintln("send to Server end");
  //    while (Serial.available()) {
  //      char c = Serial.read();
  //    }
  //    has_request = true;
  //  }
  //  if (false && has_request) {
  //    Serial.println("HTTP/1.1 200 OK");
  //    Serial.println("Content-Type: text/html");
  //    Serial.println("Connection: close");  // the connection will be closed after completion of the response
  //    Serial.println("Refresh: 5");  // refresh the page automatically every 5 sec
  //
  //    String sr = "<!DOCTYPE HTML>\n";
  //    sr += "<html>\n";
  //
  //    analogVal = 0;
  //    temp = getHeatIndexInC();
  //
  //
  //    sr += "<center>";
  //
  //    sr += "<h1 style=color:blue>";
  //    sr += temp;
  //
  //    sr += "</h1>";
  //
  //    sr += "</center>";
  //
  //    sr += "</html>";
  //    Serial.print("Content-Length: ");
  //    Serial.print(sr.length());
  //    Serial.print("\r\n\r\n");
  //    Serial.print(sr);
  //    has_request = false;
  //  }

}





/////////////Helper function


void postToServer(String path, String host, String data, String contentType) {


  /*

    POST /temperature HTTP/1.1
    Host: iot-rogerhokp.rhcloud.com
    Content-Type: application/json
    Cache-Control: no-cache
    Postman-Token: 1aee22bb-cb4d-f45d-39ed-92f96402db34

    {"test": 222}

  */
  sprintln("POST " + path + " HTTP/1.1");
  sprintln("Host: " + host);
  sprintln("Connection: close");
  sprintln("Content-Type: " + contentType);
  sprint("Content-Length: ");
  sprintln(String(data.length()));
  sprintln();
  sprintln(data);
  sprintln();



}

void sprint() {
  Serial.print("");
}
void sprint(String val) {
  Serial.print(val);
}

void sprintln() {
  Serial.println("");
}

void sprintln(String val) {
  Serial.println(val);
}

float getHeatIndexInC() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  return dht.computeHeatIndex(t, h, false);
}

