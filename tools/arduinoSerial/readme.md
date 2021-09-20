# Arduino Serial

An Arduino application to develop and test the serial port library part of omw.

Periodically sends a counter value and handles get and set LED commands.

## Protocol
### Commands
 - `01 XX` Set LED
 - `02` Get LED
 - `03` Get counter value
 - `04 xx` Set send counter interval

### Answers
 - `01 00` Set LED OK
 - `01 01` Set LED error
 - `02 XX` LED state
 - `03 XX XX XX XX` Counter value
 - `E0 00` General error

### Messages
 - `10 XX XX XX XX` Counter value
 - `E1 00` From error handler
