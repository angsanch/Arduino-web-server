class Hoster {
  private:
  File32 hosted;
  String filename;
  EthernetClient client;

  public:
    Hoster (String fileName, EthernetClient eclient, String basePath = "htdocs"){
      filename = basePath + fileName;
      client = eclient;
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

void sendHeader (EthernetClient client, String status_code, String content_type){
  String status_message = sd.open ("/info/codes/" + status_code).readStringUntil ('\n');
  file = sd.open ("/info/templates/header.txt");
  while (file.available () > 0){
    String line = file.readStringUntil ('\n');
    line.replace ("~sc~", status_code);
    line.replace ("~sm~", status_message);
    line.replace ("~ct~", content_type);
    client.println (line);
  }
  client.println ();
}

void response (EthernetClient client, String filename, String status_code){
  sendHeader (client, status_code, getContentType (filename.substring (filename.lastIndexOf ('.') + 1, filename.length ())));
  Hoster (filename, client).hostFile ();
}

String getContentType (String fileFormat){
  Serial.println ("info/content-type/" + fileFormat);
  return sd.open ("info/content-type/" + fileFormat).readStringUntil ('\n');
}
