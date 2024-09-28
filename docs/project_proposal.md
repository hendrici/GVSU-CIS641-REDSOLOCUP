Team name: REDSOLOCUP

Team members: Isaiah Hendrick

# Introduction

This project proposal is for an embedded bluetooth communication device. This will be useful for anyone attempting to send messages to others in close proximity with the use of email or text messages. Although the use of bluetooth for reliable data transfer when relaying personal messages back and forth is impractical, I believe that this project will help assist in my personal development as a programmer, widening my knowledge base and making me more marketable for future projects.

To further define this project, a bluetooth peripheral will be connected to a microcontroller and used to send messages back and forth between two devices, with messages that can be personalized by separate users using a serial UART terminal. The UART terminal should be VT100-like, giving the user some direction about how to use the application once it is opened and ready to send messages back and forth. The concept for the system is quite simple, however, it will take an extended period of time learning how to use the bluetooth interface and how to properly send messages using it.

# Anticipated Technologies

This project will require two microcontrollers with bluetooth peripherals, as well as a personal computer with a serial terminal installed. I believe that the Texas Instruments MSP432 will be suitable for this project which is programmable using C code, in addition to an Adafruit bluetooth peripheral. This peripheral will also require a simple circuit setup to be connected to the microcontroller. If time allows, a small enclosure and PCB mount may also be designed to create a sturdier, visually appealing product.

# Method/Approach

For developing this project, I plan on first setting up my hardware and creating a simple circuit connecting my bluetooth peripheral with the microcontroller. I then will spend some time determining how much work it will be to use the bluetooth interface and how to send user messages back and forth. Similarly, I will figure out how to send and receiving messages with a serial UART terminal. Once I have figured out how to send a singular message with both of these interfaces, I will then be able to work on combining both so that sending a UART message from the terminal will be received and immediately send over the bluetooth interface.

Separately, I will work on designing a serial UART terminal that allows for user input. This will include styling to closely resemble a VT100-like interface, which will require research into ANSI escape codes. This interface will be combined with the UART/bluetooth functionality to create the final product.

# Estimated Timeline

(1 week) Gather hardware and create circuit connecting bluetooth peripheral with microcontroller.

(1-2 weeks) Experimenting with the bluetooth interface; be able to send and receive data.

(1 week) Be able to send and receive data with UART; receive UART -> send bluetooth -> receive bluetooth -> send UART.

(2-3 weeks) Styling and implementation of UART terminal interface.

(2 weeks) Final testing.

(1 week) Creating enclosure and PCB mount; assembly.

# Anticipated Problems

One problem I foresee with this project is getting the bluetooth interface to work properly. I have not had much experience with the interface before, so it will require some research and trial and error to get a working final product. I also foresee some problems with formatting the input/output when using the UART terminal for aesthetic purposes. 
