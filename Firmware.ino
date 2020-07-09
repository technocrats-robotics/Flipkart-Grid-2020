
// Include Libraries
#include "Arduino.h"
#include "DCMDriverL298.h"
#include "ESP8266.h"
#include "Gyro.h"
#include "NewPing.h"
#include "UltraSonic.h"


// Pin Definitions
#define DCMOTORDRIVERL298_1_PIN_INT1	8
#define DCMOTORDRIVERL298_1_PIN_ENB	3
#define DCMOTORDRIVERL298_1_PIN_INT2	9
#define DCMOTORDRIVERL298_1_PIN_ENA	2
#define DCMOTORDRIVERL298_1_PIN_INT3	12
#define DCMOTORDRIVERL298_1_PIN_INT4	13
#define DCMOTORDRIVERL298_2_PIN_INT1	14
#define DCMOTORDRIVERL298_2_PIN_ENB	5
#define DCMOTORDRIVERL298_2_PIN_INT2	15
#define DCMOTORDRIVERL298_2_PIN_ENA	4
#define DCMOTORDRIVERL298_2_PIN_INT3	22
#define DCMOTORDRIVERL298_2_PIN_INT4	23
#define DCMOTORDRIVERL298_3_PIN_INT1	24
#define DCMOTORDRIVERL298_3_PIN_ENB	7
#define DCMOTORDRIVERL298_3_PIN_INT2	25
#define DCMOTORDRIVERL298_3_PIN_ENA	6
#define DCMOTORDRIVERL298_3_PIN_INT3	27
#define DCMOTORDRIVERL298_3_PIN_INT4	28
#define WIFI_PIN_TX	11
#define WIFI_PIN_RX	10
#define HCSR04_1_PIN_TRIG	30
#define HCSR04_1_PIN_ECHO	29
#define HCSR04_2_PIN_TRIG	32
#define HCSR04_2_PIN_ECHO	31
#define ULTRASONIC_5V_PIN_PW	34



