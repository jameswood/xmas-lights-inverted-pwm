const int ledPin[] = { 9, 10, 11, 3 };
const char lightPin = A6;
const char speedKnob = A7;
const int maxBright = 127;
const float pi = 3.1415;
const int darknessThreshold = 700;
//const int darknessThreshold = 1020;

void setup() {
  Serial.begin(115200);
  pinMode(speedKnob, INPUT);
  pinMode(lightPin, INPUT);
  TCCR1A = 0b10110000 | (TCCR1A & 0b00001111) ;
  TCCR2A = 0b10110000 | (TCCR2A & 0b00001111) ;
  for (int led = 0; led <= 3; led++ ) {
    pinMode(ledPin[led], OUTPUT);
    digitalWrite(ledPin[led], LOW);
    xmasLightWrite(ledPin[led], 0);
  }
}

void loop() {
  int currentLight = analogRead(lightPin);
  Serial.print("Light level: ");
  Serial.println(currentLight);
  if (currentLight < darknessThreshold) {
    crossfade();
  } else {
    for (int led = 0; led <= 3; led++ ) {
      digitalWrite(ledPin[led], LOW);
      delay(5000);
    };
  };
}

void crossfade() {
  for (int x = 0; x < 100; x++ ) {
    for (int led = 0; led <= 3; led++ ) {
      xmasLightWrite(ledPin[led], (0.5 * sin(0.02 * pi * (float(x) + ( led * 25 ))) + 0.5));
    }
    delay(map(analogRead(speedKnob), 0, 1023, 50, 1));
  }
}

void xmasLightWrite(int pin, float rawValue) {
  rawValue = min(rawValue, 1.0); rawValue = max(rawValue, 0.0);
  int value = int(rawValue * maxBright);
  int invertedValue = 255 - value;
  if ( ( pin == ledPin[1] ) || ( pin == ledPin[3] ) ) {
    if ( value == 0 ) {
      digitalWrite(pin, LOW);
    } else {
      analogWrite(pin, invertedValue);
    };
  } else {
    analogWrite(pin, value);
  };
}
