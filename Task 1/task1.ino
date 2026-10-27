const int redLED = 8;
const int yellowLED = 9;
const int greenLED = 10;

const unsigned long RED_TIME = 5000;
const unsigned long RED_YELLOW_TIME = 1000;
const unsigned long GREEN_TIME = 5000;
const unsigned long YELLOW_TIME = 2000;

enum State {
  RED,
  RED_YELLOW,
  GREEN,
  YELLOW
};

State currentState = RED;

void showState(State state) {
// Turn every light off before setting the new state
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);

  switch (state) {
    case RED:
    digitalWrite(redLED, HIGH);
    break;

    case RED_YELLOW:
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    break;
    
    case GREEN:
    digitalWrite(greenLED, HIGH);
    break;

    case YELLOW:
    digitalWrite(yellowLED, HIGH);
    break;
    }
}

void setup() {
pinMode(redLED, OUTPUT);
pinMode(yellowLED, OUTPUT);
pinMode(greenLED, OUTPUT);

showState(currentState); 
}

void loop() {
  switch (currentState) {
    case RED:
    delay (RED_TIME);
    currentState = RED_YELLOW;
    break;

    case RED_YELLOW:
    delay(RED_YELLOW_TIME); 
    currentState = GREEN;
    break;

    case GREEN:
    delay(GREEN_TIME);
    currentState = YELLOW;
    break;

    case YELLOW:
    delay(YELLOW_TIME);
    currentState = RED;
    break;

}
showState(currentState);

}
