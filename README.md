# REDSOLOCUP
## Overview
This repository is for an embedded bluetooth communication device using the Texas Instruments MSP432. HC-05 bluetooth peripherals are used to send messages back and forth between two devices, which can be sent and received via two separate serial terminals.

## Team Members and Roles
* [Isaiah Hendrick](https://hendrici.github.io/CIS641-HW2-HENDRICK/) (project manager)

## Run Instructions
### Required Hardware
1. [MSP432P401R Evaluation Board](https://www.digikey.com/en/products/detail/texas-instruments/MSP-EXP432P401R/5170609) x2 (looks like this board is now technically obsolete, may be able to refactor CCS project for use with simliar product)
2. [HC-05 Bluetooth Module](https://www.amazon.com/DSD-TECH-HC-05-Pass-through-Communication/dp/B01G9KSAF6/ref=sr_1_1_pp?dib=eyJ2IjoiMSJ9.VZL1p5RDGQw7c8DXaqrVkRyfFEBz0HhuagQj9O7D5y6hbVcaugJQgfkVGgef-i5rd81ad2Jos9_JO1qiDdZvkud2QxHSeYY12plp5pyJEAbI56TcgcBCwQP2jWPBM45bn5eCWv8qzhD8hW_EHmPJvAZ4Jm6tW_0uUZrqMHhi9bqJsHK-DvrxBMQCvQATJUKlT0F_4TSMo0DDuFgLovkvZ-Eez1nBWoU0x0GOSJR_aBZXJjJbtNpPRMQXshojdOVnPJc_E3Y7kMwufvPibYSbkbdAzGn-3w5r__aNq6pvrto.mSVgmUqeGHyFfHpyokEoUxY-KPig8y9yF-hMoAODz0A&dib_tag=se&keywords=hc05&qid=1733588210&s=electronics&sr=1-1) x2
3. [Arduino Uno](https://www.amazon.com/Arduino-A000066-ARDUINO-UNO-R3/dp/B008GRTSV6/ref=sr_1_3?crid=1RDB05EVYWKEI&dib=eyJ2IjoiMSJ9.XbKE6b0NGJdls38suMJhLXJd6g6Vup0nHHmmYI4Zo9qrpQnycWIOnJ8s1mQw0n3YLZv03zfQbFBrypHp7Um6U3VGfL9iHzX2HSoWw-jwEVUsO3oekPBiF6BjCHZZqevE2bsx108bNnrzpwdAu3VfUOElBpbJuGQjgDjbd5IsxSfUXHqaPKLRBYYRm5c8I3FXgGjZAHszccvyMmeAUPFVOp0zwG-9YzARbX7YRkkXNsH3Cqeb4oR5Y9zkaBaxvIDUR0MQZ8V8TkLczOlNIbNkssziI9sJz6kn74fhWa5x-fg.zqc-SOcyp9TWsmHZ2QNTibu7hI1jSCZmpMSCZwcfhkA&dib_tag=se&keywords=arduino%2Buno&qid=1733588285&s=electronics&sprefix=arduino%2Buno%2Celectronics%2C137&sr=1-3&th=1)

### Required Software
1. [Arduino IDE](https://www.arduino.cc/en/software)
2. [Code Composer Studio](https://www.ti.com/tool/CCSTUDIO)
3. Serial Terminal Application (I like to use [Tera Term](https://teratermproject.github.io/index-en.html))

### Pairing Master and Slave
1. First, we will setup the slave module.
2. Connect HC-05 bluetooth module to Arduino Uno with the following pin connections.

    | HC-05 | Arduino Uno |
    | --- | --- |
    | VCC | 3.3V |
    | GND | GND |
    | TXD | Pin 10 |
    | RXD | Pin 11 |
    | EN | Pin 9 |

3. In order to enter the AT command mode, leave VCC unconnected when plugging Arduino Nano into computer.
4. Run this [setup code](src/init_at_config_mode/init_at_config_mode.ino) using Arduino IDE.
5. After running file, reconnect VCC, and open serial terminal (for simplicity, there is one built directly into Arduino IDE). Ensure baud rate is set to 9600.
6. Enter these commands to set module as slave.
    1. `AT+RMAAD` (clear any paired devices)
    2. `AT+ROLE=0` (set as slave)
    3. `AT+ADDR` (get address of module, write down for later)
    4. `AT+UART=38400,0,0` (set baud rate to 38400)
7. Now we will setup the master module. 
8. Repeat steps 2-5 with a secondary HC-05, and then use the following commands to set the module as master.
    1. `AT+RMAAD` (clear any paired devices)
    2. `AT+ROLE=1` (set as master)
    3. `AT+CMODE=0` (allow for binding)
    4. `AT+BIND=xxxx,xx,xxxxxx` (use slave address, replace colons with commas)
    5. `AT+UART=38400,0,0` (set baud rate to 38400)

Note: Full explanation of the commands being used can be found in [this document](references/hc05_commands.pdf).

### Running the Program
1. Connect slave and master HC-05 modules to separate MSP432 boards with the following connections.

    | HC-05 | MSP432 |
    | --- | --- |
    | VCC | 3.3V |
    | GND | GND |
    | TXD | P3.2 |
    | RXD | P3.3 |

2. After installing Code Composer Studio, you will need to download a set of software tools called [MSP432Ware](https://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP432Ware/latest/index_FDS.html) in order to use driverlib when running the program. Follow the instructions within the link for installing properly.
3. Import this repository's [source code](src)  as a CCS project. 
4. Make sure to exclude the [init_at_config_mode](init_at_config_mode) folder from the build (right click folder in project explorer -> resource configurations -> exclude from build -> debug).
5. Load code on to each board separately, by pressing the debug button on the toolbar, and then the run button. Make sure to exclude either [main_slave](src/main_slave.c) or [main_master](src/main_master.c) from the build depending on which board you are flashing.
6. After both boards have been flashed, open two serial terminal instances using Tera Term (or similar), connect both to the appropriate COM port for the respective MSP432, and the program is ready to use. If nothing appears when connecting the serial terminal, you simply need to press the reset button on the MSP432 to see the startup messages.