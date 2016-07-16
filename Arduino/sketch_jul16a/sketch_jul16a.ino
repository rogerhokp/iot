#include <DHT.h>



#define DHTTYPE DHT11
#define fanPin 2
#define tempSensorPower 7
#define tempSensorPin 6

DHT dht(tempSensorPin, DHTTYPE);

void setup() {

  Serial.begin(9600);
  Serial.println("start!");

  pinMode(fanPin, OUTPUT);
  pinMode(tempSensorPin, INPUT);
  pinMode(tempSensorPower, OUTPUT);
  digitalWrite(tempSensorPower, HIGH);


  dht.begin();
}


void loop() {
  delay(2000);

  float temp = getHeatIndexInC();
  printDHT11result();
  Serial.print("now is ");
  Serial.print(temp);
  Serial.println("*C");

  if(temp >33){
    onFan();
  }else{
    offFan();
  }

}


float getHeatIndexInC() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  return dht.computeHeatIndex(t, h, false);
}


void onFan() {
  digitalWrite(fanPin, HIGH);
}


void offFan() {
  digitalWrite(fanPin, LOW);
}


void printDHT11result() {

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
}
