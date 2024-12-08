# Overview

The purpose of this document is to provide a guide for the course of the project and provide an understanding of 
what needs it seeks to fulfill. The requirements found here can provide a framework for what the project itself will 
look like and serve as a baseline going forward with its development. 

# Functional Requirements

1. Bluetooth Communication
    1. The microcontroller must be able to connect with another microcontroller via bluetooth and send messages
       back and forth.
    2. An acknowledgement must be sent between microcontrollers after every bluetooth message to confirm that it has
       been received.
2. Serial Interface
    1. The user must be able to enter and send messages using a serial terminal program.
    2. The serial interface must give a text indication when the connection between microcontrollers over Bluetooth
       has been established.

# Non-Functional Requirements

1. Serial Interface
    1. The serial terminal must be intuitive for the user to operate and simple enough to interpret incoming messages.
2. Bluetooth Communication
    1. The bluetooth communication interface must maintain a reliable connection between microcontrollers throughout the
       entirety of a messaging session.
    2. Messages sent between users shall not have any noticable latency.
3. Modularity
    1. The codebase and its components (bluetooth communication, serial UART communication, etc.) shall be modular and 
       robust, allowing for future updates.
