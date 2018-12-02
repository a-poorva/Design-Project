
#define flashingRate 2
#define buttonPin 2
#define ledPin 6

bool buttonState = false;
int counter = 0;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
int ledState = LOW;
unsigned long lastButtonTime = 0; 
unsigned long debounceTime = 250;
int freq = 1000 / flashingRate;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  
  pinMode(ledPin, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(2), button_press, FALLING);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  debounce_func();
  shine_LED();
  Serial.println(counter);
}

void debounce_func(){
  if ((millis() - lastButtonTime) > debounceTime){
    buttonState = true;
    lastButtonTime = millis();
  }
}

void button_press() {
  if (buttonState) {
    counter += 1;
    buttonState = false;
  } 
  if (counter > 5) {
    counter = 0;
  }
}


void shine_LED() {
  switch (counter) {
    case 0:
      analogWrite(ledPin, 0);
      break;
    case 1:
      analogWrite(ledPin, 75);
      break;
    case 2:
      analogWrite(ledPin, 175);
      break;
    case 3:
      analogWrite(ledPin, 255);
      break;
    case 4:
      
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
    case 5: 
      analogWrite(ledPin, 0);
      ledState = LOW;
      break;
      
      
   }
}
