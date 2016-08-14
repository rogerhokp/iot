#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WifiConnect.h>
#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN D7
#define DHTTYPE DHT11

#define ssid "hihi"
#define password "Sss99889988"
// #include <ESP8266HTTPClient.h>

LiquidCrystal lcd(D6, D5, D4, D3, D2, D1);
DHT dht(DHTPIN, DHTTYPE);

String ip;
void setup()
{
  Serial.begin(115200);
  // delay(1000);
  // Serial.flush();
  ip = WifiConnect(ssid, password);

  lcd.begin(16,2);               // initialize the lcd



  dht.begin();
}


void loop()
{

  // wifi.loop();

  // doHttpGet();

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float hic = dht.computeHeatIndex(t, h, false);

  lcd.home ();                   // go home
  lcd.print("H:");
  lcd.print(h);
  lcd.print("/T:");
  lcd.print(t);
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print("HIC: ");
  lcd.print(hic);

  // Serial.print("humidity");
  // Serial.println(temperature[0]);
  // Serial.print("temperature");
  // Serial.println(temperature[1]);
  // Serial.print("HeatIndex");
  // Serial.println(temperature[2]);
  delay(5000);

}
