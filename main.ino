#include <SPI.h>
#include <SdFat.h>
#include <Ethernet.h>

SdFat sd;

String getPath (String input) {
  int index = input.indexOf ("?");
  if (index != -1) {
    return input.substring (0, index);//If there are args
  }
  return input.substring (0, input.length ());//If there isnt any args
}
String getArgs (String input) {
  int index = input.indexOf ("?");
  if (index != -1) {
    return input.substring (index + 1, input.length ());//If there are args
  }
  return "";//If there isnt any args
}

EthernetServer server (42069);

EthernetClient list_clients [0];
bool list_availability [0];
File32 list_files [0];
int client_amount;


void setup () {
  //SD card initialization
  Serial.begin (9600);
  Serial.println ("Initializing SD card...");
  if (!sd.begin (4, SPI_HALF_SPEED)) {
    Serial.println ("SD card initialization failed!");
  } else {
    Serial.println ("SD card initialization succesful!");
  }

  //Ethernet initialization
  //Get IP
  String Sip = sd.open ("config/ip.txt").readStringUntil ('\n');
  int ipList [4];
  for (int i = 0; i < 4; i++) {
    int index = Sip.indexOf (".");
    ipList [i] = Sip.substring (0, index).toInt ();
    Sip = Sip.substring (index + 1, Sip.length ());
  }
  IPAddress ip (ipList [0], ipList [1], ipList [2], ipList [3]);

  //Get port
  long port = sd.open ("config/port.txt").readStringUntil ('\n').toInt ();

  //MAC setup
  byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

  //Server setup
  Ethernet.begin (mac, ip);
  server = EthernetServer (port);
  server.begin ();

  Serial.print ("Server started at http://");
  Serial.print (Ethernet.localIP ());
  Serial.print (':');
  Serial.println (port);

  //Initialize clients
  const int client_amount = sd.open ("config/clients.txt").readStringUntil ('\n').toInt ();
  Serial.print ("The server can host ");
  Serial.print (client_amount);
  Serial.println (" clients at once");
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
