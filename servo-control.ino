#include <Servo.h>

Servo myservo; //servo object initialization
int* parsedInts = {};

int angle = 0;
int inputspeed = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(DAC0,OUTPUT);
  pinMode(50,OUTPUT);
  Serial.begin(9600);
  while(!Serial){
    ;
  }
  Serial.setTimeout(10);
  myservo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    String input = Serial.readString();
    parseInput(input);
    Serial.println(angle);
    Serial.println(inputspeed);
    moveServo(angle);
    adjustMotorSpeed(inputspeed); 
  }
}

void parseInput(String input){
  int index = input.indexOf(';');
  String a = input.substring(0,index);
  String i = input.substring(index+1,input.length());
  angle = a.toInt();
  inputspeed = i.toInt();
}

void moveServo(int pos){
  String output = "Moving to angle: ";
  Serial.println(output + pos);
  myservo.write(pos);
}

void adjustMotorSpeed(int motorspeed){
  //double analogspeed = motorspeed * 2.55;
  if(motorspeed <= 0){
    digitalWrite(50,LOW);
  }else{
    digitalWrite(50,HIGH);
  }
  delay(500);
  if(motorspeed > 255){
    motorspeed = 255;
  }
  Serial.print(" Motorspeed :");
  Serial.println(motorspeed);
  analogWrite(DAC0,abs(motorspeed));
}
