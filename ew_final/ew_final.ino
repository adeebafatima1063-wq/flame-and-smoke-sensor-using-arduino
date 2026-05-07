#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int smokePin = A0;   
const int flamePin = 2;    
const int buzzerPin = 11;  

// Lowered threshold for better sensitivity based on your test
int smokeThreshold = 250;  

void setup() {
  Serial.begin(9600);
  pinMode(smokePin, INPUT);
  pinMode(flamePin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  
  // New Start-up Message
  lcd.setCursor(0, 0);
  lcd.print("System starting ");
  lcd.setCursor(0, 1);
  lcd.print("Please wait...  ");
  
  // Small delay to let the MQ-2 heater stabilize a bit
  delay(3000); 
  lcd.clear();
}

void loop() {
  int smokeValue = analogRead(smokePin);
  int flameValue = digitalRead(flamePin); 

  // --- Top Line: Smoke Status ---
  lcd.setCursor(0, 0);
  lcd.print("Smoke: ");
  lcd.print(smokeValue);
  lcd.print("    "); // Clears trailing digits

  // --- Bottom Line: Alarm Logic ---
  lcd.setCursor(0, 1);
  
  // Flame sensor logic
  if (flameValue == LOW) {
    lcd.print("FIRE DETECTED! ");
    digitalWrite(buzzerPin, HIGH);
  } 
  // Smoke sensor logic
  else if (smokeValue > smokeThreshold) {
    lcd.print("SMOKE DETECTED!");
    digitalWrite(buzzerPin, HIGH);
  } 
  // Normal state
  else {
    lcd.print("Status: Clear  ");
    digitalWrite(buzzerPin, LOW);
  }

  // Serial debugging
  Serial.print("S: "); Serial.print(smokeValue);
  Serial.print(" | F: "); Serial.println(flameValue);

  delay(250);
}
