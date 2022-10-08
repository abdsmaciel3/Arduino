#include <Adafruit_GPS.h>
#ifdef __AVR__
#include <SoftwareSerial.h>
#endif
#include <LiquidCrystal.h>
#define mySerial Serial
Adafruit_GPS GPS(&mySerial);
#define GPSECHO true
 
boolean usingInterrupt = false;
void useInterrupt(boolean);
 
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
 
void setup() 
{
 lcd.begin(16, 2);
 Serial.begin(115200);
 Serial.println("www.usinainfo.com.br");
 
 GPS.begin(9600);
 mySerial.begin(9600);
 
 GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
 
 GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); 
 
 GPS.sendCommand(PGCMD_ANTENNA);
 
#ifdef __arm__
 usingInterrupt = false; 
#else
 useInterrupt(true);
#endif
 
 mySerial.println(PMTK_Q_RELEASE);
 
 lcd.print("UsinaInfo");
 lcd.setCursor(0, 1);
 lcd.print("Aguardando GPS");
 
 delay(5000);
 lcd.clear();
 
}
 
#ifdef __AVR__
 
SIGNAL(TIMER0_COMPA_vect) {
 char c = GPS.read();
 
#ifdef UDR0
 if (GPSECHO)
 if (c) UDR0 = c; 
 
#endif
}
 
void useInterrupt(boolean v) {
 if (v) {
 
 OCR0A = 0xAF;
 TIMSK0 |= _BV(OCIE0A);
 usingInterrupt = true;
 } 
 else {
 
 TIMSK0 &= ~_BV(OCIE0A);
 usingInterrupt = false;
 }
}
#endif //#ifdef__AVR__
 
uint32_t timer = millis();
void loop() 
{
 
 for(int tst1=0; tst1<8; tst1++)
 {
 
 if (! usingInterrupt) {
 
 char c = GPS.read();
 
 if (GPSECHO)
 if (c) Serial.print(c);
 }
 
 if (GPS.newNMEAreceived()) {
 
 if (!GPS.parse(GPS.lastNMEA())) 
 return; 
 }
 
 if (timer > millis()) timer = millis();
 
 if (millis() - timer > 2000) { 
 timer = millis();
 
 float var = GPS.speed;
 var = var*1.852;
 
 Serial.print("nTime: ");
 Serial.print(GPS.hour, DEC); 
 Serial.print(':');
 Serial.print(GPS.minute, DEC); 
 Serial.print(':');
 Serial.print(GPS.seconds, DEC); 
 Serial.print('.');
 Serial.println(GPS.milliseconds);
 Serial.print("Date: ");
 Serial.print(GPS.day, DEC); 
 Serial.print('/');
 Serial.print(GPS.month, DEC); 
 Serial.print("/20");
 Serial.println(GPS.year, DEC);
 Serial.print("Fix: "); 
 Serial.print((int)GPS.fix);
 Serial.print(" quality: "); 
 Serial.println((int)GPS.fixquality); 
 Serial.print(GPS.longitude, 4); 
 Serial.print(GPS.lon);
 Serial.print("Speed (Km/H): "); 
 Serial.println(var);
 Serial.print("Altitude: "); 
 Serial.println(GPS.altitude);
 Serial.print("Sat: "); 
 Serial.println((int)GPS.satellites);
 
 // if (GPS.fix) 
 // {
 
 lcd.setCursor(0,0);
 lcd.print("-");
 lcd.print(GPS.latitude, 4);
 lcd.print(GPS.lat);
 lcd.setCursor(0,1);
 lcd.print("-");
 lcd.print(GPS.longitude, 4);
 lcd.print(GPS.lon);
 
 delay(2000);
 }
 
 lcd.clear();
 
 for(int tst=0; tst<8; tst++)
 { 
 float var = GPS.speed;
 var = var*1.852;
 
 lcd.print(var);
 lcd.println("Km/H");
 lcd.setCursor(0,1);
 lcd.print("Sat: "); 
 lcd.print((int)GPS.satellites);
 
 delay(1000); 
 lcd.clear();
 }
 }
}
