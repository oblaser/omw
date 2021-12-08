/*
author         Oliver Blaser
date           20.09.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <Arduino.h>


#define LED 13


unsigned long millis_old;
uint32_t cnt = 0;
uint32_t tmr_sendCounter = 0;
uint32_t sendCounterInterval = 0;
size_t nBytesReceived = 0;
const size_t trxBufferSize = 10;
uint8_t rxBuffer[trxBufferSize];
uint8_t txBuffer[trxBufferSize];


void ansGeneralError();
void ansCntVal(uint8_t msgId);
int getLed();
void setLed(int state);
void errorHandler();


void setup()
{
    pinMode(LED, OUTPUT);
    setLed(0);

    Serial.begin(19200, SERIAL_8N2);
    Serial.setTimeout(10);

    millis_old = millis();
}

void loop()
{
    ++cnt;

    // handle command
    if(nBytesReceived > 0)
    {
        switch (rxBuffer[0])
        {
        case 0x01:
            if(nBytesReceived == 2)
            {
                txBuffer[0] = 0x01;
                txBuffer[1] = 0x00;
                if(rxBuffer[1] == 0) setLed(0);
                else if(rxBuffer[1] == 1) setLed(1);
                else txBuffer[1] = 0x01;
                Serial.write(txBuffer, 2);
            }
            else ansGeneralError();
            break;
        
        case 0x02:
            if(nBytesReceived == 1)
            {
                txBuffer[0] = 0x02;
                txBuffer[1] = (getLed() > 0 ? 1 : 0);
                Serial.write(txBuffer, 2);
            }
            else ansGeneralError();
            break;
        
        case 0x03:
            if(nBytesReceived == 1)
            {
                ansCntVal(0x03);
            }
            else ansGeneralError();
            break;
        
        case 0x04:
            if(nBytesReceived == 2)
            {
                sendCounterInterval = rxBuffer[1];
                sendCounterInterval *= 1000;
                tmr_sendCounter = sendCounterInterval;

                txBuffer[0] = 0x04;
                txBuffer[1] = 0x00;
                Serial.write(txBuffer, 2);
            }
            else ansGeneralError();
            break;
        
        default:
            ansGeneralError();
            break;
        }
        
        nBytesReceived = 0;
    }

    // send counter value
    if((tmr_sendCounter == 0) && (sendCounterInterval > 0))
    {
        tmr_sendCounter = sendCounterInterval;
        ansCntVal(0x10);
    }

    // read serial
    if(Serial.available() > 0) nBytesReceived = Serial.readBytes(rxBuffer, trxBufferSize);

    // time handler
    const unsigned long millis_now = millis();
    if(millis_now != millis_old) // Caution! millis()'s return value overflows after 50 days!
    {
        millis_old = millis_now;

        if(tmr_sendCounter > 0) --tmr_sendCounter;
    }
}


void ansGeneralError()
{
    txBuffer[0] = 0xE0;
    txBuffer[1] = 0x00;
    Serial.write(txBuffer, 2);
}

void ansCntVal(uint8_t msgId)
{
    txBuffer[0] = msgId;
    txBuffer[1] = (uint8_t)((cnt >> 24) & 0xFF);
    txBuffer[2] = (uint8_t)((cnt >> 16) & 0xFF);
    txBuffer[3] = (uint8_t)((cnt >> 8) & 0xFF);
    txBuffer[4] = (uint8_t)(cnt & 0xFF);
    Serial.write(txBuffer, 5);
}

int getLed()
{
    return digitalRead(LED);
}

void setLed(int state)
{
    digitalWrite(LED, state);
}
