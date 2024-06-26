#include <FastLED.h>  // include FastLED *before* Artnet
#include <ArtnetEtherENC.h>


// Ethernet stuff
const IPAddress ip(192, 168, 0, 201);
uint8_t mac[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB};

ArtnetReceiver artnet;
uint8_t universe = 1;  // 0 - 15

// FastLED
#define NUM_LEDS 1
CRGB leds[NUM_LEDS];
const uint8_t PIN_LED_DATA = 3;

void setup() {
    Serial.begin(115200);
    delay(2000);

    FastLED.addLeds<NEOPIXEL, PIN_LED_DATA>(leds, NUM_LEDS);

    Ethernet.begin(mac, ip);
    artnet.begin();
    // artnet.subscribe_net(0);     // optionally you can change
    // artnet.subscribe_subnet(0);  // optionally you can change

    // if Artnet packet comes to this universe, forward them to fastled directly
    artnet.forward(universe, leds, NUM_LEDS);

    // this can be achieved manually as follows
    // if Artnet packet comes to this universe, this function is called
    // artnet.subscribe(universe, [&](const uint8_t* data, const uint16_t size)
    // {
    //     // set led
    //     // artnet data size per packet is 512 max
    //     // so there is max 170 pixel per packet (per universe)
    //     for (size_t pixel = 0; pixel < NUM_LEDS; ++pixel) {
    //         const size_t idx = pixel * 3;
    //         leds[pixel].r = data[idx + 0];
    //         leds[pixel].g = data[idx + 1];
    //         leds[pixel].b = data[idx + 2];
    //     }
    // });
}

void loop() {
    artnet.parse();  // check if artnet packet has come and execute callback
    FastLED.show();
}
