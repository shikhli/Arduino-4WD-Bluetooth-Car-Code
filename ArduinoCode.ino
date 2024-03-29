#include <Dictionary.h>
Dictionary<char, unsigned char*> MyDict;




////////////////////////////////
// MOTOR VARIABLES

int motorsRight_digital = 2;
int motorsLeft_digital = 4;
int motorsRight_analog = 9;
int motorsLeft_analog = 5;

char BTCommand = '0';

float speedButtonValue = 0.5f;

// FOR TANK MODE
float motorR_Value = 0.0f;
int motorR_Pole = 0;
float motorL_Value = 0.0f;
int motorL_Pole = 0;

// FOR NORMAL MODE
float motorFinalPower = 0.0f;
float gas_Value = 0.0f;
int gas_Pole = 0;
int direction_Value = 0;
float direction_Pole = 0.0f;

float motorMaxPower = 255.0f;

bool tankMode = false;

// MOTOR VARIABLES
////////////////////////////////


////////////////////////////////
// LED VARIABLES

//data display from right to left, from bottom to top, HIGH level display.
#define IIC_SCL A5
#define IIC_SDA A4

void IIC_start();
void IIC_send(unsigned char send_data);
void IIC_end();



// ALPHABET
unsigned char char_A[3] = { 0xf0, 0x48, 0xf8 };
unsigned char char_B[3] = { 0xf8, 0xa8, 0x50 };
unsigned char char_C[3] = { 0x70, 0x88, 0x88 };
unsigned char char_D[3] = { 0xf8, 0x88, 0x70 };
unsigned char char_E[3] = { 0xf8, 0xa8, 0x88 };
unsigned char char_F[3] = { 0xf8, 0x28, 0x08 };
unsigned char char_G[3] = { 0xf8, 0x88, 0xe8 };
unsigned char char_H[3] = { 0xf8, 0x20, 0xf8 };
unsigned char char_I[3] = { 0x88, 0xf8, 0x88 };
unsigned char char_J[3] = { 0x48, 0x88, 0x78 };
unsigned char char_K[3] = { 0xf8, 0x20, 0xd8 };
unsigned char char_L[3] = { 0xf8, 0x80, 0xc0 };
unsigned char char_M[3] = { 0xf8, 0x10, 0xf8 };
unsigned char char_N[3] = { 0xf8, 0x08, 0xf0 };
unsigned char char_O[3] = { 0x70, 0x88, 0x70 };
unsigned char char_P[3] = { 0xf8, 0x28, 0x38 };
unsigned char char_Q[3] = { 0x78, 0xc8, 0x78 };
unsigned char char_R[3] = { 0xf8, 0x28, 0xd0 };
unsigned char char_S[3] = { 0xb0, 0xa8, 0x68 };
unsigned char char_T[3] = { 0x08, 0xf8, 0x08 };
unsigned char char_U[3] = { 0xf8, 0x80, 0xf8 };
unsigned char char_V[3] = { 0x78, 0x80, 0x78 };
unsigned char char_W[3] = { 0xf8, 0x40, 0xf8 };
unsigned char char_X[3] = { 0xd8, 0x20, 0xd8 };
unsigned char char_Y[3] = { 0x18, 0xe0, 0x18 };
unsigned char char_Z[3] = { 0xc8, 0xa8, 0x98 };

// NUMBERS
unsigned char char_0[3] = { 0xf8, 0x88, 0xf8 };
unsigned char char_1[3] = { 0x20, 0x10, 0xf8 };
unsigned char char_2[3] = { 0xe8, 0xa8, 0xb8 };
unsigned char char_3[3] = { 0x88, 0xa8, 0xf8 };
unsigned char char_4[3] = { 0x60, 0x50, 0xf8 };
unsigned char char_5[3] = { 0xb8, 0xa8, 0xe8 };
unsigned char char_6[3] = { 0xf0, 0xa8, 0xe8 };
unsigned char char_7[3] = { 0x18, 0x08, 0xf8 };
unsigned char char_8[3] = { 0xf8, 0xa8, 0xf8 };
unsigned char char_9[3] = { 0xb8, 0xa8, 0x78 };

// Symbols
unsigned char char_question[3] = { 0x08, 0xa8, 0x38 };
unsigned char char_dot[3] = { 0x80, 0x00, 0x00 };
unsigned char char_tire[3] = { 0x20, 0x20, 0x20 };

String bt_id;

unsigned char tableEmpty[16] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
};

