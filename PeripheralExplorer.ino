/*
  Peripheral Explorer

  This example scans for BLE peripherals until one with a particular name ("LED")
  is found. Then connects, and discovers + prints all the peripheral's attributes.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.

  You can use it with another board that is compatible with this library and the
  Peripherals -> LED example.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>



void setup() {
  Serial.begin(9600);
  while (!Serial);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }

  Serial.println("BLE Central - Peripheral Explorer");
  
  // start scanning for peripherals
  BLE.scan();
}

void loop() {
  // check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    // discovered a peripheral, print out address, local name, and advertised service
//    Serial.print("Found ");
//    Serial.print(peripheral.address());
//    Serial.print(" '");
//    Serial.print(peripheral.localName());
//    Serial.print("' ");
//    Serial.print(peripheral.advertisedServiceUuid());
//    Serial.println();

    // see if peripheral is a Nordic_UART
    if (peripheral.localName() == "Nordic_UART") {
      // stop scanning
      BLE.stopScan();
      String uuid = "6e400003-b5a3-f393-e0a9-e50e24dcca9e";
      
      // After this call, myCharacteristic stores the characteristic we're looking for
      BLECharacteristic myCharacteristic;
      findCharacteristic(peripheral, uuid, myCharacteristic);

      // Subscribe code
      Serial.println("Subscribing to simple key characteristic ...");
      if (!myCharacteristic) {
        Serial.println("no characteristic found!");
        peripheral.disconnect();
        return;
      } else if (!myCharacteristic.canSubscribe()) {
        Serial.println("simple is not subscribable!");
        peripheral.disconnect();
        return;
      } else if (!myCharacteristic.subscribe()) {
        Serial.println("subscription failed!");
        peripheral.disconnect();
        return;
      }
      Serial.println("enter while loop");

      
      //Serial.println(myCharacteristic.writeValue(values, 20));
      while(1) {
      //while(peripheral.connected()) {
        if(myCharacteristic.valueUpdated()) {
          int l = 20;
          char values[l];
          
          myCharacteristic.readValue(values, l);
          Serial.println("update");
          for (int i=0; i < l; i++) {
            Serial.print(values[i]);
          }
          Serial.println();


          // Send values via MQTT
          
        }
        else {
          //Serial.println("not updated");
        }
      }

      
      
      // explorerPeripheral(peripheral);

      // peripheral disconnected, we are done
//      while (1) {
//        // do nothing
//      }
    }
  }
}

void explorerPeripheral(BLEDevice peripheral) {
  // connect to the peripheral
  Serial.println("Connecting ...");

  if (peripheral.connect()) {
    Serial.println("Connected");
  } else {
    Serial.println("Failed to connect!");
    return;
  }

  // discover peripheral attributes
  Serial.println("Discovering attributes ...");
  if (peripheral.discoverAttributes()) {
    Serial.println("Attributes discovered");
  } else {
    Serial.println("Attribute discovery failed!");
    peripheral.disconnect();
    return;
  }

  // read and print device name of peripheral
  Serial.println();
  Serial.print("Device name: ");
  Serial.println(peripheral.deviceName());
  Serial.print("Appearance: 0x");
  Serial.println(peripheral.appearance(), HEX);
  Serial.println();

  // loop the services of the peripheral and explore each
  for (int i = 0; i < peripheral.serviceCount(); i++) {
    BLEService service = peripheral.service(i);

    exploreService(service);
  }

  Serial.println();

  // we are done exploring, disconnect
//  Serial.println("Disconnecting ...");
//  peripheral.disconnect();
//  Serial.println("Disconnected");
}

void exploreService(BLEService service) {
  // print the UUID of the service
  Serial.print("Service ");
  Serial.println(service.uuid());

  // loop the characteristics of the service and explore each
  for (int i = 0; i < service.characteristicCount(); i++) {
    BLECharacteristic characteristic = service.characteristic(i);
    String myCharacteristic = characteristic.uuid();
    if (myCharacteristic.equals("6e400003-b5a3-f393-e0a9-e50e24dcca9e")) {
      Serial.print("hi mom");
    }
    else {
      Serial.print("mom not found");
    }
    exploreCharacteristic(characteristic);
  }
}

void findCharacteristic(BLEDevice peripheral, String uuid, BLECharacteristic &myCharacteristic) {

  Serial.println("Running findCharacteristic"); 
  // connect to the peripheral
  Serial.println("Connecting ...");

  if (peripheral.connect()) {
    Serial.println("Connected");
  } else {
    Serial.println("Failed to connect!");
    return;
  }

  // discover peripheral attributes
  Serial.println("Discovering attributes ...");
  if (peripheral.discoverAttributes()) {
    Serial.println("Attributes discovered");
  } else {
    Serial.println("Attribute discovery failed!");
    peripheral.disconnect();
    return;
  }

  // read and print device name of peripheral
  Serial.println();
  Serial.print("Device name: ");
  Serial.println(peripheral.deviceName());
  Serial.print("Appearance: 0x");
  Serial.println(peripheral.appearance(), HEX);
  Serial.println();

  
  // loop the services of the peripheral and explore each
  for (int i = 0; i < peripheral.serviceCount(); i++) {
    BLEService service = peripheral.service(i);
    for (int i = 0; i < service.characteristicCount(); i++) {
      BLECharacteristic characteristic = service.characteristic(i);
      String currUuid = characteristic.uuid();
      if (currUuid.equals(uuid)) {
        exploreCharacteristic(characteristic);
        myCharacteristic = characteristic;
      }
    }
    
  }
}

void exploreCharacteristic(BLECharacteristic characteristic) {
  // print the UUID and properties of the characteristic
  Serial.print("\tCharacteristic ");
  Serial.print(characteristic.uuid());
  Serial.print(", properties 0x");
  Serial.print(characteristic.properties(), HEX);
  Serial.print(characteristic.canRead());
  // check if the characteristic is readable
  if (characteristic.canRead()) {
    // read the characteristic value
    characteristic.read();
    Serial.print("Serial value length");
    Serial.print(characteristic.valueLength());
    if (characteristic.valueLength() > 0) {
      // print out the value of the characteristic
      Serial.print(", value 0x");
      printData(characteristic.value(), characteristic.valueLength());

      
    }
  }
  Serial.println();

  // loop the descriptors of the characteristic and explore each
  for (int i = 0; i < characteristic.descriptorCount(); i++) {
    BLEDescriptor descriptor = characteristic.descriptor(i);

    exploreDescriptor(descriptor);
  }
}

void exploreDescriptor(BLEDescriptor descriptor) {
  // print the UUID of the descriptor
  Serial.print("\t\tDescriptor ");
  Serial.print(descriptor.uuid());

  // read the descriptor value
  descriptor.read();

  // print out the value of the descriptor
  Serial.print(", value 0x");
  printData(descriptor.value(), descriptor.valueLength());

  Serial.println();
}

void printData(const unsigned char data[], int length) {
  for (int i = 0; i < length; i++) {
    unsigned char b = data[i];

    if (b < 16) {
      Serial.print("0");
    }

    Serial.print(b, HEX);
  }
}
