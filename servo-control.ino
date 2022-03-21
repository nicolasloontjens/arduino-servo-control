#include <Servo.h>

Servo myservo; //servo object initialization

void setup() {
  // put your setup code here, to run once:
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
    int* parsedInts = parseInput(input);
    moveServo(parsedInts[0],parsedInts[1]);
    
  }
}

int* parseInput(String input){
  int index = input.indexOf(';');
  String angle = input.substring(0,index);
  String inputspeed = input.substring(index+1,input.length());
  Serial.println(angle);
  Serial.println(inputspeed);
  int result[] = {angle.toInt(), inputspeed.toInt()};
  return result;
  //return "Angle: " + angle + " Speed: " + inputspeed;
}

void moveServo(int pos, int thespeed){
  String output = "Moving to angle: ";
  Serial.println(output + pos);
  myservo.write(pos);
}
