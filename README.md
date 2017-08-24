# Temperature-and-Humidity-Sensing-Model-With-GUI-Visualisation
To generate an ESP8266 WiFi based webserver to fetch data from a DHT sensor module( temperature and humidity sensor) and present it through a web page consisting of  Live linear graph visualisation for each of the two parameters(temperature in Celsius and Humidity percentage)

The project requires the use of the following components:-

ESP8266-01 WiFi Module
DHT11 sensor
LD33V 3.3 Voltage regulator
Tactile push button
Breadboard
Arduino Uno R3 board( ATMega 328p Chip not needed) 
Jumper wires

Pre Requisite knowledge in context to this project:-

ESP8266 Module
The ESP8266 WiFi Module is a self contained SOC with integrated TCP/IP protocol stack that can give any microcontroller access to your WiFi network. The ESP8266 is capable of either hosting an application or offloading all Wi-Fi networking functions from another application processor. Each ESP8266 module comes pre-programmed with an AT command set firmware which can also be replaced by flashing custom sketches via platforms such as Arduino IDE. The ESP8266 module is an extremely cost effective board with a huge, and ever growing, community.
Caution: The ESP8266 Module is not capable of 5-3V logic shifting and will require an external. Please do not power it directly from a 5V dev board.. Please do not power it directly from your 5V dev board.
The ESP8266 01 model has only 2 GPIO pins for flashing and running code. The GPIO pins are Digital pins and hence can not take in analog values. 

Arduino Uno R3 board
The Arduino Uno board serves the purpose of a regulated power supply with adequate ground options when the Atmega328p chip is removed from its place. This method of supplying ensures a balanced power supply and convenient breadboard circuitry and the the convenience of the Arduino IDE for programming the modules. Please note that in case the Arduino board does not have a removable microcontroller chip( the ATmega) the same effect can be produced by connecting the Reset pin to the ground pin on the Arduino board.

DHT11 Sensor
DHT11 digital temperature and humidity sensor is a composite Sensor contains a calibrated digital signal output of the temperature and humidity. Application of a dedicated digital modules collection technology and the temperature and humidity sensing technology, to ensure that the product has high reliability and excellent long-term stability. The sensor includes a resistive sense of wet components and an NTC temperature measurement devices, and connected with a high-performance 8-bit microcontroller.

LD33v voltage regulator
The LD33v voltage regulator is a 3.3V voltage regulator which is required in the project to ensure a steady supply of power to the ESP8266. This is a crucial component to the project as the 3.3V supply pin on the arduino is known to be inconsistent and may not provide accurate supply plus the fact that ESP8266 is a sensitive module and any amount of power supplied to it beyond 3.3V will damage the chip and render it useless.


METHODOLOGY

WIRING UP THE CIRCUIT:
The components should be wired up in accordance to the following diagram:-






A picture of the wired up circuit.





Uploading the sketch
To upload your compiled program to the ESP8266:
DiSconnect power to the ESP.
Bring GPIO0 to ground (press AND HOLD DOWN the pushbutton).
Power up the ESP.
Release the pushbutton
Click the round right arrow icon to upload the program( in the IDE

Highcharts Graph API
The Highcharts API is a Javascript based framework to generate various graphs as per need. It is developed by a Norway based group called Highsoft. The project requires the use of a basic Line graph which provides time series on the x axis( fetching it using javascript based function getseconds()) and the dynamically adjustable y axis to scale the temperature/humidity range. The plotline shows the temperature/ humidity values at various time lapses after beginning the graph. It is updated in matter of seconds and hence provides a realtime view of the data.



Note: The implementation of this project when done correctly may still present significant delays before the exact desired outcome is seen. In such a case please check the circuit, especially the esp chip( it should not be heated too much) and check the code as well for typing mistakes. If everything else is okay please wait till the serial monitor shows the IP for the device as mentioned above. There are chances that ESP being very inexpensive may take quite a while to ready itself. Please make sure the SSID and password in the code are given to a permitting network.

It is to be noted that the DHT11 sensor usually reports data with a possible deviation of 1-1.5 degrees plus or minus in comparison with actual values when reporting the values. Over time it normalizes with the original values. 


 

SUMMARY AND FURTHER SCOPE


The ESP8266 based temperature and humidity model is now ready and shows two parameters temperature and humidity each with their own GUIs to view. It is a cost effective DIY IoT solution and can be applied in various cases such as monitoring home garden temperature for better plant management, humidity levels inside the house as a part of home automation system etc.

Further it could be modified improvised to report crop quality in farms and enable data analytics to suggest crop practices etc. The networking portion of the code is portable to be used with any sensor on various use cases. 


REFERENCES
http://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/server-examples.html
https://learn.adafruit.com/esp8266-temperature-slash-humidity-webserver/overview
https://www.highcharts.com/demo
ESP8266 datasheet-http://www.electroschematics.com/11276/esp8266-datasheet/
DHT11 datasheet-https://akizukidenshi.com/download/ds/aosong/DHT11.pdf
