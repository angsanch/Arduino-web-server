#include <SD.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip (192, 168, 0, 202);
EthernetServer server (42069);

void setup (){
  //SD card initialization
  Serial.begin (9600);
  Serial.println ("Initializing SD card...");
  if (!SD.begin (4)){
    Serial.println ("SD card initialization failed!");
  }else{
    Serial.println ("SD card initialization succesful!");
  }

  //Ethernet initialization
  Ethernet.begin (mac, ip);
  server.begin ();
  Serial.print ("Server started at ");
  Serial.println (Ethernet.localIP ());
}
void loop (){
  
}
