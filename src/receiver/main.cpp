#include <esp_now.h>
#include <WiFi.h>

#define LED_PIN 8

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int len) {
    char message[251];
    int msgLen = min(len, 250);
    memcpy(message, data, msgLen);
    message[msgLen] = '\0';
    Serial.println(message);
    digitalWrite(LED_PIN, LOW);
    delay(100);
    digitalWrite(LED_PIN, HIGH);
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW init failed");
        return;
    }
    esp_now_register_recv_cb(OnDataRecv);
    Serial.println("Status receiver ready");
}

void loop() {
    delay(100);
}

