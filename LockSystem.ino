//Import Keypad library
#include <Keypad.h>

// Import Arduino servo motor library
#include <Servo.h>

// final values for numeric keypad
const byte rows = 3;
const byte columns = 3;

Servo servoMotor;
char password[] = "84572";
// track password index
int pIndex = 0;

char keys[rows][columns] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'}
};

// Connect row0 to pin 1, row1 to 2...
byte rowPins[rows] = {1,2,3};
// same for columns
byte colPins[columns] = {4,5,6};
// Intialize keypad object
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, rows, columns);

int pinLock = 7;
int pinUnlock = 8;

void setup(){
  pinMode(pinLock, OUTPUT);
  pinMode(pinUnlock, OUTPUT);
  // Pin - can change
  servoMotor.attach(9);
  isLocked(true);
}

void loop(){
  char key = kpd.getKey();

  if(key == password[pIndex]){
    pIndex++;
  }else{
    pIndex = 0;
  }

  if(pIndex == 5){
    isLocked(false);
  }

}

void isLocked(bool locked){

  if(locked){
    digitalWrite(pinLock, HIGH);
    digitalWrite(pinUnlock, LOW);
    servoMotor.write(10);
  }else{
    digitalWrite(pinLock, LOW);
    digitalWrite(pinUnlock, HIGH);
    servoMotor.write(11);
  }
}
