#include <SD.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip (192, 168, 0, 202);
EthernetServer server (42069);

void setup () {
  //SD card initialization
  Serial.begin (9600);
  Serial.println ("Initializing SD card...");
  if (!SD.begin (4)) {
    Serial.println ("SD card initialization failed!");
  } else {
    Serial.println ("SD card initialization succesful!");
  }

  //Ethernet initialization
  Ethernet.begin (mac, ip);
  server.begin ();
  Serial.print ("Server started at ");
  Serial.println (Ethernet.localIP ());
}
void loop () {
  EthernetClient client = server.available ();
  if (client) {
    Serial.println ("Connection started");
    String request = "";
    boolean add = false;
    while (client.connected ()) {
      if (client.available ()) {
        char readed = client.read ();
        if (add) {
          request += readed;
        }
        add = add == ((readed == ' ') == false); //Toggle add if readed char is an space
        if (readed == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Recieved");
          Serial.println (request);
          Serial.println ("------------");
          break;
        }
      }
    }
    delay (1);
    client.stop ();
  }
}
