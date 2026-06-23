#include <WiFi.h>
#include <Firebase_ESP_Client.h>

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and helper functions.
#include "addons/RTDBHelper.h"

// 1. Define WiFi Credentials
#define WIFI_SSID "Semicon ACT"
#define WIFI_PASSWORD "cracksen1605"

// 2. Define Firebase Credentials
#define API_KEY "AIzaSyDREfmxpQPR7c6H4l3JrW-Fx57IMagRoZg"
#define DATABASE_URL "https://test2-34c2b-default-rtdb.firebaseio.com/"

// Define Firebase Data objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Assign the API key (required)
  config.api_key = API_KEY;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  // Sign up as an anonymous user (easiest for testing)
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase SignUp Successok");
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  // Assign the callback function for the long running token generation task
  config.token_status_callback = tokenStatusCallback; 
  
  // Initialize the Firebase library
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("--- Setup Complete ---");
  Serial.println("Type something in the Serial Monitor and press Enter:");
}

void loop() {
  // Check if Firebase is ready and if there is data in the Serial Monitor
  if (Firebase.ready() && Serial.available() > 0) {
    
    // Read the incoming string until a newline character
    String inputData = Serial.readStringUntil('\n');
    inputData.trim(); // Remove any accidental spaces or newline characters

    if (inputData.length() > 0) {
      Serial.print("Sending to Firebase: ");
      Serial.println(inputData);

      // Send the string to the database path "/serialData/message"
      if (Firebase.RTDB.setString(&fbdo, "/serialData/message", inputData)) {
        Serial.println("Data sent successfully!");
        Serial.println("Path: " + fbdo.dataPath());
        Serial.println("Type: " + fbdo.dataType());
      } else {
        Serial.print("Failed to send data. Reason: ");
        Serial.println(fbdo.errorReason());
      }
      Serial.println("-------------------------------------");
    }
  }
}