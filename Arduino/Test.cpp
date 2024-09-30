// For testing all the components of the Trash Can togther
#include <Servo.h>

#define trigPin 9  // HC-SR04 Trig pin
#define echoPin 10 // HC-SR04 Echo pin
#define relayPin 7 // Relay pin

long duration;
int distance;
unsigned long lastDetectionTime = 0;  // To store the last time object was detected
bool relayState = false;              // Track the current state of the relay

Servo myServo;  // Create a Servo object

void setup() {
  pinMode(trigPin, OUTPUT);  // Set trigPin as an output
  pinMode(echoPin, INPUT);   // Set echoPin as an input
  pinMode(relayPin, OUTPUT); // Set relayPin as an output
  // Initialize the servo motor
  myServo.attach(6);  // Attach the servo to pin 6
  myServo.write(0);   // Initial position of the servo
  // Ensure the relay is off by default
  digitalWrite(relayPin, LOW); // Relay off (assuming active low)
  Serial.begin(9600); // Start the serial communication for debugging
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Set the trigPin high for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the echoPin, which returns the time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;
  // Print the distance to the Serial Monitor
  // Serial.print("Distance: ");
  // Serial.println(distance);

  // If the distance is less than or equal to 10 cm, immediately activate the relay and move the servo
  if (distance <= 10) {
    digitalWrite(relayPin, HIGH);  // Activate the relay
    myServo.write(180);             // Move the servo to 90 degrees
    relayState = true;             // Mark the relay as active
    lastDetectionTime = millis();  // Reset the timer to the current time
    Serial.println("Relay Active");
  } 
  
  // If the distance is greater than 10 cm and the relay is active
  else if (relayState && (millis() - lastDetectionTime >= 3000)) {
    digitalWrite(relayPin, LOW);   // Deactivate the relay after  seconds
    myServo.write(0);              // Move the servo back to 0 degrees
    relayState = false;            // Mark the relay as inactive
    Serial.println("Relay Deactive");
  }

  delay(100); // Small delay to prevent rapid switching
}
