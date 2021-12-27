#include <MIDI.h>
#include <Wire.h>

#include "Display.h"
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

//
// MUSIC variables
//
int root_note = 60;
int minor_chord[] = {0, 3, 7, 10};
int chord_index = 0;

//
// Operational Variables
//
#define MODE_INIT       0
#define MODE_ARP_135    1
#define MODE_ARP_1357   2
#define MODE_ARP_SCALE  3
#define MODE_SEQ        4

int CURRENT_MODE = MODE_INIT;

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

    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      Serial.println(F("SSD1306 allocation failed"));
      blink_error(3);
    }

    delay(2000);         // wait for initializing
    display_text("MIDI Sequencer", "Version 1.0", "");
//    display_big_text("RECORDING");
}


void display_status(int tempo, int musical_mode, int root, int op_mode) {
    char l1_buffer[32];
    sprintf(l1_buffer, "Tempo: %d", tempo);
    char l2_buffer[32];
    sprintf(l2_buffer, "%s(%s)y", "Dorian/minor", root_to_note(root));
    char l3_buffer[32];
    sprintf(l3_buffer, "%s", "arp_135");
    display_text(l1_buffer, l2_buffer, l3_buffer);

}

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


void ping_moog() {
    digitalWrite(ON_BOARD_LED, HIGH);
    int tempo = analogRead(TEMPO_IN);
    int delay_time = 1024 - tempo;

    int root = analogRead(ROOT_IN);
    root_note = 60 + (12.0 * root / 1024.0);

    int play_note = root_note + minor_chord[chord_index];
    chord_index++;
    if (chord_index > 3) {
      chord_index = 0;
    }

    display_status(tempo, 0, play_note, 0);
    digitalWrite(ON_BOARD_LED, LOW);
    
    MIDI.sendNoteOn(play_note, VELOCITY, SEND_CHANNEL);  // Send a Note
    delay(delay_time);                                   // Wait for a second
    MIDI.sendNoteOff(play_note, 0, SEND_CHANNEL);        // Stop the note
    delay(delay_time);                                   // Wait for a second
}


void loop()
{
//    if (MIDI.read()) {
//      ping()
//    }

    if (digitalRead(RUN)== LOW) {
        ping_moog();
    }
}
