
#include <HCSR04.h>

#define TRIG_PIN 12
#define ECHO_PIN 11

UltraSonicDistanceSensor hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);

const int IN1=7;
const int IN2=6;
const int IN3=5;
const int IN4=4;
#define IR_sensor_front 9 // front sensor
#define IR_sensor_back 8 // rear senson
int distance ;

void setup() 
{
Serial.begin(9600);
delay (5000); // as per sumo compat roles
}
void loop()
{
  
 int IR_front = digitalRead(IR_sensor_front);
 int IR_back = digitalRead(IR_sensor_back);
 distance = hcsr04.measureDistanceCm()/100;
 ROTATE(100);
 
    
    while (distance < 30 ) {
    
    FORWARD(100); 
  
    distance = hcsr04.measureDistanceCm()/100;
    IR_front = digitalRead(IR_sensor_front);
    IR_back = digitalRead(IR_sensor_back);
    if ( IR_front == 0 || IR_back == 0 ) { break;}
    delay(10); }
  
  
 if (IR_front == 0 ) 
   {
   Stop();
   delay (50);
   BACKWARD(255);
   delay (500);
   } 
   
 if (IR_back == 0 )  //
   {
   Stop();
   delay (50);
   FORWARD(255);
   delay (500);
   }
   

  Serial.print(distance);
  //Serial.println("cm");
  //Serial.println("IR front :");
  //Serial.println(IR_front); 
  //Serial.println("IR back :");
  //Serial.println(IR_back);  


} //--------------------------------------------
void FORWARD (int Speed){
  //When we want to let Motor To move forward,
  // just void this part on the loop section .
  Serial.println("FRAM");
  analogWrite(IN1,Speed);
  analogWrite(IN2,0);
  analogWrite(IN3,0);
  analogWrite(IN4,Speed);
}//--------------------------------------------
void BACKWARD (int Speed){
  //When we want to let Motor To move forward,
  // just void this part on the loop section .
  Serial.println("BAK");
  analogWrite(IN1,0);
  analogWrite(IN2,Speed);
  analogWrite(IN3,Speed);
  analogWrite(IN4,0);
}//--------------------------------------------
void ROTATE (int Speed)
{
  //When we want to let Motor To Rotate ,
  // just void this part on the loop section .
  Serial.println("ROTERA");
  analogWrite(IN1,Speed);
  analogWrite(IN2,0);
  analogWrite(IN3,Speed);
  analogWrite(IN4,0);
}//--------------------------------------------
void Stop(){
  //When we want to  Motor To stop ,
  // just void this part on the loop section .
  Serial.println("STOP");
  analogWrite(IN1,0);
  analogWrite(IN2,0);
  analogWrite(IN3,0);
  analogWrite(IN4,0);
}
