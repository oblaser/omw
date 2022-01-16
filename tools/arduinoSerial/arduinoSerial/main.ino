/*
author          Oliver Blaser
date            16.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#include <Arduino.h>


#define LED 13


#define PROTOCOL_RXPOS_LEN              1
#define PROTOCOL_RXPOS_DATA             2

#define PROTOCOL_TXPOS_STAT             1
#define PROTOCOL_TXPOS_LEN              2
#define PROTOCOL_TXPOS_DATA             3

#define PROTOCOL_STAT_OK                0x00
#define PROTOCOL_STAT_ERROR             0x01
#define PROTOCOL_STAT_CS                0x02
#define PROTOCOL_STAT_INVALID_PARAM     0x03


unsigned long millis_old;
uint32_t cnt = 0;
uint32_t tmr_sendCounter = 0;
uint32_t sendCounterInterval = 0;
size_t nBytesReceived = 0;
constexpr size_t trxBufferSize = 10;
uint8_t rxBuffer[trxBufferSize];
uint8_t txBuffer[trxBufferSize];

void bigEndianEncode32(uint8_t* buffer, uint32_t value);

int getLed();
void setLed(int state);

uint8_t checksum(const uint8_t* data, size_t count);
void sendBuffer();
void sendMsgCntr(uint32_t value);
void handleCmd();
void handleSetLed();
void handleGetLed();
void handleGetCntr();
void handleSetCntrInterval();



void setup()
{
    pinMode(LED, OUTPUT);
    setLed(0);

    Serial.begin(19200, SERIAL_8N2);
    Serial.setTimeout(10); // biggest cmd: 8 bytes => 19200^(-1) * 10 * 8 = 4.2ms < 10ms

    millis_old = millis();
}

void loop()
{
    // handle command
    if(nBytesReceived > 0)
    {
        txBuffer[0] = rxBuffer[0];

        if(nBytesReceived == (rxBuffer[PROTOCOL_RXPOS_LEN] + 3))
        {
            if(checksum(rxBuffer, nBytesReceived) == 0)
            {
                handleCmd();
            }
            else
            {
                txBuffer[PROTOCOL_TXPOS_STAT] = PROTOCOL_STAT_CS;
                txBuffer[PROTOCOL_TXPOS_LEN] = 0;
            }
        }
        else
        {
            txBuffer[PROTOCOL_TXPOS_STAT] = PROTOCOL_STAT_ERROR;
            txBuffer[PROTOCOL_TXPOS_LEN] = 0;
        }

        sendBuffer();
        
        nBytesReceived = 0;
    }

    // send counter value
    if((tmr_sendCounter == 0) && (sendCounterInterval > 0))
    {
        tmr_sendCounter = sendCounterInterval;
        sendMsgCntr(cnt);
    }

    // read serial
    if(Serial.available() > 0) nBytesReceived = Serial.readBytes(rxBuffer, trxBufferSize);

    // time handler
    const unsigned long millis_now = millis();
    if(millis_now != millis_old) // well, it doesn't matter in this app, but: Caution! millis()'s return value overflows after 50 days!
    {
        millis_old = millis_now;

        if(tmr_sendCounter > 0) --tmr_sendCounter;

        ++cnt;
    }
}



void bigEndianEncode32(uint8_t* buffer, uint32_t value)
{
    buffer[0] = (uint8_t)((value >> 24) & 0xFF);
    buffer[1] = (uint8_t)((value >> 16) & 0xFF);
    buffer[2] = (uint8_t)((value >> 8) & 0xFF);
    buffer[3] = (uint8_t)(value & 0xFF);
}

int getLed()
{
    return digitalRead(LED);
}

void setLed(int state)
{
    digitalWrite(LED, state);
}

uint8_t checksum(const uint8_t* data, size_t count)
{
    uint8_t r = 0;
    if(data)
    {
        for(size_t i = 0; i < count; ++i) r ^= data[i];
    }
    return r;
}

void sendBuffer()
{
    size_t txLen = txBuffer[PROTOCOL_TXPOS_LEN] + 4;
    txBuffer[txLen - 1] = checksum(txBuffer, txLen - 1);
    Serial.write(txBuffer, txLen);
}

void sendMsgCntr(uint32_t value)
{
    txBuffer[0] = 0xD1;
    txBuffer[PROTOCOL_TXPOS_STAT] = PROTOCOL_STAT_OK;
    txBuffer[PROTOCOL_TXPOS_LEN] = 0x04;
    bigEndianEncode32(txBuffer + PROTOCOL_TXPOS_DATA, value);
    sendBuffer();
}

void handleCmd()
{
    switch (rxBuffer[0])
    {
    case 0x01:
        handleSetLed();
        break;

    case 0x02:
        handleGetLed();
        break;

    case 0x03:
        handleGetCntr();
        break;

    case 0x04:
        handleSetCntrInterval();
        break;
    
    default:
        txBuffer[PROTOCOL_TXPOS_STAT] = PROTOCOL_STAT_ERROR;
        txBuffer[PROTOCOL_TXPOS_LEN] = 0;
        break;
    }
}

void handleSetLed()
{
    txBuffer[PROTOCOL_TXPOS_STAT] = PROTOCOL_STAT_OK;
    txBuffer[PROTOCOL_TXPOS_LEN] = 0;

    if(rxBuffer[PROTOCOL_RXPOS_LEN] == 1)
    {
        if(rxBuffer[PROTOCOL_RXPOS_DATA] == 0) setLed(0);
        else if(rxBuffer[PROTOCOL_RXPOS_DATA] == 1) setLed(1);
        else txBuffer[PROTOCOL_TXPOS_STAT] = PROTOCOL_STAT_INVALID_PARAM;
    }
    else txBuffer[PROTOCOL_TXPOS_STAT] = PROTOCOL_STAT_INVALID_PARAM;
}

void handleGetLed()
{
    txBuffer[PROTOCOL_TXPOS_STAT] = PROTOCOL_STAT_OK;
    txBuffer[PROTOCOL_TXPOS_LEN] = 0;

    if(rxBuffer[PROTOCOL_RXPOS_LEN] == 0)
    {
        txBuffer[PROTOCOL_TXPOS_LEN] = 1;
        txBuffer[PROTOCOL_TXPOS_DATA] = (getLed() ? 0x01 : 0x00);
    }
    else txBuffer[PROTOCOL_TXPOS_STAT] = PROTOCOL_STAT_INVALID_PARAM;
}

void handleGetCntr()
{
    txBuffer[PROTOCOL_TXPOS_STAT] = PROTOCOL_STAT_OK;
    txBuffer[PROTOCOL_TXPOS_LEN] = 0;

    if(rxBuffer[PROTOCOL_RXPOS_LEN] == 0)
    {
        txBuffer[PROTOCOL_TXPOS_LEN] = 4;
        bigEndianEncode32(txBuffer + PROTOCOL_TXPOS_DATA, cnt);
    }
    else txBuffer[PROTOCOL_TXPOS_STAT] = PROTOCOL_STAT_INVALID_PARAM;
}

void handleSetCntrInterval()
{
    txBuffer[PROTOCOL_TXPOS_STAT] = PROTOCOL_STAT_OK;
    txBuffer[PROTOCOL_TXPOS_LEN] = 0;

    if(rxBuffer[PROTOCOL_RXPOS_LEN] == 1)
    {
        sendCounterInterval = rxBuffer[PROTOCOL_RXPOS_DATA];
        sendCounterInterval *= 100;
        tmr_sendCounter = sendCounterInterval;
    }
    else txBuffer[PROTOCOL_TXPOS_STAT] = PROTOCOL_STAT_INVALID_PARAM;
}
