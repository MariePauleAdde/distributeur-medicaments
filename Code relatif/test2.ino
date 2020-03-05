//LIBRAIRIES:

//ecran LCD
#include <LiquidCrystal.h>

//horloge/temps
#include <Wire.h>
#include "RTClib.h"
#include <TimeLib.h>
#include<DS1307RTC.h>
RTC_DS1307 rtc;

//buzzer
#include "pitches.h"

//PARAMETRES moteur pas à pas 
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 12
int temps =10;
int i=0;

//On a 9 hélices qui correspondent aux 9 prises.
int nbrPrises=9;
//a pour vérifier qu'il y a bien 1/9 de tour seulement 
int a=0;

//PARAMETRES ECRAN LCD
  LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // initialise les commandes avec les n° de broches
  
// notes in the melody:
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int duration = 1000;  // 500 miliseconds


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  
  //SET UP LCD
  lcd.begin(16, 2); 
  lcd.print("Il est :"); 
  
  //SET UP MOTEUR 
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);

}

//Fonction pour corriger l'affichage de l'heure sur l'écran lcd 
void print3digits(int number) {
  if (number >= 0 && number < 10) {
    lcd.print('0');
  }
  lcd.print(number);
}

//Fonction qui fiche l'heure sur l'écran LCD
void printOnLCD(){
  tmElements_t tm;
  if (RTC.read(tm)) {
  lcd.setCursor(0, 1); //le curseur se positionne à la 1ère colonne, 2ième ligne 
  print3digits(tm.Hour);
  lcd.print("h");
  print3digits(tm.Minute);
  }
}

//Fonction qui fait faire au moteur 1/9 de tour 
void tour(int nbrPrises){
      //Mettre le moteur en marche 
    for (i=0; i <= 55; i++){
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
    }
  
}

//Fonction qui à l'heure de prise du médicament va mettre en rotation le moteur et lancer une alarme 
void heureDePrise(int heureMatin, int minuteMatin, int heureMidi, int minuteMidi ,int heureSoir, int minuteSoir){
  DateTime now = rtc.now();
  tmElements_t tm;
  Serial.println(now.hour());
  Serial.println(now.minute());

  if ((now.hour() == heureMatin && now.minute() == minuteMatin) or (now.hour()==heureMidi && now.minute()==minuteMidi) or (now.hour()==heureSoir && now.minute()==minuteSoir)) {

    //Test sur moniteur série
    Serial.println("C'est bon");

    //Mettre le buzzer en marche 
    for (int thisNote = 0; thisNote < 8; thisNote++) {
    // pin8 output the voice, every scale is 0.5 sencond
    tone(11, melody[thisNote], duration);
    // Output the voice after several minutes
    delay(300);
    }
    
    //Afficher sur l'écran lcd 
    lcd.clear();
    lcd.print("Prenez votre");
    lcd.setCursor(0, 1);
    lcd.print("medicament");

          //Mettre en marche le moteur 
    if (a==0){
    tour(9);
    a=a+1;
    }

    
  }
  
  else{
    a=0;
    Serial.println("L'alarme ne doit pas sonner");
    lcd.clear();
    lcd.print("Il est:");
    printOnLCD();
    
    
  }
}



void loop() {
  // put your main code here, to run repeatedly:
  // put your main code here, to run repeatedly:
  heureDePrise(16,17, 12,16,20,35);
  delay(1000);

}
