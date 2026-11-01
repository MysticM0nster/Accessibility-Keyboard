#ifndef MORSE_TABLE_H
#define MORSE_TABLE_H

struct MorseEntry {
  const char* sequence; // 0 = down (dit), 1 = right (dah)
  char letter;
};

const MorseEntry morseTable[] = {
  // Level 1
  {"0",    'E'},
  {"1",    'T'},

  // Level 2
  {"00",   'I'},
  {"01",   'A'},
  {"10",   'N'},
  {"11",   'M'},

  // Level 3
  {"000",  'S'},
  {"001",  'U'},
  {"010",  'R'},
  {"011",  'W'},
  {"100",  'D'},
  {"101",  'K'},
  {"110",  'G'},
  {"111",  'O'},

  // Level 4
  {"0000", 'H'},
  {"0001", 'V'},
  {"0010", 'F'},
  {"0100", 'L'},
  {"0110", 'P'},
  {"0111", 'J'},
  {"1000", 'B'},
  {"1001", 'X'},
  {"1010", 'C'},
  {"1011", 'Y'},
  {"1100", 'Z'},
  {"1101", 'Q'},
};

const int morseTableSize = sizeof(morseTable) / sizeof(morseTable[0]);

#endif