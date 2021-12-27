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
    root_note = 60 + (12.0 * root / 1024.0);
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
  "Ionian/major", "Dorian/Minor", "phrygian", "lydian", "mixolydian", "aeolian/minor", "locrian"
};

int *
int get_musical_mode() {
    // 7 available modes
    int mode = analogRead(SCALE_MODE_IN);
    mode = 7.0 * mode / 1024.0);
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
const int ionian[] = { 0, 2, 4,  5, 7, 9, 11 };

// All white keys for key of D (Minor)
//               C  D  Eb  F  G  A  Bb
//                W  H  W   W  W  W  H
const int dorian[] = { 0, 2, 3,  5, 7, 9, 10 };

// All white keys for key of E
//                 C  Db Eb  F  G  Ab  Bb
//                  H  W  W   W  H  W  W
const int phrygian[] = { 0, 1, 3,  5, 7, 8, 10 };

// All white keys for key of F
//               C  D  E  F# G  A  B
//                W  W  W   H  W  W  H
const int lydian[] = { 0, 2, 4, 6, 7, 9, 11 };

// All white keys for key of G
//                   C  D  E   F  G  A  Bb
//                    W  W  H   W  W  H  W
const int mixolydian[] = { 0, 2, 4,  5, 7, 9, 10 };

// All white keys for key of A (Natural Minor)
//                C  D  Eb  F  G  Ab  Bb
//                 W  H  W   W  H   W   W
const int aeolian[] = { 0, 2, 3,  5, 7, 8, 10 };

// All white keys for key of B
//                C  Db Eb  F  Gb Ab  Bb
//                 H  W  W   H   W   W  W
const int locrian[] = { 0, 1, 3,  5, 6, 8, 10 };

const int * mode_map = [ionian, dorian, phrygian, lydian, mixolydian, aeolian, locrian]
const int * get_scale_from_mode(mode) {
    return mode_map[mode];
}

// Harmonic Minor scale
//                C D  Eb  F  G  Ab   B
//                 W  H  W   W  H   W+  H
int harmonic[] = { 0, 2, 3,  5, 7, 8, 11 };


// Melodic Minor scale
//                C D  Eb  F  G  A  B
//                 W  H  W   W  W  W  H
int melodic[] = { 0, 2, 3,  5, 7, 8, 11 };

int maj[]   = {0, 4, 7, 11};  // 1,3,5 ionian
int minor[] = {0, 3, 7, 10};  // 1,3,5 dorian
int dim[]   = {0, 3, 6,  9};  // 1,3,5 locrian
int aug[]   = {0, 4, 8, 10};  // 1,3,5 lydian

int triad = {1, 3, 5};
int seventh = {1, 3, 5, 7}
int scale_notes = {1, 2, 3, 4, 5, 6, 7}
#endif
