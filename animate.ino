#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

const  int  LCD_NB_ROWS  =  4 ;
const  int  LCD_NB_COLUMNS  =  20 ;

/* Caractères personnalisés */
byte START_DIV_0_OF_4[8] = {
  B01111,
  B11000,
  B10000,
  B10000,
  B10000,
  B10000,
  B11000,
  B01111
}; // Char début 0 / 4

byte START_DIV_1_OF_4[8] = {
  B01111,
  B11000,
  B10000,
  B10000,
  B10000,
  B10011,
  B11000,
  B01111
}; // Char début 1 / 4

byte START_DIV_2_OF_4[8] = {
  B01111,
  B11000,
  B10000,
  B10000,
  B10111,
  B10011,
  B11000,
  B01111
}; // Char début 2 / 4

byte START_DIV_3_OF_4[8] = {
  B01111,
  B11000,
  B10000,
  B10111,
  B10111,
  B10011,
  B11000,
  B01111
}; // Char début 3 / 4

byte START_DIV_4_OF_4[8] = {
  B01111,
  B11000,
  B10011,
  B10111,
  B10111,
  B10011,
  B11000,
  B01111
}; // Char début 4 / 4

byte DIV_0_OF_8[8] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
}; // Char milieu 0 / 8

byte DIV_1_OF_8[8] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B11000,
  B00000,
  B11111
}; // Char milieu 1 / 8

byte DIV_2_OF_8[8] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B11000,
  B11000,
  B00000,
  B11111
}; // Char milieu 2 / 8

byte DIV_3_OF_8[8] = {
  B11111,
  B00000,
  B00000,
  B11000,
  B11000,
  B11000,
  B00000,
  B11111
}; // Char milieu 3 / 8

byte DIV_4_OF_8[8] = {
  B11111,
  B00000,
  B11000,
  B11000,
  B11000,
  B11000,
  B00000,
  B11111
}; // Char milieu 4 / 8

byte DIV_5_OF_8[8] = {
  B11111,
  B00000,
  B11000,
  B11000,
  B11000,
  B11011,
  B00000,
  B11111
}; // Char milieu 5 / 8

byte DIV_6_OF_8[8] = {
  B11111,
  B00000,
  B11000,
  B11000,
  B11011,
  B11011,
  B00000,
  B11111
}; // Char milieu 6 / 8

byte DIV_7_OF_8[8] = {
  B11111,
  B00000,
  B11000,
  B11011,
  B11011,
  B11011,
  B00000,
  B11111
}; // Char milieu 7 / 8

byte DIV_8_OF_8[8] = {
  B11111,
  B00000,
  B11011,
  B11011,
  B11011,
  B11011,
  B00000,
  B11111
}; // Char milieu 8 / 8

byte END_DIV_0_OF_4[8] = {
  B11110,
  B00011,
  B00001,
  B00001,
  B00001,
  B00001,
  B00011,
  B11110
}; // Char fin 0 / 4

byte END_DIV_1_OF_4[8] = {
  B11110,
  B00011,
  B00001,
  B00001,
  B00001,
  B11001,
  B00011,
  B11110
}; // Char fin 1 / 4

byte END_DIV_2_OF_4[8] = {
  B11110,
  B00011,
  B00001,
  B00001,
  B11101,
  B11001,
  B00011,
  B11110
}; // Char fin 2 / 4

byte END_DIV_3_OF_4[8] = {
  B11110,
  B00011,
  B00001,
  B11101,
  B11101,
  B11001,
  B00011,
  B11110
}; // Char fin 3 / 4

byte END_DIV_4_OF_4[8] = {
  B11110,
  B00011,
  B11001,
  B11101,
  B11101,
  B11001,
  B00011,
  B11110
}; // Char fin 4 / 4



#include <stdio.h>
#include <Wire.h>
#include <TimeLib.h>
#include "PrayerTimes.h"

double times[sizeof(TimeName) / sizeof(char*)];

void p(char *fmt, ... ) {
  char tmp[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 128, fmt, args);
  va_end (args);
  Serial.print(tmp);
}

