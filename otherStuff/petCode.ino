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

int notes[] = { NOTE_A2, NOTE_AS2, NOTE_B2, NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3,
                NOTE_GS3, NOTE_A3, NOTE_AS3, NOTE_B3, NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4,
                NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4, NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5,
                NOTE_G5, NOTE_GS5, NOTE_A5 };

int cMajor[] = {
  NOTE_C2, NOTE_D2, NOTE_E2, NOTE_F2, NOTE_G2, NOTE_A2, NOTE_B2,
  NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3,
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4,
  NOTE_C5
};

int note = 0;


int maptoScaleC(int noteValue) {                // input is scale and value of note
  int tempNote = map(noteValue, 0, 25, 0, 22);  // map to one of 5 vals

  // constrain ensures tempNote stays between 0 and 4
  tempNote = constrain(tempNote, 0, 22);
  Serial.println(cMajor[tempNote]);  // print value
  return cMajor[tempNote];           // set to clamped range
}


//  Inouts
int buzzer = 9;  // Led positive terminal to the digital pin 9.
int sensor = 2;  //signal pin of sensor to digital pin 5.
int state = LOW;
int val = 0;

const int sensorPin = A0;
int sensorValue = 0;

void setup() {              // Void setup is ran only once after each powerup or reset of the Arduino board.
  pinMode(buzzer, OUTPUT);  // Led is determined as an output here.
  pinMode(sensor, INPUT);   // PIR motion sensor is determined is an input here.



  Serial.begin(9600);
}

// void loop() {  // Void loop is ran over and over and consists of the main program.
// //tone(buzzer, 440);
//   val = digitalRead(sensor);
//   if (val == HIGH) {
//     tone(buzzer, NOTE_D4, 10);
//     Serial.println(" Motion");
//     delay(10);  // Delay of led is 500
//     if (state == LOW) {
//       Serial.println(" Motion yay");
//       state = HIGH;
//     }
//   } else {
//     //digitalWrite(led, LOW);
//     Serial.println("motion has stopped");
//     delay(10);

//     if (state == HIGH) {
//       Serial.println("The action/ motion has stopped");
//       state = LOW;
//     }
//   }
// }


void loop() {
  sensorValue = analogRead(sensorPin);  // Read analog value
  //note = maptoScaleC(sensorValue);

  //tone(buzzer, note, 10);
  if (sensorValue > 0) {
    Serial.print("Vibration Detected! Value: ");
    Serial.println(sensorValue);
    excitedSound();
  }
  delay(10);  // Small delay to stabilize
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

void dogBehavior() {
  int action = random(0, 5);  // Increased range to include the whine

  switch (action) {
    case 0: lowGrowl(random(1000, 2500)); break;
    case 1: doubleBark(); break;
    case 2: excitedSound(); break;
    case 4: petSound(); break;  // Added the whine
    case 3: /* Quiet */ break;
  }

  delay(random(1000, 2000));
}

void petSound() {
  // A dog being pet often makes a "huffing" sigh or deep grumble
  // We'll simulate this by sliding a low frequency down while pulsing it
  
  for (int repeat = 0; repeat < 2; repeat++) { // Do two "breaths"
    int startFreq = 120; // Low, chesty sound
    int endFreq = 60;    // Deep bass finish
    
    for (int freq = startFreq; freq > endFreq; freq -= 2) {
      // Pulsing the tone creates the "shudder" of a satisfied dog
      tone(buzzer, freq);
      delay(15); 
      noTone(buzzer);
      delay(5); // Tiny gap adds texture to the "breath"
    }
    
    delay(400); // Pause between breaths
  }
}

void doubleBark() {
  // First short bark
  tone(buzzer, 550);
  delay(100);
  tone(buzzer, 610);
  delay(100);
  noTone(buzzer);

  delay(150);  // Short pause between barks

  // Second short bark
  tone(buzzer, 150);
  delay(50);
  tone(buzzer, 110);
  delay(100);
  noTone(buzzer);
}

void lowGrowl(int durationMs) {
  unsigned long startTime = millis();

  while (millis() - startTime < durationMs) {
    // Rapidly alternate between very low frequencies to create "rumble"
    tone(buzzer, 60);  // Deep base
    delay(30);         // Short pulse
    tone(buzzer, 45);  // Even deeper vibration
    delay(35);
  }

  noTone(buzzer);  // End growl
}