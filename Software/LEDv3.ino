//defining pins - preprocessor directives 
#define flashingRate 2
#define buttonPin 2
#define ledPin 5

//defining variables 
int counter = 0;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
unsigned long lastButtonTime = 0; 
unsigned long debounceTime = 200;
int baudValue = 9600;
int low = 70;
int medium = 160;
int high = 255;
int frequency = 1000 / flashingRate;

//introducing starting state of button and LED
int ledState = LOW;
bool buttonState = false;


void setup() {
  pinMode(buttonPin, INPUT);
  
  pinMode(ledPin, OUTPUT);

  //interrupt
  attachInterrupt(digitalPinToInterrupt(buttonPin), button_press, FALLING);

  //serial
  Serial.begin(baudValue);
}

void loop() {
  debounce_func();
  LED_states();
  Serial.print("Your bike light is in state: "); //you can use this to debug states
  Serial.println(counter);
}

//debouncing function
void debounce_func(){
  if ((millis() - lastButtonTime) > debounceTime){
    buttonState = true;
    lastButtonTime = millis();
  }
}


//interrupt
void button_press() {
  if (buttonState) {
    counter += 1;
    buttonState = false;
  } 
  if (counter > 4) { //to make sure the counter doesn't go on forever --> easier to debug this way
    counter = 0;
  }
}

void flashing_func() { //to flash the LED at a certain frequency 
  currentMillis = millis();
      if (currentMillis - previousMillis >= frequency) {
        previousMillis = currentMillis;
        if (ledState == LOW) {
          ledState = HIGH;
        }
        else {
          ledState = LOW;
        }
      }
      digitalWrite(ledPin, ledState);
}

//switching states
void LED_states() {
  switch (counter) {
    case 0: //off
      analogWrite(ledPin, 0);
      break;
    case 1: //low brightness
      analogWrite(ledPin, low);
      break;
    case 2: //medium brightness
      analogWrite(ledPin, medium);
      break;
    case 3: //high brightness
      analogWrite(ledPin, high);
      break;
    case 4:
      //flashing using millis
      flashing_func();
      break;
     
      
      
   }
}
