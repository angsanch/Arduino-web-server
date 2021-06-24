#include <SD.h>
#include <Ethernet.h>

void setup (){
  Serial.begin (9600);

  Serial.println ("Initializing SD card...");
  if (!SD.begin (4)){
    Serial.println ("SD card initialization failed!");
  }else{
    Serial.println ("SD card initialization succesful!");
  }
}
void loop (){
  
}