unsigned char* table = tableEmpty;
bool ledEnabled = true;

// LED VARIABLES
////////////////////////////////


void setup() {

  // BT
  BTaddressReader();

  // MOTORS
  pinMode(motorsRight_analog, OUTPUT);
  pinMode(motorsLeft_analog, OUTPUT);
  pinMode(motorsRight_digital, OUTPUT);
  pinMode(motorsLeft_digital, OUTPUT);
}


void loop() {

  while (Serial.available() > 0) {
    BTCommand = Serial.read();
    Serial.println(BTCommand);

    // FOR SWITCHES
    switch (BTCommand) {
      // LED
      case '.':
        ledEnabled = false;
        ApplyLED();
        break;
      case ',':
        ledEnabled = true;
        ApplyLED();
        break;

      // TANK MODE
      case 't':
        tankMode = false;
        ApplyLED();
        break;
      case 'T':
        tankMode = true;
        ApplyLED();
        break;

      // SPEED MULTIPLIER
      case '[':
        speedButtonValue = 0.5f;
        break;
      case ']':
        speedButtonValue = 1.0f;
        break;
    }

    MotorStuff();
  }
}



void MotorStuff() {
  if (tankMode) {
    switch (BTCommand) {
      case '0':
        motorR_Pole = -1;
        motorR_Value = 1.0f;
        break;
      case '1':
        motorR_Pole = -1;
        motorR_Value = 0.8f;
        break;
      case '2':
        motorR_Pole = -1;
        motorR_Value = 0.6f;
        break;
      case '3':
        motorR_Pole = -1;
        motorR_Value = 0.4f;
        break;
      case '4':
        motorR_Pole = 0;
        motorR_Value = 0;
        break;
      case '5':
        motorR_Pole = 1;
        motorR_Value = 0.4f;
        break;
      case '6':
        motorR_Pole = 1;
        motorR_Value = 0.6f;
        break;
      case '7':
        motorR_Pole = 1;
        motorR_Value = 0.8f;
        break;
      case '8':
        motorR_Pole = 1;
        motorR_Value = 1.0f;
        break;

        //////////////////////////

      case ')':  //0
        motorL_Pole = -1;
        motorL_Value = 1.0f;
        break;
      case '!':  //1
        motorL_Pole = -1;
        motorL_Value = 0.8f;
        break;
      case '@':  //2
        motorL_Pole = -1;
        motorL_Value = 0.6f;
        break;
      case '#':  //3
        motorL_Pole = -1;
        motorL_Value = 0.4f;
        break;
      case '$':  //4
        motorL_Pole = 0;
        motorL_Value = 0;
        break;
      case '%':  //5
        motorL_Pole = 1;
        motorL_Value = 0.4f;
        break;
      case '^':  //6
        motorL_Pole = 1;
        motorL_Value = 0.6f;
        break;
      case '&':  //7
        motorL_Pole = 1;
        motorL_Value = 0.8f;
        break;
      case '*':  //8
        motorL_Pole = 1;
        motorL_Value = 1.0f;
        break;

      default:
        break;
    }
  } else {

    // NORMAL MODE
    switch (BTCommand) {
      case '0':
        gas_Pole = -1;
        gas_Value = 1.0f;
        break;
      case '1':
        gas_Pole = -1;
        gas_Value = 0.8f;
        break;
      case '2':
        gas_Pole = -1;
        gas_Value = 0.6f;
        break;
      case '3':
        gas_Pole = -1;
        gas_Value = 0.4f;
        break;
      case '4':
        gas_Pole = 0;
        gas_Value = 0;
        break;
      case '5':
        gas_Pole = 1;
        gas_Value = 0.4f;
        break;
      case '6':
        gas_Pole = 1;
        gas_Value = 0.6f;
        break;
      case '7':
        gas_Pole = 1;
        gas_Value = 0.8f;
        break;
      case '8':
        gas_Pole = 1;
        gas_Value = 1.0f;
        break;

        //////////////////////////

      case ')':  //0
        direction_Pole = -4;
        direction_Value = 1.0f;
        break;
      case '!':  //1
        direction_Pole = -3;
        direction_Value = 0.5f;
        break;
      case '@':  //2
        direction_Pole = -2;
        direction_Value = 0.0f;
        break;
      case '#':  //3
        direction_Pole = -1;
        direction_Value = 0.5f;
        break;
      case '$':  //4
        direction_Pole = 0;
        direction_Value = 1.0f;
        break;
      case '%':  //5
        direction_Pole = 1;
        direction_Value = 0.5f;
        break;
      case '^':  //6
        direction_Pole = 2;
        direction_Value = 0.0f;
        break;
      case '&':  //7
        direction_Pole = 3;
        direction_Value = 0.5f;
        break;
      case '*':  //8
        direction_Pole = 4;
        direction_Value = 1.0f;
        break;

      default:
        break;
    }
  }



  if (tankMode) {
    TankModeApply();
  } else {
    NormalModeApply();
  }

}



