/*
 * lib.c
 *
 *  Created on: Oct 16, 2023
 *      Author: trieu
 */

/**
 * @brief Porting Lib for module RFID MFRC522 which can be used for TIVA C respectively
 *
 * Connections
 * MFRC522       TIVA C                 DESCRIPTION
 * CS (SDA)      PD1 - SSI3Fss          Chip select for SPI
 * SCK           PD0 - SSI3CLK          Serial Clock for SPI
 * MOSI          PD3 - SSI3Tx           Master In Slave Out for SPI
 * MISO          PD2 - SSI3Rx           Master Out Slave In for SPI
 * IRQ           -                      Irq
 * GND           GND                    Ground
 * RST           3.3V                   Reset pin (3.3V)
 * VCC           3.3V                   3.3V power
**/

#include "lib.h"



#define PIN_HIGH        0xFF
#define PIN_LOW         0x00

uint8_t MFRC522Compare(uint8_t* cardID, uint8_t* compareID);
void MFRC522WriteRaw(uint8_t ucAddress, uint8_t ucValue);
uint8_t MFRC522ReadRaw(uint8_t ucAddress);
void MFRC522SetBitMask(uint8_t reg, uint8_t mask);
void MFRC522ClearBitMask(uint8_t reg, uint8_t mask);
uint8_t MFRC522Request(uint8_t reqMode, uint8_t* tagType);
uint8_t MFRC522ToCard(uint8_t command, uint8_t* sendData, uint8_t sendLen, uint8_t* backData, uint16_t* backLen);
uint8_t MFRC522Anticoll(uint8_t* serNum);
void MFRC522CalculateCRC(uint8_t* pIndata, uint8_t len, uint8_t* pOutData);
uint8_t MFRC522SelectTag(uint8_t* serNum);
uint8_t MFRC522Auth(uint8_t authMode, uint8_t BlockAddr, uint8_t* Sectorkey, uint8_t* serNum);
uint8_t MFRC522Read(uint8_t blockAddr, uint8_t* recvData);
uint8_t MFRC522Write(uint8_t blockAddr, uint8_t* writeData);
void MFRC522Reset(void);
void MFRC522AntennaOn(void);
void MFRC522AntennaOff(void);
void MFRC522Halt(void);

void MFRC522WriteRaw(uint8_t ucAddress, uint8_t ucValue) {

    unsigned char ucAddr;
    ucAddr = ((ucAddress<<1)&0x7E);

    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, PIN_LOW);

    SSIDataPut(SSI3_BASE, (uint8_t) ucAddr);     //Puts a data element into the SSI transmit FIFO
    while(SSIBusy(SSI3_BASE));
    SSIDataPut(SSI3_BASE, (uint8_t) ucValue);
    while(SSIBusy(SSI3_BASE));

    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, PIN_HIGH);
}

uint8_t MFRC522ReadRaw(uint8_t ucAddress) {

    uint8_t ucValue, ucAddr;

    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, PIN_LOW);
    ucAddr = ((ucAddress << 1) & 0x7E) | 0x80;

    SSIDataPut(SSI3_BASE, (uint8_t) ucAddr);
    while(SSIBusy(SSI3_BASE));
    SSIDataGet(SSI3_BASE, (uint8_t *) &ucValue);
    while(SSIBusy(SSI3_BASE));

    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, PIN_HIGH);

    return ucValue;
}

uint8_t MFRC522Check(uint8_t* id) {

    uint8_t status;

    status = MFRC522Request(PICC_REQIDL, id);                            // Find cards, return card type
    if (status == MI_OK) {
        status = MFRC522Anticoll(id);                                    // Card detected. Anti-collision, return card serial number 4 bytes
    }

    MFRC522Halt();                                                        // Command card into hibernation

    return status;

}

uint8_t MFRC522Compare(uint8_t* cardID, uint8_t* compareID) {
    uint8_t i;
    for (i = 0; i < 5; i++) {
        if (cardID[i] != compareID[i])
            return MI_ERR;
    }
    return MI_OK;
}

void MFRC522SetBitMask(uint8_t reg, uint8_t mask) {

    MFRC522WriteRaw(reg, MFRC522ReadRaw(reg) | mask);

}

void MFRC522ClearBitMask(uint8_t reg, uint8_t mask){

    MFRC522WriteRaw(reg, MFRC522ReadRaw(reg) & (~mask));

}

uint8_t MFRC522Request(uint8_t reqMode, uint8_t* tagType) {

    uint8_t status;
    uint16_t backBits; // The received data bits

    MFRC522WriteRaw(MFRC522_REG_BIT_FRAMING, 0x07); // TxLastBists = BitFramingReg[2..0]
    tagType[0] = reqMode;
    status = MFRC522ToCard(PCD_TRANSCEIVE, tagType, 1, tagType, &backBits);

    if ((status != MI_OK) || (backBits != 0x10))
        status = MI_ERR;

    return status;

}

