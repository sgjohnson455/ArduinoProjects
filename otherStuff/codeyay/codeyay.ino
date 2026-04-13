int sensor = A0;
int buzzer = 9;

// light + note
int value = 0;
int note = 0;

// button
const int buttonPin = 2;
int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(sensor);
  buttonState = digitalRead(buttonPin);
  
 // Serial.println(value);
  // Serial.println(buttonState);

  // code goes here
if (buttonState == 1) {
  note = map(value, 100, 350, 100, 700);
  Serial.println("on");

  
  delay(1);
} else {
  note = 0;
  Serial.println("off");
}

tone(buzzer, note, 10);

}
