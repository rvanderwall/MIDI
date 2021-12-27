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


int get_tempo() {
    return analogRead(TEMPO_IN);
}

#endif
