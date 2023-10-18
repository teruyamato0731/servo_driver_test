#ifndef SERVO_HPP_
#define SERVO_HPP_

#include <mbed.h>

struct Servo {
  uint8_t operator=(const uint8_t deg) {
    return raw_out = deg * 0xff / 180;
  }
  uint8_t raw_out;
};

struct ServoArray {
  ServoArray(uint32_t can_id) : can_id_{can_id} {}
  CANMessage to_msg() {
    static_assert(sizeof(servo_) <= 8);
    return CANMessage{can_id_, reinterpret_cast<const uint8_t*>(servo_), sizeof(servo_)};
  }
  auto begin() {
    return std::begin(servo_);
  }
  auto begin() const {
    return std::begin(servo_);
  }
  auto end() {
    return std::end(servo_);
  }
  auto end() const {
    return std::end(servo_);
  }
  auto& operator[](int idx) & {
    return servo_[idx];
  }

 private:
  uint32_t can_id_;
  Servo servo_[8];
};

#endif  // SERVO_HPP_
