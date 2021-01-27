#include <Arduino.h>
//I2C and LCD lib
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//Button control lib 
#include "avdweb_Switch.h"
//Button Pins
//top left = 2
Switch TopLeftButton = Switch(2, INPUT, HIGH);
//bottem left = 3
Switch BottomLeftButton = Switch(3, INPUT, HIGH);
//DLEFT = 4 
Switch DPleft = Switch(4, INPUT, HIGH);
//DRIGHT = 5
Switch DPright = Switch(5, INPUT, HIGH);
//dUP = 6
Switch DPup = Switch(6, INPUT, HIGH);
//DDOWN = 7
Switch DPdown = Switch(7, INPUT, HIGH);
//DCENTRE = 8
Switch DPcenture = Switch(8, INPUT, HIGH);

//Buzer pin
const int buzzer = 9; //buzzer to arduino pin 9


//LCD CURSOR QUARDS
int x = 0;
int y = 1;
bool cursorflash = 0;
bool diceroaled = false;
int diceroles[7];
const int jumparray[] = {2,2,2,3,3,3,3};
int jumparray_pos = 0;
int d4 = 0,d6 = 0,d8 = 0,d10 = 0,d12 = 0,d20 = 0,d100 = 0;
int roaled_dice_list_pos = 0;
String D4roles = "", D6roles = "", D8roles = "", D10roles = "", D12roles = "", D20roles = "", D100roles = "";

//Definding functions
void D_pad_map();
void flash_cursor(int amount);
void move_selection(bool diection);
void changeDice(byte action);
void DEBUG_PRINT_ARRAY();
void roal_the_dice();
void array_to_lcd();
void display_dice_roles(byte role);
void up_button_switcher();
void down_buttom_switcher();
void bottem_left_switcher();

//Setting up the lcd
LiquidCrystal_I2C lcd(0x27,16,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Serial.begin(9600); // open the serial port at 9600 bps:
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  lcd.init();// initialize the lcd 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.backlight();
  lcd.cursor_on();
  lcd.setCursor(0,0);
  lcd.print("4|6|8|10|12|20|C");
  lcd.setCursor(0,1);
  lcd.print("0-0-0-00|00|00|0");
  tone(buzzer, 100); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec
  lcd.setCursor(x,y);

}

void loop()
{
  lcd.setCursor(x,y);
  D_pad_map();
  flash_cursor(700);
  //if (diceroaled == true)
  //{
  //display_dice_roles();
  //}
}


void up_button_switcher(){
tone(buzzer, 800); // Send 1KHz sound signal...
delay(50);        // ...for 1 sec
noTone(buzzer);  
if (diceroaled == false){changeDice(1);}
else { display_dice_roles(1);
}
}

void down_buttom_switcher(){
tone(buzzer, 300); // Send 1KHz sound signal...
delay(50);        // ...for 1 sec
noTone(buzzer);   
if (diceroaled == false){changeDice(0);}
else {
  display_dice_roles(0);
}
}


void bottem_left_switcher(){
if (diceroaled == true){
diceroaled = false;
lcd.setCursor(0,0);
lcd.print("4|6|8|10|12|20|C");
lcd.setCursor(0,1);
array_to_lcd();
}
}



void display_dice_roles(byte role){
//D4roles = "", D6roles = "", D8roles = "", D10roles = "", D12roles = "", D20roles = "", D100roles = "";
  if (role == 0){
    if (roaled_dice_list_pos >= 6){
      roaled_dice_list_pos = 0;
    }
    else{
    roaled_dice_list_pos = roaled_dice_list_pos + 1;
    }
  } 
  else if (role == 1) {
    if (roaled_dice_list_pos <= 0) {
      roaled_dice_list_pos = 6;
    }
    else{
    roaled_dice_list_pos = roaled_dice_list_pos - 1;
    }
  } else if (role == 2) {
    roaled_dice_list_pos = 0;
  }
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.clear();
  switch (roaled_dice_list_pos) {
  case 0:
    lcd.setCursor(0,0);
    lcd.print("d4 : " + String(d4));
    lcd.setCursor(0,1);
    lcd.print(D4roles);
    break;
  case 1:
    lcd.setCursor(0,0);
    lcd.print("d6 : " + String(d6));
    lcd.setCursor(0,1);
    lcd.print(D6roles);
    break;
  case 2:
    lcd.setCursor(0,0);
    lcd.print("d8 : " + String(d8));    
    lcd.setCursor(0,1);
    lcd.print(D8roles);
    // statements
    break;
  case 3:
    lcd.setCursor(0,0);
    lcd.print("d10 : " + String(d10));
    lcd.setCursor(0,1);
    lcd.print(D10roles);
    // statements
    break;
  case 4:
    lcd.setCursor(0,0);
    lcd.print("d12 : " + String(d12));
    lcd.setCursor(0,1);
    lcd.print(D12roles);
    // statements
    break;
  case 5:
    lcd.setCursor(0,0);
    lcd.print("d20 : " + String(d20));
    lcd.setCursor(0,1);
    lcd.print(D20roles);
    // statements
    break;
  case 6:
    lcd.setCursor(0,0);
    lcd.print("d100 : " + String(d100));
    lcd.setCursor(0,1);
    lcd.print(D100roles);
    // statements
    break;
  default:
    // statements
    break;
}

}



