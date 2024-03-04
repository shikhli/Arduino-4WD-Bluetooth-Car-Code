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
unsigned char messageTable[5][16] = {
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x24, 0xff, 0xdb, 0x7e, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00 },  //     BT
  { 0x00, 0x00, 0x18, 0x24, 0x00, 0x42, 0x24, 0xff, 0xdb, 0x7e, 0x24, 0x00, 0x24, 0x18, 0x00, 0x00 },  //    (BT)
  { 0x3c, 0x42, 0x18, 0x24, 0x00, 0x42, 0x24, 0xff, 0xdb, 0x7e, 0x24, 0x00, 0x24, 0x18, 0x42, 0x3c },  //  (( BT ))
  { 0x3c, 0x42, 0x00, 0x00, 0x00, 0x42, 0x24, 0xff, 0xdb, 0x7e, 0x24, 0x00, 0x00, 0x00, 0x42, 0x3c },  //   ( BT )
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x24, 0xff, 0xdb, 0x7e, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00 }   //     BT
};

unsigned char patternTable[3][16] = {
  { 0xb7, 0xdd, 0x77, 0xfe, 0xdb, 0xee, 0x7f, 0xdb, 0xf7, 0xbd, 0xff, 0xd7, 0x7d, 0xdf, 0xf6, 0x7d },  // Pattern P1
  { 0x77, 0xbd, 0xef, 0xfe, 0xb7, 0xfd, 0x6f, 0xba, 0xdf, 0x7b, 0xfd, 0xaf, 0xf5, 0x7b, 0xff, 0xdd },  // Pattern P2
  { 0xbd, 0xea, 0xff, 0x5b, 0xfd, 0xee, 0xaf, 0xda, 0xf7, 0xbe, 0xe7, 0x7d, 0xef, 0xbf, 0xdb, 0x7e }   // Pattern P3
};

unsigned char fullTable[1][16] = {
  { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }  // Full
};

unsigned char carNumberTable[1][16] = {
  { 0x52, 0xaa, 0x52, 0x02, 0xfa, 0xaa, 0x52, 0x02, 0x22, 0x02, 0xf2, 0x2a, 0xf2, 0x02, 0xaa, 0xfa }  // 8B-A3 (MAC number ending)
};

unsigned char emptyTable[1][16] = {
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }  // Empty
};

int linesCount;

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

bool ledEnabled = false;

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
      IIC_send(messageTable[data_line][i]);  // send the display data
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
