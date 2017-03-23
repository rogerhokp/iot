#define R_LED 2
#define Y_LED 3
#define G_LED 4

int temp = 0;
void setup() {

  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(R_LED, OUTPUT);
  pinMode(Y_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  temp = Serial.read();

  switch(temp){
    case(114):
      digitalWrite(G_LED, LOW);
      digitalWrite(Y_LED, LOW);
      digitalWrite(R_LED, HIGH);
      Serial.println("red");
     break;
     case(121):
      digitalWrite(G_LED, LOW);
      digitalWrite(Y_LED, HIGH);
      digitalWrite(R_LED, LOW);
      Serial.println("yellow");
     break;  
     case(103):
      digitalWrite(G_LED, HIGH);
      digitalWrite(Y_LED, LOW);
      digitalWrite(R_LED, LOW);
      Serial.println("greed");
     break;
     case(97):
      digitalWrite(G_LED, HIGH);
      digitalWrite(Y_LED, HIGH);
      digitalWrite(R_LED, HIGH);
      Serial.println("all");
     break;    
     case(110):
      digitalWrite(G_LED, LOW);
      digitalWrite(Y_LED, LOW);
      digitalWrite(R_LED, LOW);
      Serial.println("no");
     break;
  }
  Serial.println(temp);

  delay(500);

}
