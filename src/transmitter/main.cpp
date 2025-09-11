#include "status_transmitter.h"
#include "test_ping.h"

bool testPingsEnabled = false;
bool randomTestPingsEnabled = true;

void setup() {
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
