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
    auto gestrue = sens.getGesture();
    switch (gestrue)
    {
    case DFRobot_PAJ7620U2::eGestureRight:
        con.controlVolume(4);
        break;
    case DFRobot_PAJ7620U2::eGestureLeft:
        con.controlVolume(-4);
        break;
    case DFRobot_PAJ7620U2::eGestureWaveSlowlyLeftRight:
        con.avrcOperation(AudioController::AvrcCommand::NEXT);
        break;
    case DFRobot_PAJ7620U2::eGestureWaveSlowlyUpDown:
        con.avrcOperation(AudioController::AvrcCommand::PREVIOUS);
        break;
    case DFRobot_PAJ7620U2::eGestureUp:
        con.avrcOperation(AudioController::AvrcCommand::PAUSE);
        break;
    case DFRobot_PAJ7620U2::eGestureDown:
        con.avrcOperation(AudioController::AvrcCommand::PLAY);
        break;
    default:
        break;
    }
}