File file;
void hostFile (String filename, EthernetClient client, String basePath = "htdocs") {
  // send web page
  filename = basePath + filename;
  Serial.println (filename);
  file = SD.open(filename);        // open web page file
  if (file) {
    while (file.available()) {
      client.write(file.read()); // send web page to client
    }
    file.close();
  }
}
