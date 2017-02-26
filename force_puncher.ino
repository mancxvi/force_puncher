/* William Oberndorfer
 * Zumo Force Detector
 *
 * A silly robot that punches magnetic fields
 */

#define PUNCH_PIN 4

#include <Wire.h>
#include <LSM303.h>
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>

LSM303 compass;
ZumoBuzzer buzzer;
bool note_playing;

int16_t previous;
int16_t current;

void setup()
{
    Serial.begin(9600);
    pinMode(PUNCH_PIN, OUTPUT);
    digitalWrite(PUNCH_PIN, LOW);
    Wire.begin();
    compass.init();
    compass.enableDefault();
    note_playing = false;
    compass.readMag();
    previous = compass.m.x;
    current = previous;
}

void loop()
{
    compass.readMag();
    current = compass.m.x;
    Serial.println(current);
    if (current - previous > 40 && !note_playing) {
        buzzer.playNote(NOTE_E(7), 200, 100);
        digitalWrite(PUNCH_PIN, HIGH);
        delay(100);
        note_playing = true;
    }
    if (note_playing) {
        digitalWrite(PUNCH_PIN, LOW);
        delay(100);
        note_playing = false;
    }
    previous = current;
    delay(100);
}
