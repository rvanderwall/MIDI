#ifndef HW_MAP_H
#define HW_MAP_H

//
// Hardware mapping
//
#define ON_BOARD_LED  13
#define TEMPO_IN      A0
#define SCALE_MODE_IN A1
#define ROOT_IN       A2

#define SELECT_UP     12
#define SELECT_DOWN   11
#define RUN           10
#define RECORD         9


#define GET_TEMPO_VALUE analogRead(TEMPO_IN)
#define GET_ROOT_VALUE analogRead(ROOT_IN)
#define GET_MODE_VALUE analogRead(SCALE_MODE_IN)


bool run() {
    return digitalRead(RUN) == LOW
}

int debounce(switch_pin) {
    delay(1);
    if (digitalRead(switch_pin) != LOW) {
        return 0;
    }
    while (digitalRead(switch_pin) == LOW) {
        delay(1);
    }
    return 1;
}

int get_select_change() {
    if (digitalRead(SELECT_UP) == LOW) {
        return debounce(SELECT_UP);
    }
    if (digitalRead(SELECT_DOWN) == LOW) {
        return -debounce(SELECT_DOWN);
    }
    return 0;
}

void setup_io() {
    pinMode(ON_BOARD_LED, OUTPUT);

    pinMode(TEMPO_IN, INPUT);
    pinMode(SCALE_MODE_IN, INPUT);
    pinMode(ROOT_IN, INPUT);

    pinMode(RUN, INPUT_PULLUP);
    pinMode(SELECT_UP, INPUT_PULLUP);
    pinMode(SELECT_DOWN, INPUT_PULLUP);
    pinMode(RECORD, INPUT_PULLUP);
}

#endif
