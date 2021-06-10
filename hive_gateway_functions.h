
#include <ArduinoBLE.h>
const char* serviceName = "ffe0";
const char* characteristicName = "ffe1";
#define MAX_NUM_BLE_EVENTS 5
Timezone myTZ;
time_t timenow;

//********************************************************************
// General Functions
//********************************************************************

// Data structure for Timestamps
typedef struct {
  String connectTime;
  String disconnectTime;
  unsigned long duration;
  String time_elapsed;
} timeStamp_t;

//********************************************************************
// WIFI Functions
//********************************************************************

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


//********************************************************************
// Bluetooth Functions
//********************************************************************

// Bluetooth function to monitor the BLE notifications
// Returns: Boolean indicating if eventThreshold Reached
bool monitorSimpleKey(BLEDevice peripheral, timeStamp_t *timeStampList) {

  bool isEventThresholdReached = false;

  // connect to the peripheral
  Serial.println("Connecting ...");
  if (peripheral.connect()) {
    Serial.println("Connected");
  } else {
    Serial.println("Failed to connect!");
    return isEventThresholdReached;
  }

  // discover peripheral attributes
  Serial.println("Discovering service ...");

  if (peripheral.discoverService(serviceName)) {
    Serial.println("Service discovered");
  } else {
    Serial.println("Attribute discovery failed.");
    peripheral.disconnect();
    return isEventThresholdReached;
  }

  // retrieve the simple key characteristic
  BLECharacteristic simpleKeyCharacteristic = peripheral.characteristic(characteristicName);

  // subscribe to the simple key characteristic
  Serial.println("Subscribing to simple key characteristic ...");
  if (!simpleKeyCharacteristic) {
    Serial.println("no simple key characteristic found!");
    peripheral.disconnect();
    return isEventThresholdReached;
  } else if (!simpleKeyCharacteristic.canSubscribe()) {
    Serial.println("simple key characteristic is not subscribable!");
    peripheral.disconnect();
    return isEventThresholdReached;
  } else if (!simpleKeyCharacteristic.subscribe()) {
    Serial.println("subscription failed!");
    peripheral.disconnect();
    return isEventThresholdReached;
  } else {
    Serial.println("BLE Connected: Start connection events");
  }

  int numOfBleNotifyEvents = 0;
  int prevState = 0;
  while (peripheral.connected() && numOfBleNotifyEvents < MAX_NUM_BLE_EVENTS) {
    // while the peripheral is connected

    // check if the value of the simple key characteristic has been updated
    if (simpleKeyCharacteristic.valueUpdated()) {
      // yes, get the value, characteristic is 1 byte so use byte value
      byte currentState = 0;

      simpleKeyCharacteristic.readValue(currentState);

      Serial.println(currentState);

      if (currentState == 0 && prevState == 1) {
        // first bit corresponds to the right button
        Serial.println("Button released");
        timeStampList[numOfBleNotifyEvents].disconnectTime = myTZ.dateTime();
        Serial.print(timeStampList[numOfBleNotifyEvents].disconnectTime);
        timeStampList[numOfBleNotifyEvents].duration = myTZ.now() - timenow;
        prevState = 0;
      }

      if (currentState == 1 &&  prevState == 0) {
        numOfBleNotifyEvents++;
        // second bit corresponds to the left button
        Serial.println("Button pressed");
        timeStampList[numOfBleNotifyEvents].connectTime = myTZ.dateTime();
        Serial.print(timeStampList[numOfBleNotifyEvents].connectTime);
        timenow = myTZ.now();
        prevState = 1;
      }
    }

    if(numOfBleNotifyEvents == MAX_NUM_BLE_EVENTS)
      isEventThresholdReached = true;
  }
  peripheral.disconnect();
  Serial.println("SensorTag disconnected!");
  return isEventThresholdReached;
}
