#ifndef LED_H
#define LED_H

#include "hw_map.h"

#define OB_LED_ON     digitalWrite(ON_BOARD_LED, HIGH)
#define OB_LED_OFF    digitalWrite(ON_BOARD_LED, LOW)


void blink_error(int err_code) {
  while (true){
     for (int c=0; c < err_code; c++) {
       digitalWrite(ON_BOARD_LED, LOW);
       delay(150);
       digitalWrite(ON_BOARD_LED, HIGH);
       delay(150);
     }
     delay(300);
  }
}


void pulse() {
    digitalWrite(ON_BOARD_LED, LOW);
    delay(50);
    digitalWrite(ON_BOARD_LED, HIGH);
    delay(50);
}

#endif
