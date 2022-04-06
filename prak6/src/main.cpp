// TUGAS
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define pinLDR A0
#define DHTTYPE DHT11
#define DHTPIN D1
#define LED_BLUE D4
#define LED_RED D2

DHT dht(DHTPIN, DHTTYPE);

unsigned long DHT_millis = 0, previousMillis = 0;
char buff[100];
float t = 0;
int h = 0, BLUE = LOW;

void setup() {
  Serial.begin(115200);
  Serial.println("Tugas Simulasi Pendeteksi Suhu dan Kelembapan dengan LED");
  dht.begin();
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}

void loop() {
  // Melakukan pembacaan sensor DHT11 menggunakan millis
  unsigned long DHT_current = millis();
  if (DHT_current - DHT_millis >= 2000) {
    DHT_millis = DHT_current;
    h = dht.readHumidity();
    t = dht.readTemperature();
    Serial.println("========SCANNING DHT11!========");
  }
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  int ldr = analogRead(pinLDR);
  Serial.print("LDR : ");
  Serial.print(ldr);
  Serial.print(" || ");
  Serial.print("Suhu : ");
  dtostrf(t, 2, 2, buff);
  Serial.print(buff);
  Serial.print("°C || Kelembapan : ");
  Serial.print(h);
  Serial.print("% || ");
  if (ldr > 512 && t < 27) {
    Serial.println("Cahaya Redup dan suhu dingin");
    digitalWrite(LED_RED, LOW);
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 300) {
      previousMillis = currentMillis;
      if (BLUE == LOW) { BLUE = HIGH; } else { BLUE = LOW; }
      digitalWrite(LED_BLUE, BLUE);
    }
  } else if (ldr < 300 && t > 27) {
    Serial.println("Cahaya Terang dan suhu panas");
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, LOW);
  } else {
    Serial.println("");
  }
  delay(1000);
}

// prak 2
// #define triggerPin D6
// #define echoPin D5

// void setup() {
//    Serial.begin (115200);
//    pinMode(triggerPin, OUTPUT);
//    pinMode(echoPin, INPUT);
//    pinMode(BUILTIN_LED, OUTPUT);
// }

// void loop() {
//    long duration, jarak;
//    digitalWrite(triggerPin, LOW);
//    delayMicroseconds(2);
//    digitalWrite(triggerPin, HIGH);
//    delayMicroseconds(10);
//    digitalWrite(triggerPin, LOW);
//    duration = pulseIn(echoPin, HIGH);
//    jarak = duration * 0.034 / 2;
//    Serial.print(jarak);
//    Serial.println(" cm");
//    delay(2000);
// }