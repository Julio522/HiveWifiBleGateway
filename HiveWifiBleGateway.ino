//Hive Proejct with Button Functionality and Sending Timestamps to AWS IOT Core

#include <SPI.h>
#include <WiFiNINA.h> //Include this instead of WiFi101.h as needed
#include <WiFiUdp.h>
#include <RTCZero.h>
#include <ezTime.h>
#include <ArduinoBearSSL.h>
#include <ArduinoECCX08.h>
#include <ArduinoMqttClient.h>
#include <ArduinoBLE.h>

#include "utility/wifi_drv.h"
#include "arduino_secrets.h"
#include "hive_gateway_functions.h"

// Variable Initialization
RTCZero rtc;

int status = WL_IDLE_STATUS;
WiFiClient    wifiClient;            // Used for the TCP socket connection
BearSSLClient sslClient(wifiClient); // Used for SSL/TLS connection, integrates with ECC508
MqttClient    mqttClient(sslClient);

/////// Enter your sensitive data in arduino_secrets.h
const char ssid[]        = SECRET_SSID;
const char pass[]        = SECRET_PASS;
const char broker[]      = SECRET_BROKER;
const char* certificate  = SECRET_CERTIFICATE;
unsigned long lastMillis = 0;

timeStamp_t timeStampList[MAX_NUM_BLE_EVENTS];

#define BUFFER_LEN 600
String connect_time, disconnect_time, duration;
char msg[BUFFER_LEN];

//**************************************************************//
void setup() {

  // Basic Setup
  Serial.begin(115200);
  while (!Serial);

  if (!ECCX08.begin()) {
    Serial.println("No ECCX08 present!");
    while (1);
  }

  // check if the WiFi module works
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  //*****************************

  bool isSetupSuccess = initialSetup();

  while (!isSetupSuccess) {
    // Setup the Wifi HotSpot
    // Collect SSID, Password
    // Wait for Submit Event
    // Save to memory

    // Retry the initial setup
    isSetupSuccess = initialSetup();
  }
}

//************************************************

// Main Loop
void loop() {

  // Connect to BLE
  connectToBle();

  //Disconnect From BLE
  disconnectBle();

  Serial.println("Ble Connection over: Connecting To Wifi");
  //*************************

  delay(500);


  // Connect to WiFi
  connectToWifi();
  printWiFiStatus();

  //Connect MQTT
  connectMQTT();

  // ToDo: Read Data from Memory and Send New Data
  // Send the data...
  Serial.print("Sending Data to the CLoud ...");
  for(int i=0; i<MAX_NUM_BLE_EVENTS; i++) {
    publishMessage(timeStampList[i]);
  }

  delay(1000);
  // Disconnecting WiFi
  disconnectWifi();

  Serial.println("Wifi Connection over: Connecting To BLE");

  delay(100);

}


unsigned long getTime() {
  // get the current time from the WiFi module
  return WiFi.getTime();
}

void connectMQTT() {
  Serial.print("Attempting to MQTT broker: ");
  Serial.print(broker);
  Serial.println(" ");

  while (!mqttClient.connect(broker, 8883)) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }
  Serial.println("\n You're connected to the MQTT broker \n");
}

void publishMessage(timeStamp_t timeStamp) {

  char dur[50];
  (void) sprintf(dur,"%lu",timeStamp.duration);
  snprintf(msg,BUFFER_LEN,"{\"Device Name\" : \"HiveWifiGateway1002\", \"Connection_Start\" : \"%s\", \"Disconnected_At\" : \"%s\", \"Duration\" : \"%s\",  \"Time_Elapsed\" : \"%s\"}", timeStamp.connectTime.c_str(), timeStamp.disconnectTime.c_str(), dur,timeStamp.time_elapsed.c_str());
//snprintf(msg,BUFFER_LEN,"{"Connection_Start" : "%s", "Disconnected_At" : "%s", "Duration" : "%lu\"}", time1.c_str(), time2.c_str(), duration);

  Serial.println("Publishing message");
  // send message, the Print interface can be used to set the message contents
  mqttClient.beginMessage("arduino/outgoing");
  mqttClient.print(msg);
  mqttClient.endMessage();
}

// Initialize clock with current time in timezone
bool timeZoneInit() {
  unsigned long epoch;
  int numberOfTries = 0, maxTries = 20;
  do {
    Serial.println("Getting time from NTP");
    epoch = WiFi.getTime();
    numberOfTries++;
    delay(100);
  }
  while ((epoch == 0) && (numberOfTries < maxTries));

  if (numberOfTries == maxTries) {
    Serial.print("NTP unreachable!!");
    return false;
  }
  else {
    Serial.print("Epoch received: ");
    Serial.println(epoch);
    rtc.setEpoch(epoch);

    Serial.println();
  }
  waitForSync();
  myTZ.setLocation(F("America/Los_Angeles"));
  // Provide official timezone names
  // https://en.wikipedia.org/wiki/List_of_tz_database_time_zones

  return true;
}


// Attempt to connect to WiFi network 3 times
bool connectToWifi() {
  int numberOfTries = 0;
  status = WiFi.status();
  while ( status != WL_CONNECTED && numberOfTries < 3) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 5 seconds for connection:
    delay(5000);
    numberOfTries++;
  }

  if (status == WL_CONNECTED)
    return true;
  else
    return false;
}

void disconnectWifi() {
  Serial.print("Disconnecting From Wifi \n");
  WiFi.disconnect();
  WiFi.end();
}

// Start BLE , scan for devices, connect to SimpleKey , monitor for notifications
void connectToBle() {
  // begin BLE initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

  // start scanning for peripheral
  BLE.scan();

  bool isEventThresholdReached = false;
  while(!isEventThresholdReached) {

    // check if a peripheral has been discovered
    BLEDevice peripheral = BLE.available();

    if (peripheral) {
      // discovered a peripheral, print out address, local name, and advertised service
      Serial.print("Found ");
      Serial.print(peripheral.address());
      Serial.print(" '");
      Serial.print(peripheral.localName());
      Serial.print("' ");
      Serial.print(peripheral.advertisedServiceUuid());
      Serial.println();

      // Check if the peripheral is a SensorTag, the local name will be:
      // "CC2650 SensorTag"
      if (peripheral.localName() == "SimpleKey") {
        // stop scanning
        BLE.stopScan();

        isEventThresholdReached = monitorSimpleKey(peripheral, timeStampList);

        // peripheral disconnected, start scanning again
        BLE.scan();
      }
    }

  }
}

void disconnectBle() {
  BLE.disconnect();
  BLE.end();
}

bool initialSetup() {
  if(connectToWifi() == true) {

    // you're connected now, so print out the status:
    printWiFiStatus();

    // ToDo: Remove infinite loop on Failure and handle Error
    // Initialize clock with current time and timezone
    while(!timeZoneInit()) {
      disconnectWifi();
      connectToWifi();
    }

    // Set a callback to get the current time
    // used to validate the servers certificate
    ArduinoBearSSL.onGetTime(getTime);
     // Set the ECCX08 slot to use for the private key
    // and the accompanying public certificate for it
    sslClient.setEccSlot(0, certificate);

    //Connect MQTT
    connectMQTT();

    // ToDo: Read Data from Memory and Send New Data
    // Send the data...
    Serial.print("Sending Data to the CLoud ...");

    delay(500);
    // Disconnecting WiFi
    disconnectWifi();

    return true;

  } else {
    Serial.print("Failed to Connect to WiFi ");
    return false;
  }
}