void NormalModeApply() {
  motorFinalPower = motorMaxPower * gas_Value * speedButtonValue;

  // FORWARD
  if (gas_Pole > 0) {

    // FORWARD RIGHT
    if (direction_Pole > 0) {
      digitalWrite(motorsLeft_digital, HIGH);
      analogWrite(motorsLeft_analog, motorFinalPower);

      if (direction_Pole > 2) {
        digitalWrite(motorsRight_digital, LOW);
      } else {
        digitalWrite(motorsRight_digital, HIGH);
      }

      analogWrite(motorsRight_analog, motorFinalPower * direction_Value);
    }

    // FORWARD LEFT
    else if (direction_Pole < 0) {
      digitalWrite(motorsRight_digital, HIGH);
      analogWrite(motorsRight_analog, motorFinalPower);

      if (direction_Pole < -2) {
        digitalWrite(motorsLeft_digital, LOW);
      } else {
        digitalWrite(motorsLeft_digital, HIGH);
      }

      analogWrite(motorsLeft_analog, motorFinalPower * direction_Value);
    }

    // FORWARD STRIGHT
    else {
      digitalWrite(motorsLeft_digital, HIGH);
      digitalWrite(motorsRight_digital, HIGH);
      analogWrite(motorsLeft_analog, motorFinalPower);
      analogWrite(motorsRight_analog, motorFinalPower);
    }
  }



  // BACK
  else if (gas_Pole < 0) {

    // BACK RIGHT
    if (direction_Pole > 0) {
      digitalWrite(motorsLeft_digital, LOW);
      analogWrite(motorsLeft_analog, motorFinalPower);

      if (direction_Pole > 2) {
        digitalWrite(motorsRight_digital, HIGH);
      } else {
        digitalWrite(motorsRight_digital, LOW);
      }

      analogWrite(motorsRight_analog, motorFinalPower * direction_Value);
    }

    // BACK LEFT
    else if (direction_Pole < 0) {
      digitalWrite(motorsRight_digital, LOW);
      analogWrite(motorsRight_analog, motorFinalPower);

      if (direction_Pole < -2) {
        digitalWrite(motorsLeft_digital, HIGH);
      } else {
        digitalWrite(motorsLeft_digital, LOW);
      }

      analogWrite(motorsLeft_analog, motorFinalPower * direction_Value);
    }

    // BACK STRIGHT
    else {
      digitalWrite(motorsRight_digital, LOW);
      digitalWrite(motorsLeft_digital, LOW);
      analogWrite(motorsLeft_analog, motorFinalPower);
      analogWrite(motorsRight_analog, motorFinalPower);
    }

  }


  //STOP
  else {
    analogWrite(motorsRight_analog, 0);
    analogWrite(motorsLeft_analog, 0);
  }
}

void TankModeApply() {

  // LEFT MOTOR
  if (motorL_Pole > 0) {
    digitalWrite(motorsRight_digital, HIGH);
  } else {
    digitalWrite(motorsRight_digital, LOW);
  }
  analogWrite(motorsRight_analog, motorMaxPower * motorL_Value * speedButtonValue);

  // RIGHT MOTOR
  if (motorR_Pole > 0) {
    digitalWrite(motorsLeft_digital, HIGH);
  } else {
    digitalWrite(motorsLeft_digital, LOW);
  }
  analogWrite(motorsLeft_analog, motorMaxPower * motorR_Value * speedButtonValue);

}



void LEDstuff() {
  /**************set the address plus 1***************/
  IIC_start();
  IIC_send(0x40);  // set the address plus 1 automatically
  IIC_end();
  /************end the process of address plus 1 *****************/


  /************set the data display*****************/
  IIC_start();
  IIC_send(0xc0);  // set the initial address as 0

  for (char i = 0; i < 16; i++) {
    IIC_send(table[i]);  // send the display data
  }
  IIC_end();
  /************end the data display*****************/


  /*************set the brightness display***************/
  IIC_start();
  IIC_send(0x8A);  // set the brightness display
  IIC_end();
  /*************end the brightness display***************/
}



