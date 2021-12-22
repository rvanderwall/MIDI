
// In the scale of C Major
// We have these modes
//  0  1  2  3  4  5  6  7  8  9  10 11 12
//  C  C# D  D# E  F  F# G  G# A  A#  B  C

// All white keys for key of C (Major)
//               C  D  E   F  G  A  B
//                W  W  H   W  W  W  H
int ionian[] = { 0, 2, 4,  5, 7, 9, 11,}

// All white keys for key of D (Minor)
//               C  D  Eb  F  G  A  Bb
//                W  H  W   W  W  W  H
int dorian[] = { 0, 2, 3,  5, 7, 9, 10 }

// All white keys for key of E
//                 C  Db Eb  F  G  Ab  Bb
//                  H  W  W   W  H  W  W
int phrygian[] = { 0, 1, 3,  5, 7, 8, 10 }

// All white keys for key of F
//               C  D  E  F# G  A  B
//                W  W  W   H  W  W  H
int lydian[] = { 0, 2, 4, 6, 7, 9, 11 }

// All white keys for key of G
//                   C  D  E   F  G  A  Bb
//                    W  W  H   W  W  H  W
int mixolydian[] = { 0, 2, 4,  5, 7, 9, 10 }

// All white keys for key of A (Natural Minor)
//                C  D  Eb  F  G  Ab  Bb
//                 W  H  W   W  H   W   W
int aeolian[] = { 0, 2, 3,  5, 7, 8, 10 }

// All white keys for key of B
//                C  Db Eb  F  Gb Ab  Bb
//                 H  W  W   H   W   W  W
int locrian[] = { 0, 1, 3,  5, 6, 8, 10 }


// Harmonic Minor (Augmented chords)
//                C D  Eb  F  G  Ab   B
//                 W  H  W   W  H   W+  H
int harmonic[] = { 0, 2, 3,  5, 7, 8, 11 }


// Melodic Minor (Dorian)
//                C D  Eb  F  G  A  B
//                 W  H  W   W  W  W  H
int harmonic[] = { 0, 2, 3,  5, 7, 8, 11 }

maj   = [0, 4, 7, 11]  // 1,3,5 ionian
minor = [0, 3, 7, 10]  // 1,3,5 dorian
dim   = [0, 3, 6,  9]  // 1,3,5 locrian
aug   = [0, 4, 8, 10]  // 1,3,5 lydian

