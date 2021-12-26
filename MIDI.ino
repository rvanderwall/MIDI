#include <MIDI.h>
#include <Wire.h>

#include "Display.h"

//
// MIDI 
//
MIDI_CREATE_DEFAULT_INSTANCE();
//int LISTEN_CHANNEL = 4;
int LISTEN_CHANNEL = MIDI_CHANNEL_OFF;  // Don't listen
int SEND_CHANNEL = 1;
int VELOCITY = 127;



//
// Hardware mapping
//
int ON_BOARD_LED = 13;
int PANEL_LED = 10;
int BUTTON = 8;
int TEMPO_IN = A0;
int ROOT_IN = A1;
int SCALE_MODE_IN = A2;


//
// MUSIC variables
//
int ROOT_NOTE = 60;
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
    pinMode(PANEL_LED, OUTPUT);

    pinMode(TEMPO_IN, INPUT);
    pinMode(ROOT_IN, INPUT);
    pinMode(SCALE_MODE_IN, INPUT);

    pinMode(BUTTON, INPUT_PULLUP);

    MIDI.begin(LISTEN_CHANNEL);

    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      Serial.println(F("SSD1306 allocation failed"));
      blink_error(3);
    }

    delay(2000);         // wait for initializing
    display_text("MIDI Sequencer", "Version 1.0", "");
//    display_big_text("RECORDING");
}

char const *note_chars[] = {
  "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
};

char const * root_to_note(int root){
    char buf[3];
    root = root - 60;
    if (root < 0) {
      root = 0;
    }
    if (root > 11) {
      root = 11;
    }
    return note_chars[root];
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
    digitalWrite(PANEL_LED, HIGH);
    delay(50);
    digitalWrite(ON_BOARD_LED, HIGH);
    digitalWrite(PANEL_LED, LOW);
    delay(50);
}


void ping_moog() {
    digitalWrite(ON_BOARD_LED, HIGH);
    int tempo = analogRead(TEMPO_IN);
    int delay_time = 1024 - tempo;

    int root = analogRead(ROOT_IN);
    ROOT_NOTE = 60 + (12.0 * root / 1024.0);

    int play_note = ROOT_NOTE + minor_chord[chord_index];
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

    if (digitalRead(BUTTON)== HIGH) {
        ping_moog();
    }
}
