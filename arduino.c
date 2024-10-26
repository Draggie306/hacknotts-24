#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11
#define LED_STRIP_PIN 6 // Define the pin connected to the LED strip

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
long a;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);             // init baud rate
    delay(1000);                    //   hold on, wait a sec
    pinMode(LED_STRIP_PIN, OUTPUT); // Set the LED strip pin as an output
}

void loop()
{
    int delay_time_interval = 1000;
    // put your main code here, to run repeatedly:
    a = sr04.Distance(); // Corrected line

    process_distance(a);

    pulse_lights();

    // Reread data from ultrasonic sensor every second (or whatever the value is in ms)
    delay(delay_time_interval);
}

void process_distance(int distance)
{
    Serial.println("\n\n");
    // Case for the distance being zero
    if (distance == 0)
    {
        Serial.println("[process_distance] :: WARN: No object detected");
    }
    else if (distance < 10)
    {
        Serial.println("[process_distance] :: Object is very close!");
    }
    else if (distance < 100)
    {
        Serial.println("[process_distance] :: Object is close");
    }
    else if (distance < 200)
    {
        Serial.println("[process_distance] :: Object is fairly far");
    }
    else if (distance < 500)
    {
        Serial.println("[process_distance] :: Object is far");
    }
    else if (distance < 1000)
    { // this is the limit for the sensor
        Serial.println("[process_distance] :: Object is out of range");
    }

    Serial.print("[process_distance/DEBUG] :: Distance: ");
    Serial.print(distance);
    Serial.println(" cm\n\n");
}

void pulse_lights()
{
    for (int brightness = 0; brightness <= 255; brightness++)
    {
        analogWrite(LED_STRIP_PIN, brightness);
        delay(10); // Adjust delay for pulsing speed
    }
    for (int brightness = 255; brightness >= 0; brightness--)
    {
        analogWrite(LED_STRIP_PIN, brightness);
        delay(10); // Adjust delay for pulsing speed
    }
}

void generate_sounds_and_control_lights(int distance)
{
    if (distance < 10)
    {
        tone(8, 1000, 1000);
        digitalWrite(13, HIGH);
        pulse_lights(); // Call the pulse lights function
    }
    else
    {
        noTone(8);
        digitalWrite(13, LOW);
        analogWrite(LED_STRIP_PIN, 0); // Turn off the LED strip
    }
}