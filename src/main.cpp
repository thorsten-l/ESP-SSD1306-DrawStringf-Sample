#include <Arduino.h>
#include <SSD1306Wire.h>

SSD1306Wire display(0x3c, SDA, SCL, GEOMETRY_64_48 );

static char binary_c_str[9];
static char buffer[32];
static uint8_t counter;

char *uint8tobinarycstr( uint8_t value )
{
  for( int i= 7; i>=0; i-- )
  {
    binary_c_str[i] = (( value & 1 ) == 1 ) ? '1': '0';
    value >>= 1;
  }
  return binary_c_str;
}

void setup() {
  Serial.begin(115200);
  delay(3000); // wait for Monitor
  binary_c_str[8] = 0; // a C string is terminated by null/zero;
  counter = 0;
  display.init();
  display.flipScreenVertically();
}

void loop() {
  Serial.printf( "d=%d u=%u h=%02X b=%s\n", (int8_t)counter, 
    counter, counter, uint8tobinarycstr(counter) );
  display.clear();
  display.drawStringf( 0,  0, buffer, "d=%d", (int8_t)counter ); // signed 8bit integer
  display.drawStringf( 0, 12, buffer, "u=%u", counter ); // unsigned 8bit integer
  display.drawStringf( 0, 24, buffer, "h=%02X", counter ); // hex 
  display.drawStringf( 0, 36, buffer, "b=%s", uint8tobinarycstr(counter)); // binary
                           // ^^^^^^ shared buffer to save memory
  display.display();
  delay( 250 );
  counter++;
}
