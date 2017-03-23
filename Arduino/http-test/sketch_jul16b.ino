void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  String hcontent = "hume=40&time=800";
  Serial.println("POST / HTTP/1.1");
  Serial.println("Host: 192.168.1.102:3000");
  Serial.println("Content-Type: application/x-www-form-urlencoded");
  Serial.println("Connection: close");
  Serial.print("Content-Length: ");
  Serial.println(hcontent.length());
  Serial.println();
  Serial.print(hcontent);
  Serial.println();

}

void loop() {
  // put your main code here, to run repeatedly:

}
