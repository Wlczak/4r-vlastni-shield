#include <OneWire.h>
#include <DallasTemperature.h>

// Pin where the DS18B20 sensor is connected (D4, which is GPIO 2)
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass the oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  pinMode(D3, OUTPUT);
  // Start up the DS18B20 sensor library
  sensors.begin();
}

void loop() {
  // Request temperature from all sensors on the bus
  sensors.requestTemperatures();
  
  // Fetch the temperature in Celsius from the first sensor (index 0)
  float temperatureC = sensors.getTempCByIndex(0);
  
  // Check if the reading is valid (not -127C)
  if (temperatureC != DEVICE_DISCONNECTED_C) {
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println(" °C");
  } else {
    Serial.println("Error: Could not read temperature data.");
  }
  
  // Wait 1 second before requesting the temperature again
  delay(1000);
}