uint8_t MFRC522ToCard(uint8_t command, uint8_t* sendData, uint8_t sendLen, uint8_t* backData, uint16_t* backLen) {

    uint8_t status = MI_ERR;
    uint8_t irqEn = 0x00;
    uint8_t waitIRq = 0x00;
    uint8_t lastBits;
    uint8_t n;
    uint16_t i;

    switch (command) {
        case PCD_AUTHENT: {
            irqEn     = 0x12;
            waitIRq = 0x10;
            break;
        }
        case PCD_TRANSCEIVE: {
            irqEn     = 0x77;
            waitIRq = 0x30;
            break;
        }
        default:
        break;
    }

    MFRC522WriteRaw(MFRC522_REG_COMM_IE_N, irqEn | 0x80);
    MFRC522ClearBitMask(MFRC522_REG_COMM_IRQ, 0x80);
    MFRC522SetBitMask(MFRC522_REG_FIFO_LEVEL, 0x80);
    MFRC522WriteRaw(MFRC522_REG_COMMAND, PCD_IDLE);

    // Writing data to the FIFO
    for (i = 0; i < sendLen; i++)
        MFRC522WriteRaw(MFRC522_REG_FIFO_DATA, sendData[i]);

    // Execute the command
    MFRC522WriteRaw(MFRC522_REG_COMMAND, command);
    if (command == PCD_TRANSCEIVE)
        MFRC522SetBitMask(MFRC522_REG_BIT_FRAMING, 0x80); // StartSend=1, transmission of data starts

    // Waiting to receive data to complete
    i = 2000; // i according to the clock frequency adjustment, the operator M1 card maximum waiting time 25ms
    do {
        // CommIrqReg[7..0]
        // Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
        n = MFRC522ReadRaw(MFRC522_REG_COMM_IRQ);
        i--;
    } while ((i!=0) && !(n&0x01) && !(n&waitIRq));

    MFRC522ClearBitMask(MFRC522_REG_BIT_FRAMING, 0x80); // StartSend=0

    if (i != 0) {
        if (!(MFRC522ReadRaw(MFRC522_REG_ERROR) & 0x1B)) {
            status = MI_OK;
            if (n & irqEn & 0x01)
                status = MI_NOTAGERR;
            if (command == PCD_TRANSCEIVE) {
                n = MFRC522ReadRaw(MFRC522_REG_FIFO_LEVEL);
                lastBits = MFRC522ReadRaw(MFRC522_REG_CONTROL) & 0x07;
                if (lastBits)
                    *backLen = (n-1)*8+lastBits; else *backLen = n*8;
                if (n == 0)
                    n = 1;
                if (n > MFRC522_MAX_LEN)
                    n = MFRC522_MAX_LEN;
                for (i = 0; i < n; i++)
                    backData[i] = MFRC522ReadRaw(MFRC522_REG_FIFO_DATA); // Reading the received data in FIFO
            }
        } else
            status = MI_ERR;
    }

    return status;

}

uint8_t MFRC522Anticoll(uint8_t* serNum) {

    uint8_t status;
    uint8_t i;
    uint8_t serNumCheck = 0;
    uint16_t unLen;

    // TxLastBists = BitFramingReg[2..0]
    MFRC522WriteRaw(MFRC522_REG_BIT_FRAMING, 0x00);
    serNum[0] = PICC_ANTICOLL;
    serNum[1] = 0x20;
    status = MFRC522ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

    if (status == MI_OK) {
        // Check card serial number
        for (i = 0; i < 4; i++)
            serNumCheck ^= serNum[i];
        if (serNumCheck != serNum[i])
            status = MI_ERR;
    }

    return status;

}

void MFRC522CalculateCRC(uint8_t*  pIndata, uint8_t len, uint8_t* pOutData) {

    uint8_t i, n;

    // CRCIrq = 0
    MFRC522ClearBitMask(MFRC522_REG_DIV_IRQ, 0x04);
    // Clear the FIFO pointer
    MFRC522SetBitMask(MFRC522_REG_FIFO_LEVEL, 0x80);
    // Write_MFRC522(CommandReg, PCD_IDLE);

    // Writing data to the FIFO
    for (i = 0; i < len; i++)
        MFRC522WriteRaw(MFRC522_REG_FIFO_DATA, *(pIndata+i));

    MFRC522WriteRaw(MFRC522_REG_COMMAND, PCD_CALCCRC);

    // Wait CRC calculation is complete
    i = 0xFF;
    do {
        n = MFRC522ReadRaw(MFRC522_REG_DIV_IRQ);
        i--;
    } while ((i!=0) && !(n&0x04)); // CRCIrq = 1

    // Read CRC calculation result
    pOutData[0] = MFRC522ReadRaw(MFRC522_REG_CRC_RESULT_L);
    pOutData[1] = MFRC522ReadRaw(MFRC522_REG_CRC_RESULT_M);
}

