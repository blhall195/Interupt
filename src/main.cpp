#include <Arduino.h>

#define LED_PIN LED_BUILTIN
#define BUTTON_PIN 12

volatile bool interrupt_button_pressed = 0;
volatile bool interrupt_button_released = 0;
volatile bool interrupt_button_pressed_timer = 0;
unsigned long timer_start = 0;
unsigned long current_time = 0;
unsigned long interval = 3000;

void LED_Low()
{
  digitalWrite(LED_PIN, LOW);
}

void LED_High()
{
  digitalWrite(LED_PIN, HIGH);
}

void LED_Flash()
{
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  delay(100);
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  delay(100);
}

void button_pressed()
{
  if (digitalRead(BUTTON_PIN) == 0)
  {
    interrupt_button_pressed = 1;
    interrupt_button_pressed_timer = 1;
  }
  else
  {
    interrupt_button_pressed = 0;
    interrupt_button_released = 1;
  }
}

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), button_pressed, CHANGE);
}

void loop()
{

  // add if statment to say when to take reading

  // this is if the user holds down the button
  while (interrupt_button_pressed == 1)
  {
    if (interrupt_button_pressed_timer == 1)
    {
      timer_start = millis();
      interrupt_button_pressed_timer = 0;
    }
    current_time = millis();
    Serial.println(current_time - timer_start);

    if (current_time - timer_start > interval)
    {
      break;
    }
  }

  if (current_time - timer_start > interval)
  {
    LED_Flash(); // replace with get/save/broadcast measurement
  }

  current_time = millis();
  timer_start = millis();

  delay(100);
}
