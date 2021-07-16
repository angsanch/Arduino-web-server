File file;
void hostFile (String filename, EthernetClient client) {
  // send web page
  Serial.println (filename);
  file = SD.open(filename);        // open web page file
  if (file) {
    while (file.available()) {
      client.write(file.read()); // send web page to client
    }
    file.close();
  }
}
