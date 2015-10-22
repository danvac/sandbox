#include <HID-Project.h>
#include <Keypad.h>


// ROWS
#define GREEN
#define BROWN
#define BLUE
#define BLACK
#define RED

// COLUMNS
#define WHITE
#define ORANGE
#define PURPLE
#define GRAY

// BUTTONS
#define TRIGGER     1
#define RELEASE     2
#define MASTER      3
#define NWS         4

#define TMS_UP      5
#define TMS_RIGHT   6
#define TMS_DOWN    7
#define TMS_LEFT    8

#define DMS_UP      9
#define DMS_RIGHT   10
#define DMS_DOWN    11
#define DMS_LEFT    12

#define CMS_UP      13
#define CMS_RIGHT   14
#define CMS_DOWN    15
#define CMS_LEFT    16

#define HAT_UP      17
#define HAT_RIGHT   18
#define HAT_DOWN    19
#define HAT_LEFT    20


const byte ROWS = 4; //four rows
const byte COLS = 5; //three columns

char keys[ROWS][COLS] = {
  {'1','5','9','u','U'},
  {'2','6','0','d','D'},
  {'3','7','A','r','R'},
  {'4','8','B','l','L'},
};

byte rowPins[ROWS] = {4, 6, 5, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 10, 11, 12, 8}; //connect to the column pinouts of the keypad

Keypad joystick = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Gamepad.begin();
  Serial.begin(9600);
  joystick.addEventListener(joystickEvent);
}

void loop(){
  char key = joystick.getKey();

  if (key != NO_KEY){
    Serial.println(key);
  }

  delay(10);
}

void joystickEvent(KeypadEvent button) {
  switch(joystick.getState()) {
    case PRESSED:
      switch(button) {
        case '1':
          Gamepad.press(1);
          break;
        case '2':
          Gamepad.press(2);
          break;
        case '3':
          Gamepad.press(3);
          break;
        case '4':
          Gamepad.press(4);
          break;
        case '5':
          Gamepad.press(5);
          break;
        case '6':
          Gamepad.press(6);
          break;
        case '7':
          Gamepad.press(7);
          break;
        case '8':
          Gamepad.press(8);
          break;
        case '9':
          Gamepad.press(9);
          break;
        case '0':
          Gamepad.press(10);
          break;
        case 'A':
          Gamepad.press(11);
          break;
        case 'B':
          Gamepad.press(12);
          break;
        case 'u':
          Gamepad.press(13);
          break;
        case 'd':
          Gamepad.press(14);
          break;
        case 'r':
          Gamepad.press(15);
          break;
        case 'l':
          Gamepad.press(16);
          break;
        case 'U':
          Gamepad.press(17);
          break;
        case 'D':
          Gamepad.press(18);
          break;
        case 'R':
          Gamepad.press(19);
          break;
        case 'L':
          Gamepad.press(20);
          break;
      }
      break;
    case RELEASED:
      switch(button) {
        case '1':
          Gamepad.release(1);
          break;
        case '2':
          Gamepad.release(2);
          break;
        case '3':
          Gamepad.release(3);
          break;
        case '4':
          Gamepad.release(4);
          break;
        case '5':
          Gamepad.release(5);
          break;
        case '6':
          Gamepad.release(6);
          break;
        case '7':
          Gamepad.release(7);
          break;
        case '8':
          Gamepad.release(8);
          break;
        case '9':
          Gamepad.release(9);
          break;
        case '0':
          Gamepad.release(10);
          break;
        case 'A':
          Gamepad.release(11);
          break;
        case 'B':
          Gamepad.release(12);
          break;
        case 'u':
          Gamepad.release(13);
          break;
        case 'd':
          Gamepad.release(14);
          break;
        case 'r':
          Gamepad.release(15);
          break;
        case 'l':
          Gamepad.release(16);
          break;
        case 'U':
          Gamepad.release(17);
          break;
        case 'D':
          Gamepad.release(18);
          break;
        case 'R':
          Gamepad.release(19);
          break;
        case 'L':
          Gamepad.release(20);
          break;
      }
      break;
  }
  Gamepad.write();
}

