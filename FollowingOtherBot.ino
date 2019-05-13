#include <Wire.h>
#define uchar unsigned char     //line follower module 
uchar t;
uchar data[16];




int enableRight=11;
int backwardRight=9;
int forwardRight=6;
int enableLeft= 10;
int forwardLeft = 3;
int backwardLeft= 5;
const int trigPin = 12;       // trig in port 
const int echoPin = 13;     // echo in 13 
int threshold = 69;     //value for when to turn 
int i=0;                // Used for jumping out of line follower f(x)
int a=0;                 //Used to run serial monitor f(x) 
long duration;
int distance;




void setup()
{
  Wire.begin();        
  Serial.begin(9600);           // Start serial monitor 
  t = 0;  
  
    pinMode(forwardRight,OUTPUT) ;        // We have to set enableRight pin as output
    pinMode(backwardRight,OUTPUT) ;
    pinMode(forwardLeft,OUTPUT) ;
    pinMode(backwardLeft,OUTPUT) ;  
// Logic pins are also set as output
    
    pinMode(enableRight, OUTPUT); 
    pinMode(enableLeft, OUTPUT);    // pmw is output 

    pinMode(trigPin, OUTPUT);      // Sets the trigPin as an Output
    pinMode(echoPin, INPUT);      // Sets the echoPin as an Input 

}

void loop()
{
  // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
// Calculating the distance
    distance= duration/58.2;
    delay(10);
// Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);

  if (a==0)
  {
    serialmonitor();
  }
  
  if (distance > 12)                // default to running linefollower f(x)
    {
      linefollower(); 
    }
  
  if (distance <= 12 && distance > 7){ 
    {
      closetoBot();     //if i is increased run ultrasonic f(x)
    }

   if (distance <= 7 && distance > 1){
    beCareful();
   }

   if (distance <= 1){
      Serial.println("STOP!");
      digitalWrite(forwardRight,HIGH) ;
      digitalWrite(forwardLeft,HIGH) ;
      digitalWrite(backwardRight,LOW) ;
      digitalWrite(backwardLeft,LOW) ;
      analogWrite(enableRight, 0) ;
      analogWrite(enableLeft, 0) ; 
   }
   }
}

void serialmonitor()
{
    
  Wire.requestFrom(9, 16);    
  while (Wire.available())   
    {
      data[t] = Wire.read(); 
      if (t < 15)
        t++;
      else
        t = 0; 
    }               // line sensor data  

}


void linefollower()
{
  if (data[14] > threshold && data[2] > 80 )      // if it senses white, turn slightly right  
    {
      Serial.println("Forward!");
      digitalWrite(forwardRight,HIGH) ;  
      digitalWrite(forwardLeft,HIGH) ; 
      digitalWrite(backwardRight,LOW) ;
      digitalWrite(backwardLeft,LOW) ;
      analogWrite(enableRight, 100) ; 
      analogWrite(enableLeft, 250) ;
    }
  
  if (data[14] < threshold && data[2] > 80)       // turn left if left sensor finds line
    {
      Serial.println("Turn Left!"); 
      digitalWrite(forwardRight,HIGH) ;
      digitalWrite(forwardLeft,HIGH) ;
      digitalWrite(backwardRight,LOW) ;
      digitalWrite(backwardLeft,LOW) ;
      analogWrite(enableRight, 100); 
      analogWrite(enableLeft, 0);
  
    }

}


void closetoBot()
{
  if (data[14] > threshold && data[2] > 80 )      // if it senses white, turn slightly right  
    {
      Serial.println("Forward!");
      digitalWrite(forwardRight,HIGH) ;  
      digitalWrite(forwardLeft,HIGH) ; 
      digitalWrite(backwardRight,LOW) ;
      digitalWrite(backwardLeft,LOW) ;
      analogWrite(enableRight, 50) ; 
      analogWrite(enableLeft, 125) ;
    }
  
  if (data[14] < threshold && data[2] > 80)       // turn left if left sensor finds line
    {
      Serial.println("Turn Left!"); 
      digitalWrite(forwardRight,HIGH) ;
      digitalWrite(forwardLeft,HIGH) ;
      digitalWrite(backwardRight,LOW) ;
      digitalWrite(backwardLeft,LOW) ;
      analogWrite(enableRight, 60); 
      analogWrite(enableLeft, 0);
  
    }


}
void beCareful()
{
  if (data[14] > threshold && data[2] > 80 )      // if it senses white, turn slightly right  
    {
      Serial.println("Forward!");
      digitalWrite(forwardRight,HIGH) ;  
      digitalWrite(forwardLeft,HIGH) ; 
      digitalWrite(backwardRight,LOW) ;
      digitalWrite(backwardLeft,LOW) ;
      analogWrite(enableRight, 10) ; 
      analogWrite(enableLeft, 60) ;
    }
  
  if (data[14] < threshold && data[2] > 80)       // turn left if left sensor finds line
    {
      Serial.println("Turn Left!"); 
      digitalWrite(forwardRight,HIGH) ;
      digitalWrite(forwardLeft,HIGH) ;
      digitalWrite(backwardRight,LOW) ;
      digitalWrite(backwardLeft,LOW) ;
      analogWrite(enableRight, 30); 
      analogWrite(enableLeft, 0);
  
    }

}
