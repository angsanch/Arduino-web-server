class Args {
  private:
    String _input;
    int _lastChecked = -1;

  public:
    void setInput (String args) {
      _input = args;
    }

    boolean exists (String tag) {
      String input = _input;//Copy because it maybe gets modificated
      while (true) {
        int index = input.indexOf (tag);
        if (index != -1) {
          if (index == 0 || input.charAt (index - 1 == '&')) {
            if (input.charAt (index + tag.length ()) == '=') {
              _lastChecked = index;
              return true;
            }
          }
          input.setCharAt (index, "\\");
        } else {
          _lastChecked = -1;
          return false;
        }
      }
    }
};

void process (EthernetClient client, String path, String arguments) {
  hostFile ("index.htm", client);
  Args args;
  args.setInput (arguments);
}
