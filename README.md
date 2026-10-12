# ♻️ Makine Öğrenmesi & Görüntü İşleme ile Akıllı Geri Dönüşüm Ayrıştırma Sistemi

<p align="center">
  <a href="#donanim-bilesenleri"><img src="https://img.shields.io/badge/Donan%C4%B1m-Deneyap%20Kart%20Mini%20v2-24292e?style=flat-square&logo=espressif" alt="Deneyap Kart" /></a>
  <a href="#yazilim-mimarisi"><img src="https://img.shields.io/badge/Python-3.9%2B-24292e?style=flat-square&logo=python" alt="Python" /></a>
  <a href="#yapay-zeka-modeli"><img src="https://img.shields.io/badge/Yapay%20Zeka-TensorFlow%20Lite-24292e?style=flat-square&logo=tensorflow" alt="TensorFlow Lite" /></a>
  <a href="#yazilim-mimarisi"><img src="https://img.shields.io/badge/G%C3%B6r%C3%BCnt%C3%BC%20%C4%B0%C5%9Fleme-OpenCV-24292e?style=flat-square&logo=opencv" alt="OpenCV" /></a>
  <a href="#donanim-bilesenleri"><img src="https://img.shields.io/badge/Sens%C3%B6r-HC--SR04%20Ultrasonik-24292e?style=flat-square" alt="HC-SR04" /></a>
  <a href="#donanim-bilesenleri"><img src="https://img.shields.io/badge/Haberle%C5%9Fme-UART%20Seri%20Port%20(9600%20baud)-24292e?style=flat-square" alt="UART" /></a>
  <a href="#lisans"><img src="https://img.shields.io/badge/Lisans-MIT-24292e?style=flat-square" alt="Lisans" /></a>
</p>

> **Sıfır Atık & Çevre Teknolojisi:** Google Teachable Machine ile eğitilmiş kenar yapay zeka (Edge AI) görüntü sınıflandırma modelini TensorFlow Lite ile koşturan, HC-SR04 ultrasonik mesafe sensörüyle optik tetikleme yapan ve atıkları **Plastik, Kağıt, Metal, Cam** olmak üzere 4 ana kategoride ayrıştırarak Deneyap Kart Mini v2 üzerinden LED ve frekans ayarlı buzzer ile geri bildirim veren otonom geri dönüşüm istasyonu.

---

<a id="icindekiler"></a>
## 📑 İçindekiler

