
#define flashingRate 2
#define buttonPin 2
#define ledPin 5

int counter = 0;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
unsigned long lastButtonTime = 0; 
unsigned long debounceTime = 330;

int ledState = LOW;
bool buttonState = false;
int freq = 1000 / flashingRate;

void setup() {
  pinMode(buttonPin, INPUT);
  
  pinMode(ledPin, OUTPUT);

  //interrupt
  attachInterrupt(digitalPinToInterrupt(2), button_press, FALLING);

  //serial
  Serial.begin(9600);
}

void loop() {
  debounce_func();
  LED_states();
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
  if (counter > 4) {
    counter = 0;
  }
}

//switching states
void LED_states() {
  switch (counter) {
    case 0: //off
      analogWrite(ledPin, 0);
      break;
    case 1: //low brightness
      analogWrite(ledPin, 70);
      break;
    case 2: //medium brightness
      analogWrite(ledPin, 160);
      break;
    case 3: //high brightness
      analogWrite(ledPin, 255);
      break;
    case 4:
      //flashing using millis
      currentMillis = millis();
      if (currentMillis - previousMillis >= freq) {
        previousMillis = currentMillis;
        if (ledState == LOW) {
          ledState = HIGH;
        }
        else {
          ledState = LOW;
        }
      }
      digitalWrite(ledPin, ledState);
      break;
     
      
      
   }
}
