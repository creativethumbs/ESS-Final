#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <elapsedMillis.h>

// notes
#define KC1     2
#define KCS1    3
#define KD1     4
#define KDS1    5
#define KE1     6
#define KF1     7
#define KFS1    8
#define KG1     9
#define KGS1    10
#define KA1     11
#define KAS1    12
#define KB1     13
#define KC2     14
#define KCS2    15
#define KD2     16
#define KDS2    17
#define KE2     18
#define KF2     19
#define KFS2    20
#define KG2     21
#define KGS2    22
#define KA2     24
#define KAS2    26
#define KB2     28
#define KC3     30

#define REST    -1

// note to self: always use unsigned long w/ millis or else time would become negative....
unsigned long startMillis;
unsigned long noteStartTime;

unsigned int sample;

// time stamp for the last time a tip was received
unsigned long lastTip = -5000;

int numTips = 0;

int LoopLength = 2;
int CurrLoop = 0;
//int LoopLength = 45;
//int CurrLoop = 5;

int NotePlaying[25];


void setup() {
  for (int i = 2; i < 22; i++) {
    pinMode(i, OUTPUT);
  }

  for (int j = 22; j <= 30; j += 2) {
    pinMode(j, OUTPUT);
  }

  Serial.begin(9600);

  // Testing keys
  /*
    for (int i = 2; i < 22; i++) {
      digitalWrite(i, HIGH);
      delay(1000);
      digitalWrite(i, LOW);
    }

    for (int j = 22; j <= 30; j += 2) {
      digitalWrite(j, HIGH);
      delay(1000);
      digitalWrite(j, LOW);
    }
  */
}


void loop() {

  if (Serial.available()) {
    int val = Serial.read();

    // note on
    if (val < 25) {
      if (!NotePlaying[val]) {
        NotePlaying[val] = true;

        if (val <= 20) {
          digitalWrite(val + 2, HIGH);
        }
        else if (val == 21) {
          digitalWrite(KA2, HIGH);
        }
        else if (val == 22) {
          digitalWrite(KAS2, HIGH);
        }
        else if (val == 23) {
          digitalWrite(KB2, HIGH);
        }
        else if (val == 24) {
          digitalWrite(KC3, HIGH);
        }
      }
    }

    // note off
    else {
      if (NotePlaying[val - 25]) {
        NotePlaying[val - 25] = false;

        if (val <= 20) {
          digitalWrite((val - 25) + 2, LOW);
        }
        else if (val == 21) {
          digitalWrite(KA2, LOW);
        }
        else if (val == 22) {
          digitalWrite(KAS2, LOW);
        }
        else if (val == 23) {
          digitalWrite(KB2, LOW);
        }
        else if (val == 24) {
          digitalWrite(KC3, LOW);
        }
      }
    }
  }

}




