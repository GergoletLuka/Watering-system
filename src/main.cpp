#include <Arduino.h>

// Define analog pins for sensors
#define plant_0 A0
#define plant_1 A1
#define plant_2 A2

// Define digital pins for motors and LEDs
#define motor_0 2
#define motor_1 3
#define motor_2 4
#define led_0   5
#define led_1   6
#define led_2   7

// Function declarations
void read_data_from_plants(int[]);
void print_data_from_array(int[]);
// Constants - global variables
const int number_of_plants = 3; // Number of plants in the system
const int min_humidity_threshold[number_of_plants] = {500, 500, 500}; // minimum threshold for each plant
const int max_humidity_threshold[number_of_plants] = {800, 800, 800}; // maximum threshold for each plant
int plants_data[number_of_plants]; // Array to store data from 3 plants
int motor_pins[number_of_plants] = {motor_0, motor_1, motor_2}; // Array to store motor pins
int leds[number_of_plants] = {led_0, led_1, led_2};

void setup() {
  // plant sensors
  pinMode(plant_0, INPUT);
  pinMode(plant_1, INPUT);
  pinMode(plant_2, INPUT);
  // motor pins
  pinMode(motor_0, OUTPUT);
  pinMode(motor_1, OUTPUT);
  pinMode(motor_2, OUTPUT);
  // leds
  pinMode(led_0, OUTPUT);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  Serial.begin(115200);

}

void loop() {
  read_data_from_plants(plants_data);
  print_data_from_array(plants_data);

  // Check if the humidity is below the threshold and if needed turn on the motor
  for (int i = 0; i < number_of_plants; i++) {
    // Check the humidity level for each plant
    if((plants_data[i] < max_humidity_threshold[i]) && (plants_data[i] > min_humidity_threshold[i])) {
      digitalWrite(motor_pins[i], HIGH);
      digitalWrite(leds[i], HIGH);
    } else {
      digitalWrite(motor_pins[i], LOW);
      digitalWrite(leds[i], LOW);
    }
    
  //Serial.println(motor_pins[i]);
  }
  delay(1);
}

// Function to read data from all plants
void read_data_from_plants(int data[]) {
  data[0] = analogRead(plant_0);
  data[1] = analogRead(plant_1);
  data[2] = analogRead(plant_2);
}

void print_data_from_array(int data[]) {
  for (int i = 0; i < number_of_plants; i++) {
    Serial.print("Plant ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(data[i]);
    Serial.println();
  }

}
