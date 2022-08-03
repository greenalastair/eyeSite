/*eyeSight
  Save your eyes from screen fatigue following 20/20/20 rule.
  LED that turns on after 20 mins, press a button, it flashes for 20 seconds
  (time you should be looking away to 20 ft distance) then turns off (back to work).
*/

int buttonState = 1; //NOTE ON buttonState: pushed in is 0 (LOW) out is 1 (HIGH)
int buttonPin = 7;
int LEDpin = 13;
int flag = 0;

int ledState = LOW;
unsigned long previousMillis = 0;
unsigned long previousFlashMillis = 0;
const long interval = 10000; // interval at which to turn on LED (milliseconds)
const long flashInterval = 150;

void setup() {
  Serial.begin(9600);
  Serial.println("eyeSight timer starting");
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LEDpin, OUTPUT);
}

void loop() {

  unsigned long currentMillis = millis(); //check the time
  buttonState = digitalRead(buttonPin); //check the button

  if (flag == 0 && buttonState == HIGH && currentMillis - previousMillis >= interval) { //once time is up, turn on the LED, advance to next code block (flag 1)
    digitalWrite(LEDpin, HIGH);
    Serial.println("LED ON");
    flag = 1;
    Serial.print("flag: ");
    Serial.println(flag);
  }

  if (flag == 0 && buttonState == LOW) {  //chck case of incorrect start configuration (button in at start with flag == 0)
    Serial.println("Button IN.... unlatch to begin");
    previousMillis = currentMillis; //reset the timer to begin timing again we dont want to start timgin until the start configuration is set
    if (currentMillis - previousFlashMillis >= flashInterval) {
      previousFlashMillis = currentMillis;
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      digitalWrite(LEDpin, ledState);
    }
  }

  if (flag == 0 && buttonState == HIGH && ledState == HIGH) { //improper config check, LED should be off in this case so trun it off
    ledState = LOW;
    digitalWrite(LEDpin, ledState);  
    previousMillis = currentMillis; //reset the timer to begin timing again we dont want to start timgin until the start configuration is set
  }

  if (flag == 1 && buttonState == LOW) { //with LED illuminated, wait for user to latch the button to indicate compliance
    Serial.print("  buttonState: ");
    Serial.println(buttonState);
    digitalWrite(LEDpin, LOW);   //once user presses button, turn off LED
    Serial.println("LED OFF");
    delay(5000); //eye relief time (20 seconds)
    digitalWrite(LEDpin, HIGH); //LED comes back on to indicate end of eye strain break
    Serial.println("LED ON");
    flag = 2; //advance to next code block (flag 2)
    Serial.print("flag: ");
    Serial.println(flag);
  }

  if (flag == 2 && buttonState == HIGH) { //wait for user to acknowledge end of eye relief break by pressing button again
    Serial.print("  buttonState: ");
    Serial.println(buttonState);
    previousMillis = currentMillis; //reset the timer to begin timing again
    digitalWrite(LEDpin, LOW);
    Serial.println("LED OFF");  //turn off LED
    flag = 0; //return to flag 0 state to loop code
    Serial.print("flag: ");
    Serial.println(flag);
  }
}
