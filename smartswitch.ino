/*
 * Copyright (c) 2016 Intel Corporation.  All rights reserved.
 * See the bottom of this file for the license terms.
 */

/*
 * Sketch: led.ino
 *
 * Description:
 *   This is a Peripheral sketch that works with a connected Central.
 *   It allows the Central to write a value and set/reset the led
 *   accordingly.
 */

#include <CurieBLE.h>

#include <Servo.h>

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEUnsignedCharCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int ledPin = 13; // we used this pin for testing purposes

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 75;    // initial servo position

void setup() {
  Serial.begin(9600);

  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  // begin initialization
  BLE.begin();

  // set advertised local name and service UUID:
  BLE.setLocalName("GENUINO 101-CE08"); // You can change it to the module name
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characeristic:
  switchCharacteristic.setValue(0);

  // start advertising
  BLE.advertise();

  Serial.println("BLE LED Peripheral");
}

void loop() {
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control the SWITCH:
      if (switchCharacteristic.written()) {
        if (switchCharacteristic.value()) {   // any value other than 0

//    If the user presses the SWITCH ON in the app, this code will run..............................

          digitalWrite(ledPin, HIGH);         // will turn the SWITCH on
          for (pos = 75; pos <= 170; pos += 1) { // goes from 75 degrees to 170 degrees
            // in steps of 1 degree 
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(10);                       // waits 10ms for the servo to reach the position
            }
            delay(500);
          for (pos = 170; pos >= 75; pos -= 1) { // goes from 170 degrees to 75 degrees
            // in steps of 1 degree 
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(10);                       // waits 10ms for the servo to reach the position
            }

            } else {                              // a 0 value

//  If the user presses the SWITCH OFF button on the app, this code will run.............................


          digitalWrite(ledPin, LOW);          // will turn the SWITCH off
          for (pos = 75; pos >= 15; pos -= 1) { // goes from 75 degrees to 15 degrees
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(10);                       // waits 10ms for the servo to reach the position
            }
            delay(500);
          for (pos = 15; pos <= 75; pos += 1) { // goes from 15 degrees to 75 degrees
            // in steps of 1 degree 
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(10);
          }
        }
      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}

/*
   Copyright (c) 2016 Intel Corporation.  All rights reserved.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
