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
    delay(333);                    //   hold on, wait a sec
    //pinMode(LED_STRIP_PIN, OUTPUT); // Set the LED strip pin as an output

    determine_pins_connected();
}

void loop(void)
{
    int delay_time_interval = 1000;
    // put your main code here, to run repeatedly:
    a = sr04.Distance(); // Corrected line

    process_distance(a);

    //pulse_lights();

    // Reread data from ultrasonic sensor every second (or whatever the value is in ms)
    delay(delay_time_interval);

    //generate_sounds_and_control_lights(a);
}

void process_distance(int distance)
{
    // shouldTrigger is flag that is used to control lights or other things.
    int shouldTrigger = 1;
    Serial.print("[process_distance] :: Raw_Distance: ");
    Serial.print(distance);

    Serial.println("\n\n");
    // Case for the distance being zero
    if (distance == 0)
    {
        Serial.println("[process_distance] :: WARN: No object detected");
        shouldTrigger = 0;
        Serial.println("cmd:DISTANCE_ZERO");
    }
    else if (distance < 10)
    {
        Serial.println("[process_distance] :: Object is very close!");
        Serial.println("cmd:DISTANCE_VERY_CLOSE");
    }
    else if (distance < 100)
    {
        Serial.println("[process_distance] :: Object is close");
        Serial.println("cmd:DISTANCE_CLOSE");
    }
    else if (distance < 200)
    {
        Serial.println("[process_distance] :: Object is fairly far");
        Serial.println("cmd:DISTANCE_FAR");
    }
    else if (distance < 500)
    {
        Serial.println("[process_distance] :: Object is far");
        Serial.println("cmd:DISTANCE_VERY_FAR");
    }
    else if (distance < 1000)
    { // this is the limit for the sensor
        Serial.println("[process_distance] :: Object is out of range");
        shouldTrigger = 0;
        Serial.println("cmd:DISTANCE_OUT_OF_RANGE");
    }

    if (shouldTrigger == 1)
    {
        Serial.print("[process_distance/DEBUG] :: Distance: ");
        Serial.print(distance);
        Serial.println(" cm\n\n");
    }
}

void pulse_lights(void)
{
    Serial.println("[pulse_lights] :: entered func");
    for (int brightness = 0; brightness <= 255; brightness++)
    {
        //Serial.print("[pulse_lights] :: adjusting brightness...");
        analogWrite(LED_STRIP_PIN, brightness);
        delay(10); // Adjust delay for pulsing speed
    }
    for (int brightness = 255; brightness >= 0; brightness--)
    {
        analogWrite(LED_STRIP_PIN, brightness);
        delay(10); // Adjust delay for pulsing speed
    }
}


/*
    Should output sound from the speaker.
*/
void generate_sounds_and_control_lights(int distance)
{
    Serial.println("[generate_sounds_and_control_lights] :: entered func");
    if (distance < 10)
    {
        Serial.println("[generate_sounds_and_control_lights] :: Case for distance < 10");
        //tone(8, 1000, 1000);
        digitalWrite(LED_STRIP_PIN, HIGH); // turns on LED.
        pulse_lights();
    }
    else
    {
        Serial.println("[generate_sounds_and_control_lights] :: Case for distance >= 10");
        // noTone(8);
        digitalWrite(LED_STRIP_PIN, LOW);
        analogWrite(LED_STRIP_PIN, 0); // Turn off the LED strip
    }
}


void determine_pins_connected(void) {
    int pins_to_check[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int num_pins = sizeof(pins_to_check) / sizeof(pins_to_check[0]);

    Serial.println("=-=-=-=-=-=-= Checking pins...\n\n");

    // read state of all pins
    for (int i = 0; i < num_pins; i++)
    {
        pinMode(pins_to_check[i], INPUT);
        int state = digitalRead(pins_to_check[i]);
        Serial.print("Pin ");
        Serial.print(pins_to_check[i]);
        Serial.print(" is ");
        Serial.println(state == HIGH ? "HIGH" : "LOW");
        Serial.println("\n");
    }

    Serial.println("=-=-=-=-=-=-= Done checking pins\n\n");

    pinMode(LED_STRIP_PIN, OUTPUT); // Set the LED strip
}