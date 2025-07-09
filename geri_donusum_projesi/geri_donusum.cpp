#include <HCSR04.h>  // UltraSonicDistanceSensor sınıfı bu kütüphanede



// LED ve buzzer pinleri
const int buzzerPin = D4;      
const int ledPlastic = D5;     
const int ledKagit = D6;       
const int ledMetal = D7;       
const int ledCam = D8;         

     
const int buzzerChannel = 0;  

// Ultrasonik sensör nesnesi (9 = trig, 10 = echo pinleri)
UltraSonicDistanceSensor distanceSensor(D9, D10); 

void setup() {
  Serial.begin(9600);

  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPlastic, OUTPUT);
  pinMode(ledKagit, OUTPUT);
  pinMode(ledMetal, OUTPUT);
  pinMode(ledCam, OUTPUT);

  ledcSetup(buzzerChannel, 2000, 8); 
  ledcAttachPin(buzzerPin, buzzerChannel);
}

void loop() {
  // Mesafeyi ultra sonic sensör nesnesi ile oku (cm cinsinden)
  float mesafe = distanceSensor.measureDistanceCm();
   Serial.println(mesafe);
  // Mesafe 15 cm'den azsa
  if (mesafe > 0 && mesafe < 15) {
    Serial.println("HAZIR");
    

    delay(1500);
  }

  // Python’dan gelen komutu işle
  if (Serial.available()) {
    String komut = Serial.readStringUntil('\n');
    komut.trim();

    Serial.print("Gelen komut: ");
    Serial.println(komut);

    if (komut == "PLASTIK") {
      digitalWrite(ledPlastic, HIGH);
      ledcWrite(buzzerChannel, 120);
      delay(300);
      ledcWrite(buzzerChannel, 0);
      delay(700);
      digitalWrite(ledPlastic, LOW);

    }
    else if (komut == "KAGIT") {
      digitalWrite(ledKagit, HIGH);
      ledcWrite(buzzerChannel, 150);
      delay(300);
      ledcWrite(buzzerChannel, 0);
      delay(700);
      digitalWrite(ledKagit, LOW);

    }
    else if (komut == "METAL") {
      digitalWrite(ledMetal, HIGH);
      ledcWrite(buzzerChannel, 180);
      delay(300);
      ledcWrite(buzzerChannel, 0);
      delay(700);
      digitalWrite(ledMetal, LOW);
      
    }
    else if (komut == "CAM") {
      digitalWrite(ledCam, HIGH);
      ledcWrite(buzzerChannel, 210);
      delay(300);
      ledcWrite(buzzerChannel, 0);
      delay(700);
      digitalWrite(ledCam, LOW);

    }
  }

  delay(100);
}
