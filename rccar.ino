#include <Servo.h>;
#define in1 5
#define in2 6
#define in3 10
#define in4 11
#define LED 13
#define enA 8
#define enB 9
#define servoPin 7

int command;  // store app command state
int buttonState = 0;
int lastButtonState = 0;

Servo servo;

void setup() {
  // put your setup code here, to run once:
  servo.attach(servoPin);
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(LED, OUTPUT);

  // center servo angle
  int centerServo = map(0, -60, 60, 0, 180);
  servo.write(centerServo);

  Serial.begin(9600); // bluetooth module baud rate
}

void forwards() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 255);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 255);
}

void backwards() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 255);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 255);
}

void left() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 255);
}

void right() {
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 255);
}

void donutsLeft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 255);
}

void donutsRight() {
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 255);
}

void forwardsRight() {
  analogWrite(in2, speedSec);
  analogWrite(in4, speed);
}

void Stop() {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  
  if(Serial.available() > 0) {
    command = Serial.read();
    Stop(); // initialize with motor stopped
    switch(command) {
      case 'a':   // forward
        forwards();
        servo.write(90);
        break;
      case 'c':   // backwards
        backwards();
        servo.write(90);
        break;
      case 'd':   // left
        forwards();
        servo.write(180);
        break;
      case 'b':   // right
        forwards();
        servo.write(0);
        break;
      case 'e':
        donutsLeft();
        servo.write(180);
        break;
      case 'I':
        donutsRight();
        servo.write(0);
        break;
      case 'H':
        forwards();
        break;
    }
  }
}
