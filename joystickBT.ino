byte ubutts1 = 0;
byte ubutts2 = 0;
int8_t ux = 0;
int8_t uy = 0;

int8_t x = 0;
int8_t y = 0;


void setup() {
  Serial.begin(115200);
  DDRD = B00000000;
  PORTD = B11111100;
  DDRB = B00100000; //no pin 13 because led
  PORTB = B00011111;
  DDRC = B00000000;
  PORTC = B00111111;
  delay(500);

}

void loop() {
  byte butts1 = ~(((PIND & B11111100)>>2) | ((PINB & B00000011)<<6));
  byte butts2 = ((~(PINB & B00011100))>>2) ^ B11111000;
  byte dpad = ~(PINC | B11110000);

  if(dpad&(1<<3)) {
      y=-127;
    }else if(dpad&(1<<1)){
      y=127;
    }else{y=0;}

  if(dpad&(1<<0)) {
      x=-127;
    }else if(dpad&(1<<2)){
      x=127;
    }else{x=0;}

  if(butts1 != ubutts1 || butts2 != ubutts2 || x != ux || y != uy ){

      Serial.write((uint8_t)0xFD);
      Serial.write((uint8_t)0x06);
      Serial.write((uint8_t)x);
      Serial.write((uint8_t)y);
      Serial.write((uint8_t)0x00);
      Serial.write((uint8_t)0x00);
      Serial.write((uint8_t)butts1);
      Serial.write((uint8_t)butts2);
      
      ubutts1=butts1;
      ubutts2=butts2;
      ux=x;
      uy=y;
      delay(15);
    
    }
 /*
  Serial.print("y = ");
  Serial.print(y,DEC);
  Serial.print(" ,");

  Serial.print("x = ");
  Serial.print(x,DEC);
  Serial.print(" ,");
      
  Serial.print(dpad, BIN) ; // prints to monitor
  Serial.print(" - dpad - ");
  Serial.print(dpad,HEX);  // prints to monitor  

  Serial.print(", ");
  Serial.print(butts2, BIN) ; // prints to monitor
  Serial.print(" - botones 2o byte - ");
  Serial.print(butts2,HEX);  // prints to monitor

  Serial.print(", ");
  Serial.print(butts1, BIN) ; // prints to monitor
  Serial.print(" - botones 1er byte - ");
  Serial.println(butts1,HEX);  // prints to monitor
  
  delay(1000);
  */

}


