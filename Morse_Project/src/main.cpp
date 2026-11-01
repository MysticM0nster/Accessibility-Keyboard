#include "Arduino.h"
#include "morse_table.h"
#include <cstring>

struct MorseNode {
  char letter;
  MorseNode* dit;
  MorseNode* dah;
};

const int DIT_BUTTON_PIN = 1; //temporary numbers, volatile
const int DAH_BUTTON_PIN = 2;
const int CONFIRM_BUTTON_PIN = 3;

const int DIT_VALUE = 0;
const int DAH_VALUE = 1;

bool dit_was_pressed = false;
bool dah_was_pressed = false;
bool confirm_was_pressed = false;

MorseNode root = {'\0', nullptr, nullptr};
MorseNode* current_node = &root;

void buildMorseTree() {
  for (int i = 0; i < morseTableSize; i++) {
    MorseNode* current = &root;   // every letter starts back at the top

    for (int j = 0; j < strlen(morseTable[i].sequence); j++) {
      char step = morseTable[i].sequence[j];

      if (step == '0') {
        if (current->dit == nullptr) {
          // create a new node, store its address in current->dit
          current->dit = new MorseNode{'\0', nullptr, nullptr};
          
        }
        // move current down to its dit child
        current = current->dit;
      } else {
        // the same two things, but for dah
        if (current->dah == nullptr) {
          current->dah = new MorseNode{'\0', nullptr, nullptr};
          
        }
        current = current->dah;
      }
    }
    
    // label the node you ended on with this entry's letter
    current->letter = morseTable[i].letter;
  }
}

void advanceMorseTree(int button_press) {
  if (button_press == 0) {
    if (current_node->dit == nullptr) {
      return; //idk what to do when there is nowhere left to go
    } else {
      current_node = current_node->dit; // this moves the node down one, right? just advances through the door?
    }

  } else if (button_press == 1) {
    if (current_node->dah == nullptr) {
      return; //same here as with dit
    } else {
      current_node = current_node->dah;
    }
  }
}

void confirmMorseTreePosition() {
  





}

void setup() {
  Serial.begin(115200);
  buildMorseTree();

  pinMode(DIT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DAH_BUTTON_PIN, INPUT_PULLUP);

  MorseNode* test = root.dit;   // E
  test = test->dah;             // should be A
  Serial.println(test->letter); // expect: A
}

void loop() {
  // int dit_button_state = digitalRead(DIT_BUTTON_PIN);
  // int dah_button_state = digitalRead(DAH_BUTTON_PIN);
  bool dit_is_pressed = (digitalRead(DIT_BUTTON_PIN) == LOW);
  bool dah_is_pressed = (digitalRead(DAH_BUTTON_PIN) == LOW);
  bool confirm_is_pressed = (digitalRead(CONFIRM_BUTTON_PIN) == LOW);

  if (dit_is_pressed && !dit_was_pressed) {
    advanceMorseTree(DIT_VALUE);
    dit_was_pressed = dit_is_pressed;

  } else if (dah_is_pressed && !dah_was_pressed) {
    advanceMorseTree(DAH_VALUE);
    dah_was_pressed = dah_is_pressed;
  
  } else if (confirm_is_pressed && !confirm_was_pressed) {
    confirmMorseTreePosition();
  }
  delay(20); //TODO: make this non-blocking!!! (debounce)
}