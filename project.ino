// this is the source code for the RC Car group project made by the Delta university students:

// Name:                  ID:
// Ahmed Salah El Kadii   1221196
// Ahmed Mahmoud Gamal    1221282
// Zeyad Tarek Serag      1221083
// Lina Mohamed Fouad     1221158
//
// description:
// This code is for the Arduino Uno that is used to control the RC Car, it receives commands from the HC-05 Bluetooth module and controls the motors accordingly.
//
// features
// 1- The car can move forwards, backwards, left, right, and stop.
// 2- The car can move at different speeds.
// 3- The car can have its reverse mode disabled.
// 4- The car has backup LEDs that turn on when the car is moving backwards.
// 5- The car has a backup sensor that can detect an obstacle behind it (check the uno code).

//MotorsA&B
int motorPin1 = 4;
int motorPin2 = 5;
int enableA = 9;
//MotorsC&D
int motorPin3 = 6;
int motorPin4 = 7;
int enableB = 10;

// Both motors on each side would be connected in parallel to the same pins, the car would move similar to a tank

//BackUp LEDS
int LED1 = 12;
int LED2 = 13;

//Variables
int distance = 0;
int speedA = 80;
int speedB = 90;
int direction = 0; // Variable to store the direction of the car, 1 means forwards and -1 means backwards 0 means stopped
int arduinoUno = 2;

void setup() {
    Serial.begin(9600); //Initializing a serial connection between the arduinoand the HC-05
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
    pinMode(arduinoUno, OUTPUT);
    pinMode(enableA, OUTPUT);
    pinMode(enableB, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    analogWrite(enableA, speedA);
    analogWrite(enableB, speedB);
}

void loop() {
    char input; // Variable to store Bluetooth input

    if (Serial.available() > 0) {
        input = Serial.read(); // Read Bluetooth input
        if (input == 'B') {
            speedA = 65;
            speedB = 55;
            analogWrite(enableA, speedA);
            analogWrite(enableB, speedB);
        } else if (input != 'X' && input != 'x') {
            speedA = 80;
            speedB = 90;
            analogWrite(enableA, speedA);
            analogWrite(enableB, speedB);
        }
        switch (input) {
            case 'X':
                speedA = 130;
                speedB = 140;
                digitalWrite(arduinoUno, LOW);
                analogWrite(enableA, speedA);
                analogWrite(enableB, speedB);
                break;
            case 'x':
                speedA = 80;
                speedB = 90;
                digitalWrite(arduinoUno, LOW);
                analogWrite(enableA, speedA);
                analogWrite(enableB, speedB);
                break;
            case 'F':
                digitalWrite(LED1, LOW);
                digitalWrite(LED2, LOW);
                digitalWrite(arduinoUno, LOW);
                Move(1, 1);
                break;
            case 'B':
                digitalWrite(LED1, HIGH);
                digitalWrite(LED2, HIGH);
                Move(-1, -1);
                digitalWrite(arduinoUno, HIGH);
                break;
            case 'L':
                digitalWrite(LED1, LOW);
                digitalWrite(LED2, LOW);
                digitalWrite(arduinoUno, LOW);
                Move(1, -1);
                break;
            case 'R':
                digitalWrite(LED1, LOW);
                digitalWrite(LED2, LOW);
                digitalWrite(arduinoUno, LOW);
                Move(-1, 1);
                break;
            case 'S':
                digitalWrite(LED1, LOW);
                digitalWrite(LED2, LOW);
                digitalWrite(arduinoUno, LOW);
                Move(0, 0);
                break;
            default:
                break;
        }
    } else {
        input = 'S'; // Default to 'S' if no input
    }
}

void Move(int directionL, int directionR) {
    if (directionL == 1) {
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
    } else if (directionL == -1) {
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
    } else {
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, LOW);
    }

    if (directionR == 1) {
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, LOW);
    } else if (directionR == -1) {
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, HIGH);
    } else {
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, LOW);
    }

    if (directionL == 0 && directionR == 0) direction = 0;
    else if (directionL == 1 && directionR == 1) direction = 1;
    else if (directionL == -1 && directionR == -1) direction = -1;
}

