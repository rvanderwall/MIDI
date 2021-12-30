#include <MIDI.h>
#include <Wire.h>

#include "hw_map.h"
#include "Display.h"
#include "led.h"
#include "music.h"

//
// MIDI 
//
MIDI_CREATE_DEFAULT_INSTANCE();
//#define LISTEN_CHANNEL  
#define LISTEN_CHANNEL MIDI_CHANNEL_OFF    // Don't listen
#define SEND_CHANNEL  1
#define VELOCITY    127


//
// Operational Modes
//
#define MODE_INIT       0
#define MODE_ARP_135    1
#define MODE_ARP_1357   2
#define MODE_ARP_SCALE  3
#define MODE_SEQ        4
int current_mode = MODE_INIT;

void setup()
{
    pinMode(ON_BOARD_LED, OUTPUT);

    pinMode(TEMPO_IN, INPUT);
    pinMode(ROOT_IN, INPUT);
    pinMode(SCALE_MODE_IN, INPUT);

    pinMode(RUN, INPUT_PULLUP);
    pinMode(SELECT_UP, INPUT_PULLUP);
    pinMode(SELECT_DOWN, INPUT_PULLUP);
    pinMode(RECORD, INPUT_PULLUP);

    MIDI.begin(LISTEN_CHANNEL);
    init_display();

    delay(2000);         // wait for initializing
    display_text("MIDI Sequencer", "Version 1.1", "");
}

void record() {
   display_big_text("RECORDING");
}

void display_status(int tempo, int musical_mode, int note, int op_mode) {
    char l1_buffer[32];
    sprintf(l1_buffer, "Tempo: %d", tempo);
    char l2_buffer[32];
    sprintf(l2_buffer, "%s(%s)", mode_to_string(musical_mode), note_to_string(note));
    char l3_buffer[32];
    sprintf(l3_buffer, "%s", op_mode_to_string(op_mode));
    display_text(l1_buffer, l2_buffer, l3_buffer);
}


void send_note_to_moog() {
    OB_LED_ON;
    int tempo = get_tempo();
    int delay_time = 1024 - tempo;
    int root_note = get_root_note();
    int m_mode = get_musical_mode();
    int o_mode = get_op_mode();
    int play_note = get_next_note(root_note, m_mode, o_mode);
    
    display_status(tempo, m_mode, play_note, o_mode);
    OB_LED_OFF;

    MIDI.sendNoteOn(play_note, VELOCITY, SEND_CHANNEL);  // Send a Note
    delay(delay_time);                                   // Wait for a moment
    MIDI.sendNoteOff(play_note, 0, SEND_CHANNEL);        // Stop the note
    delay(delay_time);                                   // Wait for a moment
}


void loop()
{
//    if (MIDI.read()) {
//      ping()
//    }

    if (digitalRead(RUN)== LOW) {
        send_note_to_moog();
    }
}
