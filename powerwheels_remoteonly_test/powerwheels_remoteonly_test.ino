#include <Servo.h>
#define LEFTPIN 4
#define RIGHTPIN 5
#define JOYSTICK_PIN_Y A9
#define JOYSTICK_PIN_X A8
// Set limit to 0.33 for solid floors (and normal usage),
// and set to 0.66 for carpet.
// or 1 if you want to kill someone.
#define LIMIT 0.7
// I'm testing it at my (carpeted) house, so 0.66 works
// Technically, its 2/3 (I measure in thirds for this), but the extra digit would just seem cursed
// This is orthodox-compatible software, people.
Servo leftServo;
Servo rightServo;
int joysticky_remote=0;
int joystickx_remote=0;
int joysticky=0;
int joystickx=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial3.begin(9600);
  leftServo.attach(LEFTPIN);
  rightServo.attach(RIGHTPIN);
  pinMode(JOYSTICK_PIN_Y,INPUT);
  pinMode(JOYSTICK_PIN_X,INPUT);
}
String readsofar="";

void handle(String data){
  // When we hit the \n character (char 10, for future reference) we push everything over here.
  joystickx_remote=(data.substring(0,4)).toInt();
  joysticky_remote=(data.substring(4,8)).toInt();
}

boolean remoteonly=false;
int cx=0;
int cy=0;

int intabs(int absmax){
  int returner=0;
  if (absmax>=0){
    returner=absmax;
  }
  else{
    returner=absmax*-1;
  }
  return returner;
}

void loop() {
  if (Serial3.available()){
    int pootch=Serial3.read();
    char poosh=pootch;
    if (poosh==char(10)){
      handle(readsofar);
      readsofar="";
    }
    else{
      readsofar+=poosh;
    }
  }
  joysticky=analogRead(JOYSTICK_PIN_Y)-512;
  joystickx=analogRead(JOYSTICK_PIN_X)-512;
  if (remoteonly or intabs(joysticky_remote)+intabs(joystickx_remote)>5){
    cx=joystickx_remote;
    cy=joysticky_remote;
  }
  else{
    cx=joystickx;
    cy=joysticky;
  }
  cx=cx*LIMIT*-1;
  cy=cy*LIMIT;
  leftServo.writeMicroseconds(1500+cy-cx);
  rightServo.writeMicroseconds(1500-cy-cx);
  Serial.print(cx);
  Serial.print(", ");
  Serial.println(cy);
}