1. [Proje Özeti ve Temel Amacı](#proje-ozeti)
2. [Sistem Çalışma Prensibi ve İş Akışı](#calisma-prensibi)
3. [Donanım Mimarisi ve Pin Bağlantı Şeması](#donanim-bilesenleri)
4. [Yapay Zeka Modeli & Teachable Machine](#yapay-zeka-modeli)
5. [Yazılım Mimarisi (Python & C++)](#yazilim-mimarisi)
6. [Proje Dosya Ağacı](#dosya-agaci)
7. [Kurulum ve Çalıştırma Rehberi](#kurulum-ve-calistirma)
8. [İletişim Protokolü (Seri Port Veri Paketleri)](#protokol)
9. [Gelecek Geliştirme Önerileri](#gelistirme-onerileri)
10. [Geliştirici](#gelistirici)
11. [Lisans](#lisans)

---

<a id="proje-ozeti"></a>
## 🌟 1. Proje Özeti ve Temel Amacı

Kentsel katı atık yönetiminde geri dönüşümün en büyük engellerinden biri, çöplerin kaynağında doğru ayrıştırılamamasıdır. Karışık toplanan malzemelerin kalitesi düşmekte ve geri kazanım maliyetleri katlanmaktadır.

Bu proje; **Nesnelerin İnterneti (IoT)**, **Görüntü İşleme (OpenCV)** ve **Kenar Yapay Zeka (TensorFlow Lite)** teknolojilerini harmanlayarak, atık kutusunun önüne gelen nesneleri insan müdahalesine gerek kalmadan anında analiz eden ve doğru kutuya yönlendiren **Akıllı Geri Dönüşüm Ayrıştırma İstasyonu** prototipidir.

- 🎯 **Otomatik Algılama:** HC-SR04 ultrasonik sensörü ile atığın hazneye bırakıldığını temassız tespit eder.
- ⚡ **Düşük Gecikmeli Çıkarım (Inference):** 224x224 boyutuna optimize edilmiş `model_unquant.tflite` modeli ile milisaniyeler içinde sınıflandırma yapar.
- 🔊 **Çoklu Geri Bildirim:** Her atık türü için farklı frekanslı tonlarda buzzer uyarısı ve bağımsız ayrılmış LED göstergeleri sunar.

---

<a id="calisma-prensibi"></a>
## 🔄 2. Sistem Çalışma Prensibi ve İş Akışı

Sistem donanım (Deneyap Kart) ile istemci bilgisayar (Python / TFLite) arasında iki yönlü seri port (UART) iletişimi üzerine kurgulanmıştır:

```
┌────────────────────────────────┐                 ┌──────────────────────────────┐
│    DENEYAP KART MINI v2        │                 │    HOST BİLGİSAYAR (PYTHON)   │
│                                │                 │                              │
│  HC-SR04 Mesafe Sensörü        │                 │  Webcam (Görüntü Yakalama)   │
│  mesafe < 15 cm algılandı!     │                 │                              │
│               │                │                 │                              │
│               ▼                │  UART "HAZIR"   │                              │
│  Seri porta "HAZIR" yazar  ───┼─────────────────┼─► Python tetiklenir          │
│                                │  (9600 baud)    │   Kameradan kare alır        │
│                                │                 │   224x224 Normalize eder     │
│                                │                 │   TFLite Çıkarımı yapar      │
│                                │                 │                              │
│                                │  UART "PLASTIK" │                              │
│  Komut Karşılanır:             │  veya "KAGIT"   │                              │
│  D5 (Plastik) / D6 (Kağıt) ◄───┼─────────────────┼── Sınıf komutunu gönderir    │
│  D7 (Metal)   / D8 (Cam)       │  veya "METAL"   │                              │
│  Buzzer frekansı tetiklenir    │  veya "CAM"     │                              │
└────────────────────────────────┘                 └──────────────────────────────┘
```

1. **Tetikleme Aşaması:** Atık kutusunun girişine bir nesne yaklaştırıldığında (mesafe `< 15 cm`), Deneyap Kart bunu algılar ve `HAZIR\n` sinyali basar.
2. **Görüntü Alma & Ön İşleme:** Python arka plan betiği sinyali alır almaz kameradaki en güncel kareyi yakalar, `224x224` boyutuna yeniden ölçekler ve `0.0 - 1.0` aralığına normalize eder.
3. **TFLite Çıkarımı:** Tensör `interpreter` üzerinde çalıştırılarak en yüksek olasılığa sahip sınıf (`np.argmax`) belirlenir.
4. **Aksiyon & Aktüatör Sürüşü:** Algılanan sınıfa ait metin UART üzerinden karta iletilir. Kart ilgili LED'i yakar ve buzzer ile o sınıfa özel frekansta uyarı sesi çalar.

---

<a id="donanim-bilesenleri"></a>
## 🔌 3. Donanım Mimarisi ve Pin Bağlantı Şeması

### Kullanılan Bileşenler Tablosu
| Bileşen | Model / Tip | Görev | Çalışma Gerilimi |
| :--- | :--- | :--- | :---: |
| **Mikrodenetleyici** | Deneyap Kart Mini v2 (ESP32-S2) | Sensör okuma, aktüatör kontrolü & UART köprüsü | 3.3V / 5V |
| **Mesafe Sensörü** | HC-SR04 Ultrasonik | Nesne yaklaşma tespiti (Optik tetikleyici) | 5V |
| **Kamera** | Standart USB Web Kamera / Endüstriyel Kamera | Nesne görüntüsü yakalama | 5V (USB) |
| **Görsel Geri Bildirim** | 4x 5mm LED (Mavi, Beyaz, Sarı, Yeşil) | Atık kategorisi durum göstergeleri | 3.3V (220Ω dirençli) |
| **İşitsel Geri Bildirim**| Pasif Buzzer (PWM / LEDC) | Sınıfa göre değişken frekansta ses uyarısı | 3.3V |
| **Host Bilgisayar** | Windows / Linux / macOS | Model çıkarımı ve görüntü işleme sunucusu | — |

### Deneyap Kart Mini v2 Pin Bağlantı Haritası

| Sensör / Aktüatör | Deneyap Kart Pini | Modu / Fonksiyonu | Açıklama |
| :--- | :---: | :---: | :--- |
| **HC-SR04 Trig** | `D9` | OUTPUT | 10µs ultrasonik tetikleme sinyali |
| **HC-SR04 Echo** | `D10` | INPUT | Yansıyan ses dalgası dönüş süresi |
| **Buzzer** | `D4` | OUTPUT (LEDC PWM) | Kanal 0, 2000Hz başlangıç, 8-bit çözünürlük |
| **Plastik LED** | `D5` | OUTPUT | Plastik atık algılandığında yanar |
| **Kağıt LED** | `D6` | OUTPUT | Kağıt atık algılandığında yanar |
| **Metal LED** | `D7` | OUTPUT | Metal atık algılandığında yanar |
| **Cam LED** | `D8` | OUTPUT | Cam atık algılandığında yanar |
| **VCC & GND** | `5V / 3V3` & `GND`| Güç Hatları | Ortak toprak (Common Ground) |

> ⚠️ **Önemli Not:** HC-SR04 5V ile beslenirken Echo pini 5V çıkış verir. Deneyap Kart Mini v2 GPIO pinlerini korumak için Echo hattında 1kΩ / 2kΩ gerilim bölücü direnç kullanılması tavsiye edilir.

---

<a id="yapay-zeka-modeli"></a>
## 🧠 4. Yapay Zeka Modeli & Teachable Machine

Model, **Google Teachable Machine** platformu üzerinde transfer öğrenme (MobileNet mimarisi) kullanılarak eğitilmiş ve mikrodenetleyici / edge cihazlarla uyumlu **TensorFlow Lite (`model_unquant.tflite`)** formatında dışa aktarılmıştır.

### Sınıflandırma Etiketleri (`labels.txt`) & Ses Geri Bildirimleri
| Etiket ID | Sınıf Adı | Malzeme Türü | Tetiklenen LED | Buzzer PWM Değeri | Frekans / Ton Etkisi |
| :---: | :--- | :--- | :---: | :---: | :--- |
| `0` | `plastic` | Plastik Şişe, Kapak, Poşet | `D5` (Plastik) | `120` duty | Düşük-Orta Ton (Bip) |
| `1` | `paper` | Gazete, Karton, Defter | `D6` (Kağıt) | `150` duty | Orta Ton (Bip) |
| `2` | `glass` | Cam Şişe, Kavanoz, Bardak | `D8` (Cam) | `210` duty | Tiz Ton (Bip) |
| `3` | `metal` | İçecek Kutusu, Konserve, Folyo | `D7` (Metal) | `180` duty | Yüksek Ton (Bip) |

### Model Giriş & Çıkış Tensör Özellikleri
- **Girdi Şekli (Input Shape):** `[1, 224, 224, 3]` (RGB renkli resim)
- **Girdi Veri Tipi:** `float32` (Değerler `0.0` - `1.0` aralığında)
- **Çıktı Şekli (Output Shape):** `[1, 4]` (4 sınıf için Softmax olasılık dağılımı)
- **Model Boyutu:** ~2.09 MB (Düşük kaynak tüketimi ve gerçek zamanlı FPS)

---

<a id="yazilim-mimarisi"></a>
## 💻 5. Yazılım Mimarisi (Python & C++)

### 🐍 Python İstemci Kod Analizi (`geri_donusum.py`)
Python tarafı, TensorFlow Lite yorumlayıcısını ve OpenCV kamera akışını eş zamanlı yönetir:

```python
# TensorFlow Lite yorumlayıcısı yükleme
interpreter = tf.lite.Interpreter(model_path="model_unquant.tflite")
interpreter.allocate_tensors()

# Deneyap Kart'tan 'HAZIR' geldiğinde tetiklenen çıkarım
if mesaj == "HAZIR":
    ret, frame = cap.read()
    img = cv2.resize(frame, (224, 224))
    img = img.astype(np.float32) / 255.0
    img = np.expand_dims(img, axis=0)
    interpreter.set_tensor(input_details[0]['index'], img)
    interpreter.invoke()
    prediction = interpreter.get_tensor(output_details[0]['index'])
    predicted_label = labels[np.argmax(prediction[0])]
    # Seri porta komut gönderme (Örn: b'PLASTIK\n')
```

### ⚡ Deneyap Kart Gömülü C++ Kodu (`geri_donusum.cpp`)
ESP32 donanım timer tabanlı `ledc` PWM kütüphanesini ve `HCSR04` ultrasonik kütüphanesini kullanır:

```cpp
// Mesafeyi ölç
float mesafe = distanceSensor.measureDistanceCm();
if (mesafe > 0 && mesafe < 15) {
    Serial.println("HAZIR");
    delay(1500); // Nesnenin sabitlenmesi için bekle
}

// Python'dan gelen sınıf komutunu karşıla
if (Serial.available()) {
    String komut = Serial.readStringUntil('\n');
    komut.trim();
    if (komut == "PLASTIK") {
        digitalWrite(ledPlastic, HIGH);
        ledcWrite(buzzerChannel, 120);
        delay(300);
        ledcWrite(buzzerChannel, 0);
        delay(700);
        digitalWrite(ledPlastic, LOW);
    }
    // ... KAGIT, METAL, CAM koşulları
}
```

---

<a id="dosya-agaci"></a>
## 📂 6. Proje Dosya Ağacı

```bash
geri-donusum-projesi/
│
├── geri_donusum_projesi/              # Ana kaynak kod ve model dizini
│   ├── model_unquant.tflite          # Teachable Machine TFLite sınıflandırma modeli (2.09 MB)
│   ├── labels.txt                    # 4 Sınıf etiket listesi (plastic, paper, glass, metal)
│   ├── geri_donusum.py               # Python uç istemci (OpenCV + TFLite + PySerial)
│   └── geri_donusum.cpp              # Deneyap Kart Mini v2 gömülü C++ firmware kodu
│
├── .gitattributes                    # Git öznitelik ayarları
└── README.md                         # Profesyonel teknik dokümantasyon dosyası
```

---

<a id="kurulum-ve-calistirma"></a>
## 🚀 7. Kurulum ve Çalıştırma Rehberi

### Adım 1: Depoyu Klonlayın
```bash
git clone https://github.com/kvsrustun/geri-donusum-projesi.git
cd geri-donusum-projesi/geri_donusum_projesi
```

### Adım 2: Python Ortamını Hazırlayın
Python 3.9 veya daha güncel bir sürüm gereklidir. Sanal ortam (virtual environment) açmanız önerilir:

```bash
# Sanal ortam oluşturma
python -m venv venv

# Sanal ortamı aktif etme (Windows):
venv\Scripts\activate
# Sanal ortamı aktif etme (Linux/Mac):
source venv/bin/activate

# Gerekli kütüphaneleri yükleme
pip install opencv-python tensorflow pyserial numpy
```

> 💡 **İpucu:** Tam boyutlu TensorFlow yerine sadece çıkarım yapmak için `tflite-runtime` da kullanılabilir.

### Adım 3: Deneyap Kart'a Kodu Yükleyin
1. Arduino IDE veya Deneyap Kart IDE'yi açın.
2. **Araçlar > Kart > Deneyap Kart Mini v2** seçin.
3. Kütüphane Yöneticisinden **HCSR04** (Martin Sosic) kütüphanesini yükleyin.
4. `geri_donusum.cpp` dosyasını açıp USB üzerinden karta derleyip yükleyin.
5. Kartın bağlandığı seri portu not edin (Örn: Windows'ta `COM7`, Linux'ta `/dev/ttyUSB0`).

### Adım 4: Python Betiğini Başlatın
`geri_donusum.py` içindeki port adını kartınızın portu ile eşleştirin:
```python
ser = serial.Serial('COM7', 9600, timeout=1)  # Kendi portunuzu yazın
```

Betiği çalıştırın:
```bash
python geri_donusum.py
```

- Kameranız açılacaktır. Nesneyi ultrasonik sensöre 15 cm'den yakın tuttuğunuzda anlık tahmin ekranda belirecek, LED yanacak ve buzzer ötecektir.
- Programdan çıkmak için kamera penceresindeyken `q` tuşuna basabilirsiniz.

---

<a id="protokol"></a>
## 📡 8. İletişim Protokolü (Seri Port Veri Paketleri)

Tüm iletişim standart UART protokolü üzerinden `9600 baud rate`, 8 veri biti, eşlik biti yok (None), 1 durma biti (8-N-1) formatında satır sonu (`\n`) ile yapılır:

| Kaynak | Hedef | Mesaj | Tetikleyici Durum |
| :--- | :--- | :---: | :--- |
| Deneyap Kart | Python | `HAZIR\n` | HC-SR04 mesafesi `0 < mesafe < 15` cm olduğunda |
| Python | Deneyap Kart | `PLASTIK\n` | TFLite modeli en yüksek olasılıkla plastik tahmin ettiğinde |
| Python | Deneyap Kart | `KAGIT\n` | TFLite modeli kağıt tahmin ettiğinde |
| Python | Deneyap Kart | `METAL\n` | TFLite modeli metal tahmin ettiğinde |
| Python | Deneyap Kart | `CAM\n` | TFLite modeli cam tahmin ettiğinde |

---

<a id="gelistirme-onerileri"></a>
## 💡 9. Gelecek Geliştirme Önerileri

- 🤖 **Servo Motorlu Mekanik Ayrıştırma:** Her kategori için bir servo motor kontrol edilerek atığın ilgili çöp kutusu kapağına otomatik yönlendirilmesi.
- 📺 **I2C OLED / LCD Ekran:** Tahmin edilen atık türü ve model güven skorunun (`%98.4 Plastik`) ekranda anlık gösterilmesi.
- ☁️ **Bulut ve Sıfır Atık Veri Takibi:** MQTT / Firebase ile günlük geri dönüştürülen atık miktarlarının belediye veya okul panosuna aktarılması.
- 📷 **Kamera Doğrudan Kart Üzerinde:** Deneyap Kart 1A + OV2640 kamera modülü ile bilgisayara ihtiyaç duymadan doğrudan kart üzerinde (TinyML) çalıştırma.

---

<a id="gelistirici"></a>
## 👤 10. Geliştirici

**Kevser Üstün**  
- Bilgisayar Mühendisliği Öğrencisi — Giresun Üniversitesi  
- GitHub: [@kvsrustun](https://github.com/kvsrustun)  
- Proje Deposu: [geri-donusum-projesi](https://github.com/kvsrustun/geri-donusum-projesi)  

---

<a id="lisans"></a>
## 📜 11. Lisans

Bu proje [MIT Lisansı](LICENSE) kapsamında açık kaynak olarak sunulmuştur. Eğitim, araştırma ve ticari projelerde özgürce kullanılabilir, geliştirilebilir ve uyarlanabilir.
