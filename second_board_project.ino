//Buzzers
int Buzzer1 = 4;
int Buzzer2 = 5;

//LEDs
int trigPin = 8;
int echoPin = 9;

int nano = 10;

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(Buzzer1, OUTPUT);
    pinMode(Buzzer2, OUTPUT);
    pinMode(nano, INPUT);
    digitalWrite(Buzzer1, LOW);
    digitalWrite(Buzzer2, LOW);
}

void loop() {
    if (digitalRead(nano) == HIGH) {
        ReverseCam();
    } else {
        digitalWrite(Buzzer1, LOW);
        digitalWrite(Buzzer2, LOW);
    }
}


int MeasureDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    unsigned long duration = pulseIn(echoPin, HIGH);
    unsigned long distance_cm = duration * 0.0343 / 2; // Speed in cm/µs

    delay(50);
    return distance_cm;
}

void ReverseCam() {
    int distance = MeasureDistance(); // Measure distance once

    if (distance <= 50 && distance > 20) {
        digitalWrite(Buzzer1, HIGH);
        digitalWrite(Buzzer2, HIGH);
        delay(100);
        digitalWrite(Buzzer1, LOW);
        digitalWrite(Buzzer2, LOW);
        delay(1000); // Longer spacing between beeps
    } else if (distance <= 20 && distance > 10) {
        digitalWrite(Buzzer1, HIGH);
        digitalWrite(Buzzer2, HIGH);
        delay(100);
        digitalWrite(Buzzer1, LOW);
        digitalWrite(Buzzer2, LOW);
        delay(500);  // Mid-range spacing
    } else if (distance <= 15 && distance >= 7) {
        digitalWrite(Buzzer1, HIGH);
        digitalWrite(Buzzer2, HIGH);
        delay(100);
        digitalWrite(Buzzer1, LOW);
        digitalWrite(Buzzer2, LOW);
        delay(100); // Short spacing for close proximity
    } else if (distance < 7) {
        digitalWrite(Buzzer1, HIGH);
        digitalWrite(Buzzer2, HIGH);
        delay(50);
    } else {
        digitalWrite(Buzzer1, LOW);
        digitalWrite(Buzzer2, LOW);
    }
}
