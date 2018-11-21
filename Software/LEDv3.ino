
#define buttonPin 2
#define ledPin 5

int ledState = HIGH;         // the current state of the LED
bool buttonState;             // the current reading from the button
int lastButtonState = LOW;   // the previous reading from the button
int max_brightness = 255;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 2000;    // the debounce time; increase if the output flickers

int counter = 0;
int brightness = 0;

void setup() { 
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  //initial LED state
  digitalWrite(ledPin, ledState);

  //interrupt
  attachInterrupt(digitalPinToInterrupt(2), press_the_button, RISING);

  //Serial
  Serial.begin(9600);
}

void loop() {
  debounce_func();
  shine_the_light();
  counter_func();
  digitalRead(ledState);
  Serial.println(counter);
}
  


void counter_func() {//counter and to make sure counter doesn't go on forever
  if (buttonState = true) {
  lastButtonState = digitalRead(buttonPin);
  delay(200);
  buttonState = digitalRead(buttonPin);
    if (buttonState == 1 && lastButtonState == 0){
      counter = counter + 1;

    }
  }
 buttonState = false;
 
  if (counter > 4) {
    counter = 0;
  }
}


void debounce_func() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
    if ((millis() - lastDebounceTime) > debounceDelay) {
   
      if (reading != buttonState) {
        buttonState = reading;

        if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }

  
  digitalWrite(ledPin, ledState);
  lastButtonState = reading;
}

void shine_the_light() {
  switch (counter) {
    case 0: {//case for on & off
        buttonState = digitalRead(buttonPin);
        if (buttonState == HIGH) {
          digitalWrite(ledPin, HIGH);
        }
      else {
        digitalWrite(ledPin, LOW);
      }
      break;
    }
    case 1:  {//case for blinking
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
        break;
      }
    case 2: {//case for very bright 
      brightness = int(max_brightness);
      ledState = HIGH;
      analogWrite(ledPin, ledState);
    }
        break;
      
    case 3: { //case for intermediate
      brightness = int(max_brightness/2);
      ledState = HIGH;
      analogWrite(ledPin, brightness);
        break;
    }
        
     case 4: {//case for low brightness
      brightness = int(max_brightness/4);
      ledState = HIGH;
      analogWrite(ledPin, brightness);
        break;
      }
     
     

  }
}



void press_the_button()  {
  
  counter++;

}
