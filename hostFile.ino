class Hoster {
  private:
    File32 hosted;
    EthernetClient client;
    String status_code;
    String content_type;
    String filename;

  public:
    Hoster (EthernetClient eclient, String estatus_code, String econtent_type, File32 file) {
      client = eclient;
      status_code = estatus_code;
      content_type = econtent_type;
      hosted = file;
    }

    void sendHeader () {
      String status_message = sd.open ("/info/codes/" + status_code).readStringUntil ('\n');
      File32 header = sd.open ("/info/templates/header.txt");
      while (header.available () > 0) {
        String line = header.readStringUntil ('\n');
        line.replace ("~sc~", status_code);
        line.replace ("~sm~", status_message);
        line.replace ("~ct~", content_type);
        client.println (line);
      }
      client.println ();
    }

    void hostFile () {
      // send web page
      if (hosted) {
        while (hosted.available()) {
          client.write(hosted.read()); // send web page to client
        }
        hosted.close();
      }
    }
};

void response (EthernetClient client, String filename, String status_code) {
  filename = "htdocs" + filename;
  Serial.print ('-');
  Serial.println (filename);
  Hoster host (client, status_code, getContentType (filename.substring (filename.lastIndexOf ('.') + 1, filename.length ())), sd.open (filename));
  host.sendHeader ();
  host.hostFile ();
}

String getContentType (String fileFormat) {
  Serial.println ("info/content-type/" + fileFormat);
  return sd.open ("info/content-type/" + fileFormat).readStringUntil ('\n');
}
