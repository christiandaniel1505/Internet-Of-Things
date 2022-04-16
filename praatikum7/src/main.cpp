//Prak 1
// #include <Arduino.h>
// #include <Wire.h>
// void setup()
// {
//   Wire.begin();
//   Serial.begin(115200);
//   Serial.println("\nI2C Scanner");
// }

// void loop()
// {
//   byte error, address;
//   int nDevices;
//   Serial.println("Scanning...");
//   nDevices = 0;
//   for (address = 1; address < 127; address++)
//   {
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();
//     if (error == 0)
//     {
//       Serial.print("I2C ditemukan pada 0x");
//       if (address < 16)
//       {
//         Serial.print("0");
//       }
//       Serial.println(address, HEX);
//       nDevices++;
//     }
//     else if (error == 4)
//     {
//       Serial.print("Unknow error at address 0x");
//       if (address < 16)
//       {
//         Serial.print("0");
//       }
//       Serial.println(address, HEX);
//     }
//   }
//   if (nDevices == 0)
//   {
//     Serial.println("No I2C devices found\n");
//   }
//   else
//   {
//     Serial.println("done\n");
//   }
//   delay(3000);
// }

// prak2
// #include <Arduino.h>
// #include <LiquidCrystal_I2C.h>

// LiquidCrystal_I2C lcd(0x27, 16, 2);

// void setup()
// {
//   lcd.init(); // initialize the lcd
//   lcd.backlight();
//   lcd.clear();
//   lcd.home();
// }

// void scrollText(int row, String message, int delayTime, int lcdColumns)
// {
//   for (int i = 0; i < lcdColumns; i++)
//   {
//     message = " " + message;
//   }
//   message = message + " ";
//   for (int pos = 0; pos < message.length(); pos++)
//   {
//     lcd.setCursor(0, row);
//     lcd.print(message.substring(pos, pos + lcdColumns));
//     delay(delayTime);
//   }
// }

// void loop()
// {
//   lcd.home();
//   lcd.print("Daniel Prayogo");
//   scrollText(1, "Subuh 04.14 - Terbit 05.32 - Dhuhur 11.30 - Ashar 14.50 - Magrib 17.20 - Isya' 18.30", 350, 26);
// }


TUGAS 
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <time.h>

#define LED_RED   D5
#define LED_GREEN D4
#define LED_BLUE  D6

DHT dht(D3, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char *ssid     = "SSID";
const char *password = "password";
unsigned long DHT_millis = 0, LED_millis = 0;
char buff[100];
float t = 0, tf = 0;
int led = HIGH;

void setTime(int timezone)
{
  configTime(timezone * 3600, 0, "id.pool.ntp.org");
  time_t now = time(nullptr);
  while (now < 1000)
  {
    delay(500);
    now = time(nullptr);
  }
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
}

void setup() {
  // put your setup code here, to run once:
  dht.begin();
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  WiFi.begin(ssid, password);
  setTime(7);
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long DHT_current = millis();
  if (DHT_current - DHT_millis >= 1000) {
    DHT_millis = DHT_current;
    t = dht.readTemperature();
    tf = (t*1.8)+32;
  }
  if (isnan(t)){
    lcd.home();
    lcd.print("DHT Failed!");
    return;
  }
  if (t < 30) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, HIGH);
    unsigned long currentMillis = millis();
    if (currentMillis - LED_millis >= 300) {
      LED_millis = currentMillis;
      if (led == LOW) { led = HIGH; } else { led = LOW; }
      digitalWrite(LED_GREEN, led);
    }
  } else if (t > 30 && t < 32) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    unsigned long currentMillis = millis();
    if (currentMillis - LED_millis >= 300) {
      LED_millis = currentMillis;
      if (led == LOW) { led = HIGH; } else { led = LOW; }
      digitalWrite(LED_BLUE, led);
    }
  } else {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, HIGH);
    unsigned long currentMillis = millis();
    if (currentMillis - LED_millis >= 300) {
      LED_millis = currentMillis;
      if (led == LOW) { led = HIGH; } else { led = LOW; }
      digitalWrite(LED_RED, led);
    }
  }
  lcd.home();
  sprintf(buff, "%.2f%cC  %.2f%cF", t, (char)223, tf, (char)223);
  lcd.print(buff);
  lcd.setCursor(0,1);
  time_t now = time(nullptr);
  struct tm* p_timeinfo = localtime(&now);
  sprintf(buff, "%d-%d-%d %02d:%02d:%02d", p_timeinfo->tm_mday, p_timeinfo->tm_mon+1, p_timeinfo->tm_year-100, p_timeinfo->tm_hour, p_timeinfo->tm_min, p_timeinfo->tm_sec);
  lcd.print(buff);
}