// LED FUNCTIONS
void IIC_start() {
  digitalWrite(IIC_SCL, LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA, HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL, HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA, LOW);
  delayMicroseconds(3);
}
void IIC_send(unsigned char send_data) {
  for (char i = 0; i < 8; i++) {
    digitalWrite(IIC_SCL, LOW);
    delayMicroseconds(3);
    if (send_data & 0x01) {
      digitalWrite(IIC_SDA, HIGH);
    } else {
      digitalWrite(IIC_SDA, LOW);
    }
    delayMicroseconds(3);
    digitalWrite(IIC_SCL, HIGH);
    delayMicroseconds(3);
    send_data = send_data >> 1;
  }
}
void IIC_end() {
  digitalWrite(IIC_SCL, LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA, LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL, HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA, HIGH);
  delayMicroseconds(3);
}


// BT MAC TO LED
void BTaddressReader() {
  Serial.begin(9600);  // 9600
  delay(1000);
  Serial.println("AT+ADDR?");  // "AT+ADDR?"

  bt_id = "BT-?";
  unsigned long startedWaiting = millis();
  unsigned long howLongToWait = 2000L;
  while (Serial.available() <= 0 && millis() - startedWaiting <= howLongToWait) {}

  if (Serial.available() > 0) {
    String s = Serial.readString();
    Serial.println(s);
    bt_id = s.substring(s.length() - 6, s.length());
  }

  Serial.println(bt_id);


  // CREATE SYMBOL DICTIONARY
  MyDict.set('0', char_0);
  MyDict.set('1', char_1);
  MyDict.set('2', char_2);
  MyDict.set('3', char_3);
  MyDict.set('4', char_4);
  MyDict.set('5', char_5);
  MyDict.set('6', char_6);
  MyDict.set('7', char_7);
  MyDict.set('8', char_8);
  MyDict.set('9', char_9);

  MyDict.set('A', char_A);
  MyDict.set('B', char_B);
  MyDict.set('C', char_C);
  MyDict.set('D', char_D);
  MyDict.set('E', char_E);
  MyDict.set('F', char_F);
  MyDict.set('G', char_G);
  MyDict.set('H', char_H);
  MyDict.set('I', char_I);
  MyDict.set('J', char_J);
  MyDict.set('K', char_K);
  MyDict.set('L', char_L);
  MyDict.set('M', char_M);
  MyDict.set('N', char_N);
  MyDict.set('O', char_O);
  MyDict.set('P', char_P);
  MyDict.set('Q', char_Q);
  MyDict.set('R', char_R);
  MyDict.set('S', char_S);
  MyDict.set('T', char_T);
  MyDict.set('U', char_U);
  MyDict.set('V', char_V);
  MyDict.set('W', char_W);
  MyDict.set('X', char_X);
  MyDict.set('Y', char_Y);
  MyDict.set('Z', char_Z);

  MyDict.set('?', char_question);
  MyDict.set('.', char_dot);
  MyDict.set('-', char_tire);


  ApplyLED();
}

unsigned char newTable[16];

void ApplyLED() {

  if (ledEnabled) {
    newTable[0] = MyDict.get(bt_id.charAt(0))[0];
    newTable[1] = MyDict.get(bt_id.charAt(0))[1];
    newTable[2] = MyDict.get(bt_id.charAt(0))[2];
    newTable[3] = 0x00;
    newTable[4] = MyDict.get(bt_id.charAt(1))[0];
    newTable[5] = MyDict.get(bt_id.charAt(1))[1];
    newTable[6] = MyDict.get(bt_id.charAt(1))[2];
    newTable[7] = 0x00;
    newTable[8] = 0x00;
    newTable[9] = MyDict.get(bt_id.charAt(2))[0];
    newTable[10] = MyDict.get(bt_id.charAt(2))[1];
    newTable[11] = MyDict.get(bt_id.charAt(2))[2];
    newTable[12] = 0x00;
    newTable[13] = MyDict.get(bt_id.charAt(3))[0];
    newTable[14] = MyDict.get(bt_id.charAt(3))[1];
    newTable[15] = MyDict.get(bt_id.charAt(3))[2];

    table = newTable;
  } else {
    table = tableEmpty;
  }

  pinMode(IIC_SCL, OUTPUT);
  pinMode(IIC_SDA, OUTPUT);
  digitalWrite(IIC_SCL, LOW);
  digitalWrite(IIC_SDA, LOW);

  LEDstuff();
}
