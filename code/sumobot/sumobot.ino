#include <HCSR04.h>

#define SPEED_FORWARDS 150
#define SPEED_BACKWARDS 150 
#define SPEED_ROTATE 150

enum PinMappings
{
  SIG_START,
  SIG_KILL, // ;)
  SENSOR_SND_TRIG,
  SENSOR_SND_ECHO,
  SENSOR_IR_FRONT,
  SENSOR_IR_BACK,
  MOTOR_IN1,
  MOTOR_IN2,
  MOTOR_IN3,
  MOTOR_IN4,
  _SIZE_LIMIT,
};

static uint8_t const pin[_SIZE_LIMIT] = {
    [SIG_START] = 2,
    [SIG_KILL] = 3,
    [SENSOR_SND_TRIG] = 12,
    [SENSOR_SND_ECHO] = 11,
    [SENSOR_IR_FRONT] = 9,
    [SENSOR_IR_BACK] = 8,
    [MOTOR_IN1] = 6,
    [MOTOR_IN2] = 7,
    [MOTOR_IN3] = 4,
    [MOTOR_IN4] = 5,
};

UltraSonicDistanceSensor hcsr04(12, 11);

void setup()
{
  Serial.begin(9600);
  pinMode(pin[MOTOR_IN1], OUTPUT);
  pinMode(pin[MOTOR_IN2], OUTPUT);
  pinMode(pin[MOTOR_IN3], OUTPUT);
  pinMode(pin[MOTOR_IN4], OUTPUT);
  waitStartSignal();
}

void loop()
{
  float distanceCm = hcsr04.measureDistanceCm();

  rotateLeft(SPEED_ROTATE);

  while (distanceCm < 20 && distanceCm > 0)
  {
    int frontIR = digitalRead(pin[SENSOR_IR_FRONT]);
    int backIR = digitalRead(pin[SENSOR_IR_BACK]);
    if (frontIR == 0)
    {
      backward(SPEED_BACKWARDS);
      delay(500);
      break;
    }

    if (backIR == 0)
    {
      forward(SPEED_FORWARDS);
      delay(500);
      break;
    }
    forward(SPEED_FORWARDS); 
    distanceCm = hcsr04.measureDistanceCm();
  }
  Serial.println(distanceCm);
  delay(150);
}

void waitStartSignal()
{
  Serial.println(__func__);
  while (digitalRead(pin[SIG_START]) != HIGH)
  {
    Serial.println("Waiting for start signal");
  }
}

void checkStopSignal()
{
  if (digitalRead(pin[SIG_KILL]) != HIGH)
  {
    Serial.println("Got kill signal, stopping..");
    stop();
    delay(500);
  }
}

void forward(int speed)
{
  Serial.println(__func__);
  analogWrite(pin[MOTOR_IN1], speed);
  analogWrite(pin[MOTOR_IN2], 0);
  analogWrite(pin[MOTOR_IN3], 0);
  analogWrite(pin[MOTOR_IN4], speed);
  checkStopSignal();
}

void backward(int speed)
{
  Serial.println(__func__);
  analogWrite(pin[MOTOR_IN1], 0);
  analogWrite(pin[MOTOR_IN2], speed);
  analogWrite(pin[MOTOR_IN3], speed);
  analogWrite(pin[MOTOR_IN4], 0);
  checkStopSignal();
}

void rotateLeft(int speed)
{
  Serial.println(__func__);
  analogWrite(pin[MOTOR_IN1], speed);
  analogWrite(pin[MOTOR_IN2], 0);
  analogWrite(pin[MOTOR_IN3], speed);
  analogWrite(pin[MOTOR_IN4], 0);
  checkStopSignal();
}

void rotateRight(int speed)
{
  Serial.println(__func__);
  analogWrite(pin[MOTOR_IN1], 0);
  analogWrite(pin[MOTOR_IN2], speed);
  analogWrite(pin[MOTOR_IN3], 0);
  analogWrite(pin[MOTOR_IN4], speed);
  checkStopSignal();
}

void stop()
{
  Serial.println(__func__);
  analogWrite(pin[MOTOR_IN1], 0);
  analogWrite(pin[MOTOR_IN2], 0);
  analogWrite(pin[MOTOR_IN3], 0);
  analogWrite(pin[MOTOR_IN4], 0);
}
