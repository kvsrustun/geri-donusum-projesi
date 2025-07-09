import cv2
import numpy as np
import serial
import tensorflow as tf

# Modeli yükle
interpreter = tf.lite.Interpreter(model_path="model_unquant.tflite")
interpreter.allocate_tensors()
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()

# Etiketleri oku
with open("labels.txt", "r") as f:
    labels = [line.strip().split(" ", 1)[1].lower() for line in f.readlines()]

# Seri portu başlat
ser = serial.Serial('COM7', 9600, timeout=1)

# Kamerayı başlat
cap = cv2.VideoCapture(0)

while True:
    # Deneyap Kart'tan gelen mesajı oku
    if ser.in_waiting > 0:
        mesaj = ser.readline().decode().strip()
        if mesaj == "HAZIR":
            print("Cisim yakında, tahmin yapılıyor...")

            ret, frame = cap.read()
            if not ret:
                continue

            img = cv2.resize(frame, (224, 224))
            img = img.astype(np.float32) / 255.0
            img = np.expand_dims(img, axis=0)

            interpreter.set_tensor(input_details[0]['index'], img)
            interpreter.invoke()
            prediction = interpreter.get_tensor(output_details[0]['index'])

            class_index = np.argmax(prediction[0])
            predicted_label = labels[class_index]

            print("Tahmin:", predicted_label)

            # Komut gönder
            if "paper" in predicted_label:
                ser.write(b'KAGIT\n')
            elif "metal" in predicted_label:
                ser.write(b'METAL\n')
            elif "plastic" in predicted_label:
                ser.write(b'PLASTIK\n')
            elif "glass" in predicted_label:
                ser.write(b'CAM\n')

    # Kamerayı göster (her zaman açık)
    ret, frame = cap.read()
    if ret:
        cv2.imshow("Kamera", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Temizlik
cap.release()
cv2.destroyAllWindows()
ser.close()
