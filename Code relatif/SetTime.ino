//FONCTION POUR MODIFIER L'HEURE
#include <Time.h>
void setup() {
  Serial.begin(9600);
  setTime(10,10,00,01,12,2019); 
  

}

void loop() {
  
  dayStr();
  
  
}
