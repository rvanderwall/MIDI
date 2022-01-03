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
    int root = GET_ROOT_VALUE;
    int root_note = 60 + (12.0 * root / 1024.0);
    return root_note;
}

char const * note_to_string(int note){
    char buf[3];
    note = note % 12;
    return note_chars[note];
}

//
// - Modes
//
char const *mode_chars[] = {
  "Ionian/Major", "Dorian/Minor", "phrygian", "lydian", "mixolydian", "aeolian/minor", "locrian"
};

int get_musical_mode() {
    // 7 available modes
    int mode = GET_MODE_VALUE;
    mode = 7.0 * mode / 1024.0;
    return mode;
}

char const * mode_to_string(int mode){
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

const int * chord_map[] = {triad, seventh, scale_notes};
const int note_counts[] = {3, 4, 8};

const int * get_chord_from_chord_num(int chord_num) {
    chord_num = chord_num % 3;
    return chord_map[chord_num];
}

const int get_note_count_from_chord_num(int chord_num) {
    chord_num = chord_num % 3;
    return note_counts[chord_num];
}

int get_direction_flag_from_chord_num(int chord_num) {
    if (chord_num < 3) {
        return 0;
    }
    return 1;
}

char const *chord_name_chars[] = {
  "Triad-135", "Seventh-1357", "Scale-12345678", "Triad+-135", "Seventh+-1357", "Scale+-1-8-1"
};

//
// MUSIC variables
//
int note_index = 0;
int direction = 1;
int cur_chord_num = 0;


void update_cur_chord_num(int update_direction) {
    if (update_direction == 0){
        return;
    }
    cur_chord_num += update_direction;
    if (cur_chord_num > 5) {
        cur_chord_num = 0;
    }
    if (cur_chord_num < 0) {
        cur_chord_num = 5;
    }
    note_index = 0;
}

int get_chord_num() {
    return cur_chord_num;
}

char const *chord_num_to_string(int chord_num){
    return chord_name_chars[chord_num];
}



int get_next_note(int root_note, int m_mode, int chord_num) {
    const int *chord = get_chord_from_chord_num(chord_num);
    int notes_in_chord = get_note_count_from_chord_num(chord_num);
    int direction_flag = get_direction_flag_from_chord_num(chord_num);

    const int *scale = get_scale_from_mode(m_mode);     // Scale of notes to chose from
    int note_offset = chord[note_index] - 1;            // note offsets (triad, 7th, etc,)
    int play_note = root_note + scale[note_offset];

    if (direction_flag == 0) {
        note_index++;
        if (note_index >= notes_in_chord) {
            note_index = 0;
        }
    }
    else {
        note_index += direction;
        if (note_index >= notes_in_chord) {
           direction = -1;
           note_index--;
        }
        if (note_index < 0) {
          direction = 1;
          note_index = 0;
        }
    }

    return play_note;
}  

#endif
