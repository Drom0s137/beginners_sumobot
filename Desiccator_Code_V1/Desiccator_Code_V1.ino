/*------ Decciator Code----- */
/*-------definning Outputs------*/
#define LMlF 4       // left motor
#define LMlB 5       // left motor
#define LMRF 3       // right motor
#define LMRB 2       // right motor

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
const int pinIRd = 8;
const int pinIRa = A0;
const int pinLED = 9;
int IRvalueA = 0;
int IRvalueD = 0;
int count = 0;

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   pinMode(pinIRd,INPUT);
   pinMode(pinIRa,INPUT);
   pinMode(pinLED,OUTPUT);
   pinMode(LMlF, OUTPUT);
   pinMode(LMlB, OUTPUT);

}

void loop() {
  //ultrasonic sensor
   long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
   Serial.print(inches);
   Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   Serial.print("Analog Reading=");
   Serial.print(IRvalueA);
   Serial.print("\t Digital Reading=");
   Serial.println(IRvalueD);   //1 for black, 0 for white
  
   delay(100);
   IRvalueA = analogRead(pinIRa);
   IRvalueD = digitalRead(pinIRd);


  if((IRvalueD == 1) && cm < 100)     // Move Forward
  {
    if (count == 0){
    digitalWrite(LMlB, LOW);
    digitalWrite(LMlF, HIGH);
    digitalWrite(LMRB, LOW);
    digitalWrite(LMRF, HIGH);
    Serial.println("collide");
    delay(3000);
    }
    if(count == 1){
    digitalWrite(LMlB, HIGH);
    digitalWrite(LMlF, LOW);
    digitalWrite(LMRB, HIGH);
    digitalWrite(LMRF, LOW);
    Serial.println("avoid");
    delay(2000);
    }
    if (count == 2){ // Turning the Bot to the Right Side
    digitalWrite(LMlB, HIGH);
    digitalWrite(LMlF, HIGH);
    digitalWrite(LMRB, LOW);
    digitalWrite(LMRF, HIGH);
    Serial.println("Turning to the RIGHT");
    delay(1000);
    count = -1;
    }
    count ++;
  }
  else {
    digitalWrite(LMlF, LOW);
    digitalWrite(LMlB, LOW);
    digitalWrite(LMRF, LOW);
    digitalWrite(LMRB, LOW);
    Serial.println("Stop moving");
    count = 0;
  }
  
}


long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
