#include <LiquidCrystal_I2C.h>

// Pin definitions
const int buttonPin = 2;
const int ledPin = 3;
const int trigPin = 12;
const int echoPin = 13;
const int buzzerPin = 8;

// Constants
const int DISTANCE_THRESHOLD = 20; // Batas jarak dalam cm
const int MAX_DISTANCE = 200;

// Variables
int buttonState = 0;
int lastButtonState = 0;
int caseNumber = 1;
long duration;
int distance;

// Initialize LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize pins
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Initialize Serial dan LCD
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
  // Tampilkan pesan awal
  lcd.setCursor(0, 0);
  lcd.print("PING Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Case 1 Active");
  delay(2000);
  lcd.clear();
}

int measureDistance() {
  // Clear trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Trigger PING sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Baca durasi
  duration = pulseIn(echoPin, HIGH);
  
  // Hitung jarak dalam cm
  distance = duration * 0.034 / 2;
  
  // Batasi jarak maksimum
  if (distance > MAX_DISTANCE || distance < 0) {
    distance = MAX_DISTANCE;
  }
  
  return distance;
}

void displayDistance(int distance) {
  // Tampilkan di LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jarak: ");
  lcd.print(distance);
  lcd.print(" cm");
  
  // Tampilkan di Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void case1() {
  // Kasus 1: Pembacaan dasar PING
  lcd.setCursor(0, 1);
  lcd.print("Mode: Kasus 1");
  int dist = measureDistance();
  displayDistance(dist);
  delay(100);
}

void case2() {
  // Kasus 2: PING dengan peringatan
  int dist = measureDistance();
  displayDistance(dist);
  
  if (dist < DISTANCE_THRESHOLD) {
    // Aktifkan buzzer
    tone(buzzerPin, 1000);
    // Tampilkan peringatan
    Serial.println("PERINGATAN: Objek terlalu dekat!");
    lcd.setCursor(0, 1);
    lcd.print("PERINGATAN!");
  } else {
    noTone(buzzerPin);
    lcd.setCursor(0, 1);
    lcd.print("Mode: Warning");
  }
  delay(100);
}

void case3() {
  // Kasus 3: PING dengan LED PWM
  int dist = measureDistance();
  displayDistance(dist);
  lcd.setCursor(0, 1);
  lcd.print("Mode: LED PWM");
  
  // LED mati jika jarak > 50cm
  if (dist > 50) {
    analogWrite(ledPin, 0);
    Serial.println("LED: OFF (>50cm)");
  } else {
    // Atur brightness LED berdasarkan jarak untuk 0-50cm
    int brightness = map(dist, 0, 50, 255, 0);
    analogWrite(ledPin, brightness);
  }
  
  delay(100);
}

void loop() {
  // Baca status tombol
  buttonState = digitalRead(buttonPin);
  
  // Cek jika tombol ditekan
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Increment nomor kasus
    caseNumber++;
    if (caseNumber > 3) caseNumber = 1;
    
    // Reset output
    noTone(buzzerPin);
    analogWrite(ledPin, 0);
    lcd.clear();
    
    // Tampilkan pergantian kasus
    Serial.print("Beralih ke Kasus ");
    Serial.println(caseNumber);
    delay(200); // Debounce delay
  }
  
  // Jalankan kasus yang aktif
  switch (caseNumber) {
    case 1:
      case1();
      break;
    case 2:
      case2();
      break;
    case 3:
      case3();
      break;
  }
  
  // Simpan status tombol
  lastButtonState = buttonState;
}