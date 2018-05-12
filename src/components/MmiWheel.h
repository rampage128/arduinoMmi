#ifndef MMIWHEEL_H
#define MMIWHEEL_H

class MmiWheel {
  public:
    MmiWheel(uint8_t id) {
      _id = id;
    }
    void turn(uint8_t id, int8_t amount) {
      if (_id == id) {
        _amount = amount;
      }
    }
    int8_t getAmount() {
      return _state;
    }
    bool wasTurned() {
      return _state != 0;
    }
    void update() {
      if (_amount != _state) {
        _state = _amount;
        _amount = 0;
      }
    }
  private:
    int8_t _state = 0;
    int8_t _amount = 0;
  
    uint8_t _id = 0x00;
};

#endif