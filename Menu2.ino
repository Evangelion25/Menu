//Libraries used on the project//

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Defining pins and variables//
int downb = 10;
int upb= 11;
int selectb = 12;
int ext = 13;
int menu = 1;
int ONE_WIRE_BUS = 8;
int SENSOR = 9;

int temp1;
int hum1;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DHT dht(SENSOR,DHT11);

//Instructions for each pin//
void setup() {
  lcd.begin();
  lcd.backlight();
  pinMode(upb, INPUT_PULLUP);
  pinMode(downb, INPUT_PULLUP);
  pinMode(selectb, INPUT_PULLUP);
  pinMode(ext, INPUT_PULLUP);
  pinMode(2, INPUT);
  sensors.begin();
  dht.begin();
  updateMenu();
}
// Buttons interaction//
void loop() { 
  //up button//
    if (!digitalRead(upb)){
     menu ++;
     updateMenu();
     delay(100);
     while(!digitalRead(upb));
    }
//down button//
    if (!digitalRead(downb)){ 
     menu --;
     updateMenu();
     delay(100);
     while(!digitalRead(downb));
    }
//select button//
    if(!digitalRead(selectb)){
     executeAction();
     delay(100);
     while(!digitalRead(selectb));
    }
//exit button//
    if(!digitalRead(ext)){
      updateMenu();
      delay(100);
      while(!digitalRead(ext));
    }
  }
// Menu funtions//
void updateMenu() {
  switch (menu) {
    case 0:
      menu = 1;
    case 1:
      lcd.clear();
      lcd.print(">Sensor1");
      lcd.setCursor(0, 1);
      lcd.print(" Sensor2");
      break;
    case 2: 
      lcd.clear();
      lcd.print(" Sensor1");
      lcd.setCursor(0, 1);
      lcd.print(">Sensor2");
      break;
    case 3:
      lcd.clear();
      lcd.print(">Sensor3");
      lcd.setCursor(0, 1);
      lcd.print(" Sensor4");
      break;
    case 4:
      lcd.clear();
      lcd.print(" Sensor3");
      lcd.setCursor(0, 1);
      lcd.print(">Sensor4");
      break;
    case 5:
      menu = 4;
      break;
 }
}
//Execution of the sensors//
void executeAction(){
  switch (menu) {
    case 1:
      actsensor1();
      break;
    case 2:
      actsensor2();
      break;
    case 3:
      actsensor3();
      break;
    case 4:
      actsensor4();
      break; 
  }
}

//Individual funtions for the sensors//

//Soil sensor funtion//
void actsensor1(){
  int val = analogRead(A0);
  int h = ((val)*-.160513)+ 164.2047;

  lcd.setCursor(0,0);
  lcd.print("Humedad: ");
  lcd.print(h);
  lcd.print("%");

  lcd.setCursor (0,1);
  lcd.print("de la tierra");
  delay(100);
}
//DS18B20 sensor funtion//
void actsensor2(){
  sensors.requestTemperatures();

  float temp = sensors.getTempCByIndex(0);
  int t = temp; 
 
  lcd.setCursor (0, 0 );
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");
  delay(100);
  
  lcd.setCursor (0,1);
  lcd.print("            ");
  delay(100);
}
//DHT11 sensor funtion//
void actsensor3(){
 hum1 = dht.readHumidity();    
 temp1 = dht.readTemperature();
  
  lcd.setCursor(0,0);              
  lcd.print("Humedad ");
  lcd.print(hum1);
  lcd.print(" %");                     
            
  lcd.setCursor(0,1);
  lcd.print("Temp "); 
  lcd.print(temp1);
  lcd.print(" C");                   
  delay (100);
}
//Just a message//
void actsensor4(){

  lcd.setCursor(0,0);
  lcd.print("There you go man");
  lcd.setCursor (0,1);
  lcd.print("            ");
  delay(100);
  
}