// Global variables and defines
// ====================================================================
// vvvvvvvvvvvvvvvvvvvv ENTER YOUR WI-FI SETTINGS  vvvvvvvvvvvvvvvvvvvv
//
const char *SSID     = "WIFI-SSID"; // Enter your Wi-Fi name 
const char *PASSWORD = "PASSWORD" ; // Enter your Wi-Fi password
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// ====================================================================
char* const host = "www.google.com";
int hostPort = 80;
// object initialization
DCMDriverL298 dcMotorDriverL298_1(DCMOTORDRIVERL298_1_PIN_ENA,DCMOTORDRIVERL298_1_PIN_INT1,DCMOTORDRIVERL298_1_PIN_INT2,DCMOTORDRIVERL298_1_PIN_ENB,DCMOTORDRIVERL298_1_PIN_INT3,DCMOTORDRIVERL298_1_PIN_INT4);
DCMDriverL298 dcMotorDriverL298_2(DCMOTORDRIVERL298_2_PIN_ENA,DCMOTORDRIVERL298_2_PIN_INT1,DCMOTORDRIVERL298_2_PIN_INT2,DCMOTORDRIVERL298_2_PIN_ENB,DCMOTORDRIVERL298_2_PIN_INT3,DCMOTORDRIVERL298_2_PIN_INT4);
DCMDriverL298 dcMotorDriverL298_3(DCMOTORDRIVERL298_3_PIN_ENA,DCMOTORDRIVERL298_3_PIN_INT1,DCMOTORDRIVERL298_3_PIN_INT2,DCMOTORDRIVERL298_3_PIN_ENB,DCMOTORDRIVERL298_3_PIN_INT3,DCMOTORDRIVERL298_3_PIN_INT4);
ESP8266 wifi(WIFI_PIN_RX,WIFI_PIN_TX);
Gyro gyro;
NewPing hcsr04_1(HCSR04_1_PIN_TRIG,HCSR04_1_PIN_ECHO);
NewPing hcsr04_2(HCSR04_2_PIN_TRIG,HCSR04_2_PIN_ECHO);
UltraSonic ultraSonic_5v(ULTRASONIC_5V_PIN_PW);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    wifi.init(SSID, PASSWORD);
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // L298N Motor Driver with Dual Hobby DC motors #1 - Test Code
    //Start both motors. note that rotation direction is determined by the motors connection to the driver.
    //You can change the speed by setting a value between 0-255, and set the direction by changing between 1 and 0.
    dcMotorDriverL298_1.setMotorA(200,1);
    dcMotorDriverL298_1.setMotorB(200,0);
    delay(2000);
    //Stop both motors
    dcMotorDriverL298_1.stopMotors();
    delay(2000);

    }
    else if(menuOption == '2') {
    // L298N Motor Driver with Dual Hobby DC motors #2 - Test Code
    //Start both motors. note that rotation direction is determined by the motors connection to the driver.
    //You can change the speed by setting a value between 0-255, and set the direction by changing between 1 and 0.
    dcMotorDriverL298_2.setMotorA(200,1);
    dcMotorDriverL298_2.setMotorB(200,0);
    delay(2000);
    //Stop both motors
    dcMotorDriverL298_2.stopMotors();
    delay(2000);

    }
    else if(menuOption == '3') {
    // L298N Motor Driver with Dual Hobby DC motors #3 - Test Code
    //Start both motors. note that rotation direction is determined by the motors connection to the driver.
    //You can change the speed by setting a value between 0-255, and set the direction by changing between 1 and 0.
    dcMotorDriverL298_3.setMotorA(200,1);
    dcMotorDriverL298_3.setMotorB(200,0);
    delay(2000);
    //Stop both motors
    dcMotorDriverL298_3.stopMotors();
    delay(2000);

    }
    else if(menuOption == '4') {
    // ESP8266-01 - Wifi Module - Test Code
    //Send request for www.google.com at port 80
    wifi.httpGet(host, hostPort);
    // get response buffer. Note that it is set to 250 bytes due to the Arduino low memory
    char* wifiBuf = wifi.getBuffer();
    //Comment out to print the buffer to Serial Monitor
    //for(int i=0; i< MAX_BUFFER_SIZE ; i++)
    //  Serial.print(wifiBuf[i]);
    //search buffer for the date and time and print it to the serial monitor. This is GMT time!
    char *wifiDateIdx = strstr (wifiBuf, "Date");
    for (int i = 0; wifiDateIdx[i] != '\n' ; i++)
    Serial.print(wifiDateIdx[i]);

    }
    else if(menuOption == '5')
    {
    // Disclaimer: The Ublox NEO-6M GPS Module is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '6') {
    // SparkFun ITG-3200 - Triple-Axis Digital-Output Gyro Breakout - Test Code
    // Get gyro readings in three axes.
    int gyroX = gyro.getX();
    int gyroY = gyro.getY();
    int gyroZ = gyro.getZ();
    Serial.print(F("X: ")); Serial.print(gyroX); 
    Serial.print(F("\tY: ")); Serial.print(gyroY); 
    Serial.print(F("\tZ: ")); Serial.println(gyroZ);

    }
    else if(menuOption == '7') {
    // Ultrasonic Sensor - HC-SR04 #1 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04_1Dist = hcsr04_1.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04_1Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '8') {
    // Ultrasonic Sensor - HC-SR04 #2 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04_2Dist = hcsr04_2.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04_2Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '9')
    {
    // Disclaimer: The QuadBand GPRS-GSM SIM800L is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '10') {
    // LV-MaxSonar-EZ1 - Ultrasonic Range Finder - Test Code
    //Get distance measurement in cm. see also ultraSonic_5v.getInches()
    float ultraSonic_5vDist = ultraSonic_5v.getCms();
    Serial.print(F("Distance: ")); Serial.print(ultraSonic_5vDist); Serial.println(F("[cm]"));

    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) L298N Motor Driver with Dual Hobby DC motors #1"));
    Serial.println(F("(2) L298N Motor Driver with Dual Hobby DC motors #2"));
    Serial.println(F("(3) L298N Motor Driver with Dual Hobby DC motors #3"));
    Serial.println(F("(4) ESP8266-01 - Wifi Module"));
    Serial.println(F("(5) Ublox NEO-6M GPS Module"));
    Serial.println(F("(6) SparkFun ITG-3200 - Triple-Axis Digital-Output Gyro Breakout"));
    Serial.println(F("(7) Ultrasonic Sensor - HC-SR04 #1"));
    Serial.println(F("(8) Ultrasonic Sensor - HC-SR04 #2"));
    Serial.println(F("(9) QuadBand GPRS-GSM SIM800L"));
    Serial.println(F("(10) LV-MaxSonar-EZ1 - Ultrasonic Range Finder"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing L298N Motor Driver with Dual Hobby DC motors #1"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing L298N Motor Driver with Dual Hobby DC motors #2"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing L298N Motor Driver with Dual Hobby DC motors #3"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing ESP8266-01 - Wifi Module"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing Ublox NEO-6M GPS Module - note that this component doesn't have a test code"));
    		else if(c == '6') 
    			Serial.println(F("Now Testing SparkFun ITG-3200 - Triple-Axis Digital-Output Gyro Breakout"));
    		else if(c == '7') 
    			Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04 #1"));
    		else if(c == '8') 
    			Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04 #2"));
    		else if(c == '9') 
    			Serial.println(F("Now Testing QuadBand GPRS-GSM SIM800L - note that this component doesn't have a test code"));
    		else if(c == '10') 
    			Serial.println(F("Now Testing LV-MaxSonar-EZ1 - Ultrasonic Range Finder"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/