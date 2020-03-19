#include<Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial ArduinoUno(A0, A1);

// Ultrasonic
const int trigPin = A4;
const int echoPin = A5; 

long duration;
int distance;

//Servo
Servo funnel;
Servo sweep1;
Servo sweep2;

//Johnson Motors
int lm1 = 2;
int lm2 = 4;
int rm1 = 6;
int rm2 = 7;
int pos = 0;

//Water Sump
int sm = 12;

//Serial
int val;
int mode=0;

void setup() {
  //Serial Interface
  Serial.begin(9600);
  ArduinoUno.begin(4800);
  
  //Johnson Motors
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);

  //Sump Motors
  pinMode(sm, OUTPUT);

  //Ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Servo
  funnel.attach(9);
}

void loop()
{
  serial();
  while(mode == 0) {
    Serial.println("Entered Auto Mode");
    Auto();
  }
  while(mode == 1) {
    Serial.println("Entered Manual Mode");
    manual();
  }
}

void Auto()
{
  while(mode==0){
    serial();
    ultrasonic();
  if (distance < 30) {
    forward();
    Serial.print("ForwardA");
    delay(400);
    sfunnel();
    Stop();
    Serial.print("Plant");
    delay(150);
    water();
    delay(500);
    Serial.print("Water");
    forward();
    delay(300);
  }
  else if (distance > 30) {
    Stop();
    Serial.print("Stop");
  }
}
}

void manual()
{
  while(mode==1){
    serial();
  if ( val == 2)
    {forward();
    Serial.print("Forward");}
  else if ( val == 3)
   {reverse();
    Serial.print("Reverse");}
  else if ( val == 4) 
    {right();
    Serial.print("Right");}
  else if ( val == 5)
    {left();
    Serial.print("Left");}
  else if ( val == 6)
    {water();
    Serial.print("Sump");}
  else if ( val == 7)                                                                                      
    {sfunnel();
    Serial.print("Funnel");}
  else if ( val == 8)
    {Stop();
    Serial.print("Stop");}
}
}

void ultrasonic()
{
  digitalWrite(trigPin, LOW); // Clears the trigPin 2ms
  delay(2);
  digitalWrite(trigPin, HIGH); // Sets the trigPin on HIGH for 10ms
  delay(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);// Reads the echoPin, sound travel time in ms
  distance = duration * 0.017
  ; // Calculating the distance
  return(distance);
}

void serial()
{
   while (ArduinoUno.available() > 0) {
   val = ArduinoUno.parseFloat();
   if (ArduinoUno.read() == '\n') {
   Serial.println(val);
   if (val==1)
   mode=0;
   else if (val==10)
   mode=1;
    }
  }
}

void forward()
{
  digitalWrite(lm1, 1);
  digitalWrite(lm2, 0);
  digitalWrite(rm1, 1);
  digitalWrite(rm2, 0);
}

void reverse()
{
  digitalWrite(lm1, 0);
  digitalWrite(lm2, 1);
  digitalWrite(rm1, 0);
  digitalWrite(rm2, 1);
}

void left()
{
  digitalWrite(lm1, 0);
  digitalWrite(lm2, 1);
  digitalWrite(rm1, 1);
  digitalWrite(rm2, 0);
}

void right()
{
  digitalWrite(lm1, 1);
  digitalWrite(lm2, 0);
  digitalWrite(rm1, 0);
  digitalWrite(rm2, 1);
}

void Stop()
{
  digitalWrite(rm1, 0);
  digitalWrite(rm2, 0);
  digitalWrite(lm1, 0);
  digitalWrite(lm2, 0);
}
void sfunnel () // Servo Funnel
{
  for (pos = 0; pos <= 50; pos += 1) { 
    funnel.write(pos);              
    delay(15);                       
  }
  for (pos = 50; pos >= 0; pos -= 1) 
  { 
    funnel.write(pos);              
    delay(15);                       
  }
}
void water() //Water Sump
{
  digitalWrite(sm, HIGH);
}
