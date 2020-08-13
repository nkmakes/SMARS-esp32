#include <Arduino.h>
/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    Adapted by Manos Zeakis for ESP32 and TB6612FNG
*/

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <TB6612_ESP32.h>

#define AIN1 13
#define BIN1 12
#define AIN2 14
#define BIN2 27
#define PWMA 26
#define PWMB 25
#define STBY 17

const int offsetA = 1;
const int offsetB = -1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY,5000 ,8,1 );
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY,5000 ,8,2 );

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");

        for (int i = 0; i < rxValue.length(); i++) {
          Serial.print(rxValue[i]);
        }

        Serial.println();

        if (rxValue.find("A") != -1) {
            Serial.println("front");
            forward(motor1, motor2, 50);
            delay(1000);
            brake(motor1, motor2);
        }
        else if (rxValue.find("B") != -1) {
            Serial.println("back");
            back(motor1, motor2, -50);
            delay(1000);
            brake(motor1, motor2);
      }
        else if (rxValue.find("C") != -1) {
            Serial.println("right");
            right(motor1, motor2, 150);
            delay(600);
            brake(motor1, motor2);
            }
        else if (rxValue.find("D") != -1) {
            Serial.println("left");
            left(motor1, motor2, 150);
            delay(600);
            brake(motor1, motor2);
      }
        else if (rxValue.find("E") != -1) {
            Serial.println("left");
            right(motor1, motor2, 150);
            delay(2400);
            brake(motor1, motor2);
      }        Serial.println();
        Serial.println("*********");
      }
    }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("Raidho"); // Give it a name

  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_TX,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );
                      
  pCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_RX,
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();

  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
}

void loop() {
}