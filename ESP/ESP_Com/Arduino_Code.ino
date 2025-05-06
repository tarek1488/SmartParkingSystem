#include <AccelStepper.h>

#define STEPMODE 4  // FULLSTEP for 28BYJ-48

// Motor Driver Pins
#define IN1 11    // D1
#define IN2  10   // D2
#define IN3 9    // D5
#define IN4 8    // D6
#define IR_PIN 7  // D7 - IR sensor pin
#define OUT1 6    // D1
#define OUT2  5   // D2
#define OUT3 4    // D5
#define OUT4 3    // D6
#define IR_PINO 2 // D7 - IR sensor pin

const int numberStepsPerRev = 256*2; // Half revolution for open/close
AccelStepper myStepper(STEPMODE, IN1, IN3, IN2, IN4);
AccelStepper mySteppero(STEPMODE, OUT1, OUT3, OUT2, OUT4);

bool gateIsUp = false;
bool gateIsUpO = false;


// 
bool isFull = true;
char str;

void setup() {
  Serial.begin(9600);
  pinMode(IR_PIN, INPUT);
  pinMode(IR_PINO, INPUT);

  myStepper.setMaxSpeed(600.0);
  myStepper.setAcceleration(100.0);
  myStepper.setSpeed(300.0);
  myStepper.moveTo(0); // Start with gate down

  mySteppero.setMaxSpeed(600.0);
  mySteppero.setAcceleration(100.0);
  mySteppero.setSpeed(300.0);
  mySteppero.moveTo(0); // Start with gate down


}

void loop() {

  //COMM
  receive();

  
  bool carDetected = digitalRead(IR_PIN) == LOW;
  bool carDetected_o = digitalRead(IR_PINO) == LOW;

  // Logic for the first gate (myStepper)
  if (carDetected && !gateIsUp && myStepper.distanceToGo() == 0 && !isFull) {
    // Car arrived & gate is down: open gate (move up)
    myStepper.moveTo(numberStepsPerRev);  // Move up (define your "up" position)
    gateIsUp = true;
  } else if (!carDetected && gateIsUp && myStepper.distanceToGo() == 0) {
    // Car left & gate is up: close gate (move down)
    myStepper.moveTo(0);  // Move back to horizontal position
    gateIsUp = false;
  }

  // Logic for the second gate (mySteppero)
  if (carDetected_o && !gateIsUpO && mySteppero.distanceToGo() == 0) {
    // Car left & gate is down: open gate (move up)
    mySteppero.moveTo(-numberStepsPerRev);  // Move up (define your "up" position)
    gateIsUpO = true;
  } else if (!carDetected_o && gateIsUpO && mySteppero.distanceToGo() == 0) {
    // Car arrived & gate is up: close gate (move down)
    mySteppero.moveTo(0);  // Move back to horizontal position
    gateIsUpO = false;
  }

  // Run motors to their respective target positions
  myStepper.run();  
  mySteppero.run();  
}


// Function to receive flag
void receive() {
  //Checking is any data is coming from Esp8266
  if (Serial.available()) {
    str = Serial.read();
    Serial.println(str);
    Serial.flush();//Clearing all Serial print

    Serial.print("isFull: ");
    if (str ==116) {
        isFull = true;
    } else if (str == 102){
        isFull = false;
    }
    else{
      Serial.println("failed");
    }
    Serial.println(isFull);
  }

}