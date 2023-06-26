#include <Servo.h>

//Servos
Servo Q1;
Servo Q2;
Servo Q3;
Servo Q4;
Servo Q5;

//Servo Pins
byte Q1Pin = 8;
byte Q2Pin = 6;
byte Q3Pin = 5;
byte Q4Pin = 4;
byte Q5Pin = 3;

//Servo Limits
byte servoMin = 0;
byte servoMax = 180;

//Initialize to default positions
int Q1Pos = 90;
int Q2Pos = 180;
int Q3Pos = 180;
int Q4Pos = 90;
int Q5Pos = 0;

const byte MAX_BUFFER=40;
bool dataValid=false;
byte dataLenght=0;
char inputBuffer[MAX_BUFFER];
String data;
byte TS=0;

void setup() {
  Serial.begin(115200);
  delay(500); // delay() is OK in setup as it only happens once
  
  // initialize the servos
  Q1.attach(Q1Pin);
  Q2.attach(Q2Pin);
  Q3.attach(Q3Pin);
  Q4.attach(Q4Pin);
  Q5.attach(Q5Pin);

  // move to default position
  moveServo();
  
  // tell the PC we are ready
  Serial.println("<Arduino is ready>");
}

void loop() {
  readData();
  parseData();
  if(dataValid==true){
    moveServo();
    messageBack();
  }
}

void readData(){
    //Read From Serial
  if (Serial.available() > 0) {
    data = Serial.readStringUntil('\n');
    dataLenght=data.length();
    if(dataLenght<=24)
      dataValid=true;
  }
}

void parseData(){
  char * strtokIndx; // this is used by strtok() as an index
  data.toCharArray(inputBuffer, dataLenght);

  strtokIndx = strtok(inputBuffer,",");     
  Q1Pos = atoi(strtokIndx);     
  
  strtokIndx = strtok(NULL, ","); 
  Q2Pos = atoi(strtokIndx);    
  
  strtokIndx = strtok(NULL, ","); 
  Q3Pos = atoi(strtokIndx);   
  
  strtokIndx = strtok(NULL, ","); 
  Q4Pos = atoi(strtokIndx);   

  strtokIndx = strtok(NULL, ","); 
  Q5Pos = atoi(strtokIndx); 
}

void moveServo(){
  Q1.write(Q1Pos);
  Q2.write(Q2Pos);
  Q3.write(Q3Pos);
  Q4.write(Q4Pos);
  Q5.write(Q5Pos);
}

void messageBack(){
  char message[MAX_BUFFER+10];
  Serial.print("RAW DATA: <");
  Serial.print(data);
  Serial.print(">");
  Serial.print(" ");

  sprintf(message,"Q1=%d Q2=%d Q3=%d Q4=%d Q5=%d",
        Q1Pos,Q2Pos,Q3Pos,Q4Pos,Q5Pos);
  Serial.println(message);
    
  delay(10);
  dataValid=false;
}