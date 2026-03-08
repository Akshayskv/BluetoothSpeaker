#include <Arduino.h>
#include "includes/AudioController.h"

AudioController con("obama", 22, 25, 26, 12);

void setup() {
    con.init();
}

void loop() {

}