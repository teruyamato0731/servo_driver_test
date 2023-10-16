#include <mbed.h>

// Const variable
constexpr uint32_t servo_can_id = 140;

// Function prototype

// IO
CAN can{PA_11, PA_12, (int)1e6};
// CAN can{PB_12, PB_13, (int)1e6};
// CANMessage msg;

// Struct definition
struct Servo {
  CANMessage to_msg() {
    return CANMessage{can_id, pwm, sizeof(pwm)};
  }

  uint32_t can_id;
  uint8_t pwm[8];
};

// Global variable
Servo servo{servo_can_id};

/// @brief The application entry point.
int main() {
  // put your setup code here, to run once:
  printf("\nsetup\n");
  while(1) {
    // put your main code here, to run repeatedly:
    auto now = HighResClock::now();
    static auto pre = now;
    if(now - pre > 20ms) {
      const auto msg = servo.to_msg();
      bool success = can.write(msg);
      if(!success) printf("fail ");
      printf("\n");
      pre = now;
    }
  }
}

// Function definition
