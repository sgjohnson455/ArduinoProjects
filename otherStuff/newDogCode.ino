#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
// Define all notes above :)

#include <Stepper.h>
#include <Servo.h>

//  In/Outs
const int buttonPin = 13;  // START/STOP - Never unplug without turning it off
const int buzzer = 9;      // Audio
const int sensorPin = A0;  // Head-petting Sensor
int sensorValue = 0;       // (track input from head)

// Stepper setup (ULN2003)
const int stepsPerRevolution = 2048;
Stepper neckStepper(stepsPerRevolution, 2, 4, 3, 5);

Servo tailServo;
const int TAIL_CENTER = 90;   // neutral position
const int TAIL_LEFT   = 60;   // left wag limit
const int TAIL_RIGHT  = 120;  // right wag limit
const int TAIL_WAGS   = 2;    // wags per head pat
const int TAIL_SPEED  = 10;   // ms delay between degree steps (lower = faster)


// Movement settings
const int MAX_SWING = 512;  // ~70 degrees
const int STEP_SIZE = 50;

long position = 0;            // 0 = center (TRACK CENTER - also important bc NO OWL DOGS)
bool motorEnabled = false;    // used to track if safetly stopped
bool lastButtonState = HIGH;  // track on/off state
bool directionRight = true;  // RESTORED - was missing from your new code

// On and Off
bool machineOn = false;
bool alreadyStopped = false;

// Variables
const int state = LOW;
int val = 0;

///////////////////////////////////////////
//Setup
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Start/Stop
  pinMode(buzzer, OUTPUT);           // Noise
  // No initialization for Touch Head Sensor
  lastButtonState = digitalRead(buttonPin);  // IMPORTANT FIX

  machineOn = false;  // default OFF
  alreadyStopped = false;

  neckStepper.setSpeed(5);

  tailServo.attach(7);           // *** attach tail servo to pin 7 ***
  tailServo.write(TAIL_CENTER);  // *** start centered ***
  delay(500);

  Serial.begin(9600);  // For printing code
  Serial.print("Welcome to Dog Machine");
}

void loop() {
  handleButton();

  // Kill Loop early if machine not 'on'
  // if (!machineOn) {
  //   if (!alreadyStopped) {
  //     stopMotor();  // run ONCE
  //     alreadyStopped = true;
  //   }
  //   return;
  // }

  //REINSTATE
  sensorValue = analogRead(sensorPin);  // get Head Touch Input

  // Behavior Code
  if (sensorValue > 100) {
    Serial.print("Dog Head Pat: ");
    Serial.println(sensorValue);
    excitedSound();
    wagTail();
    // moveLeft();
    // recenter();
    // moveRight();
    // recenter();
  }
}

/////////////////////////////////////////////////
// Helper

void wagTail() {
  Serial.println("Wagging tail!");

  for (int i = 0; i < TAIL_WAGS; i++) {
    // Sweep to right
    for (int pos = TAIL_CENTER; pos <= TAIL_RIGHT; pos++) {
      tailServo.write(pos);
      delay(TAIL_SPEED);
    }
    // Sweep to left
    for (int pos = TAIL_RIGHT; pos >= TAIL_LEFT; pos--) {
      tailServo.write(pos);
      delay(TAIL_SPEED);
    }
    // Return to center
    for (int pos = TAIL_LEFT; pos <= TAIL_CENTER; pos++) {
      tailServo.write(pos);
      delay(TAIL_SPEED);
    }
  }

  Serial.println("Tail wag done.");
}

void excitedSound() {
  // A series of 3 to 5 rapid, happy yips
  delay(500);
  int yips = random(3, 6);

  for (int i = 0; i < yips; i++) {
    // Quick rising pitch (chirp)
    for (int freq = 500; freq < 800; freq += 30) {
      tone(buzzer, freq);
      delay(5);
    }
    noTone(buzzer);

    // Short, irregular gaps between yips make it sound more "excited"
    delay(random(40, 100));
  }
}

void handleButton() {
  bool onButtonState = digitalRead(buttonPin);

  // detect press (HIGH → LOW)
  if (lastButtonState == HIGH && onButtonState == LOW) {
    machineOn = !machineOn;

    Serial.print("Machine State: ");
    Serial.println(machineOn ? "ON" : "OFF");

    delay(200);  // debounce
  }

  lastButtonState = onButtonState;
}
void budgeLeft() {
  long nextPos = position - STEP_SIZE;
  int stepAmount = nextPos - position;  // will be negative (moves left)
  neckStepper.step(stepAmount);
  position = nextPos;

  Serial.print("Left: ");
  Serial.println(position);
}
void moveLeft() {
  int stepAmount = -MAX_SWING - position;  // calculate steps needed from wherever we are
  neckStepper.step(stepAmount);
  position = -MAX_SWING;

  Serial.print("Left: ");
  Serial.println(position);
}

void moveRight() {
  int stepAmount = MAX_SWING - position;  // go straight to +512 from wherever we are
  neckStepper.step(stepAmount);
  position = MAX_SWING;

  Serial.print("Right: ");
  Serial.println(position);
}

void recenter() {
  if (position == 0) return;  // safe to call even if no move was made

  int stepAmount = -position;  // works for both +512 and -512 back to center
  neckStepper.step(stepAmount);
  position = 0;

  Serial.println("Recentered");
}

void stopMotor() {
  Serial.println("Stopping motor and returning to center...");

  while (position != 0) {
    int stepAmount;

    if (position > 0) {
      stepAmount = -STEP_SIZE;
      if (position + stepAmount < 0) stepAmount = -position;
    } else {
      stepAmount = STEP_SIZE;
      if (position + stepAmount > 0) stepAmount = -position;
    }

    neckStepper.step(stepAmount);
    position += stepAmount;
  }
  // fix tail pos
  tailServo.write(TAIL_CENTER);
  Serial.println("Motor stopped and centered.");

  Serial.println("Motor stopped and centered.");
}


