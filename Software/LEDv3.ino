
const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

// Variable Variables
int ledState = LOW;         // the current state of the LED
volatile int buttonState;             // the current state of button
int lastButtonState = LOW;   // last state of button

unsigned long current_time = 0;
unsigned long debounce = 100;    // the debounce time
unsigned long old_time = 0;

int counter = 0;

//for brightness
int brightness = 255;    // how bright the LED is
int increment = 5;    // how many points to fade the LED by

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  //initial LED state
  digitalWrite(ledPin, ledState);

  //interrupt
  attachInterrupt(digitalPinToInterrupt(2), buttonPress, RISING);

  //Serial
  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
  digitalRead(ledState);
  Serial.println(counter);

  //anti-bouncing
  if (buttonState) {
    buttonState = 0;
    old_time = millis();

    if (current_time - old_time >= debounce) {
      counter++;
    }
  }



  current_time = old_time;

  //to make sure counter doesn't go on forever
  if (counter > 5) {
    counter = 0;
  }


  switch (counter) {
    case 1: {//case for on & off
        buttonState = digitalRead(buttonPin);
        if (buttonState == HIGH) {
          digitalWrite(ledPin, HIGH);
        }
      else {
        digitalWrite(ledPin, LOW);
      }
      break;
    }
    case 2:  {//case for blinking
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
        break;
      }
    case 3: {//case for very bright
        int current_brightness = digitalRead(ledPin);
        if (current_brightness = HIGH) {
          current_brightness = current_brightness + increment;
          }
    }
        break;
      
    case 4: { //case for intermediate
      
        int current_brightness = digitalRead(ledPin);
        if (current_brightness = HIGH) {
          current_brightness = current_brightness - increment;
          }
    
        break;
    }
        
        
      
    case 5: {//case for low brightness
        int current_brightness = digitalRead(ledPin);
        if (current_brightness = HIGH) {
          current_brightness = current_brightness - 3*(increment);
          }
        break;
      }

  }
}



void buttonPress()  {
  
  counter++;

}
