# ♻️ Akıllı Geri Dönüşüm Ayırma Sistemi

Bu proje, Teachable Machine ile eğitilmiş bir görüntü sınıflandırma modelini kullanarak **kağıt, metal, plastik ve cam** atıkları tanır. Deneyap Kart Mini v2 ile entegre çalışır. HC-SR04 ultrasonik sensörü sayesinde yalnızca bir cisim 15 cm'den yakındaysa tanıma yapılır. Tanınan atığa göre LED yakılır ve buzzer ses verir.

---

## 🧠 Kullanılan Teknolojiler

- ✅ **Python** (OpenCV, TensorFlow Lite)
- ✅ **Arduino C++** (Deneyap Kart IDE)
- ✅ **Teachable Machine** (Google)
- ✅ **HC-SR04 Ultrasonik Sensör**
- ✅ **Buzzer + LED ile Geri Bildirim**

---

## 🔧 Donanım Gereksinimleri

- Deneyap Kart Mini v2
- HC-SR04 Ultrasonik Mesafe Sensörü
- 4 Adet LED (Plastik, Kağıt, Metal, Cam için)
- Buzzer
- USB Kamera
- Bilgisayar (Python çalıştırmak için)

---

## 📂 Proje Dosya Yapısı

geri-donusum-projesi/
├── model_unquant.tflite # Teachable Machine'den indirilen model
├── labels.txt # Sınıf etiketleri
├── geri_donusum.py # Python tarafı (görüntü işleme ve tahmin)
├── Deneyap Kart/
│ └── geri_donusum.cpp # Deneyap Kart'taki kod
├── README.md # Bu dosya


---

## 🧠 Nasıl Çalışır?

1. Ultrasonik sensör cisim algılarsa Deneyap Kart `"HAZIR"` mesajını seri porttan Python'a gönderir.
2. Python tarafı kameradan görüntü alır, modele verir.
3. Tahmine göre `"KAGIT"`, `"METAL"`, `"PLASTIK"` veya `"CAM"` komutu Deneyap Kart'a geri gönderilir.
4. Deneyap Kart, ilgili LED'i yakar ve buzzer çalar.

---

## 🖥️ Python Tarafını Çalıştırmak

1. Gerekli kütüphaneleri yükle:

pip install opencv-python tensorflow

2. geri_donusum.py dosyasını çalıştır:

python geri_donusum.py
Not: model_unquant.tflite ve labels.txt dosyaları aynı klasörde olmalı.

⚙️ Deneyap Kart Tarafı

Deneyap Kart IDE'de geri_donusum.cpp dosyasını aç.
Kart ve port seçimini yaptıktan sonra kartına yükle.
HC-SR04 sensörünün TRIG = D9, ECHO = D10 pinlerine bağlı olduğundan emin ol.

📝 Örnek Etiket Dosyası (labels.txt)
Kodu kopyala
0 paper
1 metal
2 plastic
3 glass

📸 Görsel Tanıma Modeli
Model Google Teachable Machine üzerinden eğitilmiştir. model_unquant.tflite olarak indirilip Python tarafından kullanılır.

💡 Geliştirme Fikirleri
Servo motor ile atıkları fiziksel olarak yönlendirme
LCD ekran ile sınıfı görsel olarak gösterme


👤 Geliştirici
Kevser ÜSTÜN
Bilgisayar Mühendisliği Öğrencisi
Giresun Üniversitesi




