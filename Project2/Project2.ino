/* replace ? and add code in ???*/
#include <Arduino.h>
#include <DHT.h>
#include "NewPing.h"
#include <ESP32Servo.h>

// define DHT11 sensor pin
#define DHT_PIN   4

#define DHT_TYPE DHT11
DHT dht11(DHT_PIN, DHT_TYPE);

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400


//define pins
#define LED_PIN 1
#define DHT_PIN   4
#define TRIG_PIN 40     
#define ECHO_PIN  39      
#define BUZZER_PIN 35     
#define Servo_PIN 16 

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

Servo servo;

void setup() {
  // Initialize Serial Monitor 
  Serial.begin(9600);    
  // initialize the DHT11 sensor
  dht11.begin();
  //attach servo pin
  servo.attach(Servo_PIN);
  // config the pin mode of each pin
  pinMode(LED_PIN, OUTPUT); 
  pinMode(BUZZER_PIN, OUTPUT); 
  pinMode(TRIG_PIN, OUTPUT); 
  pinMode(ECHO_PIN, INPUT); }
  


void loop() {

  // read humidity
  float humi  = dht11.readHumidity();
  // read temperature in Celsius
  float tempC = dht11.readTemperature();
  // read temperature in Fahrenheit
  float tempF = dht11.readTemperature(true);

  // check whether the reading is successful or not
  if ( isnan(tempC) || isnan(tempF) || isnan(humi)) {
    Serial.println("Failed to read from DHT11 sensor!");
  } else if (tempC <= 30) {
      
        // servo motor stop 
        servo.write(90);
       // Serial Monitor show Safe
        Serial.println("Safe");
       // buzzer no sound
        digitalWrite(BUZZER_PIN, LOW);
  } else if (humi >= 30) {
       // servo motor stop 
        servo.write(90);
       // Serial Monitor show Caution
        Serial.println("Caution!!!");
       // buzzer continuously alarm
        tone(BUZZER_PIN, 500, 1000);
       // report heat source distance from Ultrasonic sensor
        delay(50);
        int distance = sonar.ping_cm();
        Serial.print("Heat source distance: ");
        Serial.print(distance); Serial.println(" cm");
    } 
    else if (humi < 30)  {
      // servo motor run
        servo.write(0);
       // Serial Monitor show Dangerous
        Serial.println("Dangerous!!!!");
       // buzzer beep
        digitalWrite(BUZZER_PIN, HIGH); 
        delay(200); 
        digitalWrite(BUZZER_PIN, LOW);
        delay(200);
  }
  

  // wait a 2 seconds between readings
  delay(2000);
}
