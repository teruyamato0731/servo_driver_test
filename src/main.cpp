#include <mbed.h>

#include "Servo.hpp"

// Const variable
constexpr uint32_t servo_can_id = 140;

// Function prototype

// IO
CAN can{PA_11, PA_12, (int)1e6};
// CAN can{PB_12, PB_13, (int)1e6};
// CANMessage msg;
DigitalIn button{BUTTON1};

// Struct definition

// Global variable
ServoArray servo_arr{servo_can_id};

/// @brief The application entry point.
int main() {
  // put your setup code here, to run once:
  printf("\nsetup\n");
  while(1) {
    // put your main code here, to run repeatedly:
    auto now = HighResClock::now();
    static auto pre = now;
    if(now - pre > 20ms) {
      if(button) {
        for(auto& e: servo_arr) e = 180;
      } else {
        for(auto& e: servo_arr) e = 0;
      }
      for(auto e: servo_arr) printf("%02x ", e.raw_out);
      const auto msg = servo_arr.to_msg();
      bool success = can.write(msg);
      if(!success) printf("fail ");
      printf("\n");
      pre = now;
    }
  }
}

// Function definition
