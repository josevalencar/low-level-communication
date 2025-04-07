# Low-Level Communication Protocol

This project implements a custom low-level communication protocol between two Arduino devices using direct pin manipulation. It demonstrates fundamental concepts of digital communication and bit-level data transmission.

## Overview

The project consists of two Arduino programs:
- **Transmitter (arduino1.cpp)**: Sends 4-bit binary messages
- **Receiver (arduino2.cpp)**: Receives and decodes the transmitted messages

## How It Works

### Communication Protocol

1. **Synchronization Phase**
   - The transmitter sends a synchronization pattern (HIGH-LOW-HIGH-LOW)
   - The receiver detects the timing between edges to establish communication timing
   - This ensures both devices are synchronized before data transmission

2. **Data Transmission**
   - Each bit is transmitted using a Manchester encoding scheme
   - Bit '1': LOW-to-HIGH transition
   - Bit '0': HIGH-to-LOW transition
   - Each bit period is divided into two equal halves (TX_HALF_BIT = 150ms)

### Algorithms

1. **Transmitter Algorithm**
   - Validates 4-bit binary input
   - Sends synchronization pattern
   - Encodes each bit using Manchester encoding
   - Provides feedback through Serial monitor

2. **Receiver Algorithm**
   - Detects synchronization pattern
   - Calculates bit timing from sync pattern
   - Decodes incoming bits using interrupt-based detection
   - Converts received bits to decimal value

## Hardware Requirements

- 2 Arduino boards (e.g., Arduino Uno)
- Jumper wires
- Transmitter: Connect to pin 3
- Receiver: Connect to pin 2

## How to Run

1. **Setup**
   - Connect the Arduino boards according to the pin configuration
   - Upload `arduino1.cpp` to the transmitter Arduino
   - Upload `arduino2.cpp` to the receiver Arduino

2. **Operation**
   - Open Serial Monitor on the transmitter Arduino (9600 baud)
   - Enter a 4-bit binary number (e.g., "1010")
   - The receiver will display the received bits and their decimal value

3. **Example**
   ```
   Transmitter:
   > Enter binary number: 1010
   Bits: 1010
   Transmission complete!

   Receiver:
   Message received: 1010
   Decimal value: 10
   ```

## Technical Details

- Bit Rate: ~3.33 bits per second (TX_HALF_BIT = 150ms)
- Encoding: Manchester
- Data Format: 4-bit binary numbers
- Error Detection: Basic input validation
- Synchronization: Custom sync pattern with timing detection

## Limitations

- Fixed 4-bit message length
- No error correction
- Relatively slow transmission rate
- Requires direct physical connection between devices

## Future Improvements

- Implement error detection and correction
- Add support for variable message length
- Increase transmission speed
- Add wireless communication support
