#include <MIDI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//
// MIDI 
//
MIDI_CREATE_DEFAULT_INSTANCE();
int LISTEN_CHANNEL = 4;
int LISTEN_CHANNEL = MIDI_CHANNEL_OFF;  // Don't listen
int SEND_CHANNEL = 1;
int VELOCITY = 127;


//
// OLED Display screen
//
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// https://arduinogetstarted.com/tutorials/arduino-oled
// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


//
// Hardware mapping
//
int ON_BOARD_LED = 13;
int PANEL_LED = 10;
int BUTTON = 8;
int SPEED = A0;


//
// MUSIC variables
//
int ROOT_NOTE = 60;
int minor_chord[] = {0, 3, 7, 10};
int chord_index = 0;


void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PANEL_LED, OUTPUT);
    pinMode(SPEED, INPUT);

    pinMode(BUTTON, INPUT_PULLUP);
    MIDI.begin(LISTEN_CHANNEL);

    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      Serial.println(F("SSD1306 allocation failed"));
      blink_error(3);
    }

    delay(2000);         // wait for initializing
    display_text("MIDI Sequencer", null);
}


void display_text(char *line1, char *line2) {
    oled.clearDisplay(); // clear display
    oled.setTextSize(1);         // text size
    oled.setTextColor(WHITE);    // text color
    if (line1 != null) {
        oled.setCursor(0, 10);   // position to display
        oled.println(line1);     // text to display
    }
    if (line2 != null) {
        oled.setCursor(0, 20);   // position to display
        oled.println(line2);     // text to display
    }
    oled.display();              // show on OLED
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
    int play_note = ROOT_NOTE + minor_chord[chord_index];
    chord_index++;
    if (chord_index > 3) {
      chord_index = 0;
    }

    int delay_time = 1024 - analogRead(SPEED);
    char buffer[128];
    sprintf(buffer, "got delay = %d", delay_time);
    display_text(null, buffer);
    
    MIDI.sendNoteOn(play_note, VELOCITY, SEND_CHANNEL);  // Send a Note
    delay(delay_time);                                   // Wait for a second
    MIDI.sendNoteOff(play_note, 0, SEND_CHANNEL);        // Stop the note
    delay(delay_time);                                   // Wait for a second
    digitalWrite(ON_BOARD_LED, LOW);
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
