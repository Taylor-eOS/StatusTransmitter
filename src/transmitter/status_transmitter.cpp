#include "status_transmitter.h"
#include <esp_now.h>
#include <WiFi.h>

#define LED_PIN 8

uint8_t receiverMAC[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Status send: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "OK" : "Failed");
}

void initStatusTransmitter() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW init failed");
        return;
    }
    esp_now_register_send_cb(OnDataSent);
    memcpy(peerInfo.peer_addr, receiverMAC, 6);
    peerInfo.channel = 1;
    peerInfo.encrypt = false;
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
    Serial.println("Status transmitter ready");
}

void sendStatusMessage(String message) {
    uint8_t messageData[250];
    int msgLen = min((int)message.length(), 249);
    memcpy(messageData, message.c_str(), msgLen);
    messageData[msgLen] = '\0';
    digitalWrite(LED_PIN, LOW);
    esp_now_send(receiverMAC, messageData, msgLen + 1);
    delay(50);
    digitalWrite(LED_PIN, HIGH);
}

