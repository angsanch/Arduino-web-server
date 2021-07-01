#include <SD.h>
#include <Ethernet.h>

class Parser {
  private:
    String _input;
    int _index;

  public:
    String getPath () {
      _index = _input.indexOf ("?");
      if (_index != -1) {
        return _input.substring (1, _index);//If there are args
      }
      return _input.substring (1, _input.length ());//If there isnt any args
    }
    String getArgs () {
      _index = _input.indexOf ("?");
      if (_index != -1) {
        return _input.substring (_index + 1, _input.length ());//If there are args
      }
      return "";//If there isnt any args
    }
    void setInput (String input) {
      _input = input;
    }
};

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
          client.println ("HTTP/1.1 200 OK");
          client.println ("Content-Type: text/html");
          client.println ("Connection: close");
          client.println ();
          
          //Process and send response to the request
          Parser prs;
          prs.setInput (request);
          String path = prs.getPath ();
          String arguments = prs.getArgs ();
          process (client, path, arguments);//Redirect processing to a specialized function

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
