#include <Arduino.h>

#define Echo 2
#define Trig 4
#define SensE A0
#define SensD A1
#define pwmA 3
#define Ain2 5
#define Ain1 6
#define STBY 8
#define Bin1 9
#define Bin2 10
#define pwmB 11

int vel = -255;


void Motor(signed int velocidade1, signed int velocidade2, bool freio1, bool freio2)
{
  if (!freio1)
  {
    if (velocidade1 > 0)
    {
      digitalWrite(Ain1, HIGH);
      digitalWrite(Ain2, LOW);
      analogWrite(pwmA, velocidade1);
    }
    else
    {
      if (velocidade1 == 0)
      {
        digitalWrite(Ain1, LOW);
        digitalWrite(Ain2, LOW);
        analogWrite(pwmA, velocidade1);
      }
      else
      {
        digitalWrite(Ain1, LOW);
        digitalWrite(Ain2, HIGH);
        analogWrite(pwmA, -velocidade1);
      }
    }
  }
  else
  {
    digitalWrite(Ain1, HIGH);
    digitalWrite(Ain2, HIGH);
    digitalWrite(pwmA, HIGH);

  }

  if (!freio2)
  {
    if (velocidade2 > 0)
    {
      digitalWrite(Bin1, HIGH);
      digitalWrite(Bin2, LOW);
      analogWrite(pwmB, velocidade2);
    }
    else
    {
      if (velocidade2 == 0)
      {
        digitalWrite(Bin1, LOW);
        digitalWrite(Bin2, LOW);
        analogWrite(pwmB, velocidade2);
      }
      else
      {
        digitalWrite(Bin1, LOW);
        digitalWrite(Bin2, HIGH);
        analogWrite(pwmB, -velocidade2);

      }
    }
  }
  else
  {
    digitalWrite(Bin1, HIGH);
    digitalWrite(Bin2, HIGH);
    digitalWrite(pwmB, HIGH);

  }
}


long Distancia() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  return pulseIn(Echo, HIGH) * 0.017;
}

void setup() {
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(SensE, INPUT);
  pinMode(SensD, INPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(Ain2, OUTPUT);
  pinMode(Ain1, OUTPUT);
  pinMode(Bin2, OUTPUT);
  pinMode(Bin1, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);
  Serial.begin(9600);

  //Delay de 5s padrao de inicio de partida
  delay(1000);
}
int see1=false;
int see2 =false;
int see3 =false;

void loop() {

  
  if (analogRead(SensD) < 200  || analogRead(SensE) < 200){
    Motor(0,0,1,1);
    Motor(-255,-255,0,0);
    delay(500);
    Motor(-255,0,0,0);
    delay(200);
  
  } else if (see1 && see2 &&see3 && analogRead(SensD) > 200  && analogRead(SensE) > 200) {
    Motor(200,200,0,0);
  }else {
    Motor(200,-200,0,0);
  }
  see3 = see2;
  see2 = see1;
  if (Distancia()< 25){
    see1=true;
  }else {
    see1=false;
  }
}



