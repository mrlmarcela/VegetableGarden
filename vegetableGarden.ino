/*
Project name: Vegetable garden
Author: Marcela Lima
Contact: mrl.marcelalima@gmail.com
microcontroller: ESP8266 NodeMCU
Abstract: This project was developed in order to build a self-manageable vegetable garden, making the plant manage to stay moist enough to live.
*/

/*Including library for internet connection. 
This library is already available from the Arduino IDE*/

#include <ESP8266WiFi.h>

// Defining the pins of our esp8266

#define pinAnalog A0
#define pinRelay D8
#define pinSensor D7

// Declaring the variables

int valAnalog;
int attempts = 50;
int percentage;
char SSID[] = "";
char NETKEY[] = "";
char *assetName = "esp8266";

// Start of network connection functions

void printNetworkData()
{
    Serial.println("- - - - - - - - - - - - - - - - - - - - - - - -");
    Serial.println("Hostname: " + (String)assetName);

    Serial.println("Connected in: " + (String)SSID);

    Serial.print("My address IP: ");
    Serial.println(WiFi.localIP());

    Serial.println("- - - - - - - - - - - - - - - - - - - - - - - - ");
}

void wifiConect()
{
    delay(2000);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(SSID);

    WiFi.begin(SSID, NETKEY);

    WiFi.hostname(assetName);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        attempts--;

        if (attempts == 0)
        {
            Serial.println();
            Serial.println("Time-out. Check your settings and try again.");
            delay(1000);
        }
    }
}

// End of network connection functions

// Start of function to irrigate the plant

void irrigatePlant()
{
    if (percentage <= 45)
    {
        Serial.print(percentage);
        Serial.println("%");
        Serial.println("Irrigating the plant...");
        digitalWrite(pinRelay, HIGH);
        delay(1000);
    }
}

// End of function to irrigate the plant

// Start of the function that turns off the pump

void turnOffPump()
{
    if (percentage > 45)
    {
        Serial.print(percentage);
        Serial.println("%");
        Serial.println("irrigated plant");
        digitalWrite(pinRelay, LOW);
    }
}

// End of the function that turns off the pump

void setup(void)
{
    // Starting the serial monitor
    Serial.begin(115200);

    // Declaring pins as input or output
    pinMode(pinRelay, OUTPUT);
    pinMode(pinSensor, OUTPUT);

    // Declaring the sensor pin in high state
    digitalWrite(pinSensor, HIGH);

    // Calling the network connection functions
    wifiConect();
    printNetworkData();
    delay(2000);
}

void loop()
{
    // Starting to read the analog value of the sensor
    valAnalog = analogRead(pinAnalog);

    // Relating analog value to percentage
    percentage = map(valAnalog, 1023, 0, 0, 100);

    // Calling the functions to irrigate the plant and turn off the pump
    irrigatePlant();
    turnOffPump();
    delay(1500);
}
