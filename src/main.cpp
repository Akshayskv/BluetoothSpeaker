#include <Arduino.h>
#include "DFRobot_PAJ7620U2.h"
#include "includes/AudioController.h"

DFRobot_PAJ7620U2 sens;

AudioController con("espSpeaker", 22, 25, 26, 12);

void setup() {
    Serial.begin(115200);
    con.init();
    Wire.begin(18, 19);
    while(sens.begin() != 0) {
        Serial.println("Error initializing sensor!");
    }

    sens.setGestureHighRate(false);
}

void loop() {
    auto ges = sens.getGesture();
    if(ges != sens.eGestureNone) {
        String desc = sens.gestureDescription(ges);
        Serial.print("gesture: "); Serial.println(desc);
    }
}