void roal_the_dice(){
  D4roles = "", D6roles = "", D8roles = "", D10roles = "", D12roles = "", D20roles = "", D100roles = "";
  d4 = 0;
  d6 = 0;
  d8 = 0;
  d10 = 0;
  d12 = 0;
  d20 = 0;
  d100 = 0;
  int temprandom = 0;
  for (int i = 0; i < diceroles[0]; i++){
  temprandom = random(1,5);
  D4roles = D4roles + "+" + String(temprandom);
  d4 = d4 + temprandom;

  }


  for (int i = 0; i < diceroles[1]; i++){
  temprandom = random(1,7);
  D6roles = D6roles + "+" + String(temprandom);
  d6 = d6 + temprandom;
  }  


  for (int i = 0; i < diceroles[2]; i++){
  temprandom = random(1,9); 
  D8roles = D8roles + "+" + String(temprandom);
  d8 = d8 + temprandom;

  } 


  for (int i = 0; i < diceroles[3]; i++){
  temprandom = random(1,11);
  D10roles = D10roles + "+" + String(temprandom);
  d10 = d10 + temprandom;
  } 


  for (int i = 0; i < diceroles[4]; i++){
  temprandom = random(1,13);
  D12roles = D12roles + "+" + String(temprandom);
  d12 = d12 + temprandom;
  } 


  for (int i = 0; i < diceroles[5]; i++){
  temprandom = random(1,21); 
  D20roles = D20roles + "+" + String(temprandom);
  d20 = d20 + temprandom; 
  } 


  for (int i = 0; i < diceroles[6]; i++){
  temprandom = random(1,101); 
  D100roles = D100roles + "+" + String(temprandom);
  d100 = d100 + temprandom; 
  } 


//Serial.println("DICE ROLES");
//Serial.println("D4");
//Serial.println(String(d4));
//Serial.println(D4roles);
//Serial.println("D6");
//Serial.println(String(d6));
//Serial.println(D6roles);
//Serial.println("D8");
//Serial.println(String(d8));
//Serial.println(D8roles);
//Serial.println("D10");
//Serial.println(String(d10));
//Serial.println(D10roles);
//Serial.println("D12");
//Serial.println(String(d12));
//Serial.println(D12roles);
//Serial.println("D20");
//Serial.println(String(d20));
//Serial.println(D20roles);
//Serial.println("D100");
//Serial.println(String(d100));
//Serial.println(D100roles);
  diceroaled = true;
  display_dice_roles(2);

}

//Flashes the highlited text 
void flash_cursor(int amount)
{
    if (millis() % amount == 0){
      if (cursorflash == 0) {
        cursorflash = 1;
        lcd.cursor();
      }
      else {
        cursorflash = 0;
        lcd.noCursor();
      }
  }
}
//0 = left
//1 = right
void move_selection(bool diection)
{
lcd.cursor();
if (diection == 1)
{
  x = x + jumparray[jumparray_pos];
  Serial.println(String("old jumparray pos" + String(jumparray_pos)));
  if (x >= 16 ){
    jumparray_pos = 0;
    x = 0;
  }
  else {jumparray_pos = jumparray_pos + 1;
    Serial.println(String("new jumparray pos" + String(jumparray_pos)));
}
}


if (diection == 0)
{
  if (jumparray[jumparray_pos] == 3){
     x = x - jumparray[jumparray_pos - 1];
     jumparray_pos = jumparray_pos - 1;
  }
  else
  {
    x = x - jumparray[jumparray_pos];
    Serial.println(String("old jumparray pos" + String(jumparray_pos)));

    if (x < 0 ){
      jumparray_pos = 6;
      x = 15;
    }
    else {jumparray_pos = jumparray_pos - 1;
        Serial.println(String("new jumparray pos" + String(jumparray_pos)));
  }
}
}
  tone(buzzer, 500); // Send 1KHz sound signal...
  delay(50);        // ...for 1 sec
  noTone(buzzer);   

}

