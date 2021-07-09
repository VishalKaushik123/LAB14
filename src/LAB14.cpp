/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Vishal/Documents/CTDProjects/LAB14/src/LAB14.ino"
/*
 * Project LAB14
 * Description:
 * Author:
 * Date:
 */
#include "MQTT.h"
#include <blynk.h>
#include "oled-wing-adafruit.h"

void setup();
void loop();
#line 11 "c:/Users/Vishal/Documents/CTDProjects/LAB14/src/LAB14.ino"
void callback(char *topic, byte *payload, unsigned int length);

OledWingAdafruit display;

SYSTEM_THREAD(ENABLED);

MQTT client("lab.thewcl.com", 1883, callback);

void callback(char *topic, byte *payload, unsigned int length)
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;

  if (p[0] == '1')
  {
    digitalWrite(D7, HIGH);
  }
  else if (p[0] == '0')
  {
    digitalWrite(D7, LOW);
  }
  else
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print(p);
    display.display();
  }
}

// Method to send messages via blynk
BLYNK_WRITE(V1)
{
  String pinData = param.asString();
  client.publish("lab-14", pinData);
  
}





// setup() runs once, when the device is first turned on.
void setup()
{
  Serial.begin(9600);

  pinMode(D7, OUTPUT);

  Blynk.begin("OzQeTUqWE0vRPD3cbMTSJ--_QzLgmlnd", IPAddress(167, 172, 234, 162), 9090); // in setup

  display.setup();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
}

// loop() runs over and over again, as quickly as it can execute.

void loop()
{
  client.loop();
  display.loop();
  Blynk.run();

  if (client.isConnected())
  {
    if (display.pressedA())
    {
      client.publish("lab-14", "Pressed A");
    }

    if (display.pressedB())
    {
      client.publish("lab-14", "Pressed B");
    }

    if (display.pressedC())
    {
      client.publish("lab-14", "Pressed C");
    }
  }
  else
  {
    client.connect(System.deviceID());
    client.subscribe("lab-14");
    // client.subscribe("lab-14-chat");
  }
}