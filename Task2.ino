class TrafficLightSystem {

  private:

    // LED pin numbers
    enum led {
      carRed = 8,
      carYellow = 9,
      carGreen = 10,
      pedRed = 11,
      pedGreen = 12
    };

    // Button pin
    const int button = 7;

    // Traffic light states
    enum state {
      RED,
      RED_YELLOW,
      GREEN,
      PEDESTRIAN
    };

    state currentState;
    bool buttonPressed = false;
    unsigned long stateStartTime = 0;

    // Change state and reset timer
    void changeTo(state nextState) {
      currentState = nextState;
      stateStartTime = millis();
    }

  public:

    // Constructor
    TrafficLightSystem() {
      currentState = RED;
    }

    // Set pin modes
    void setPins() {
      pinMode(carRed, OUTPUT);
      pinMode(carYellow, OUTPUT);
      pinMode(carGreen, OUTPUT);
      pinMode(pedRed, OUTPUT);
      pinMode(pedGreen, OUTPUT);

      pinMode(button, INPUT_PULLUP);

      // Initial lights
      setLights(HIGH, LOW, LOW, HIGH, LOW);
      stateStartTime = millis();
    }

    // Control the lights
    void setLights(bool cr, bool cy, bool cg,
                   bool pr, bool pg) {
      digitalWrite(carRed, cr);
      digitalWrite(carYellow, cy);
      digitalWrite(carGreen, cg);
      digitalWrite(pedRed, pr);
      digitalWrite(pedGreen, pg);
    }

    // Check button
    void checkButton() {
      if (digitalRead(button) == LOW) {
        buttonPressed = true;
      }
    }

    // Change state
    void changeState() {
      checkButton();

      switch (currentState) {

        case RED:
          // Car RED, pedestrian RED
          setLights(HIGH, LOW, LOW, HIGH, LOW);

          if (buttonPressed) {
            changeTo(PEDESTRIAN);
          }
          else if (millis() - stateStartTime >= 5000UL) {
            changeTo(RED_YELLOW);
          }
          break;

        case RED_YELLOW:
          // Car RED + YELLOW, pedestrian RED
          setLights(HIGH, HIGH, LOW, HIGH, LOW);

          if (millis() - stateStartTime >= 5000UL) {
            if (buttonPressed) {
              changeTo(PEDESTRIAN);
            }
            else {
              changeTo(GREEN);
            }
          }
          break;

        case GREEN:
          // Car GREEN, pedestrian RED
          setLights(LOW, LOW, HIGH, HIGH, LOW);

          if (millis() - stateStartTime >= 10000UL) {
            if (buttonPressed) {
              // Go directly to pedestrian crossing
              changeTo(PEDESTRIAN);
            }
            else {
              // Normal sequence: GREEN -> RED
              changeTo(RED);
            }
          }
          break;

        case PEDESTRIAN:
          // Car RED, pedestrian GREEN
          setLights(HIGH, LOW, LOW, LOW, HIGH);

          if (millis() - stateStartTime >= 10000UL) {
            buttonPressed = false;
            changeTo(RED);
          }
          break;
      }
    }
};

TrafficLightSystem trafficLight;

void setup() {
  trafficLight.setPins();
}

void loop() {
  trafficLight.changeState();
}
