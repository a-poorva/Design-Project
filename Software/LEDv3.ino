
const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

// Variable Variables
int ledState = LOW;         // the current state of the LED
volatile int buttonState;             // the current state of button
int lastButtonState = LOW;   // last state of button

unsigned long newtime = 0;  // the last time the button was toggled
unsigned long debounce = 50;    // the debounce time
unsigned long oldtime = 0; 
int counter = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  
 //initial LED state
  digitalWrite(ledPin, ledState);
  attachInterrupt(digitalPinToInterrupt(2), buttonPress, CHANGE);   //WHY IS THERE AN ERROR HERE OMG 

  //for brightness
  int brightness = 255;    // how bright the LED is
  int fadeAmount = 5;    // how many points to fade the LED by
  int counter = 0; //counter
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalread(ledState)
  
  switch(counter) {
    case 0: { //case for switching on and off    //SHOULD I MAKE THIS A SEP FUNCTION
      if (buttonState) {
        buttonState = 0;
        newtime = millis();

        if (newtime - oldtime >= debounce) {
          ledState = HIGH; 
        }
          else {
            ledState = LOW;
                }
           }
        oldtime = newtime;
        } 
      }
     case 1:  {//case for blinking
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
      delay(500);
     }
     case 2: {//case for very bright
      digitalWrite(ledPin, brightness);
      while(brightness > 0 && brightness < 255) {
        brightness = brightness + fadeAmount;
      }
     case 3 { //case for intermediate
      digitalWrite(ledPin, brightness);
      while(brightness > 0 && brightness < (brightness/2)) {
        brightness = brightness + fadeAmount;
      }
     case 4: {//case for low brightness
      digitalWrite(ledPin, brightness);
      while(brightness > 0 && brightness < (brightness/4)) {
        brightness = brightness + fadeAmount;
      }
     }
    }
   }
  }
 }
        
void buttonPress() {
  buttonState = TRUE;
  counter++
}
