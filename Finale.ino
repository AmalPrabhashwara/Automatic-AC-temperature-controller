#include <IRremote.h> //Lib for IT Blaster and TSOP
#include <DHT.h> //Library for dht11 Temperature and Humidity sensor (Download from Link in article)
#include <LiquidCrystal.h>
#define DHT11_PIN 2//Sensor output pin is connected to pin 13
#define DHTTYPE DHT11
#define up 3
#define down 18
DHT dht(DHT11_PIN, DHTTYPE); //Sensor object named as DHT
LiquidCrystal lcd(26,27,28,29,30,31); 
IRsend irsend;
int CalTemp(int DesTemp,int MesTemp);
int Desired_temperature=23; //The desired temperature is 27*C at any time
int Measured_temp;
int AC_Temp;
char temp_error = 0;//have to be measured using thermometer
int Pev_value=0;
boolean AC = false;
int khz = 38; 

unsigned int  Temp16[] = {8200,3950, 550,1500, 600,400, 600,450, 600,450, 550,1450, 600,500, 550,450, 600,400, 600,450, 600,450, 550,450, 600,450, 550,1500, 550,450, 600,450, 600,450, 550,500, 550,450, 600,450, 550,1450, 600,450, 550,1500, 550,450, 600,1400, 600,1450, 550,1450, 600,1450, 600,450, 550};  // LG 880815E

unsigned int  Temp17[] = {8200,4000, 600,1400, 650,400, 650,350, 650,400, 550,1500, 550,450, 650,400, 550,500, 550,450, 550,500, 550,450, 600,450, 600,1450, 550,450, 550,450, 700,350, 600,450, 600,450, 600,1400, 600,450, 550,500, 500,1500, 650,350, 650,1400, 550,1500, 550,1450, 600,1400, 600,1450, 600};  // LG 880825F

unsigned int  Temp18[] = {8200,3950, 550,1500, 550,450, 600,450, 550,450, 600,1450, 600,450, 550,450, 600,450, 600,450, 550,450, 600,450, 600,450, 550,1450, 600,450, 550,450, 600,450, 600,450, 550,500, 500,1500, 550,1500, 550,450, 550,1500, 550,450, 550,1500, 550,450, 600,450, 550,500, 600,450, 500};  // LG 8808350

unsigned int  Temp19[] = {8200,4000, 600,1450, 600,400, 600,450, 600,400, 600,1400, 650,400, 650,400, 600,400, 650,400, 650,400, 600,450, 600,400, 600,1450, 600,400, 650,400, 600,400, 650,400, 600,1450, 600,400, 600,450, 600,450, 600,1400, 600,450, 550,1450, 600,450, 600,450, 600,450, 550,1450, 550};  // LG 8808451

unsigned int  Temp20[] = {8150,4000, 550,1450, 650,400, 650,400, 600,450, 500,1500, 550,500, 550,500, 500,500, 550,500, 600,400, 550,500, 550,500, 500,1500, 550,500, 600,450, 550,450, 600,450, 500,1550, 550,450, 600,1450, 600,400, 600,1400, 650,450, 500,1500, 550,500, 550,450, 600,1450, 600,400, 600};  // LG 8808552

unsigned int  Temp21[] = {8150,4000, 600,1400, 650,400, 650,400, 600,450, 550,1450, 600,450, 600,400, 650,400, 600,450, 550,500, 600,400, 600,450, 550,1450, 600,450, 550,500, 550,450, 600,450, 550,1500, 500,1500, 550,450, 600,450, 550,1450, 600,450, 550,1500, 550,450, 600,450, 550,1500, 550,1450, 550};  // LG 8808653

unsigned int  Temp22[] = {8200,3950, 550,1450, 600,450, 550,450, 600,450, 550,1450, 550,450, 600,400, 600,450, 550,450, 600,450, 550,450, 550,500, 500,1500, 550,450, 550,450, 600,400, 600,450, 550,1450, 550,1450, 550,1450, 600,450, 550,1450, 600,450, 500,1500, 550,450, 550,1450, 600,400, 600,450, 550};  // LG 8808754

unsigned int  Temp23[] = {8200,3950, 550,1500, 550,450, 550,450, 600,400, 600,1450, 550,450, 600,450, 550,450, 600,400, 600,450, 550,500, 550,450, 550,1450, 600,450, 550,450, 550,450, 550,1450, 600,450, 550,500, 550,450, 550,450, 550,1500, 550,450, 550,1450, 600,400, 550,1500, 550,450, 550,1450, 550};  // LG 8808855

unsigned int Temp24[] = {8150,4000, 550,1500, 500,500, 550,450, 550,500, 500,1450, 600,450, 550,450, 550,500, 500,500, 550,450, 600,400, 600,450, 550,1450, 550,450, 550,500, 500,500, 500,1500, 600,450, 550,450, 550,1450, 550,450, 550,1500, 500,500, 500,1500, 600,400, 550,1450, 550,1450, 550,450, 550};  // LG 8808956
 
