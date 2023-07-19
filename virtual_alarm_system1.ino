#include <Keypad.h>

// C++ code
//
int value=0;
int adder=0;
bool active=false;
bool alarm=false;
const byte Rows=4;
const byte Cols=4;
String button_pressed="";
char buttons[Rows][Cols]={{'1','2','3','A'},{'4','5','6','B'},
{'7','8','9','C'},{'*','0','#','D'}};
  
byte rowpins[Rows]={2,3,4,5};
byte colpins[Cols]={6,7,8,9};
byte ledpin=12;
byte motion1pin=10;
byte motion2pin=11;
byte reedpin=13;
byte Alarmpin=A0;
Keypad customKeypad = Keypad(makeKeymap(buttons),
                             rowpins, colpins, Rows, Cols);

void setup()
{
  pinMode(Alarmpin,OUTPUT);
  pinMode(ledpin,OUTPUT);
  Serial.begin(9600);
  pinMode(motion1pin,INPUT);
  pinMode(motion2pin,INPUT);
  pinMode(reedpin,INPUT);
  
}

void loop(){
  char charkey=customKeypad.getKey();
  switch(charkey){
    case 'D':
    adder=10;
    button_pressed="";
    break;
    case 'C':
    adder=20;
    button_pressed="";
    break;
    case 'B':
    button_pressed="30";
    break;
    case 'A':
    button_pressed="Arm";
    break;
    default:
    if(isdigit(charkey)){
      value=adder+int(charkey-'0');
      adder=0;
      button_pressed=String(value);
    }
    else
      button_pressed=button_pressed;
    break;
  }
  check_activation();
  check_alarm();
 
}

void check_activation(){
  if(button_pressed.compareTo("Arm")==0){
    active=true;
    digitalWrite(ledpin,HIGH);
  }
  else if(button_pressed.compareTo("4")==0){
    digitalWrite(ledpin,LOW);
    active=false;
  }
}
                             
void check_alarm(){
  bool motion1=INPUT_IS_HIGH(motion1pin);
  bool motion2=INPUT_IS_HIGH(motion2pin);
  bool reed=INPUT_IS_HIGH(reedpin);
  if(active&&(motion1&&motion2||reed)){
    alarm=1;
    tone(Alarmpin,111);
  }
  if(!active)
     noTone(Alarmpin);
}

bool INPUT_IS_HIGH(byte input_pin){
  return digitalRead(input_pin)==HIGH;
}
    
                                   
                                   