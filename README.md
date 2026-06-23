# ESP32 to Firebase Realtime Database

Send data from an **ESP32** to **Firebase Realtime Database (RTDB)** over Wi-Fi using the Arduino IDE. Type a message in the Serial Monitor and watch it appear live in your Firebase console.

---

## 📋 Features

- Connects ESP32 to Wi-Fi automatically
- Authenticates with Firebase using Anonymous Sign-In
- Sends any string typed in Serial Monitor to Firebase RTDB
- Prints success/failure feedback in the Serial Monitor

---

## 🛠️ Hardware Required

| Component | Quantity |
|-----------|----------|
| ESP32 development board | 1 |
| USB cable (data-capable) | 1 |
| PC / Laptop | 1 |

---

## 📦 Libraries Required

Install the following libraries via Arduino IDE → **Library Manager** (`Sketch > Include Library > Manage Libraries`):

| Library | Author |
|---------|--------|
| `Firebase ESP Client` | Mobizt |
| `WiFi` | Arduino (built-in for ESP32) |

> **Note:** The `Firebase ESP Client` library includes the required `addons/TokenHelper.h` and `addons/RTDBHelper.h` headers automatically.

---

## ☁️ Firebase Setup

1. Go to [Firebase Console](https://console.firebase.google.com/) and create a new project.
2. Navigate to **Build → Realtime Database** and click **Create Database**.
   - Choose your region and start in **Test Mode** (for development).
3. Go to **Project Settings → General** and copy your **Web API Key**.
4. Copy your **Database URL** (looks like `https://your-project-default-rtdb.firebaseio.com/`).
5. Enable **Anonymous Sign-In**:
   - Go to **Build → Authentication → Sign-in method**
   - Enable **Anonymous**.

---

## ⚙️ Configuration

Open the sketch and update the following defines at the top:

```cpp
// Wi-Fi credentials
#define WIFI_SSID     "your_ssid"
#define WIFI_PASSWORD "your_password"

// Firebase credentials
#define API_KEY       "your_api_key"          // From Project Settings → General
#define DATABASE_URL  "your_database_url"     // From Realtime Database dashboard
```

---

## 🚀 How to Use

1. Open the project in **Arduino IDE**.
2. Select your board: **Tools → Board → ESP32 Dev Module** (or your specific model).
3. Select the correct **COM port** under **Tools → Port**.
4. Click **Upload**.
5. Open **Serial Monitor** (`Tools → Serial Monitor`) and set baud rate to **115200**.
6. Wait for the `--- Setup Complete ---` message.
7. Type any message in the Serial Monitor input box and press **Enter**.
8. Check your Firebase Realtime Database — the message will appear at `/serialData/message`.

---

## 📡 Serial Monitor Output (Example)

```
Connecting to Wi-Fi....
Connected with IP: 192.168.1.105

Firebase SignUp Successok
--- Setup Complete ---
Type something in the Serial Monitor and press Enter:

Sending to Firebase: Hello World
Data sent successfully!
Path: /serialData/message
Type: string
-------------------------------------
```

---

## 🗂️ Firebase Database Structure

```
your-project/
└── serialData/
    └── message: "Hello World"
```

Each new message **overwrites** the previous value at `/serialData/message`.

---

## 🔧 Troubleshooting

| Problem | Solution |
|---------|----------|
| `Connecting to Wi-Fi` never resolves | Double-check `WIFI_SSID` and `WIFI_PASSWORD` |
| `Firebase SignUp` fails | Ensure Anonymous Auth is enabled in Firebase Console |
| `Failed to send data` | Verify `API_KEY` and `DATABASE_URL` are correct |
| No data in Firebase | Check database rules — set to `true` for read/write in test mode |
| Board not detected | Install [ESP32 board support](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html) in Arduino IDE |

### Firebase Database Rules (Test Mode)

```json
{
  "rules": {
    ".read": true,
    ".write": true
  }
}
```

> ⚠️ These rules are for **development only**. Secure them before deploying to production.

---

## 📁 Project Structure

```
esp32-firebase/
├── esp32_firebase.ino   # Main Arduino sketch
└── README.md            # This file
```

---

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).

---

## 🙏 Acknowledgements

- [Firebase ESP Client by Mobizt](https://github.com/mobizt/Firebase-ESP-Client)
- [Espressif ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)
