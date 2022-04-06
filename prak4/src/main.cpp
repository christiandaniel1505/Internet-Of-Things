#include <Arduino.h>
#define GREEN_LED D6 //led warna hijau
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D0, OUTPUT);
  pinMode(D6, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // 3 dits (3 titik atau huruf S)
  for (int x = 0; x < 3; x++)
  {
    digitalWrite(D6, HIGH);
    digitalWrite(D0, LOW);
    digitalWrite(LED_BUILTIN, LOW);// LED nyala
    delay(150); // delay selama 150ms
    digitalWrite(D6, LOW);
        digitalWrite(D0, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);// LED mati
    delay(100); // delay selama 100ms
  }
  delay(100);
  // 3 dahs (3 garis atau huruf O)
  for (int x = 0; x < 3; x++)
  {
    digitalWrite(D6, HIGH);
    digitalWrite(D0, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    delay(400); // delay selama 400ms
    digitalWrite(D6, LOW); // LED mati
    digitalWrite(D0, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100); // delay selama 100ms
  }
  // 100ms delay to cause slight gap between letters
  delay(100);
  // 3 dits again (3 titik atau huruf S)
  for (int x = 0; x < 3; x++)
  {
    digitalWrite(D6, HIGH);
    digitalWrite(D0, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    delay(150); // delay selama 150ms
    digitalWrite(D6, LOW); // LED mati
    digitalWrite(D0, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100); // delay selama 100ms
  }
  // wait 5 seconds before repeating the SOS signal
  delay(5000);
}