# Overview
The purpose of this document is to provide a guide for the course of the embedded bluetooth communication project and provide a comprehensive description of the functional and non-functional requirements associated with the project. The requirements found here can provide a framework for what the project itself will look like and serve as a baseline going forward with its development. 

# Software Requirements
This section lists all of the functional and non-functional requirements of the system, split into categories.

## Functional Requirements
### UART Communication
| ID | Requirement |
| :-------------: | :----------: |
| FR1 | The bluetooth UART instance should be initialized to a baud rate of 38400. |
| FR2 | The serial UART instance should be initialized to a baud rate of 9600. |
| FR3 | The system should accept messages up to but not exceeding 256 characters. |
| FR4 | The system should allow for each user to send messages to the other via bluetooth. |
| FR5 | The system should be able to connect to a bluetooth peripheral and serial terminal via UART instances. |

### Input/Output Handling
| ID | Requirement |
| :-------------: | :----------: |
| FR6 | The system should handle new-line character inputs (\r\n) as a method to send a message. |
| FR7 | The system should validate input length to ensure the buffer does not exceed its maximum length. |
| FR8 | The system should handle backspace and delete character inputs properly. |
| FR9 | The system should echo received characters from the serial UART instance when inputted. |
| FR10 | The system shall ensure newline characters are cleared from the character buffer to ensure clean data transmission. |

### UART Configuration
| ID | Requirement |
| :-------------: | :----------: |
| FR11 | MCLK and HSMCLK should be initialized to 48 MHz during operation. |
| FR12 | The main system clock should operate at 3 MHz. |
| FR13 | The baud rates for both UART instances must be calculated using the system clock value. |
| FR14 | The UART parity should be set to least significant bit first. |
| FR15 | The UART configuration should utilize 1 stop bit for communication. |

### Interrupt Handling
| ID | Requirement |
| :-------------: | :----------: |
| FR16 | The system shall support interrupts for receiving UART data bytes. |
| FR17 | The system shall prioritize incoming bluetooth messages over serial messages. |
| FR18 | Interrupts should be used in order to update character buffers. |
| FR19 | The serial interrupt must echo its byte data every time it is triggered. |
| FR20 | The interrupts must handle each character buffer in circular fashion. |

### Bluetooth Pairing
| ID | Requirement |
| :-------------: | :----------: |
| FR21 | The system must contain both a master and slave bluetooth module. |
| FR22 | Each bluetooth module should be setup using an Arduino Uno. |
| FR23 | Each bluetooth module must be put into AT command mode in order to configure the baud rate and mode. |
| FR24 | Each bluetooth module must be fully configured before using the main program. |
| FR25 | The bluetooth modules must be paired before messages can be sent to each other. |

## Non-Functional Requirements
### Usability
| ID | Requirement |
| :-------------: | :----------: |
| NFR1 | The system must maintain the integrity of messages when being sent between devices.  |
| NFR2 | The system must provide an intuitive UI for sending and viewing messages. |
| NFR3 | The system must maintain connection between both bluetooth modules throughout the session to ensure reliable data transfer. |
| NFR4 | The system must be able to handle any buffer overflows properly. |
| NFR5 | Buffer manipulation must be easy to understand when reading and writing to. |

### Program Content
| ID | Requirement |
| :-------------: | :----------: |
| NFR6 | The system shall print an ASCII style cover art image upon startup. |
| NFR7 | The system shall print a welcome message specifying the user # upon startup. |
| NFR8 | The system should display a indicator before each message showing which user sent it. |
| NFR9 | The system should consistently prompt the user to enter a message. |
| NFR10 | The system should be able to print colored system messages. |

### Maintainability
| ID | Requirement |
| :-------------: | :----------: |
| NFR11 | Functions written in the program must be designed modularly for future use. |
| NFR12 | The system must utilize libraries for code organization and readability. |
| NFR13 | The system must contain well commented code. |
| NFR14 | The system must utilize the MSP432WARE driverlib as much as possible to ensure readability. |
| NFR15 | Each function in the program must contain proper documentation explaining its purpose. |

### Performance
| ID | Requirement |
| :-------------: | :----------: |
| NFR16 | The system must handle user input with little latency. |
| NFR17 | The system must avoid getting stuck in loops while reading incoming messages. |
| NFR18 | The system must handle bluetooth communication with little latency. |
| NFR19 | The system should be easily reset and able to send messages repeatedly. |
| NFR20 | The system should print startup messages in a reasonable timeframe. |

### Scalability
| ID | Requirement |
| :-------------: | :----------: |
| NFR21 | The system must be able to support more than one UART instance. |
| NFR22 | The system should allow for buffer sizes to be increased if necessary. |
| NFR23 | The system should only allow for one bluetooth connection per device.  |
| NFR24 | The system should only allow for one serial terminal connection per device. |
| NFR25 | The system should have the capacity to recognize particular inputs for future development, where users could type commands. |

# Change management plan
This section is a description of how I plan to get others to incorporate this application within a business environment.

This application was created to serve as a learning module for bluetooth application in an embedded system. In order to get others to use it, and learn more about how to use bluetooth modules in further projects, I plan to give access to this project to my peers, with extended documentation and a step-by-step process of how I completed my implementation. Through use of modular functions and compatibility with UART, I can show them how easy it is to implement bluetooth messaging into their own system, such as I have done. I also plan to acknowledge any problems or user issues colleagues may face and help with their implementation to better promote usage of this product.

# Traceability links
This section shows how the software artifacts, specifically use case diagrams, class diagrams, and activity diagrams, are linked to the system requirements to ensure traceability. Each table provides an overview that maps each artifact to its corresponding functional or non-functional requirements.

## Use Case Diagram Traceability
| Artifact ID | Artifact Name | Requirement ID |
| :-------------: | :----------: | :----------: |
| Use Case Diagram #1 | Transmit/Receive Serial Data | FR16-20 |
| Use Case Diagram #1 | Transmit/Receive Bluetooth Data | FR17, NFR18 |
| Use Case Diagram #1 | Initialize Bluetooth Connection | FR21-25 |
| Use Case Diagram #2 | Print System Messages | NFR6-10 |
| Use Case Diagram #2 | Print User Messages | FR4, NFR16 |
| Use Case Diagram #2 | Type/Send Message | FR4 |

## Class Diagram Traceability
| Artifact Name | Requirement ID |
| :-------------: |:----------: |
| System Clock | FR11-12 |
| Interrupt Handler | FR16-20 |
| UART Connection | FR1-5, 13-15 |
| UART Message Handler | FR6-10 |


## Activity Diagram Traceability
| Artifact ID | Artifact Name | Requirement ID |
| :-------------: | :----------: | :----------: |
| Activity Diagram #1 | Handle Serial/Bluetooth Data | FR16-20 |
| Activity Diagram #2 | User Interaction | FR5, 21-25, NFR24 | 

# Software Artifacts
This section provides links to all of the artifacts mentioned in the traceability links section, including the use case diagrams, class diagrams, and activity diagrams that were created for the development of this project.

* [Use Case Diagram #1](../artifacts/HENDRICK_CIS641_USECASEDIAGRAM1.pdf)
* [Use Case Diagram #2](../artifacts/HENDRICK_CIS641_USECASEDIAGRAM2.pdf)

* [Class Diagram](../artifacts/HENDRICK_CIS641_CLASSDIAGRAM.pdf)

* [Activity Diagram #1](../artifacts/HENDRICK_CIS641_ACTIVITYDIAGRAM1.pdf)
* [Activity Diagram #2](../artifacts/HENDRICK_CIS641_ACTIVITYDIAGRAM2.pdf)