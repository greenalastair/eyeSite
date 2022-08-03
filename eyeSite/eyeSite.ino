


int buttonState = 0;
int buttonPin = 7;
int LEDpin = 13;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LEDpin, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
      digitalWrite(LEDpin, HIGH);
  } else if (buttonState == LOW) {
    digitalWrite(LEDpin, LOW);
  }
}
