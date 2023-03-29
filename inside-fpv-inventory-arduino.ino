#include <Arduino.h>
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale;

int trigPin1 = A0;
int echoPin1 = A1;
int trigPin2 = A2;
int echoPin2 = A3;
int trigPin3 = A4;
int echoPin3 = A5;
long empty_row_length = 43;
long box_width = 9;
long motor_weight = 35.5;

void setup() {
  Serial.begin(9600);

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  // Serial.println(scale.read());    \\  // print a raw reading from the ADC
  scale.read();

  // Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC
  scale.read_average(20);

  // Serial.println(scale.get_value(5));
  scale.get_value(5);   

  // Serial.println(scale.get_units(5), 1); 
  scale.get_units(5);

  scale.set_scale(312.5);
  //scale.set_scale(-471.497);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0


  // Serial.println(scale.read());                 // print a raw reading from the ADC
  scale.read(); 

  // Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC
  scale.read_average(20);

  // Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()
  scale.get_value(5);

  // Serial.println(scale.get_units(5), 1); 
  scale.get_units(5);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
}

void loop() {
  double total_weight = scale.get_units();
  

  // Serial.println(scale.get_units(), 1);

  int x = frames();
  //Serial.println("total frames : " + String(x));

  int y = drones1();
  int z = drones2();
  
  //Serial.println("total drones : " + String(tot));

  int m = (total_weight-5)/motor_weight;
  //Serial.println("total motors : " + String(m));

  // Serial.println("frames : " + String(x) + "  Drones1 : " + String(y) + "  Drones2 : " + String(z) + "  motors : " + String(m));
  // Serial.println(String(x) + "," + String(y) + ","+ String(z) + "," + String(m));
  String total = String(x) + "," + String(y) + ","+ String(z) + "," + String(m);
  Serial.println(total);


  delay(5000);
}

int frames() {
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  long duration1 = pulseIn(echoPin1, HIGH);
  long rem_len1 = duration1 * 0.0343 / 2;
  float tot_box_len1 = empty_row_length - rem_len1;
  int boxes1 = tot_box_len1 / box_width;
  return boxes1;
}

int drones1() {
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  long duration2 = pulseIn(echoPin2, HIGH);
  long rem_len2 = duration2 * 0.0343 / 2;
  float tot_box_len2 = empty_row_length - rem_len2;
  int boxes2 = tot_box_len2 / box_width;
  return boxes2;
}

int drones2() {
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  long duration3 = pulseIn(echoPin3, HIGH);
  long rem_len3 = duration3 * 0.0343 / 2;
  float tot_box_len3 = empty_row_length - rem_len3;
  int boxes3 = tot_box_len3 / box_width;
  return boxes3;
}