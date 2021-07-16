class Args {
  private:
    String _input;
    int _lastChecked = -1;

  public:
    void setInput (String args) {
      _input = args;
    }

    boolean exists (String tag) {
      int from = 0;
      while (true) {
        int index = _input.indexOf (tag, from);
        if (index != -1) {
          if (index == 0 || _input.charAt (index - 1 == '&')) {
            if (_input.charAt (index + tag.length ()) == '=') {
              _lastChecked = index;
              return true;
            }
          }
          from = index + 1;
        } else {
          _lastChecked = -1;
          return false;
        }
      }
    }

    String get (String tag) {
      if (exists (tag)) {
        int openIndex = _lastChecked + tag.length () + 1;
        int closeIndex = _input.length () - 1;
        for (int i = openIndex; i < closeIndex; i++) {
          if (_input.charAt (i) == '&') {
            closeIndex = i;
            break;
          }
        }
        return _input.substring (openIndex);
      } else {
        return "doesnt exist";
      }
    }
};

void processGET (EthernetClient client, String path, String arguments) {
  if (path == "/"){
    hostFile ("index.htm", client);
  } else if (path.indexOf (".") > 0){
    hostFile (path, client);
  } else {
    hostFile ("notfound.htm", client);
  }
}
