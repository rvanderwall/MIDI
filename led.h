#ifndef LED_H
#define LED_H

#include "hw_map.h"

#define OB_LED_ON     digitalWrite(ON_BOARD_LED, HIGH)
#define OB_LED_OFF    digitalWrite(ON_BOARD_LED, LOW)


void blink_error(int err_code) {
  while (true){
     for (int c=0; c < err_code; c++) {
       OB_LED_ON;
       delay(150);
       OB_LED_OFF;
       delay(150);
     }
     delay(300);
  }
}


void pulse() {
    OB_LED_ON;
    delay(50);
    OB_LED_OFF;
    delay(50);
}

#endif
