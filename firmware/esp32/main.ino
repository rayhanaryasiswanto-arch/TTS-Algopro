
#include <OneWire.h>
#include <DallasTemperature.h>

// Pin DATA DS18B20
#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const unsigned long INTERVAL = 5000;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(115200);
  sensors.begin();

  delay(1000);

  if (sensors.getDeviceCount() == 0) {
    Serial.println("ERROR: DS18B20 tidak terdeteksi");
  } else {
    Serial.println("SYSTEM_READY");
    Serial.println("elapsed_seconds,temperature_c");
  }
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= INTERVAL) {
    previousMillis = currentMillis;

    sensors.requestTemperatures();
    float suhu = sensors.getTempCByIndex(0);

    if (suhu == DEVICE_DISCONNECTED_C ||
        suhu < -55.0 || suhu > 125.0) {
      Serial.println("ERROR: Sensor tidak valid");
    } else {
      float waktu = currentMillis / 1000.0;

      Serial.print(waktu, 1);
      Serial.print(",");
      Serial.println(suhu, 2);
    }
  }
}
