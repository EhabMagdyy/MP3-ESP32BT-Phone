#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "BluetoothSerial.h"

#define MP3_TX_PIN              17
#define MP3_RX_PIN              16

/* You can change it to number of songs you want to play in SD-Card */
#define NO_OF_AUDIO             4
/* MP3 Variables */
unsigned char audioNumber = 1;
unsigned char isPaused = 0;
unsigned char volume = 0;
/* Bluetooth variables */
String device_name = "ESP32-BT";
BluetoothSerial SerialBT;
unsigned char bt_value = 0;

SoftwareSerial softwareSerial(MP3_RX_PIN, MP3_TX_PIN);
DFRobotDFPlayerMini player;

void setup()
{
  softwareSerial.begin(9600);
  SerialBT.begin(device_name); 
  player.begin(softwareSerial);

  player.volume(20);
  player.play(1);
}

void loop() 
{
    /* Get bluetooth value */
    if (SerialBT.available()) 
    {
        bt_value = SerialBT.read();
    }

    switch(bt_value)
    {
        /* play next audio */
        case 'N':
          /* play the next audio */
          audioNumber = ((audioNumber + 1) > NO_OF_AUDIO)? 1 : (audioNumber + 1);
          player.play(audioNumber);
          break;
        /* Pause/Resume audio */
        case 'R':
          if(isPaused)
          {
              player.start();
              isPaused = 0;
          }
          else
          {
              player.pause();
              isPaused = 1;
          }
          break;
        /* play the previous audio */
        case 'P':
          audioNumber = ((audioNumber - 1) == 0)? NO_OF_AUDIO : (audioNumber - 1); 
          player.play(audioNumber);
          break;
        /* Change volume to 10 */
        case 0x10:
          player.volume(10);
          break;
        /* Change volume to 20 */
        case 0x20:
          player.volume(20);
          break;
        /* Change volume to 30 */
        case 0x30:
          player.volume(30);
          break;
    }
}