#include "RTClib.h"
RTC_DS1307 rtc;
uint32_t unixxtime;


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long previousMillisforChange = 0;

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)
const long intervalforChange = 2250;

#define countof(a) (sizeof(a) / sizeof(a[0]))

/**
   Fonction de configuration de l'écran LCD pour la barre de progression.
   Utilise tous les caractéres personnalisés de 0 à 8.
*/
void setup_progressbar() {

  /* Enregistre les caractères personnalisés dans la mémoire de l'écran LCD */
  lcd.createChar(0, START_DIV_4_OF_4);
  lcd.createChar(1, DIV_0_OF_8);
  lcd.createChar(2, DIV_8_OF_8);
  lcd.createChar(3, END_DIV_0_OF_4);
  // Les autres caractéres sont configurés dynamiquement
}


/**
   Fonction de configuration dynamique de l'écran LCD pour la barre de progression.

   @param bank Le numéro de la banque de caractéres à configurer.
*/
void switch_progressbar_bank(byte bank) {

  // IMPORTANT : Il est nécessaire de faire un lcd.clear() ou un lcd.setCursor() aprés chaque changement de banque.

  /* Change de banque de caractères */
  switch (bank) {
    case 0:
      lcd.createChar(4, START_DIV_0_OF_4);
      lcd.createChar(5, START_DIV_1_OF_4);
      lcd.createChar(6, START_DIV_2_OF_4);
      lcd.createChar(7, START_DIV_3_OF_4);
      break;

    case 1:
      lcd.createChar(4, DIV_1_OF_8);
      lcd.createChar(5, DIV_2_OF_8);
      lcd.createChar(6, DIV_3_OF_8);
      lcd.createChar(7, DIV_4_OF_8);
      break;

    case 2:
      lcd.createChar(4, DIV_4_OF_8);
      lcd.createChar(5, DIV_5_OF_8);
      lcd.createChar(6, DIV_6_OF_8);
      lcd.createChar(7, DIV_7_OF_8);
      break;

    case 3:
      lcd.createChar(4, END_DIV_1_OF_4);
      lcd.createChar(5, END_DIV_2_OF_4);
      lcd.createChar(6, END_DIV_3_OF_4);
      lcd.createChar(7, END_DIV_4_OF_4);
      break;
  }
}


/**
   Fonction dessinant la barre de progression.

   @param percent Le pourcentage à afficher.
*/
void draw_progressbar(byte percent, byte line) {
  lcd.setCursor(2, 1);
  lcd.print("Initialising");

  /* Déplace le curseur sur la ligne */
  lcd.setCursor(0, line);

  /* Map la plage (0 ~ 100) vers la plage (0 ~ (LCD_NB_COLUMNS - 4) * 2 * 4 - 2 * 4) */
  byte nb_columns = map(percent, 0, 100, 0, (LCD_NB_COLUMNS - 4) * 2 * 4 - 2 * 4);
  // Chaque caractére affiche 2 barres verticales de 4 pixels de haut, mais le premier et dernier caractére n'en affiche qu'une.

  /* Dessine chaque caractére de la ligne */
  for (byte i = 0; i < LCD_NB_COLUMNS - 4; ++i) {

    if (i == 0) { // Premiére case

      /* Affiche le char de début en fonction du nombre de colonnes */
      if (nb_columns > 4) {
        lcd.write((byte) 0); // Char début 4 / 4
        nb_columns -= 4;

      } else if (nb_columns == 4) {
        lcd.write((byte) 0); // Char début 4 / 4
        nb_columns = 0;

      } else {
        switch_progressbar_bank(0);
        lcd.setCursor(i, line);
        lcd.write(nb_columns + 4); // Char début N / 4
        nb_columns = 0;
      }

    } else if (i == LCD_NB_COLUMNS - 5) { // Derniére case

      /* Affiche le char de fin en fonction du nombre de colonnes */
      if (nb_columns > 0) {
        switch_progressbar_bank(3);
        lcd.setCursor(i, line);
        lcd.write(nb_columns + 3); // Char fin N / 4

      } else {
        lcd.write(3); // Char fin 0 / 4
      }

    } else { // Autres cases

      /* Affiche le char adéquat en fonction du nombre de colonnes */
      if (nb_columns == 0) {
        lcd.write(1); // Char div 0 / 8

      } else if (nb_columns >= 8) {
        lcd.write(2); // Char div 8 / 8
        nb_columns -= 8;

      } else if (nb_columns >= 4 && nb_columns < 8) {
        switch_progressbar_bank(2);
        lcd.setCursor(i, line);
        lcd.write(nb_columns); // Char div N / 8
        nb_columns = 0;

      } else if (nb_columns < 4) {
        switch_progressbar_bank(1);
        lcd.setCursor(i, line);
        lcd.write(nb_columns + 3); // Char div N / 8
        nb_columns = 0;
      }
    }
  }

  /* Affiche le pourcentage */
  char tmp[5];
  sprintf(tmp, "%3d%%", percent);
  lcd.print(tmp);
}