unsigned int Temp25[] = {8200,3950, 600,1450, 550,500, 550,450, 600,450, 550,1450, 600,450, 550,500, 600,400, 600,450, 550,500, 550,450, 600,450, 550,1450, 550,500, 550,450, 600,450, 550,1450, 600,450, 550,1450, 600,450, 550,500, 500,1500, 550,500, 500,1500, 550,500, 500,1500, 550,1450, 550,1500, 500};  // LG 8808A57

unsigned int Temp26[] = {8200,3950, 550,1450, 550,500, 550,450, 550,450, 550,1450, 600,450, 550,450, 600,450, 550,450, 550,450, 600,450, 550,450, 550,1450, 600,450, 550,450, 600,450, 500,1500, 550,450, 550,1450, 550,1500, 550,450, 550,1450, 600,450, 500,1500, 550,1450, 550,450, 600,450, 550,450, 550};  // LG 8808B58
  
unsigned int Temp27[] = {8200,3950, 550,1500, 550,450, 550,450, 600,450, 550,1450, 550,450, 600,450, 550,450, 550,500, 550,450, 550,450, 600,450, 550,1450, 550,450, 600,450, 550,450, 550,1450, 550,1450, 600,450, 550,450, 600,450, 500,1500, 550,450, 550,1450, 550,1500, 550,450, 550,450, 550,1500, 500};  // LG 8808C59

unsigned int Temp28[] = {8200,3950, 600,1450, 550,500, 550,450, 600,450, 550,1450, 600,450, 550,450, 600,450, 550,500, 550,450, 600,450, 550,450, 550,1500, 550,450, 600,450, 550,500, 500,1500, 550,1450, 650,400, 550,1450, 600,450, 550,1450, 600,450, 550,1450, 550,1500, 550,450, 550,1500, 550,450, 550};  // LG 8808D5A

unsigned int Temp29[] = {8150,3950, 600,1450, 550,450, 600,450, 550,450, 550,1450, 550,450, 600,450, 550,450, 550,450, 600,450, 550,450, 550,450, 550,1500, 550,450, 550,450, 600,450, 500,1500, 500,1500, 550,1450, 550,450, 600,450, 500,1500, 550,450, 550,1450, 550,1450, 600,450, 500,1500, 550,1450, 550};  // LG 8808E5B

unsigned int Temp30[] = {8150,4000, 550,1500, 500,500, 550,500, 500,450, 600,1450, 550,450, 550,500, 550,450, 550,500, 550,400, 600,450, 550,500, 500,1500, 550,450, 550,450, 550,500, 500,1500, 550,1450, 550,1450, 550,1500, 500,500, 550,1450, 550,450, 550,1450, 550,1500, 500,1500, 600,400, 600,400, 550};  // LG 8808F5C


void setup()
{
Serial.begin(9600);
dht.begin();
lcd.begin(16,2);
attachInterrupt(digitalPinToInterrupt(up), increaseTemp,RISING);
attachInterrupt(digitalPinToInterrupt(down), reduceTemp,RISING);
}

void loop() {
 // mesured_temp = dht.readTemperature();
   Measured_temp= dht.readTemperature()+ temp_error;
   Serial.print("Room Temperature: "); Serial.print(Measured_temp);Serial.print("C");
   lcd.setCursor(0,0);lcd.print("Room T:");lcd.print( Measured_temp);
   Serial.print("##############AC Temp: "); Serial.print(AC_Temp);Serial.println("C");
   lcd.setCursor(0,1);lcd.print("AC T:");lcd.print( AC_Temp); lcd.print(" SET:");lcd.print( Desired_temperature);
   delay(500);

AC_Temp=CalTemp(Desired_temperature,Measured_temp);

if ( Measured_temp != Pev_value) //Change the temperature only if the measured voltage value changes
{
switch(AC_Temp)
{
  case 16:
  sendIR(Temp16); 
  break;
  case 17:
  sendIR(Temp17);
  break;
  case 18:
  sendIR(Temp18);
  break;
  case 19:
  sendIR(Temp19);
  break;
  case 20:
  sendIR(Temp20);
  break;
  case 21:
  sendIR(Temp21);
  break;
  case 22:
  sendIR(Temp22);
  break;
  case 23:
  sendIR(Temp23);
  break;
  case 24:
  sendIR(Temp24);
  break;
  case 25:
  sendIR(Temp25);
  break;
  case 26:
  sendIR(Temp26);
  break;
  case 27:
  sendIR(Temp27);
  break;
  case 28:
  sendIR(Temp28);
  break;
  case 29:
  sendIR(Temp29);
  break;
  case 30:
  sendIR(Temp30);
  break;  
}


}
Pev_value = Measured_temp;
}

int CalTemp(int DesTemp,int MesTemp)
{
  int val=2*DesTemp-MesTemp;
  if(val>30)
  return 30;
  else if(val>15)
  return val;
  else
  return 16;
}

void increaseTemp() 
 {
  Desired_temperature++;
  Serial.print("Desired_temperature=");
  Serial.println(Desired_temperature);
 }

void reduceTemp() 
 {
  Desired_temperature--;
  Serial.print("Desired_temperature =");
  Serial.println(Desired_temperature);
 }
 void sendIR(int Array[])
 {
  for(int i=0;i<5;i++)
  {
  irsend.sendRaw(Array, sizeof(Array) / sizeof(Array[0]), khz);
  delay(1000);
  }
 }

