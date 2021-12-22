
#include <MIDI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int ON_BOARD_LED = 13;
int PANEL_LED = 10;
int BUTTON = 8;
int SPEED = A0;


int LISTEN_CHANNEL = 4;
int SEND_CHANNEL = 1;
int VELOCITY = 127;
int NOTE = 60;

int minor_chord[] = {0, 3, 7, 10};
int chord_index = 0;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PANEL_LED, OUTPUT);
    pinMode(SPEED, INPUT);

    pinMode(BUTTON, INPUT_PULLUP);
//    MIDI.begin(LISTEN_CHANNEL);                      // Launch MIDI and listen to channel
    MIDI.begin(MIDI_CHANNEL_OFF);                      // Don't listen

    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      Serial.println(F("SSD1306 allocation failed"));
      blink_error(3);
    }
  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display
  // https://arduinogetstarted.com/tutorials/arduino-oled
  
  oled.setTextSize(1);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display
  oled.println("Hello World!"); // text to display
  oled.display();               // show on OLED
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

void blink() {
    digitalWrite(ON_BOARD_LED, LOW);
    digitalWrite(PANEL_LED, HIGH);
    delay(20);
    digitalWrite(ON_BOARD_LED, HIGH);
    digitalWrite(PANEL_LED, LOW);
    delay(20);
}


void ping_moog() {
    digitalWrite(ON_BOARD_LED, HIGH);
    int play_note = NOTE + minor_chord[chord_index];
    chord_index++;
    if (chord_index > 3) {
      chord_index = 0;
    }

    int delay_time = 1024 - analogRead(SPEED);
    char buffer[128];
  sprintf(buffer, "got delay = %d", delay_time);
  oled.clearDisplay();
  oled.setCursor(0, 20);        // position to display
  oled.println(buffer); // text to display
  oled.display();               // show on OLED
    
    MIDI.sendNoteOn(play_note, VELOCITY, SEND_CHANNEL);   // Send a Note
    delay(delay_time);                                     // Wait for a second
    MIDI.sendNoteOff(play_note, 0, SEND_CHANNEL);         // Stop the note
    delay(delay_time);                                   // Wait for a second
    digitalWrite(ON_BOARD_LED, LOW);
}

void loop()
{
//    if (MIDI.read())                    // If we have received a message
//    {
//      ping()
//    }
    if (digitalRead(BUTTON)== HIGH) {
//      blink();
      ping_moog();
    }
}