/** Fonction setup() */
void setup() {

 

  while (!Serial); // for Leonardo/Micro/Zero

  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  }

  /* Initialise l'écran LCD */
  lcd.begin(LCD_NB_COLUMNS, LCD_NB_ROWS);
  setup_progressbar();
  lcd.clear();



  for (int i = 0; i <= 100; i++) {
    static byte percent = 0;
    draw_progressbar(percent, 2);
    percent++;
  }
  lcd.clear();

}

int var1 = 0;

/** Fonction loop() */
void loop() {
DateTime now = rtc.now();
unixxtime  = now.unixtime();
setTime(unixxtime);


  /* Valeur en pourcent de la barre de progression */
  int dst = 1;

  set_calc_method(ISNA);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(15);
  set_isha_angle(15);


  get_prayer_times(year(), month(), day(), 51.373591, -0.211379, 1, times);
  Serial.println(TimeName[0]);
  Serial.println(times[0]);
  Serial.print(now.year());

  

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

//    Serial.print(now.year(), DEC);
//    Serial.print('/');
//    Serial.print(now.month(), DEC);
//    Serial.print('/');
//    Serial.print(now.day(), DEC);

  }

  unsigned long currentMillisforChange = millis();

  if (currentMillisforChange - previousMillisforChange >= intervalforChange) {
    // save the last time you blinked the LED
    previousMillisforChange = currentMillisforChange;


    var1++;
    if (var1 == 6) {
      var1 = 1;
    }
    clearLCDLine(2);


  }

  //  RtcDateTime now = Rtc.GetDateTime();
  //
  //  char timestring[10];
  //
  //    snprintf_P(timestring,
  //            countof(timestring),
  //            PSTR("%02u:%02u:%02u"),
  //            now.Hour(),
  //            now.Minute(),
  //            now.Second() );
  //    Serial.print(timestring);


  // Let's figure out when the next prayer is //
  double currTime = now.hour() + now.minute() / 60.0;
  int h;

  for (h = 0; h < sizeof(times) / sizeof(double); h++)
  {
    if (times[h] >= currTime)
      break;
  }
  if ((times[h] - currTime) < 0)
  {
    h = 0;
    //pTime = times[i];
  }


  char TimeString[10]; //9 digits plus the null char
  sprintf(TimeString, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());


  int fajrTimeHour = (int)times[0];
  int fajrTimeMinute = (times[0] - fajrTimeHour) * 60;
  char fajrTimeHourMin[6];
  sprintf(fajrTimeHourMin, "%02d:%02d", fajrTimeHour, fajrTimeMinute);

  int dhuhrTimeHour = (int)times[2];
  int dhuhrTimeMinute = (times[2] - dhuhrTimeHour) * 60;
  char dhuhrTimeHourMin[6];
  sprintf(dhuhrTimeHourMin, "%02d:%02d", dhuhrTimeHour, dhuhrTimeMinute);

  int asrTimeHour = (int)times[3];
  int asrTimeMinute = (times[3] - asrTimeHour) * 60;
  char asrTimeHourMin[6];
  sprintf(asrTimeHourMin, "%02d:%02d", asrTimeHour, asrTimeMinute);

  int maghribTimeHour = (int)times[5];
  int maghribTimeMinute = (times[5] - maghribTimeHour) * 60;
  char maghribTimeHourMin[6];
  sprintf(maghribTimeHourMin, "%02d:%02d", maghribTimeHour, maghribTimeMinute);

  int ishaTimeHour = (int)times[6];
  int ishaTimeMinute = (times[6] - ishaTimeHour) * 60;
  char ishaTimeHourMin[6];
  sprintf(ishaTimeHourMin, "%02d:%02d", ishaTimeHour, ishaTimeMinute);

  int nextTimeHour = (int)times[h];
  int nextTimeMinute = (times[h] - nextTimeHour) * 60;
  char nextTimeHourMin[6];
  sprintf(nextTimeHourMin, "%02d:%02d", nextTimeHour, nextTimeMinute);

  lcd.setCursor(3, 0);
  lcd.print("Habeeb's Clock");
  lcd.setCursor(6, 1);
  lcd.print(TimeString);
  
 
  lcd.setCursor(3, 3);
  lcd.print(TimeName[h] + String(":"));

  lcd.setCursor(12, 3);
  lcd.print(nextTimeHourMin);


  lcd.setCursor(0, 0);
  lcd.print(var1);



  switch (var1) {
    case 1:

      lcd.setCursor(3, 2);
      lcd.print("Fajr:");
      lcd.setCursor(12, 2);
      lcd.print(fajrTimeHourMin);
      break;
    case 2:

      lcd.setCursor(3, 2);
      lcd.print("Dhuhr:");
      lcd.setCursor(12, 2);
      lcd.print(dhuhrTimeHourMin);
      break;
    case 3:
      lcd.setCursor(3, 2);
      lcd.print("Asr:");
      lcd.setCursor(12, 2);
      lcd.print(asrTimeHourMin);
      break;
    case 4:
      lcd.setCursor(3, 2);
      lcd.print("Maghrib:");
      lcd.setCursor(12, 2);
      lcd.print(maghribTimeHourMin);
      break;
    case 5:
      lcd.setCursor(3, 2);
      lcd.print("Isha:");
      lcd.setCursor(12, 2);
      lcd.print(ishaTimeHourMin);
      break;
  }

}

