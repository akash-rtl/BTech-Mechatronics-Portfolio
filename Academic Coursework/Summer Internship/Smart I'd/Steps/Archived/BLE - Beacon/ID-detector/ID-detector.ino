#include <BLEDevice.h>
#include <BLEScan.h>

#define SCAN_TIME_SECONDS 3 // Adjust scan duration as needed

BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
        // Check if the device name is "BT05"
        if (advertisedDevice.getName() == "BT05") {
            
            Serial.print("Address: ");
            Serial.print(advertisedDevice.getAddress().toString().c_str());
            Serial.print(" --- RSSI: ");
            Serial.println(advertisedDevice.getRSSI());
            
        }
    }
};

void setup() {
    Serial.begin(115200);
    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true);
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99);
}

void loop() {
    Serial.println();
    Serial.println("Found BLE Devices: ");

    // Start BLE scanning
    pBLEScan->start(SCAN_TIME_SECONDS, false);

    // Delay for the scan duration
    delay(SCAN_TIME_SECONDS * 1000);

    // Stop BLE scanning
    pBLEScan->stop();

    // Delay before starting the next scan
    delay(100);
}
