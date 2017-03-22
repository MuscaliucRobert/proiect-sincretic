#include <LiquidCrystal.h>
#include<EEPROM.h>
#define MAX 9
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

typedef struct Optiuni
{
  String nume;
  int valoare;
  int adresa;
} Optiuni;
const String numeOpt[]={"Alege","Start","Temp_set","T_inc","T_men","T_rac","Kp","Ki","Kd","Resetare"};
const int valoareOpt[]={15,20,33,21,5,2,4,5,6,1};
Optiuni Opt1,Opt2,Opt3,Opt4,Opt5,Opt6,Opt7,Opt8,Opt9,Opt10;
Optiuni meniu[]={Opt1,Opt2,Opt3,Opt4,Opt5,Opt6,Opt7,Opt8,Opt9,Opt10};
int b1=8;
int b2=9;
int b3=10;
int b4=11;
int index=-1;
int nr=0;
int state = 0;
int changedValue;
int adresaCurenta = 0;

void setup() {
// set up the LCD's number of columns and rows:
lcd.begin(16, 2);
// Print a message to the LCD.
pinMode(b1,INPUT);
pinMode(b2,INPUT);
pinMode(b3,INPUT);
pinMode(b4,INPUT);
lcd.print("Meniu");
for (int i=0;i<=MAX;i++){
  meniu[i].nume=numeOpt[i];
  meniu[i].valoare = EEPROM.get(adresaCurenta,meniu[i].valoare);
  meniu[i].adresa = adresaCurenta;
  adresaCurenta += sizeof(meniu[index].valoare);
  //meniu[i].valoare=valoareOpt[i];
  }
}

void printMeniu(){
  lcd.print("Meniu");
  lcd.setCursor (0,1);
  lcd.print(meniu[index].nume);
//  lcd.setCursor (meniu[index].nume.length()+2,1);
//  lcd.print(meniu[index].valoare);
}

void printSeteazaMeniu(int valoare){
  lcd.print("Seteaza: ");
  lcd.setCursor(0,1);
  lcd.print(meniu[index].nume);
  lcd.setCursor (meniu[index].nume.length()+2,1);
  lcd.print(valoare); 
}

void loop() {
  lcd.setCursor (0,0);
  if ((digitalRead(b1)& 1) == 1){
    if (state==2 || state==3){
      lcd.clear();
      changedValue++;
      printSeteazaMeniu(changedValue);
      state=3;
    }
    else{
    state=1;
    lcd.clear();
    index++;
    if (index > MAX){
      index = 0;
      printMeniu();
    }
    else{
      printMeniu();
    }
    }
    delay(300);
  }
  if ((digitalRead(b2)& 1) == 1){
    if (state==2 || state==3){
      lcd.clear();
      changedValue--;
      printSeteazaMeniu(changedValue);
      state=3;
    }
    else{
    state=1;
    lcd.clear();
    index--;
    if (index < 0){
      index = MAX;
      printMeniu(); 
      }
    else{
      printMeniu();
    }
    }

    
    delay(300);
  }
  if ((digitalRead(b3)& 1) == 1){
    if (state==3){
      lcd.clear();
      meniu[index].valoare=changedValue;
      printMeniu();
      EEPROM.put(meniu[index].adresa,meniu[index].valoare);
      state=0;
    }
    if (state==1){
      state=2;
      lcd.clear();
      lcd.setCursor(0,0);
      printSeteazaMeniu(meniu[index].valoare);
      changedValue=meniu[index].valoare;
    }
  }
  if ((digitalRead(b4)& 1) == 1){
    
    if (state==3 || state==2){
      lcd.clear();
      printMeniu();
      state=0;
    }
  }
  lcd.setCursor(12,0);
  lcd.print(state);
  
}
