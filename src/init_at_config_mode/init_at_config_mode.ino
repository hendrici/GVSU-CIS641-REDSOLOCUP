/**
 * @file BluetoothSerialCommunication.ino
 * @brief Script for initial pairing of HC-05 module
 *
 * This code sets the HC-05 to AT command mode for configuration and allows the user to send AT
 * commands through the serial terminal. Both the slave and master modules need to be setup
 * individually. See the document in the references folder for the needed commands.
 *
 * Connections:
 * - Pin 10: RX pin of HC-05
 * - Pin 11: TX pin of HC-05
 * - Pin 9: Enable pin of HC-05
 * - GND: GND pin of HC-05
 * - 3.3V: VCC pin of HC-05
 */

/* Custom includes */
#include <SoftwareSerial.h>

/* Pin 10 is RX, pin 11 is TX */
SoftwareSerial BTSerial(10, 11);

void setup()
{
  /* set enable pin high on HC-05 to turn on AT mode */
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  
  /* start serial terminal to configure HC-05 using AT commands, serial baud rate is 9600 */
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  
  /* use 38400 baud rate for sending data to HC-05 */
  BTSerial.begin(38400);
}

void loop()
{
  /* check RX for incoming data and pass it to serial terminal */
  if (BTSerial.available())
    Serial.write(BTSerial.read());

  /* check serial terminal for incoming data and pass it to TX line */
  if (Serial.available())
    BTSerial.write(Serial.read());
}