void array_to_lcd()
{
  String display_string = "";
  for(int i = 0; i < 7; i++)
  {
    if (i == 4 || i == 5 || i == 6){
    display_string = display_string + "|";
    }
    if (diceroles[i] <= 9) {
    display_string = display_string + String(diceroles[i]) + "-";
    }
    else{
      display_string = display_string + String(diceroles[i]);
    }
}
lcd.setCursor(0,1);
lcd.print(display_string);
lcd.setCursor(x,y);
}
//0 decress roal
//1 incres roal 
//2 reset roal
void changeDice(byte action)
{
//int array_position = map(x, 0, 14, 0, 8);
Serial.println(String(jumparray_pos));
//if (array_position == 8){array_position = 7;}
switch (action) {
  case 0:
    if (diceroles[jumparray_pos] > 0)
    {
    diceroles[jumparray_pos] = diceroles[jumparray_pos] - 1;
    }
    break;
  case 1:
    diceroles[jumparray_pos] = diceroles[jumparray_pos] + 1; 
    break;
  case 2:
    diceroles[jumparray_pos] = 0;
    tone(buzzer, 100); // Send 1KHz sound signal...
    delay(50);        // ...for 1 sec
    noTone(buzzer); 
    break;
  default:
    Serial.println("HOW DID YOU EVEN GET HERE !!!!!");
    break;
}
DEBUG_PRINT_ARRAY();
array_to_lcd();
}

void DEBUG_PRINT_ARRAY(){
  Serial.println("--------");
  for(int i = 0; i < 8; i++)
  {
    Serial.println(String(diceroles[i]));
  }
  Serial.println("--------");

}

void D_pad_map()
{
  TopLeftButton.poll();
  if(TopLeftButton.switched()) Serial.print("TopLeftButton switched ");
  if(TopLeftButton.pushed()) {roal_the_dice();}
  if(TopLeftButton.released()) Serial.println("TopLeftButton released");
  //-------------------------------------------------------------------------------------
  BottomLeftButton.poll();
  if(BottomLeftButton.switched()) Serial.print("BottomLeftButton switched ");
  if(BottomLeftButton.pushed()) {bottem_left_switcher();}
  if(BottomLeftButton.released()) Serial.println("BottomLeftButton released");
  //-------------------------------------------------------------------------------------
  DPleft.poll();
  if(DPleft.switched()) Serial.print("DPleft switched ");
  if(DPleft.pushed()) {move_selection(0);}
  if(DPleft.released()) Serial.println("DPleft released");
  //-------------------------------------------------------------------------------------
  DPright.poll();
  if(DPright.switched()) Serial.print("DPright switched ");
  if(DPright.pushed()) {move_selection(1);}
  if(DPright.released()) Serial.println("DPright released");
  //-------------------------------------------------------------------------------------
  DPup.poll();
  if(DPup.switched()) Serial.print("DPup switched ");
  if(DPup.pushed()) {up_button_switcher();}
  if(DPup.released()) Serial.println("DPup released");
  //-------------------------------------------------------------------------------------
  DPdown.poll();
  if(DPdown.switched()) Serial.print("DPdown switched ");
  if(DPdown.pushed()) {down_buttom_switcher();}
  if(DPdown.released()) Serial.println("DPdown released");
  //-------------------------------------------------------------------------------------
  DPcenture.poll();
  if(DPcenture.switched()) Serial.print("DPcenture switched ");
  if(DPcenture.pushed()) {changeDice(2);}
  if(DPcenture.released()) Serial.println("DPcenture released");
  //-------------------------------------------------------------------------------------
}



/*
{
  lcd.cursor();
  if (diection == 0)
    {
    if (x  - 2 < 0)
      {
        x = 14;
      }
    else
      {
          x = ((x - 2) % 16);
      }
    }
    else 
    {
    x = ((x + 2) % 16);
    }
*/