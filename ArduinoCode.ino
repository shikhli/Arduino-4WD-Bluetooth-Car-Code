int motorsRight_analog = 9;
int motorsRight_digital = 2;

int motorsLeft_analog = 5;
int motorsLeft_digital = 4;

char BTCommand = 'S';
int motorPower = 0;
float directionValue = 1.0f;

int dirLR = 0;
int dirFB = 0;


////////////////////////////////
// LED VARIABLES

//data display from right to left, from bottom to top, HIGH level display.
#define IIC_SCL A5
#define IIC_SDA A4

unsigned char data_line = 0;
unsigned char delay_count = 0;
unsigned char data_display1 = 0;
unsigned char data_display2 = 0;
unsigned char data_display3 = 0;
unsigned char data_display4 = 0;
unsigned char data_display5 = 0;
unsigned char data_display6 = 0;
unsigned char data_display7 = 0;
unsigned char data_display8 = 0;
unsigned char data_display9 = 0;
unsigned char data_display10 = 0;
unsigned char data_display11 = 0;
unsigned char data_display12 = 0;
unsigned char data_display13 = 0;
unsigned char data_display14 = 0;
unsigned char data_display15 = 0;
unsigned char data_display16 = 0;

void IIC_start();
void IIC_send(unsigned char send_data);
void IIC_end();

unsigned char table[5][16] = {
  // { 0x00, 0x00, 0x00, 0x00, 0xde, 0xdf, 0x99, 0x99, 0x99, 0xfb, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00 }, // S
  // { 0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0xff, 0xff, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00 }, // T
  // { 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x99, 0x99, 0x99, 0x99, 0x81, 0xc3, 0x00, 0x00, 0x00, 0x00 }, // E
  // { 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x19, 0x19, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00 }, // A
  // { 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x07, 0xfe, 0xfe, 0x07, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00 }  // M

  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Empty
  { 0xce, 0x91, 0x91, 0x91, 0x76, 0x00, 0xfe, 0x11, 0x11, 0x11, 0xfe, 0x00, 0xff, 0x11, 0x11, 0x03 },  // SAF
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Empty
  { 0xfb, 0x89, 0xcf, 0x00, 0xff, 0x81, 0xff, 0x00, 0xfb, 0x89, 0xcf, 0x00, 0x3c, 0x22, 0xff, 0x20 },  // 2024
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Empty
};

unsigned char emptyTable[1][16] = {
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Empty
};

int linesCount;
bool ledEnabled = false;
// LED VARIABLES
////////////////////////////////




void setup() {
  Serial.begin(9600);

  pinMode(motorsRight_analog, OUTPUT);
  pinMode(motorsLeft_analog, OUTPUT);
  pinMode(motorsRight_digital, OUTPUT);
  pinMode(motorsLeft_digital, OUTPUT);

  // LED SETUP
  pinMode(IIC_SCL, OUTPUT);
  pinMode(IIC_SDA, OUTPUT);
  digitalWrite(IIC_SCL, LOW);
  digitalWrite(IIC_SDA, LOW);
}



