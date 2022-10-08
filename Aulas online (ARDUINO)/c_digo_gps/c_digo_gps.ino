/*
   Project: NEO-6M GY-GPS6MV2 GPS module
   Function:This sample code demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   
The module GND pin is connected to Arduino GND pin
The module RX pin is connected to Arduino pin 3
The module TX pin is connected to Arduino pin 4
The module VCC pin is connected to Arduino 5V pin
*/
//*************************************************************
#include <TinyGPS++.h>//include the library code
#include <SoftwareSerial.h>//include the library code
//*******************************************************
TinyGPSPlus gps;// The TinyGPS++ object
SoftwareSerial ss(4, 3);// The serial connection to the GPS device
void setup()
{
  Serial.begin(9600);
  ss.begin(9600);

  Serial.println();
  Serial.println(F("Sats HDOP Latitude   Longitude   Fix  Date        Time   Date   Alt    Course Speed"));
  Serial.println(F("---------------------------------------------------------------------------------------------------------------------------------------"));
}

void loop()
{
  static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;

  printInt(gps.satellites.value(), gps.satellites.isValid(), 5); // satelites
  Serial.print(",");
  printInt(gps.hdop.value(), gps.hdop.isValid(), 5); //acurácia
  Serial.print(",");
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6); // latitude
  Serial.print(",");
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6); // longitude
  Serial.print(",");
  printInt(gps.location.age(), gps.location.isValid(), 5); // fix?
  Serial.print(",");
  printDateTime(gps.date, gps.time); //datatempo
  Serial.print(",");
  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2); //altitude
  Serial.print(",");
  printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
  Serial.print(",");
  printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
  Serial.print(",");
  


  Serial.println();
  
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartDelay(0);
}