uint8_t MFRC522SelectTag(uint8_t* serNum) {

    uint8_t i;
    uint8_t status;
    uint8_t size;
    uint16_t recvBits;
    uint8_t buffer[9];

    buffer[0] = PICC_SELECTTAG;
    buffer[1] = 0x70;

    for (i = 0; i < 5; i++)
        buffer[i+2] = *(serNum+i);
    MFRC522CalculateCRC(buffer, 7, &buffer[7]);
    status = MFRC522ToCard(PCD_TRANSCEIVE, buffer, 9, buffer, &recvBits);

    if ((status == MI_OK) && (recvBits == 0x18))
        size = buffer[0];
    else
        size = 0;

    return size;

}

uint8_t MFRC522Auth(uint8_t authMode, uint8_t blockAddr, uint8_t* sectorKey, uint8_t* serNum) {

    uint8_t status;
    uint16_t recvBits;
    uint8_t i;
    uint8_t buff[12];

    // Verify the command block address + sector + password + card serial number
    buff[0] = authMode;
    buff[1] = blockAddr;

    for (i = 0; i < 6; i++)
        buff[i+2] = *(sectorKey+i);
    for (i=0; i<4; i++)
        buff[i+8] = *(serNum+i);
    status = MFRC522ToCard(PCD_AUTHENT, buff, 12, buff, &recvBits);

    if ((status != MI_OK) || (!(MFRC522ReadRaw(MFRC522_REG_STATUS2) & 0x08)))
        status = MI_ERR;

    return status;

}

uint8_t MFRC522Read(uint8_t blockAddr, uint8_t* recvData) {

    uint8_t status;
    uint16_t unLen;

    recvData[0] = PICC_READ;
    recvData[1] = blockAddr;
    MFRC522CalculateCRC(recvData,2, &recvData[2]);
    status = MFRC522ToCard(PCD_TRANSCEIVE, recvData, 4, recvData, &unLen);

    if ((status != MI_OK) || (unLen != 0x90))
        status = MI_ERR;

    return status;

}

uint8_t MFRC522Write(uint8_t blockAddr, uint8_t* writeData) {

    uint8_t status;
    uint16_t recvBits;
    uint8_t i;
    uint8_t buff[18];

    buff[0] = PICC_WRITE;
    buff[1] = blockAddr;
    MFRC522CalculateCRC(buff, 2, &buff[2]);
    status = MFRC522ToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);

    if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
        status = MI_ERR;

    if (status == MI_OK) {
        // Data to the FIFO write 16Byte
        for (i = 0; i < 16; i++)
            buff[i] = *(writeData+i);
        MFRC522CalculateCRC(buff, 16, &buff[16]);
        status = MFRC522ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);

        if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
            status = MI_ERR;
    }

    return status;

}

void MFRC522Init(void) {

    MFRC522Reset();
    MFRC522WriteRaw(MFRC522_REG_T_MODE, 0x8D);
    MFRC522WriteRaw(MFRC522_REG_T_PRESCALER, 0x3E);
    MFRC522WriteRaw(MFRC522_REG_T_RELOAD_L, 30);
    MFRC522WriteRaw(MFRC522_REG_T_RELOAD_H, 0);
    // MFRC522WriteRaw(MFRC522_REG_RF_CFG, 0x70);
    MFRC522WriteRaw(MFRC522_REG_TX_AUTO, 0x40);
    MFRC522WriteRaw(MFRC522_REG_MODE, 0x3D);
    // Open the antenna
    MFRC522AntennaOn();
}

void MFRC522Reset(void) {

    MFRC522WriteRaw(MFRC522_REG_COMMAND, PCD_RESETPHASE);

}

void MFRC522AntennaOn(void) {
    uint8_t temp;

    temp = MFRC522ReadRaw(MFRC522_REG_TX_CONTROL);
    if (!(temp & 0x03))
        MFRC522SetBitMask(MFRC522_REG_TX_CONTROL, 0x03);
}

void MFRC522AntennaOff(void) {

    MFRC522ClearBitMask(MFRC522_REG_TX_CONTROL, 0x03);

}

void MFRC522Halt(void) {

    uint16_t unLen;
    uint8_t buff[4];

    buff[0] = PICC_HALT;
    buff[1] = 0;
    MFRC522CalculateCRC(buff, 2, &buff[2]);
    MFRC522ToCard(PCD_TRANSCEIVE, buff, 4, buff, &unLen);

}
