#include <Arduhdlc.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
  #include <avr/boot.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16



#define MAX_HDLC_FRAME_LENGTH 32
void send_character(uint8_t data);

/* Function to handle a valid HDLC frame */
void hdlc_frame_handler(const uint8_t *data, uint16_t length);
void HSV_to_RGB(float h, float s, float v, byte *r, byte *g, byte *b);








// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Arduhdlc hdlc(&send_character, &hdlc_command_router, MAX_HDLC_FRAME_LENGTH);

/* Function to send out one 8bit character */
void send_character(uint8_t data) {
    Serial.print((char)data);
}



enum serial_commands {
    COMMAND_ERROR = 0, // 0
    COMMAND_ECHO,
    COMMAND_READ_SIGNATURE,
    COMMAND_DEMO,
    COMMAND_WHITE_LEVEL,
    COMMAND_COLOR_LEVEL,
};
enum serial_responses {
    RESPONSE_ERROR = 0, // 0
    RESPONSE_VERSION,
    RESPONSE_BUTTON_PRESS,
    RESPONSE_READ_SIGNATURE,
    RESPONSE_ECHO_DATA,
};

int delayval = 500; // delay for half a second


void hdlc_command_router(const uint8_t *framebuffer, uint16_t framelength) {
    
    enum serial_commands command = static_cast<serial_commands>(framebuffer[0]);
    
    switch(command)
    {
        case COMMAND_ERROR: command_error(); break;
        case COMMAND_ECHO: command_echo_data(framebuffer, framelength); break;                               //0x7E 0x01 0x00 0x06 0x1F 0x7E 
        case COMMAND_READ_SIGNATURE:         command_read_signature(framebuffer, framelength); break;
        case COMMAND_DEMO: command_demo(framebuffer, framelength); break;                                    //0x7e 0x03 0x1C 0x3D 0x7E 
        case COMMAND_WHITE_LEVEL: command_white_level(framebuffer, framelength); break;                      // 0x7E 0x04 0x00 0x83 0x4d 0x7E | 0x7E 0x04 0x7F 0xBB 0xFA 0x7E| 0x7E 0x04 0xFF 0x46 0x80 0x7E
        case COMMAND_COLOR_LEVEL: command_color_level(framebuffer, framelength); break;
        default:
        command_default();
        break;
    }
}


// ECHO the data back, for testing CRC sum
void command_echo_data(const uint8_t *framebuffer, uint16_t framelength) {
    hdlc.frameDecode((const char*)framebuffer, framelength);
}

void command_error(void) {
    char data[2] = {(uint8_t)RESPONSE_ERROR, 1};
    //data[0] = RESPONSE_ERROR;
    hdlc.frameDecode(data, 2);
}

void command_read_signature(const uint8_t *framebuffer, uint16_t framelengthd) {
    char signature[4]={1, 2, 3, 4};
    //signature[0] = RESPONSE_READ_SIGNATURE;
    //signature[1] = boot_signature_byte_get(0); //Device Signature Byte 1
    //signature[2] = boot_signature_byte_get(2); //Device Signature Byte 2
    //signature[3] = boot_signature_byte_get(4); //Device Signature Byte 3
    //signature[4] = boot_signature_byte_get(1); //RC Oscillator Calibration Byte
    hdlc.frameDecode(signature, 4);
}

void command_default(void) {
    char data[2] = {(uint8_t)RESPONSE_ERROR, 2};
    //data[0] = RESPONSE_ERROR;
    hdlc.frameDecode(data, 2);
}


void command_demo(const uint8_t *framebuffer, uint16_t framelength) {
  delayval=50;
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  pixels.show();
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(255,0,0));
    pixels.show();
    delay(delayval);
  }
  //for(int i=0;i<NUMPIXELS;i++){
  //  pixels.setPixelColor(i, pixels.Color(0,0,0));
  //}
  //pixels.show();
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(NUMPIXELS-i, pixels.Color(0,255,0));
    pixels.show();
    delay(delayval);
  }
  //for(int i=0;i<NUMPIXELS;i++){
  //  pixels.setPixelColor(i, pixels.Color(0,0,0));
  //}
  //pixels.show();
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,255));
    pixels.show();
    delay(delayval);
  }
  //for(int i=0;i<NUMPIXELS;i++){
  //  pixels.setPixelColor(i, pixels.Color(0,0,0));
  //}
  //pixels.show();
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(255,255,255));
    pixels.show();
    delay(delayval);
  }
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  pixels.show();
  delay(delayval);
  delayval=100;
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(255,0,0));
  }
  pixels.show();
  delay(delayval);
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  pixels.show();
  delay(delayval);
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,255,0));
  }
  pixels.show();
  delay(delayval);
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  pixels.show();
  delay(delayval);
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,255));
  }
  pixels.show();
  delay(delayval);
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  pixels.show();
  delay(delayval);
  

  
}
void command_white_level(const uint8_t *framebuffer, uint16_t framelength) {
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(framebuffer[1],framebuffer[1],framebuffer[1]));
  }
  pixels.show();
  
}
void command_color_level(const uint8_t *framebuffer, uint16_t framelength) {
  byte r, g, b;
  float h, s, v;
  h=framebuffer[1]*1.41;
  s=100;
  v=framebuffer[2]*0.39;

  HSV_to_RGB(h, s, v, &r, &g, &b);
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(r,g,b));
  }
  pixels.show();
}



void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  pinMode(1,OUTPUT); 
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
  Serial.print("System ready");
}


void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  
}

void serialEvent() {
    while (Serial.available()) {
        // get the new byte:
        char inChar = (char)Serial.read();
        hdlc.charReceiver(inChar);
    }
}

void HSV_to_RGB(float h, float s, float v, byte *r, byte *g, byte *b)
{
  float p,q,t,f;
  int i;
  
  h = max(0.0, min(360.0, h));
  s = max(0.0, min(100.0, s));
  v = max(0.0, min(100.0, v));
  
  s /= 100;
  v /= 100;

  
  
  if(s == 0) {
    // Achromatic (grey)
    *r = *g = *b = round(v*255);
    return;
  }

  h /= 60; // sector 0 to 5
  i = floor(h);
  f = h - i; // factorial part of h
  p = v * (1 - s);
  q = v * (1 - s * f);
  t = v * (1 - s * (1 - f));
  
  switch(i) {
    case 0:
      *r = round(255*v);
      *g = round(255*t);
      *b = round(255*p);
      break;
    case 1:
      *r = round(255*q);
      *g = round(255*v);
      *b = round(255*p);
      break;
    case 2:
      *r = round(255*p);
      *g = round(255*v);
      *b = round(255*t);
      break;
    case 3:
      *r = round(255*p);
      *g = round(255*q);
      *b = round(255*v);
      break;
    case 4:
      *r = round(255*t);
      *g = round(255*p);
      *b = round(255*v);
      break;
    default: // case 5:
      *r = round(255*v);
      *g = round(255*p);
      *b = round(255*q);
    }
}