void loop() {

  LEDstuff();

  while (Serial.available() > 0) {
    BTCommand = Serial.read();
    Serial.println(BTCommand);


    switch (BTCommand) {

      // LED
      case 'O':
        ledEnabled = false;
        break;
      case 'I':
        ledEnabled = true;
        break;


      // MOTORS
      case '0':
        dirFB = -1;
        motorPower = 255;
        break;
      case '1':
        dirFB = -1;
        motorPower = 200;
        break;
      case '2':
        dirFB = -1;
        motorPower = 155;
        break;
      case '3':
        dirFB = -1;
        motorPower = 100;
        break;
      case '4':
        motorPower = 0;
        dirFB = 0;
        break;
      case '5':
        dirFB = 1;
        motorPower = 100;
        break;
      case '6':
        dirFB = 1;
        motorPower = 155;
        break;
      case '7':
        dirFB = 1;
        motorPower = 200;
        break;
      case '8':
        dirFB = 1;
        motorPower = 255;
        break;







      case ')':  //0
        dirLR = -4;
        directionValue = 0.0f;
        break;
      case '!':  //1
        dirLR = -3;
        directionValue = 0.25f;
        break;
      case '@':  //2
        dirLR = -2;
        directionValue = 0.5f;
        break;
      case '#':  //3
        dirLR = -1;
        directionValue = 0.75f;
        break;
      case '$':  //4
        dirLR = 0;
        directionValue = 1.0f;
        break;
      case '%':  //5
        dirLR = 1;
        directionValue = 0.75f;
        break;
      case '^':  //6
        dirLR = 2;
        directionValue = 0.5f;
        break;
      case '&':  //7
        dirLR = 3;
        directionValue = 0.25f;
        break;
      case '*':  //8
        dirLR = 4;
        directionValue = 0.0f;
        break;

      default:
        break;
    }


    // FORWARD
    if (dirFB > 0) {
      // FORWARD RIGHT
      if (dirLR > 0) {
        digitalWrite(motorsLeft_digital, HIGH);
        digitalWrite(motorsRight_digital, HIGH);
        analogWrite(motorsLeft_analog, motorPower);
        analogWrite(motorsRight_analog, motorPower * directionValue);
      }
      // FORWARD LEFT
      else if (dirLR < 0) {
        digitalWrite(motorsRight_digital, HIGH);
        digitalWrite(motorsLeft_digital, HIGH);
        analogWrite(motorsRight_analog, motorPower);
        analogWrite(motorsLeft_analog, motorPower * directionValue);
      }
      // FORWARD STRIGHT
      else {
        digitalWrite(motorsLeft_digital, HIGH);
        analogWrite(motorsLeft_analog, motorPower);
        digitalWrite(motorsRight_digital, HIGH);
        analogWrite(motorsRight_analog, motorPower);
      }
    }



    // BACK
    else if (dirFB < 0) {
      // BACK RIGHT
      if (dirLR > 0) {
        digitalWrite(motorsLeft_digital, LOW);
        analogWrite(motorsLeft_analog, motorPower);  // 100%

        if (dirLR < 2) {
          digitalWrite(motorsRight_digital, LOW);
        } else {
          digitalWrite(motorsRight_digital, HIGH);
        }
        analogWrite(motorsRight_analog, motorPower * directionValue);
      }

      // BACK LEFT
      else if (dirLR < 0) {
        digitalWrite(motorsRight_digital, LOW);
        analogWrite(motorsRight_analog, motorPower);  // 100%

        if (dirLR > -2) {
          digitalWrite(motorsLeft_digital, LOW);
        } else {
          digitalWrite(motorsLeft_digital, HIGH);
        }
        analogWrite(motorsLeft_analog, motorPower * directionValue);
      }

      // BACK STRIGHT
      else {
        digitalWrite(motorsLeft_digital, LOW);
        analogWrite(motorsLeft_analog, motorPower);
        digitalWrite(motorsRight_digital, LOW);
        analogWrite(motorsRight_analog, motorPower);
      }
    }

    //STOP
    else {
      analogWrite(motorsRight_analog, 0);
      analogWrite(motorsLeft_analog, 0);
    }
  }
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


  if (ledEnabled) {
    for (char i = 0; i < 16; i++) {
      IIC_send(table[data_line][i]);  // send the display data
    }
    linesCount = 5;
  } else {
    for (char i = 0; i < 16; i++) {
      IIC_send(emptyTable[data_line][i]);  // send the display data
    }
    linesCount = 1;
  }

  if (++delay_count >= 10) {
    delay_count = 0;
    data_line++;
    if (data_line >= linesCount) {
      data_line = 0;
    }
  }


  IIC_end();
  /************end the data display*****************/
  /*************set the brightness display***************/
  IIC_start();
  IIC_send(0x8A);  // set the brightness display
  IIC_end();
  /*************end the brightness display***************/
  delay(100);
}



// LED STUFF
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