//LIBRAIRIES:
//ecran LCD
#include <LiquidCrystal.h>
//horloge/temps
#include <Wire.h>
#include "RTClib.h"
#include <TimeLib.h>
#include<DS1307RTC.h>
//buzzer
#include "pitches.h"
//moteur pas à pas 
#include <Stepper.h>


RTC_DS1307 rtc;


//PARAMETRES ECRAN LCD
  LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // initialise les commandes avec les n° de broches
  
// notes in the melody:
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int duration = 500;  // 500 miliseconds

//Moteur pas à pas 
#define IN1 12
#define IN2 13
#define IN3 14
#define IN4 15
int temps =10;
int i=0;
const int nombrePas = 32*64;
Stepper monMoteur(nombrePas, IN1, IN2, IN3, IN4);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2); 
  Serial.begin(9600);
  lcd.print("Il est :"); 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT); 
  monMoteur.setSpeed(1);

}

//Met un 0 devant pour obtenir 09H01 par exemple au lieu de 9H1
void print3digits(int number) {
  if (number >= 0 && number < 10) {
    lcd.print('0');
  }
  lcd.print(number);
}
//Affiche l'heure sur l'écran LCD
void printOnLCD(){
  tmElements_t tm;
  if (RTC.read(tm)) {
  lcd.setCursor(0, 1); //le curseur se positionne à la 1ère colonne, 2ième ligne 
  print3digits(tm.Hour);
  lcd.print("h");
  print3digits(tm.Minute);
  }
}

void heureDePrise(int heureMatin, int minuteMatin, int heureMidi, int minuteMidi ,int heureSoir, int minuteSoir){
  DateTime now = rtc.now();
  tmElements_t tm;
  Serial.println(now.hour());
  Serial.println(now.minute());

  if ((now.hour() == heureMatin && now.minute() == minuteMatin) or (now.hour()==heureMidi && now.minute()==minuteMidi) or (now.hour()==heureSoir && now.minute()==minuteSoir)) {
    Serial.println("C'est bon");
    /*for (int thisNote = 0; thisNote < 8; thisNote++) {
    // pin8 output the voice, every scale is 0.5 sencond
    tone(11, melody[thisNote], duration);
     
    // Output the voice after several minutes
    delay(100);
    }*/
    for (i=0; i <= 511; i++){
      Serial.println(i);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      delay(temps);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      delay(temps);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      delay(temps);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      delay(temps); 
      monMoteur.step(nombrePas);
      delay(500);
    }
      }
 
  else{
    Serial.println("L'alarme ne doit pas sonner");
  }
}

// moteur 28ybj-48

void loop() {
  // put your main code here, to run repeatedly:
  printOnLCD();
  heureDePrise(9,50, 12,16,20,35);

}