void clearLCDLine(int line)
{
  lcd.setCursor(0, line);
  for (int n = 0; n < 20; n++) // 20 indicates symbols in line. For 2x16 LCD write - 16
  {
    lcd.print(" ");
  }
}

char *getNextPTimeName(/*double &pTime,*/ char *pTimeName)
{
  DateTime now = rtc.now();

  double currTime = now.hour() + now.minute() / 60.0;
  int i;

  set_calc_method(ISNA);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(OneSeventh);

  //get_prayer_times(year(), month(), day(), 46.9500, 7.4458, 1, times);
  get_prayer_times(now.year(), now.month(), now.day(), 51.373176, -0.210757, 1, times);
  for (i = 0; i < sizeof(times) / sizeof(double); i++)
  {
    if (times[i] >= currTime)
      break;
  }
  if ((times[i] - currTime) < 0)
  {
    i = 0;
    //pTime = times[i];
  }
  //pTime = times[i];
  //sprintf(pTimeName, "%s", TimeName[i]);
  //Serial.println(pTimeName);
  //Serial.println( TYPE_NAME(pTimeName) );
  return pTimeName;
}

double &getNextPTime(double &pTime, char *pTimeName)
{
  DateTime now = rtc.now();

  double currTime = now.hour() + now.minute() / 60.0;
  int i;

  set_calc_method(ISNA);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(OneSeventh);

  

  //get_prayer_times(year(), month(), day(), 46.9500, 7.4458, 1, times);
  get_prayer_times(now.year(), now.month(), now.day(), 51.373176, -0.210757, 1, times);
  for (i = 0; i < sizeof(times) / sizeof(double); i++)
  {
    if (times[i] >= currTime)
      break;
  }
  if ((times[i] - currTime) < 0)
  {
    i = 0;
    //pTime = times[i];
  }
  //pTime = times[i];
  //sprintf(pTimeName, "%s", TimeName[i]);
  //Serial.println(pTimeName);
  return pTime;

}
