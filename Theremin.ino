#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int trigPin = 10;
const int echoPin = 11;
const int tonePin = 9;
const int pwmPin = 5;
const int buttonPin = 2;
const int potPin = A0;

long duration;
float smoothDistance = 0;
const float alpha = 0.3;
int distance;
int note;
int mode = 0;
bool isMuted = false;
unsigned long lastPress = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Natural notes A to A5 (no sharps/flats)
int snappedNotes[] = {
  440, // A
  494, // B
  523, // C
  587, // D
  659, // E
  698, // F
  784, // G
  880  // A5
};

String noteNames[] = {
  "A", "B", "C", "D", "E", "F", "G", "A5"
};

String fxModes[] = {
  "Clean", "Tremolo", "Glitch", "Reverb"
};

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(tonePin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(potPin, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Theremin Synth");
  lcd.setCursor(0, 1);
  lcd.print("FX Mode: Clean");
  delay(1000);
}

void loop() {
  // FX Mode & Mute Toggle
  if (digitalRead(buttonPin) == LOW && millis() - lastPress > 300) {
    unsigned long holdTime = 0;
    while (digitalRead(buttonPin) == LOW) {
      delay(10);
      holdTime += 10;
      if (holdTime >= 2000) break;
    }

    lastPress = millis();
    if (holdTime >= 2000) {
      isMuted = !isMuted;
    } else {
      mode = (mode + 1) % 4;
    }
  }

  // Distance Measurement with Smoothing
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  float rawDistance = duration * 0.034 / 2;
  smoothDistance = alpha * rawDistance + (1 - alpha) * smoothDistance;
  distance = (int)smoothDistance;

  if (distance >= 5 && distance <= 45) {
    int index = map(distance, 5, 45, 0, 7);
    index = constrain(index, 0, 7);
    note = snappedNotes[index];

    lcd.setCursor(0, 0);
    lcd.print("Note: ");
    lcd.print(noteNames[index]);
    lcd.print("    ");

    lcd.setCursor(0, 1);
    lcd.print("FX Mode: ");
    lcd.print(fxModes[mode]);
    lcd.print("   ");

    if (isMuted) {
      noTone(tonePin);
      analogWrite(pwmPin, 255);
    }

    else if (mode == 0) {
      tone(tonePin, note);
      analogWrite(pwmPin, 255);
    }

    else if (mode == 1) {
      tone(tonePin, note);
      int potValue = analogRead(potPin);
      float tremoloSpeed = 20 + pow((1023 - potValue) / 1023.0, 2.0) * 280;
      tremoloSpeed = constrain(tremoloSpeed, 20, 300);
      int lfo = (sin(millis() / tremoloSpeed) + 1.0) * 127.5;
      analogWrite(pwmPin, lfo);
    }

    else if (mode == 2) {
      int glitchChance = random(0, 10);
      if (glitchChance < 7) {
        tone(tonePin, note);
        analogWrite(pwmPin, 255);
        delay(random(50, 80));
        noTone(tonePin);
        delay(random(30, 60));
      } else {
        noTone(tonePin);
        analogWrite(pwmPin, 0);
        delay(random(30, 50));
      }
    }

    else if (mode == 3) {
      tone(tonePin, note);
      analogWrite(pwmPin, 255);
      delay(random(20, 40));
      noTone(tonePin);
      delay(random(20, 30));
    }

  } else {
    noTone(tonePin);
  }

  delay(30);
}
