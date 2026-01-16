/* replace ? and add code in ???*/
#include "pitches.h"
#include "Arduino.h"
#include "NewPing.h"

// define ultrasonic pins
#define TRIG_PIN   5       
#define ECHO_PIN    4     

// define buzzer pin ？
#define BUZZER_PIN  35   

//Define Built-in LED pin
#define LED_PIN 1      

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

//*** Define distance as a variable ***
float distance;  

//jingle bells high_tone

int melody_high[] = {
  
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4,
  NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4,
  NOTE_D4, NOTE_G4
};

int noteDurations_high[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8, 2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};
  //jingle bells LOW
int melody_low[] = {

  NOTE_E3, NOTE_E3, NOTE_E3,
  NOTE_E3, NOTE_E3, NOTE_E3,
  NOTE_E3, NOTE_G3, NOTE_C3, NOTE_D3, NOTE_E3,
  NOTE_F3, NOTE_F3, NOTE_F3, NOTE_F3,
  NOTE_F3, NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3,
  NOTE_E3, NOTE_D3, NOTE_D3, NOTE_E3,
  NOTE_D3, NOTE_G3
};

int noteDurations_low[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8, 2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};


void setup() {

  // initialize serial monitor
  Serial.begin(9600);        // ***Start the serial communication set baud rate.***
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);       // Set pin connected to LED as an output pin
 // set pins mode
  
 
  
}

void loop() { 
  // Get the distance from the Ultrasonic Sensor
    float distance = sonar.ping_cm();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(500);

      if (distance > 10 || distance<=0) {
        // turn on built in LED
        digitalWrite(LED_PIN, HIGH);
      }
      else if (distance <= 10 && distance >= 5) {
        // turn off built in LED
        digitalWrite(LED_PIN, LOW);

        // play high tone Jingle-Bells Iterate over the notes of the melody_high:
        Serial.println("Playing Jingle Bells...");
        // Iterate over the notes of the melody:
        for (int thisNote = 0; thisNote < 14 ; thisNote++) {
        // To calculate the note duration, take one second divided by the note type.
        int noteDuration = 1000 / noteDurations_high[thisNote];
        tone(BUZZER_PIN, melody_high[thisNote], noteDuration);
        // To distinguish the notes, set a minimum time between them.
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // Stop the tone playing:
        noTone(BUZZER_PIN);}

      } 
      else if (distance <5 ) {
        // turn off built in LED
        digitalWrite(LED_PIN, LOW);

        // play low tone Jingle-Bells Iterate over the notes of the melody_low
        Serial.println("Playing Jingle Bells...");
        // Iterate over the notes of the melody:
        for (int thisNote = 0; thisNote < 14 ; thisNote++) {
        // To calculate the note duration, take one second divided by the note type.
        int noteDuration = 1000 / noteDurations_low[thisNote];
        tone(BUZZER_PIN, melody_low[thisNote], noteDuration);
        // To distinguish the notes, set a minimum time between them.
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // Stop the tone playing:
        noTone(BUZZER_PIN);
   
} 
  delay(100); 
      }
}