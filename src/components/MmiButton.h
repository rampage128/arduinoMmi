#ifndef MMIBUTTON_H
#define MMIBUTTON_H

#include <arduinoIO.h>

class MmiButtonInput : public Input {
  public:
    MmiButtonInput(int buttonId) {
      _buttonId = buttonId;
    }
    virtual boolean getState() { 
      return _state;
    }
    void update(int buttonId, boolean newState) {
      if (buttonId == _buttonId) {
        _state = newState;
      }
    }
  private:
    uint8_t _buttonId = 0x00;
    boolean _state = false;
};

class MmiButton : public Button {
  public:
    MmiButton(MmiButtonInput *input) : Button(input) {
      _input = input;
    }
    void updateTrigger(int buttonId, boolean newState) {
      _input->update(buttonId, newState);
    }
    ~MmiButton() {
      delete _input;
    }
  private:
    MmiButtonInput *_input;
};

#endif