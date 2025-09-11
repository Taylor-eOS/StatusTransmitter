#include "status_transmitter.h"
#include "test_ping.h"

bool testPingsEnabled = false;
bool randomTestPingsEnabled = false;

void setup() {
    Serial.begin(115200);
    initStatusTransmitter();
    initPingSender();
}

void loop() {
    if (testPingsEnabled) {
        sendTestPings();
    }
    else if (randomTestPingsEnabled) {
        sendRandomTestPings();
    }
    delay(1000);
}
