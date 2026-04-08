#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
// Define all notes above :)

int notes [ ] = { NOTE_A2,NOTE_AS2,NOTE_B2 , NOTE_C3 , NOTE_CS3 , NOTE_D3 , NOTE_DS3 , NOTE_E3 ,NOTE_F3  ,NOTE_FS3, NOTE_G3,  
NOTE_GS3, NOTE_A3, NOTE_AS3, NOTE_B3,NOTE_C4 , NOTE_CS4, NOTE_D4 , NOTE_DS4 , NOTE_E4 , NOTE_F4 , NOTE_FS4 , NOTE_G4, 
NOTE_GS4, NOTE_A4 , NOTE_AS4 , NOTE_B4 , NOTE_C5, NOTE_CS5, NOTE_D5 , NOTE_DS5 , NOTE_E5 , NOTE_F5 , NOTE_FS5 , 
NOTE_G5 , NOTE_GS5 , NOTE_A5  };
// this is an array of text_labels, in this case from note A2, 4 octaves untl note A5

// C Major notes (1)
//int cMajor[] = { NOTE_C3, NOTE_D3, NOTE_E3, NOTE_G3, NOTE_A3 }; // 131, 147, 165, 196, 220
int cMajor[] = { 
  NOTE_C2, NOTE_D2, NOTE_E2, NOTE_F2, NOTE_G2, NOTE_A2, NOTE_B2, 
  NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3, 
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, 
  NOTE_C5
};

// G Major (2)
int gMajor[] = { 
  NOTE_G2, NOTE_A2, NOTE_B2, NOTE_C3, NOTE_D3, NOTE_E3, NOTE_FS3,
  NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_FS4,
  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_FS5, NOTE_G5 
};

// A Major (3)
int aMajor[] = { 
  NOTE_A2, NOTE_B2, NOTE_CS3, NOTE_D3, NOTE_E3, NOTE_FS3, NOTE_GS3,
  NOTE_A3, NOTE_B3, NOTE_CS4, NOTE_D4, NOTE_E4, NOTE_FS4, NOTE_GS4,
  NOTE_A4, NOTE_B4, NOTE_CS5, NOTE_D5, NOTE_E5, NOTE_FS5, NOTE_GS5, NOTE_A5 
};

// E Minor (4)
int eMinor[] = { 
  NOTE_E2, NOTE_FS2, NOTE_G2, NOTE_A2, NOTE_B2, NOTE_C3, NOTE_D3,
  NOTE_E3, NOTE_FS3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C4, NOTE_D4,
  NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5 
};

// Sensor Values
int sensorMax = 400; // REPLACE WHEN TESTED
int sensorMin = 90; // REPLACE WHEN TESTED

// Board variables
int sensor = A0; // junction between light sensor and resistor to input pin AO
int buzzer = 11; //buzzer connecting pin 11

int value = 0; //variable used to store sensor readings
int note = 0; //variable used to store frequency of note based on sensor reading

// New Buttons
const int buttonOne = 6;
const int buttonTwo = 7;
int buttonStateOne = 0;
int buttonStateTwo = 0;

int scaleVal = 0;


// FUNCTIONS ///////////////////////////////////////////

int maptoScaleC(int noteValue) { // input is scale and value of note
  int tempNote = map(noteValue, sensorMin, sensorMax, 0, 22); // map to one of 5 vals 
  
  // constrain ensures tempNote stays between 0 and 4
  tempNote = constrain(tempNote, 0, 22);
  //Serial.println(cMajor[tempNote]); // print value
  return cMajor[tempNote]; // set to clamped range
}

int maptoScaleE(int noteValue) { // input is scale and value of note
  int tempNote = map(noteValue, sensorMin, sensorMax, 0, 22); // map to one of 5 vals 
  
  // constrain ensures tempNote stays between 0 and 4
  tempNote = constrain(tempNote, 0, 22);
  //Serial.println(eMinor[tempNote]); // print value
  return cMajor[tempNote]; // set to clamped range
}

int maptoScaleG(int noteValue) { // input is scale and value of note
  int tempNote = map(noteValue, sensorMin, sensorMax, 0, 22); // map to one of 5 vals 
  
  // constrain ensures tempNote stays between 0 and 4
  tempNote = constrain(tempNote, 0, 22);
  //Serial.println(gMajor[tempNote]); // print value
  return gMajor[tempNote]; // set to clamped range
}

int maptoScaleA(int noteValue) { // input is scale and value of note
  int tempNote = map(noteValue, sensorMin, sensorMax, 0, 22); // map to one of 5 vals 
  
  // constrain ensures tempNote stays between 0 and 4
  tempNote = constrain(tempNote, 0, 22);
  //Serial.println(aMajor[tempNote]); // print value
  return aMajor[tempNote]; // set to clamped range
}



int chooseScale(int b1, int b2) {
  if (b1 == 1 && b2 == 1) {
    return 4;
  }
  if (b1 == 1) {
      return 2;
  }
  if (b2 == 1) {
      return 3;
  }
  return 1; // Cmajor is 1
};

//int[] 



////////////////////////////////////////////////////////



// CODE ////////////////////////////////////////////////

void setup() {
  // put your setup code here, to run once:
  pinMode(sensor,INPUT);   //pin A0 configured as input
  pinMode(buzzer,OUTPUT);  // pin 11 configured as output

  pinMode(buttonOne, INPUT);
  pinMode(buttonTwo, INPUT);

  Serial.begin(9600); // allow for write out
}

void loop() {


  // put your main code here, to run repeatedly:
  buttonStateOne = digitalRead(buttonOne);
  buttonStateTwo = digitalRead(buttonTwo);

   //Serial.println("here1"); // print value

  value = analogRead(sensor); //ambient light in class was 800
  value = constrain(value, sensorMin, sensorMax);
  Serial.println(value); // print value

 scaleVal = chooseScale(buttonStateOne, buttonStateTwo);
 //note = maptoScaleC(value, cMajor);

 switch (scaleVal) {
  case 4:
    note = maptoScaleE(value);
    //Serial.println("eMinor"); // print value
    break;
  case 3:
    note = maptoScaleA(value);
    //Serial.println("a"); // print value
    break;
  case 2:
    note = maptoScaleG(value);
    //Serial.println("g"); // print value
    break;
  default:
    note = maptoScaleC(value);
    //Serial.println("cMajor"); // print value
    break;
 }



  tone(buzzer, note, 10);   // Play for 10 units;    tone (pin_number, frequeny , duration);   OR tone(pin_number, frequency, duration);
  delay(1);
}
