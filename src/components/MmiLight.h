#ifndef MMILIGHT_H
#define MMILIGHT_H

class MmiLight {
  public:
    MmiLight(uint8_t lightId, Mmi *mmi) {
      _mmi = mmi;
      _lightId = lightId;
    }
    void on() {
      this->set(true);
    }
    void off() {
      this->set(false);
    }
    void toggle() {
      this->set(!_state);
    }
    boolean isOn() {
      return _state;
    }
    void set(boolean state) {
      _state = state;
      _mmi->setLight(_lightId, state);
    }
  private:
    uint8_t _lightId = 0;
    boolean _state = false;
    Mmi *_mmi;
};

#endif