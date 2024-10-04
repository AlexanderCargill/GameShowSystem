#include <stdint.h>
//#include <string.h>

#include <WiFi.h>
#include <WiFiUDP.h>

// defines 

#define YELLOW_LED_PIN 21
#define RED_LED_PIN 19
#define BLUE_LED_PIN 5
#define GREEN_LED_PIN 18

#define YELLOW_SWITCH_PIN 12
#define RED_SWITCH_PIN 25
#define BLUE_SWITCH_PIN 33
#define GREEN_SWITCH_PIN 23 


// Network Credentials

const char* ssid = "D6 Theatre Guest";
const char* password = "@homecomingcentre!";

// UDP Stuff

WiFiUDP udp;
#define LOCAL_PORT 2000

#define REMOTE_IP "192.168.50.209"
#define REMOTE_PORT 2000

enum color {NONE = 0, 
            YELLOW, 
            RED, 
            BLUE, 
            GREEN };

uint8_t button_pressed = 0;

uint8_t current_yellow_button_value = 1;
uint8_t previous_yellow_button_value = 1;

uint8_t current_red_button_value = 1;
uint8_t previous_red_button_value = 1;
uint8_t red_led_on = 0;

uint8_t current_blue_button_value = 1;
uint8_t previous_blue_button_value = 1;

uint8_t current_green_button_value = 1;
uint8_t previous_green_button_value = 1;

void setup(){
   

    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);

    pinMode(YELLOW_SWITCH_PIN, INPUT_PULLUP);
    pinMode(RED_SWITCH_PIN, INPUT_PULLUP);
    pinMode(BLUE_SWITCH_PIN, INPUT_PULLUP);
    pinMode(GREEN_SWITCH_PIN, INPUT_PULLUP);

    // attachInterrupt(12, interrupt_handle_yellow, FALLING);

     Serial.begin(115200);
 
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting to WiFi Network ..");
 
    while(WiFi.status() != WL_CONNECTED){
       
    }
 
    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());

    Serial.println("\nInitiating UDP");
    udp.begin(WiFi.localIP(), LOCAL_PORT);

    Serial.println("\nSending UDP Packets.");
    
}


void loop(){

    if(Serial.available() > 0)
    {
      char command = Serial.read();
      Serial.println("Command Recieved.");
      if(command == '\n')
      {
        if(red_led_on == 1)
        {
          red_led_on = 0;
        } 
        else 
        {
          red_led_on = 1;
        }
      }
    }
    
    current_yellow_button_value = digitalRead(YELLOW_SWITCH_PIN);
    current_red_button_value = digitalRead(RED_SWITCH_PIN);
    current_blue_button_value = digitalRead(BLUE_SWITCH_PIN);
    current_green_button_value = digitalRead(GREEN_SWITCH_PIN);

    if(!current_yellow_button_value && previous_yellow_button_value)
    {
      button_pressed = YELLOW;
      udp.beginPacket(REMOTE_IP, REMOTE_PORT);
      udp.write(&button_pressed, 1);
      udp.endPacket();
      Serial.println(button_pressed);
      digitalWrite(YELLOW_LED_PIN, HIGH);
      delay(3000);
      digitalWrite(YELLOW_LED_PIN, LOW);
    }
    else if(!current_red_button_value && previous_red_button_value)
    {
      button_pressed = RED;
      udp.beginPacket(REMOTE_IP, REMOTE_PORT);
      udp.write(&button_pressed, 1);
      udp.endPacket();
      Serial.println(button_pressed);
      digitalWrite(RED_LED_PIN, HIGH);
      delay(3000);
      digitalWrite(RED_LED_PIN, LOW);
    }
    else if(!current_blue_button_value && previous_blue_button_value)
    {
      button_pressed = BLUE;
      udp.beginPacket(REMOTE_IP, REMOTE_PORT);
      udp.write(&button_pressed, 1);
      udp.endPacket();
      Serial.println(button_pressed);
      digitalWrite(BLUE_LED_PIN, HIGH);
      delay(3000);
      digitalWrite(BLUE_LED_PIN, LOW);
    }
    else if(!current_green_button_value && previous_green_button_value)
    {
      button_pressed = GREEN;
      udp.beginPacket(REMOTE_IP, REMOTE_PORT);
      udp.write(&button_pressed, 1);
      udp.endPacket();
      Serial.println(button_pressed);
      digitalWrite(GREEN_LED_PIN, HIGH);
      delay(3000);
      digitalWrite(GREEN_LED_PIN, LOW);
    }

  previous_yellow_button_value = current_yellow_button_value;
  previous_red_button_value = current_red_button_value;
  previous_blue_button_value = current_blue_button_value;
  previous_green_button_value = current_green_button_value;
    
}


