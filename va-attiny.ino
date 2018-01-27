/*
this sketch is adapted by niq_ro from
http://www.tehnic.go.ro
http://www.niqro.3x.ro
http://nicuflorica.blogspot.ro/
http://arduinotehniq.blogspot.com/
for made a dual thermometer & battery status for car with ATtiny85 as Arduino..

 * 3-pin Arduino interface for HD44780 LCDs via 74HC595 Shift Register
 *     by Rowan Simms   code@rowansimms.com
 *     License: Creative Commons - Attribution.
 *     Full Documentation and Description:  http://rowansimms.com/article.php/lcd-hookup-in-seconds
 *
 * This sketch allows Arduinos to use a shift register to control an LCD, allowing 
 * a reduction in pins it requires from 6 to 3 while still retaining full control
 * including backlight on/off.
 * This requires the use of the LiquidCrystal595 library
 * available at:https://bitbucket.org/rowansimms/arduino-lcd-3pin/downloads/
 * http://nicuflorica.blogspot.ro/2015/01/termometru-dublu-si-indicator-tensiune.html
 * http://nicuflorica.blogspot.ro/2017/07/programator-pentru-attiny254585-cu.html
 */

#include <LiquidCrystal595.h>    // include the library
LiquidCrystal595 lcd(0,1,2);     // datapin, latchpin, clockpin pb0, pb1, pb2


#define VT_PIN A3 //pin2 pb3
#define AT_PIN A2 //pin3 pb4
unsigned long tpmasurare;  // variabila pentru memorare timp masurare (in ms)
float sumatensiune = 0.;   // valoare insumare tensiune pentru calcul medie
float sumacurent = 0.; // valoare insumare curent pentru calcul medie
float current = 0.;   // valoare curent
float tensiune = 0.; // valoare tensiune
int trcurent = 0;
int trtensiune = 0;

void setup() {
   analogReference(INTERNAL); 
  
    lcd.begin(8,2);             // 8characters, 2 rows
 


 lcd.clear(); // clear the screen
 lcd.setCursor(0, 0); 
 lcd.print("ATtiny85"); // print a text
 lcd.setCursor(3, 1); 
 lcd.print("V-A"); // print a text
 delay (1500);
 lcd.clear(); // clear the screen


 lcd.setCursor(0, 1); 
 lcd.print("@ VladGh"); 
 delay (1000);
 lcd.clear(); 
 uint16_t time = millis();
}


void loop() {
sumatensiune = 0;
// sumatensiunei = 0;
  sumacurent = 0;
    for (int i=1; i <= 20; i++)
  {
 trtensiune = analogRead(VT_PIN);
 sumatensiune = sumatensiune + trtensiune;
  trcurent = analogRead(AT_PIN);

  sumacurent = sumacurent + trcurent;
delay (100);  // pauza de 100ms intre masuratori
    }

// calculam valorile medii
sumacurent = sumacurent/20.;
sumatensiune = sumatensiune/20.;

  tensiune=(float)(99.66+.467)/.467*1*sumatensiune/1023-.72;

 current=(float)1/0.22*sumacurent/1023;
 
 
  lcd.setCursor(0, 0);
    lcd.print("U=");
    if (tensiune < 10.0) lcd.print(" ");  // daca tensiunea e mai mica de 10V 
    lcd.print(tensiune);
    lcd.print("V");
     lcd.setCursor(0, 1);
    lcd.print("I=");
    if (current < 10.0) lcd.print(" ");  // daca curentul e mai mic de 10A 
    lcd.print(current);
    lcd.print("A");
    lcd.setCursor(0, 1);
   
}
