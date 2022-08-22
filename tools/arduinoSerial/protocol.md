# Protocol
## General Structure
### Command
`| Command | Length | Data | Checksum |`
### Answer
`| Command | Status | Length | Data | Checksum |`
### Message
Messages can occur "randomly".

`| Message | Length | Data | Checksum |`

### Length
Number of data bytes.

### Status Code
| Value | Description |
|:---:|:---|
| 0x00 | OK |
| 0x01 | General error |
| 0x02 | Checksum error |
| 0x03 | Invalid parameter value |

### Checksum
XOR over all previous bytes. E.g.: `Command XOR Length XOR Data[0] XOR data[1] XOR ...`



## Commands
### Set LED
#### Command
| Byte | Value | Description |
|:---|:---:|:---|
| CMD | 0x01 |  |
| LEN | 0x01 |  |
| LED | 0x00<br/>0x01 | LED off<br/>LED on |
| CHECK| 0xXX | See _[Checksum](#checksum)_ |

#### Answer
| Byte | Value | Description |
|:---|:---:|:---|
| CMD | 0x01 |  |
| STAT | 0xXX | See _[Status Code](#status-code)_ |
| LEN | 0x00 |  |
| CHECK| 0xXX | See _[Checksum](#checksum)_ |


### Get LED
#### Command
| Byte | Value | Description |
|:---|:---:|:---|
| CMD | 0x02 |  |
| LEN | 0x00 |  |
| CHECK| 0xXX | See _[Checksum](#checksum)_ |

#### Answer
| Byte | Value | Description |
|:---|:---:|:---|
| CMD | 0x02 |  |
| STAT | 0xXX | See _[Status Code](#status-code)_ |
| LEN | 0x01 |  |
| LED | 0x00<br/>0x01 | LED is off<br/>LED is on |
| CHECK| 0xXX | See _[Checksum](#checksum)_ |


### Get Counter
#### Command
| Byte | Value | Description |
|:---|:---:|:---|
| CMD | 0x03 |  |
| LEN | 0x00 |  |
| CHECK| 0xXX | See _[Checksum](#checksum)_ |

#### Answer
| Byte | Value | Description |
|:---|:---:|:---|
| CMD | 0x03 |  |
| STAT | 0xXX | See _[Status Code](#status-code)_ |
| LEN | 0x04 |  |
| CNT[4] |  | BigEndian encoded counter value |
| CHECK| 0xXX | See _[Checksum](#checksum)_ |


### Set Send Counter Interval
#### Command
| Byte | Value | Description |
|:---|:---:|:---|
| CMD | 0x04 |  |
| LEN | 0x01 |  |
| TIME | 0x00<br/>0xXX | Disable counter value message<br/>Period of the sending interval (`value` * 100ms) |
| CHECK| 0xXX | See _[Checksum](#checksum)_ |

#### Answer
| Byte | Value | Description |
|:---|:---:|:---|
| CMD | 0x04 |  |
| STAT | 0xXX | See _[Status Code](#status-code)_ |
| LEN | 0x00 |  |
| CHECK| 0xXX | See _[Checksum](#checksum)_ |



## Messages
### Counter value
| Byte | Value | Description |
|:---|:---:|:---|
| MSG | 0xD1 |  |
| STAT | 0x00 | OK - See _[Status Code](#status-code)_ |
| LEN | 0x04 |  |
| CNT[4] |  | BigEndian encoded counter value |
| CHECK| 0xXX | See _[Checksum](#checksum)_ |
