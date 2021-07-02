class Args {
  private:
    String _input;

  public:
    void setInput (String args) {
      _input = args;
    }

    boolean exists (String tag) {
      int index = _input.indexOf (tag);
      if (index != -1) {
        if (index == 0 || _input.charAt (index - 1 == '&')) {
          if (_input.charAt (index + tag.length ()) == '=') {
            return true;
          }
        }
      }
      return false;
    }
};

void process (EthernetClient client, String path, String arguments) {
  hostFile ("index.htm", client);
  Args args;
  args.setInput (arguments);
}
