#ifndef MUSIC_H
#define MUSIC_H

#include "hw_map.h"

//
// - Notes
//
char const *note_chars[] = {
  "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
};

int get_root_note() {
    // 12 notes per octave
    // 60 is middle C
    int root = analogRead(ROOT_IN);
    int root_note = 60 + (12.0 * root / 1024.0);
    return root_note;
}

char const * note_to_string(int root){
    char buf[3];
    root = root % 12;
    return note_chars[root];
}

//
// - Modes
//
char const *mode_chars[] = {
  "Ionian/Major", "Dorian/Minor", "phrygian", "lydian", "mixolydian", "aeolian/minor", "locrian"
};

int get_musical_mode() {
    // 7 available modes
    int mode = analogRead(SCALE_MODE_IN);
    mode = 7.0 * mode / 1024.0;
    return mode;
}

char const *mode_to_string(int mode){
    char buf[16];
    return mode_chars[mode];
}


// In the scale of C Major
// We have these modes
//  0  1  2  3  4  5  6  7  8  9  10 11 12
//  C  C# D  D# E  F  F# G  G# A  A#  B  C

// All white keys for key of C (Major)
//               C  D  E   F  G  A  B
//                W  W  H   W  W  W  H
const int ionian[] = { 0, 2, 4,  5, 7, 9, 11, 12 };

// All white keys for key of D (Minor)
//               C  D  Eb  F  G  A  Bb
//                W  H  W   W  W  W  H
const int dorian[] = { 0, 2, 3,  5, 7, 9, 10, 12 };

// All white keys for key of E
//                 C  Db Eb  F  G  Ab  Bb
//                  H  W  W   W  H  W  W
const int phrygian[] = { 0, 1, 3,  5, 7, 8, 10, 12 };

// All white keys for key of F
//               C  D  E  F# G  A  B
//                W  W  W   H  W  W  H
const int lydian[] = { 0, 2, 4, 6, 7, 9, 11, 12 };

// All white keys for key of G
//                   C  D  E   F  G  A  Bb
//                    W  W  H   W  W  H  W
const int mixolydian[] = { 0, 2, 4,  5, 7, 9, 10, 12 };

// All white keys for key of A (Natural Minor)
//                C  D  Eb  F  G  Ab  Bb
//                 W  H  W   W  H   W   W
const int aeolian[] = { 0, 2, 3,  5, 7, 8, 10, 12 };

// All white keys for key of B
//                C  Db Eb  F  Gb Ab  Bb
//                 H  W  W   H   W   W  W
const int locrian[] = { 0, 1, 3,  5, 6, 8, 10, 12 };

const int * mode_map[] = {ionian, dorian, phrygian, lydian, mixolydian, aeolian, locrian};
const int * get_scale_from_mode(int mode) {
    return mode_map[mode];
}

// Harmonic Minor scale
//                C D  Eb  F  G  Ab   B
//                 W  H  W   W  H   W+  H
int harmonic[] = { 0, 2, 3,  5, 7, 8, 11 };


// Melodic Minor scale
//                C D  Eb  F  G  A  B
//                 W  H  W   W  W  W  H
const int melodic[] = { 0, 2, 3,  5, 7, 8, 11 };


//
// Scales
//
const int triad[] = {1, 3, 5};
const int seventh[] = {1, 3, 5, 7};
const int scale_notes[] = {1, 2, 3, 4, 5, 6, 7, 8};

const int * op_mode_map[] = {triad, seventh, scale_notes};
const int * get_op_mode_from_mode(int op_mode) {
    op_mode = op_mode %3;
    return op_mode_map[op_mode];
}

char const *op_mode_chars[] = {
  "Triad-135", "Seventh-1357", "Scale-12345678", "Triad+-135", "Seventh+-1357", "Scale+-1-8-1"
};

int get_op_mode() {
    // 6 available op modes
    return 5;
}

char const *op_mode_to_string(int op_mode){
    char buf[16];
    return op_mode_chars[op_mode];
}


//
// MUSIC variables
//
int note_index = 0;
int direction = 1;

int get_next_note(int root_note, int m_mode, int o_mode) {
    const int *chord = get_op_mode_from_mode(o_mode);
    int notes_in_chord = 8;

    const int *scale = get_scale_from_mode(m_mode);     // Scale of notes to chose from
    int note_offset = chord[note_index] - 1;            // note offsets (triad, 7th, etc,)
    int play_note = root_note + scale[note_offset];

    note_index += direction;
    if (note_index > notes_in_chord - 1) {
       direction = -1;
       note_index = notes_in_chord - 1;
    }
    if (note_index < 0) {
      direction = 1;
      note_index = 0;
    }

    return play_note;
}  

#endif
