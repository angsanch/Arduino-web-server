class Hoster {
  private:
    File32 hosted;
    EthernetClient client;
    String status_code;
    String content_type;
    String filename;

  public:
    Hoster (EthernetClient eclient, String estatus_code, String econtent_type, String fileName, String basePath = "htdocs") {
      client = eclient;
      status_code = estatus_code;
      content_type = econtent_type;
      filename = basePath + fileName;
    }

    void sendHeader () {
      String status_message = sd.open ("/info/codes/" + status_code).readStringUntil ('\n');
      hosted = sd.open ("/info/templates/header.txt");
      while (hosted.available () > 0) {
        String line = hosted.readStringUntil ('\n');
        line.replace ("~sc~", status_code);
        line.replace ("~sm~", status_message);
        line.replace ("~ct~", content_type);
        client.println (line);
      }
      client.println ();
    }

    void hostFile () {
      // send web page
      Serial.println (filename);
      hosted = sd.open(filename);        // open web page file
      if (hosted) {
        while (hosted.available()) {
          client.write(hosted.read()); // send web page to client
        }
        hosted.close();
      }
    }
};

File32 file;

void response (EthernetClient client, String filename, String status_code) {
  Hoster host (client, status_code, getContentType (filename.substring (filename.lastIndexOf ('.') + 1, filename.length ())), filename);
  host.sendHeader ();
  host.hostFile ();
}

String getContentType (String fileFormat) {
  Serial.println ("info/content-type/" + fileFormat);
  return sd.open ("info/content-type/" + fileFormat).readStringUntil ('\n');
}
