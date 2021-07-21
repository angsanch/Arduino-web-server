File32 file;
void hostFile (String filename, EthernetClient client, String basePath = "htdocs") {
  // send web page
  filename = basePath + filename;
  Serial.println (filename);
  file = sd.open(filename);        // open web page file
  if (file) {
    while (file.available()) {
      client.write(file.read()); // send web page to client
    }
    file.close();
  }
}

void sendHeader (EthernetClient client, String status_code){
  String status_message = sd.open ("/info/codes/" + status_code).readStringUntil ('\n');
  file = sd.open ("/info/templates/header.txt");
  while (file.available () > 0){
    String line = file.readStringUntil ('\n');
    line.replace ("~sc~", status_code);
    line.replace ("~sm~", status_message);
    line.replace ("~ct~", "text/html");
    client.println (line);
  }
  client.println ();
}
