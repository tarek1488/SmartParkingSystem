#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

char str;

SoftwareSerial espSerial(4, 0);  // RX = D7 (pin 7), TX = D8 (pin 8)





#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

#include                "addons/RTDBHelper.h"
#include                "addons/TokenHelper.h"

#define   API_KEY       "AIzaSyBciZaTMo3nHLj9ycBXhLAh9zczkZnvPdQ"
#define   DATABASE_URL  "https://smartgarageproject-7f82b-default-rtdb.firebaseio.com/"
#define   ssid          "WE_DAD8B8"
#define   pass          "onlyWAYout"

//#define LED_BUILTIN      D4

FirebaseData            fbdo;
FirebaseAuth            auth;
FirebaseConfig          config;

//String Data1       =     "0";
//String Data2       =     "0";
bool signupok      =     false;
int free_slots =0;
int PrevSlots =0;
void setup() {
  Serial.begin(9600);     // Initialize the Arduino serial port
  espSerial.begin(9600);  // Initialize the ESP8266 serial port
  pinMode(LED_BUILTIN,OUTPUT);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,pass);

  Serial.begin(9600);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to:");
  Serial.print(ssid); 
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP());

  config.api_key = API_KEY;
  config.database_url= DATABASE_URL;
  
  if(Firebase.signUp(&config,&auth,"",""))
  {
    Serial.println("OK");
    signupok=true;
  }
  else
  {
    Serial.println("Error");
  }
config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config,&auth);
  Firebase.reconnectWiFi(true);
  Serial.println(Firebase.RTDB.getString(&fbdo,"/x"));
  // Initialize LCD
  Wire.begin(12,13);
  lcd.init();
  lcd.backlight();
    // Display "Free Slots: " followed by the value on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Garage EL Ra7ma");
  lcd.setCursor(0, 1);
  lcd.print("Free Slots:");
  lcd.print(6);
}

void loop() {
  // Main code to run repeatedly
  if (Firebase.ready() && signupok) {  // Ensure Firebase is ready and signup is OK

    // Get the integer value of 'free_slots' from Firebase
    if (Firebase.RTDB.getInt(&fbdo, "/free_slots")) {  // Correct function: getInt
      free_slots = fbdo.intData();  // Save it directly as integer
      Serial.println(free_slots);   // Print the value
    } else {
      Serial.println(fbdo.errorReason()); // Print error if it fails
    }

    delay(10);  // Small delay
  }

  // Only send if the free_slots changed
  if (free_slots != PrevSlots) {
    PrevSlots = free_slots;
    send();  // Send update
  }

}

void send() {
  if (free_slots > 0) {
    str = 'f';  // Free slots available
  } else {
    str = 't';  // No free slots
  }
    // Display "Free Slots: " followed by the value on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Garage EL Ra7ma");
  lcd.setCursor(0, 1);
  lcd.print("Free Slots:");
  lcd.print(free_slots);

  espSerial.print(str);  // Send 'f' or 't'
  delay(3000);  // Delay before next possible send
}
//_________________________________________________________________