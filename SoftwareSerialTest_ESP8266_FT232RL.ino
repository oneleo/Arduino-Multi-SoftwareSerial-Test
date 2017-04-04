# include <SoftwareSerial.h>

// Set SoftwareSerial to wifi ESP8266.
SoftwareSerial wifiSerial ( 2, 3 ); // RX: D2, TX: D3

// Set SoftwareSerial to ttl FT232RL.
SoftwareSerial ttlSerial ( 10, 11 ); // RX: D10, TX: D11

void setup ( )
  {
    // Given a Baud Rate for Arduino Serial Port ( D1, D0 )
    Serial.begin ( 9600 );
    // Waiting for Arduino Serial ready.
    while ( Serial.available ( ) != false )
      {
        ; // wait for serial port to connect. Needed for native USB port only
      }
    Serial.println ( "Serial available!" );
    
    wifiSerial.begin ( 9600 );
    while ( wifiSerial.available ( ) != false )
      {
        ; // wait for serial port to connect. Needed for native USB port only
      }
    wifiSerial.listen ( );
    Serial.println ( "wifiSerial available!" );

    ttlSerial.begin ( 9600 );
    while ( ttlSerial.available ( ) != false )
      {
        ; // wait for serial port to connect. Needed for native USB port only
      }
    ttlSerial.listen ( );
    Serial.println ( "ttlSerial available!" );
  }

void loop ( )
  {

    while ( Serial.available ( ) > 0 )
      {
        byte inByte = Serial.read ( );
        // Because use the multiple Software Serial Port, have to delay sometime to read
        // Otherwise, will get non-complite byte data.
        delay ( 20 );
        // write a byte ( 8 bits: 0 ~ 255 ); Compare to the char is 8 bits: -128 ~ 127
        wifiSerial.write ( inByte );        
        ttlSerial.write ( inByte );
      }

    // Key point: because I use multiple SoftwareSerial, listen on the Wifi Software Serial Port.
    wifiSerial.listen ( );
    // While there is data coming in, read it and send to the hardware serial port:
    while ( wifiSerial.available ( ) > 0 )
      {
        // Because use the multiple Software Serial Port, have to delay sometime to read
        // Otherwise, will get non-complite byte data.
        byte inByte = wifiSerial.read ( );
        delay ( 20 );
        Serial.write ( inByte );
        ttlSerial.write ( inByte );    
      }
  }

