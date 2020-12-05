#define Y_PIN A3
#define X_PIN A2
#define BUTTON_PIN_1 4
#define BUTTON_PIN_2 2
#define BUTTON_PIN_3 9
#define BUTTON_PIN_4 8

int yposition=0;
int xposition=0;
int yzero=0;
int xzero=0;
String buttons="0000";
void setup(){
  Serial1.begin(9600);
  Serial.begin(9600);
  yzero=analogRead(Y_PIN);
  xzero=analogRead(X_PIN);
  pinMode(BUTTON_PIN_1,INPUT);
  pinMode(BUTTON_PIN_2,INPUT);
  pinMode(BUTTON_PIN_3,INPUT);
  pinMode(BUTTON_PIN_4,INPUT);
}
String tostring_addzeros(int number){
  String adder="000";
  if (number>9){
    adder="00";
  }
  if (number>99){
    adder="0";
  }
  if (number<0){
    adder="00";
  }
  if (number<-9){
    adder="0";
  }
  if (number<-99){
    adder="";
  }
  String result=adder+number;
  return result;
}
void loop(){
  if (digitalRead(BUTTON_PIN_1)==HIGH){
    Serial.println("BUTTON ONE PRESSED");
  }
  yposition=analogRead(Y_PIN)-yzero;
  xposition=analogRead(X_PIN)-xzero;
  Serial1.print(tostring_addzeros(-xposition));
  Serial1.println(tostring_addzeros(yposition));
}
