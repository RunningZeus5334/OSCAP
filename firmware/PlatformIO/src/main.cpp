#include <Arduino.h>
#include <NeoPixelBus.h>

// --- CONFIGURATIE ---
#define MAX_LEDS_PER_BUS 300
#define BAUD_RATE 921600
#define FAILSAFE_TIMEOUT_MS 3000

// Pin-toewijzing per board (3 onafhankelijke bussen)
#if defined(ESP32)
  #define PIN_BUS_0 16
  #define PIN_BUS_1 17
  #define PIN_BUS_2 18
  // ESP32 RMT kanalen voor parallelle aansturing zonder stotteren
  NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt0Ws2812xMethod> strip0(MAX_LEDS_PER_BUS, PIN_BUS_0);
  NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt1Ws2812xMethod> strip1(MAX_LEDS_PER_BUS, PIN_BUS_1);
  NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt2Ws2812xMethod> strip2(MAX_LEDS_PER_BUS, PIN_BUS_2);
#elif defined(ARDUINO_ARCH_RP2040)
  #define PIN_BUS_0 2
  #define PIN_BUS_1 3
  #define PIN_BUS_2 4
  // Pico PIO state machines (NeoPixelBus 2.8+ benaming)
  NeoPixelBus<NeoGrbFeature, Rp2040x4Pio0Ws2812xMethod> strip0(MAX_LEDS_PER_BUS, PIN_BUS_0);
  NeoPixelBus<NeoGrbFeature, Rp2040x4Pio1Ws2812xMethod> strip1(MAX_LEDS_PER_BUS, PIN_BUS_1);
  NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> strip2(MAX_LEDS_PER_BUS, PIN_BUS_2);
#endif

uint8_t buffer[MAX_LEDS_PER_BUS * 3];
unsigned long lastDataTime = 0;
bool isCleared = true;

void clearAllStrips() {
  strip0.ClearTo(RgbColor(0, 0, 0));
  strip1.ClearTo(RgbColor(0, 0, 0));
  strip2.ClearTo(RgbColor(0, 0, 0));
  strip0.Show();
  strip1.Show();
  strip2.Show();
  isCleared = true;
}

void setup() {
  Serial.begin(BAUD_RATE);
  
  strip0.Begin();
  strip1.Begin();
  strip2.Begin();
  
  clearAllStrips();
}

void loop() {
  // Check op Fail-safe timeout (bijv. als PC uitgaat of script stopt)
  if (!isCleared && (millis() - lastDataTime > FAILSAFE_TIMEOUT_MS)) {
    clearAllStrips();
  }

  // Wacht op minimaal de 5 header-bytes: [0xAA, 0x55, BUS_ID, LEN_HIGH, LEN_LOW]
  if (Serial.available() >= 5) {
    if (Serial.read() == 0xAA) {
      if (Serial.read() == 0x55) {
        uint8_t busId = Serial.read();
        uint16_t payloadLen = (Serial.read() << 8) | Serial.read();

        if (payloadLen <= sizeof(buffer)) {
          // Lees de exacte hoeveelheid kleur-bytes uit
          size_t bytesRead = Serial.readBytes(buffer, payloadLen);
          
          if (bytesRead == payloadLen) {
            uint16_t numLeds = payloadLen / 3;
            
            for (uint16_t i = 0; i < numLeds; i++) {
              RgbColor color(buffer[i * 3], buffer[i * 3 + 1], buffer[i * 3 + 2]);
              if (busId == 0) strip0.SetPixelColor(i, color);
              else if (busId == 1) strip1.SetPixelColor(i, color);
              else if (busId == 2) strip2.SetPixelColor(i, color);
            }

            if (busId == 0) strip0.Show();
            else if (busId == 1) strip1.Show();
            else if (busId == 2) strip2.Show();

            lastDataTime = millis();
            isCleared = false;
          }
        }
      }
    }
  }
}