#include "test_ping.h"
#include "StatusTransmitter.h"

static const unsigned long PING_INTERVAL_MS = 3000;

void initPingSender() {
    initStatusTransmitter();
    randomSeed(analogRead(A0));
}

void sendTestPings() {
    static unsigned long lastPing = 0;
    unsigned long now = millis();
    if (now - lastPing >= PING_INTERVAL_MS) {
        lastPing = now;
        sendStatusMessage("PING");
    }
}

void sendRandomTestPings() {
    static unsigned long lastPing = 0;
    const char* messages[] = {"PING", "HELLO", "TEST", "ALIVE"};
    const int numMessages = sizeof(messages) / sizeof(messages[0]);
    unsigned long now = millis();
    if (now - lastPing >= PING_INTERVAL_MS) {
        lastPing = now;
        int idx = random(numMessages);
        sendStatusMessage(messages[idx]);
    }
}

