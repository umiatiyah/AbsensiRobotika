#include <ESP8266WiFi.h>
#include <HttpClient.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>
int ledB = 16;
int ledG = 5;
int ledR = 4;
LiquidCrystal_I2C lcd(0x3f, 16, 2);

SoftwareSerial fpsensor(12, 13);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fpsensor);
int fingerprintID ;
int query = 0;

const char* ssid = "ASUS_X00TD"; //Nama WiFi
const char* password = "12345678a"; //password WiFi

void setup() {
  lcd.begin();
  lcd.backlight();
finger.begin(57600);
//  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    lcd.setCursor(0, 0);      
    lcd.print("Connecting..");
    delay(500);
  }
  if (finger.verifyPassword()) {
    lcd.clear();
    lcd.setCursor(0, 0);      
    lcd.print("Tap Finger!");
  }
  else {
    lcd.setCursor(0, 0);      
    lcd.println("Didn't find finger:(");
    while (1) {
      delay(1);
    }
  }

}

void loop() {

  fingerprintID = getFingerprintIDez();
  delay(50);
  if (WiFi.status() == WL_CONNECTED && query == 1) {
    lcd.setCursor(7, 0);      
    lcd.print("Sending..");
    HTTPClient http;
    http.begin("http://absensirobotika.000webhostapp.com//get-id.php?id=" + String(fingerprintID)); //masukan url website anda, get-id.php adalah file php yang akan dieksekusi
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
     lcd.setCursor(1, 1);      
     lcd.print(payload);
     delay(2000);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Tap Finger!");
    }
    http.end();
    query = 0;
  }
}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;


  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) {
      lcd.clear();
      lcd.setCursor(0, 0);      
      lcd.print("not found");
      delay(1000);
      lcd.clear();
      lcd.print("Tap Finger!");
      
    return -1;
  }
  lcd.clear();
  lcd.setCursor(0, 0);      
  lcd.print("ID#");
  lcd.print(finger.fingerID);
  query = 1;
  return finger.fingerID;
}
