#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
//wifi credentials
#define WIFI_SSID "MSB"
#define WIFI_PASSWORD "onetwothreefour"
 //Firebase credentials
#define FIREBASE_HOST "https://led-on-and-off-e7761-default-rtdb.asia-southeast1.firebasedatabase.app/"   // Without "https://"
#define FIREBASE_AUTH "AIzaSyC9ZL8fbri_3OlmnFKRBklpFNlJBIsqSBM"  
// DHT setup
#define LED_PIN 2 
FirebaseData firebaseData;
FirebaseConfig config;
FirebaseAuth auth;
void setup()
{
   Serial.begin(115200);
   pinMode(LED_PIN, OUTPUT);
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\Connected to WiFi");
  //set firebase config
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  // No authentication needed with legacy token
  Firebase.begin(&config,&auth);
  Firebase.reconnectWiFi(true);

}
void loop()
{
 if (Firebase.getString(firebaseData, "/LEDDD")) {
    String ledState = firebaseData.stringData();
    Serial.println("LEDDD: " + ledState);

    if (ledState == "ON") {
      digitalWrite(LED_PIN, HIGH);
    } else if (ledState == "OFF") {
      digitalWrite(LED_PIN, LOW);
    }
  } else {
    Serial.println("Error: " + firebaseData.errorReason());
  }

  delay(1000);  // check every second
}