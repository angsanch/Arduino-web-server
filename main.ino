#include <SPI.h>
#include <SD.h>
#include <Ethernet.h>


String getPath (String input) {
  int index = input.indexOf ("?");
  if (index != -1) {
    return input.substring (1, index);//If there are args
  }
  return input.substring (1, input.length ());//If there isnt any args
}
String getArgs (String input) {
  int index = input.indexOf ("?");
  if (index != -1) {
    return input.substring (index + 1, input.length ());//If there are args
  }
  return "";//If there isnt any args
}

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip (192, 168, 138, 202);
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
    String type = "";
    int add = 0;
    while (client.connected ()) {
      if (client.available ()) {
        char readed = client.read ();

        if (readed == ' ') {
          add ++;
        } else {
          switch (add) {
            case 0:
              type += readed;
              break;
            case 1:
              request += readed;
              break;
          }
        }

        if (readed == '\n') {
          client.println ("HTTP/1.1 200 OK");
          client.println ("Content-Type: text/html");
          client.println ("Connection: close");
          client.println ();

          //Process and send response to the request
          Serial.println (type);
          if (type == "GET") {
            processGET (client, getPath (request), getArgs (request));//Redirect processing to a specialized function
          } else if (type == "POST") {
            Serial.println ("post request");
          }

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
