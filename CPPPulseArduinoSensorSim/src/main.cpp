#include <Arduino.h>
#include <ArduinoBLE.h>

byte flag = 0b00111110;
byte bmp;
byte heart[8] = {0b00001110, 60, 0, 0, 0, 0, 0, 0};
bool _BLEClientConnected = false;

const char Id[] = "14701820-620a-3973-7c78-9cfff0876abd";
const char name[] = "FakeHR2";
const char HRServiceId[] = "180D";
const char HeartRateMeasurementId[] = "2A37";
const char ClientCharacteristicId[] = "2902";
const char BodySensorLocationId[] = "2A38";
const char HeartRateControlPointId[] = "2A39";

BLEService HRService(HRServiceId);
BLECharacteristic HRMesurementCharacterictic(HeartRateMeasurementId,BLENotify, 8);
BLECharacteristic ClientCharacteristic(ClientCharacteristicId, BLEWrite | BLERead, 8);
BLECharacteristic HRLocationCharacterictic(BodySensorLocationId, BLERead, 8);
BLECharacteristic HRControlCharacterictic(HeartRateControlPointId, BLEWrite, 8);
BLEDescriptor HRMesurementDescriptor("2901", "HRM");
BLEDescriptor HRMLocationDescriptor("2901", "HRL");
BLEDescriptor HRControlDescriptor("2901", "HRL");
BLEDescriptor ClientDescriptor("2902", "HRL");

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  BLE.begin();

  BLE.setLocalName(name);
  BLE.setDeviceName(name);
  BLE.setAdvertisedService(HRService);
  HRService.addCharacteristic(HRMesurementCharacterictic);
  HRService.addCharacteristic(ClientCharacteristic);
  HRService.addCharacteristic(HRControlCharacterictic);
  HRService.addCharacteristic(HRLocationCharacterictic);

  HRMesurementCharacterictic.addDescriptor(HRMesurementDescriptor);
  HRLocationCharacterictic.addDescriptor(HRMLocationDescriptor);
  HRControlCharacterictic.addDescriptor(HRControlDescriptor);
  ClientCharacteristic.addDescriptor(ClientDescriptor);
      BLE.addService(HRService);

  // start advertising

  BLE.advertise();
}

void loop()
{
  // wait for a BLE central
  BLEDevice central = BLE.central();

  if (central)
  {
    while (central.connected())
    {
      digitalWrite(LED_BUILTIN, HIGH);
      heart[1] = (byte)75;
      HRMesurementCharacterictic.writeValue(heart,8);
      delay(400);
      heart[1]=(byte)65;
      digitalWrite(LED_BUILTIN, LOW);
      HRMesurementCharacterictic.writeValue(heart,8);
      delay(400);
    }

    digitalWrite(LED_BUILTIN, LOW);
  }
}