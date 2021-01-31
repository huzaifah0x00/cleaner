/**
  @file    wifi_car_esp8266_AP.ino
  @brief   Simple example of Wifi Car controlled by a web server in AP Mode. See also :
           http://www.instructables.com/id/A-very-cheap-ESP8266-WiFi-smart-car-controlled-by-/

           Example of commands to control the car :
           
           MOVE:
           - http://<YourIP>:<YourPort>/move?dir=F (Forward)
           - http://<YourIP>:<YourPort>/move?dir=B (Bacward)
           
           ACTION:
           - http://<YourIP>:<YourPort>/action?type=1 (Action 1)
           - http://<YourIP>:<YourPort>/action?type=1 (Action 2)


  @author  LACOUR Vincent
  @date    2019-10
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "WIFI_CAR_ESP9266";
const char *password = "wificarpassword";

IPAddress ip(192, 168, 4, 1);
IPAddress netmask(255, 255, 255, 0);
const int port = 8080; // Port
ESP8266WebServer server(port);

static const uint8_t LEFT_WHEELS_TPIN = 4;
static const uint8_t RIGHT_WHEELS_TPIN = 12;

static const uint8_t pwm_A = 5;
static const uint8_t pwm_B = 4;
static const uint8_t dir_A = 0;
static const uint8_t dir_B = 2;

// Motor speed = [0-1024]
int motor_speed = 1024;

void setup()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(ip, ip, netmask);
    WiFi.softAP(ssid, password);

    pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output

    pinMode(LEFT_WHEELS_TPIN, OUTPUT);
    pinMode(RIGHT_WHEELS_TPIN, OUTPUT);

    digitalWrite(LEFT_WHEELS_TPIN, LOW);
    digitalWrite(RIGHT_WHEELS_TPIN, LOW);

    server.on("/move", HTTP_GET, handleMoveRequest);
    server.on("/action", HTTP_GET, handleActionRequest);
    server.onNotFound(handleNotFound);
    server.begin();
}

void loop()
{
    server.handleClient();
}

void handleActionRequest()
{
    if (!server.hasArg("type"))
    {
        server.send(404, "text / plain", "Action: undefined");
        return;
    }
    String type = server.arg("type");
    if (type.equals("1"))
    {
        // TODO : Action 1
        server.send(200, "text / plain", "Action 1");
    }
    else if (type.equals("2"))
    {
        // TODO : Action 2
        server.send(200, "text / plain", "Action 2");
    }
    else if (type.equals("3"))
    {
        // TODO : Action 3
        server.send(200, "text / plain", "Action 3");
    }
    else if (type.equals("4"))
    {
        // TODO : Action 4
        server.send(200, "text / plain", "Action 4");
    }
    else if (type.equals("5"))
    {
        // TODO : Action 5
        server.send(200, "text / plain", "Action 5");
    }
    else if (type.equals("6"))
    {
        // TODO : Action 6
        server.send(200, "text / plain", "Action 6");
    }
    else if (type.equals("7"))
    {
        // TODO : Action 7
        server.send(200, "text / plain", "Action 7");
    }
    else if (type.equals("8"))
    {
        // TODO : Action 8
        server.send(200, "text / plain", "Action 8");
    }
    else
    {
        server.send(404, "text / plain", "Action: undefined");
    }
}

void handleMoveRequest()
{
    if (!server.hasArg("dir"))
    {
        server.send(404, "text / plain", "Move: undefined");
        return;
    }
    String direction = server.arg("dir");
    if (direction.equals("F"))
    {
        forward();
        server.send(200, "text / plain", "Move: forward");
    }
    else if (direction.equals("B"))
    {
        backward();
        server.send(200, "text / plain", "Move: backward");
    }
    else if (direction.equals("S"))
    {
        stop_motors();
        server.send(200, "text / plain", "Move: stop");
    }
    else if (direction.equals("L"))
    {
        turn_left();
        server.send(200, "text / plain", "Turn: Left");
    }
    else if (direction.equals("R"))
    {
        turn_right();
        server.send(200, "text / plain", "Turn: Right");
    }
    else
    {
        server.send(404, "text / plain", "Move: undefined");
    }
}

void handleNotFound()
{
    server.send(404, "text / plain", "404: Not found");
}

void stop_motors()
{
    //   analogWrite(pwm_A, 0);
    //   analogWrite(pwm_B, 0);
    digitalWrite(LEFT_WHEELS_TPIN, LOW);
    digitalWrite(RIGHT_WHEELS_TPIN, LOW);
}

void backward()
{
    analogWrite(pwm_A, motor_speed);
    analogWrite(pwm_B, motor_speed);
    digitalWrite(dir_A, LOW);
    digitalWrite(dir_B, HIGH);
}

void forward()
{
    //   analogWrite(pwm_A, motor_speed);
    //   analogWrite(pwm_B, motor_speed);
    //   digitalWrite(dir_A, HIGH);
    //   digitalWrite(dir_B, LOW);
    digitalWrite(LEFT_WHEELS_TPIN, HIGH);
    digitalWrite(RIGHT_WHEELS_TPIN, HIGH);
}

void turn_left()
{
    //   analogWrite(pwm_A, motor_speed);
    //   analogWrite(pwm_B, motor_speed);
    //   digitalWrite(dir_A, HIGH);
    //   digitalWrite(dir_B, HIGH);
    digitalWrite(LEFT_WHEELS_TPIN, HIGH);
    digitalWrite(RIGHT_WHEELS_TPIN, LOW);
}

void turn_right()
{
    //   analogWrite(pwm_A, motor_speed);
    //   analogWrite(pwm_B, motor_speed);
    //   digitalWrite(dir_A, LOW);
    //   digitalWrite(dir_B, LOW);
    digitalWrite(LEFT_WHEELS_TPIN, LOW);
    digitalWrite(RIGHT_WHEELS_TPIN, HIGH);
}

// // void setup() {
// //   // put your setup code here, to run once:
// //   delay(5000);

// //   pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output

// //   pinMode(4, OUTPUT);
// //   pinMode(12, OUTPUT);

// //   digitalWrite(4, HIGH);
// //   digitalWrite(12, HIGH);
// //   Serial.begin(9600);

// // }

// // void loop() {
// //   // put your main code here, to run repeatedly:
// //   // but actually the LED is on; this is because
// //   // it is active low on the ESP-01)
// //   Serial.println("wtf i'm working bruh..");
// //   delay(2000);                      // Wait for a second
// //   digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
// //   digitalWrite(4, HIGH);
// //   digitalWrite(12, HIGH);

// //   delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
// //   digitalWrite(4, LOW);
// //   digitalWrite(12, LOW);
// //   digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level

// // }

// #include "ESP8266WiFi.h"
// #include <WiFiClient.h>
// #include <ESP8266WebServer.h>

// const char *ssid = "ESPap";
// const char *password = "thereisnospoon";

// ESP8266WebServer server(80);

// /* Just a little test message.  Go to http://192.168.4.1 in a web browser
//    connected to this access point to see it.
// */
// void handleRoot()
// {
//     server.send(200, "text/html", "<h1>You are connected</h1>");
// }

// void handleForward()
// {
//     Serial.println("wtf bro");
//     digitalWrite(4, HIGH);
//     digitalWrite(12, HIGH);
//     server.send(200, "text/html", "<h1>Going Forward</h1>");
// }

// void handleLeft()
// {
//     digitalWrite(4, HIGH);
//     digitalWrite(12, LOW);
//     server.send(200, "text/html", "<h1>Going Forward</h1>");
// }
// void handleStopLeft()
// {
//     // digitalWrite(4, HIGH);
//     digitalWrite(12, HIGH);
//     server.send(200, "text/html", "<h1>Going Forward</h1>");
// }

// void handleRight()
// {
//     digitalWrite(4, LOW);
//     digitalWrite(12, HIGH);
//     server.send(200, "text/html", "<h1>Going Forward</h1>");
// }
// void handleStopRight()
// {
//     digitalWrite(4, HIGH);
//     server.send(200, "text/html", "<h1>Going Forward</h1>");
// }

// void setup()
// {

//     Serial.begin(115200);
//     pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output

//     pinMode(4, OUTPUT);
//     pinMode(12, OUTPUT);

//     delay(1000);

//     Serial.print("Configuring access point...");
//     /* You can remove the password parameter if you want the AP to be open. */
//     WiFi.softAP(ssid, password);

//     IPAddress myIP = WiFi.softAPIP();
//     Serial.print("AP IP address: ");
//     Serial.println(myIP);
//     Serial.println("HTTP server started");
//     server.on("/", handleRoot);
//     server.on("/forward", handleForward);

//     server.on("/stopforward", handleStopForward);
//     server.on("/left", handleLeft);
//     server.on("/stopleft", handleStopLeft);
//     server.on("/right", handleRight);
//     server.on("/stopright", handleStopRight);

//     server.begin();
// }

// void loop()
// {
//     server.handleClient();
// }
