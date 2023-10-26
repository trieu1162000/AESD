// rc522            TIVA C                    DESCRIPTION
// CS (SDA)           PD1                       SSI3Fss             Chip select for SPI
// SCK                PD0                       SSI3CLK             Serial Clock for SPI
// MOSI               PD3                       SSI3Tx              Master In Slave Out for SPI
// MISO               PD2                       SSI3Rx              Master Out Slave In for SPI
// IRQ                -                         Irq
// GND                GND                       Ground
// RST                3.3V                      Reset pin (3.3V)
// VCC                3.3V                      3.3V power

#include "rc522_api.h"

static void configureSPI(void){

    // TBD. Need to accordingly change Port and Pins.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);
    GPIOPinTypeSSI(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_3|GPIO_PIN_2);
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 1000000, 8);
    SSIEnable(SSI0_BASE);
}

static void lowCSPin(void){

}

static void rc522WriteRaw(uint8_t ucAddress, uint8_t ucValue) {
    unsigned char ucAddr;
    struct spi_transfer SPITransfer[2];  
    struct spi_message  SPIMessage;
    CLR_SPI_CS;
    ucAddr = ((ucAddress<<1)&0x7E);

    //    SPIWriteByte(ucAddr);
    //    SPIWriteByte(value);
    spi_message_init( &SPIMessage );
    memset( SPITransfer, 0, sizeof(SPITransfer) );

    SPITransfer[ 0 ].tx_buf = &ucAddr;  
    SPITransfer[ 0 ].len = 1;
    spi_message_add_tail( &SPITransfer[0], &SPIMessage );
    SPITransfer[ 1 ].tx_buf = &ucValue;  
    SPITransfer[ 1 ].len = 1;  
    spi_message_add_tail( &SPITransfer[1], &SPIMessage );  
    spi_sync( rc522_spi, &SPIMessage );

    SET_SPI_CS;
}

static uint8_t rc522ReadRaw(uint8_t ucAddress) {
    uint8_t ucValue, ucAddr;
    int ret;
    CLR_SPI_CS;
    ucAddr = ((ucAddress << 1) & 0x7E) | 0x80;
    ret = spi_write_then_read(rc522_spi, &ucAddr, 1, &ucValue, 1);
    if(ret != 0) {
        UARTStringPut("spi_write_then_read err = %d\n");
    }
    SET_SPI_CS;
    return ucValue;    
}

static uint8_t rc522Check(uint8_t* id) {
    uint8_t status;
    UARTStringPut("rc522Check: Request -> Anticoll -> Halt\n");
    status = rc522ClearBitMask(PICC_REQIDL, id);                            // Find cards, return card type
    if (status == MI_OK) {
        UARTStringPut("rc522Check: Pass to call rc522ClearBitMask Func\n");
        status = rc522Anticoll(id);                                    // Card detected. Anti-collision, return card serial number 4 bytes
        if (status == MI_OK) 
            UARTStringPut("rc522Check: Pass to call rc522Anticoll Func\n");
        else 
            UARTStringPut("rc522Check: Fail to call rc522Anticoll Func\n");
        UARTStringPut("rc522Check: Next to the rc522Halt Func\n");
    }
    else 
    {
        UARTStringPut("rc522Check: Fail to call rc522ClearBitMask Func\nrc522Check: Skip rc522Anticoll Func and Jump to the rc522Halt Func\n");
    }
    rc522Halt();                                                        // Command card into hibernation 
    return status;
}

static uint8_t rc522Compare(uint8_t* cardID, uint8_t* compareID) {
    uint8_t i;
    for (i = 0; i < 5; i++) {
        if (cardID[i] != compareID[i]) 
        return MI_ERR;
    }
    return MI_OK;
}

static void rc522SetBitMask(uint8_t reg, uint8_t mask) {
    rc522WriteRaw(reg, rc522ReadRaw(reg) | mask);
}

static void rc522ClearBitMask(uint8_t reg, uint8_t mask){
    rc522WriteRaw(reg, rc522ReadRaw(reg) & (~mask));
}

static uint8_t rc522ClearBitMask(uint8_t reqMode, uint8_t* tagType) {
    uint8_t status;  
    uint16_t backBits;                                        // The received data bits

    rc522WriteRaw(rc522_REG_BIT_FRAMING, 0x07);        // TxLastBists = BitFramingReg[2..0]
    tagType[0] = reqMode;
    status = rc522ToCard(PCD_TRANSCEIVE, tagType, 1, tagType, &backBits);
    if ((status != MI_OK) || (backBits != 0x10)) 
    {
        status = MI_ERR;
        UARTStringPut("rc522ClearBitMask: Fail to call rc522ToCard Func\n");
    }
    else
        UARTStringPut("rc522ClearBitMask: Pass to call rc522ToCard Func\n");
    return status;
}

static uint8_t rc522ToCard(uint8_t command, uint8_t* sendData, uint8_t sendLen, uint8_t* backData, uint16_t* backLen) {
    uint8_t status     = MI_ERR;
    uint8_t irqEn     = 0x00;
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

    rc522WriteRaw(rc522_REG_COMM_IE_N, irqEn | 0x80);
    rc522ClearBitMask(rc522_REG_COMM_IRQ, 0x80);
    rc522SetBitMask(rc522_REG_FIFO_LEVEL, 0x80);
    rc522WriteRaw(rc522_REG_COMMAND, PCD_IDLE);

    // Writing data to the FIFO
    for (i = 0; i < sendLen; i++) 
    rc522WriteRaw(rc522_REG_FIFO_DATA, sendData[i]);

    // Execute the command
    rc522WriteRaw(rc522_REG_COMMAND, command);
    if (command == PCD_TRANSCEIVE) 
    rc522SetBitMask(rc522_REG_BIT_FRAMING, 0x80);        // StartSend=1,transmission of data starts 

    // Waiting to receive data to complete
    i = 2000;    // i according to the clock frequency adjustment, the operator M1 card maximum waiting time 25ms
    do {
        // CommIrqReg[7..0]
        // Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
        n = rc522ReadRaw(rc522_REG_COMM_IRQ);
        i--;
    } while ((i!=0) && !(n&0x01) && !(n&waitIRq));

    UARTStringPut("rc522ToCard:: i = %d\n",i);

    rc522ClearBitMask(rc522_REG_BIT_FRAMING, 0x80);                                                                // StartSend=0

    if (i != 0)  {
        if (!(rc522ReadRaw(rc522_REG_ERROR) & 0x1B)) {
            status = MI_OK;
            UARTStringPut("rc522ToCard: MI_OK with rc522ReadRaw Func\n");
            if (n & irqEn & 0x01) {
                status = MI_NOTAGERR;
                UARTStringPut("rc522ToCard: MI_NOTAGERR with rc522ReadRaw Func\n");
            }
            if (command == PCD_TRANSCEIVE) {
                n = rc522ReadRaw(rc522_REG_FIFO_LEVEL);
                lastBits = rc522ReadRaw(rc522_REG_CONTROL) & 0x07;
                if (lastBits) 
                *backLen = (n-1)*8+lastBits; else *backLen = n*8;
                if (n == 0) 
                n = 1;
                if (n > rc522_MAX_LEN) 
                n = rc522_MAX_LEN;
                for (i = 0; i < n; i++) 
                backData[i] = rc522ReadRaw(rc522_REG_FIFO_DATA);        // Reading the received data in FIFO
            }
        } else {
            status = MI_ERR;
            UARTStringPut("rc522ToCard: MI_ERR with rc522ReadRaw Func\n");
        }
    }
    return status;
}

static uint8_t rc522Anticoll(uint8_t* serNum) {
    uint8_t status;
    uint8_t i;
    uint8_t serNumCheck = 0;
    uint16_t unLen;

    rc522WriteRaw(rc522_REG_BIT_FRAMING, 0x00);                                                // TxLastBists = BitFramingReg[2..0]
    serNum[0] = PICC_ANTICOLL;
    serNum[1] = 0x20;
    status = rc522ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);
    if (status == MI_OK) {
        // Check card serial number
        for (i = 0; i < 4; i++) 
        serNumCheck ^= serNum[i];
        if (serNumCheck != serNum[i]) 
        status = MI_ERR;
    }
    return status;
} 

static void rc522CalculateCRC(uint8_t*  pIndata, uint8_t len, uint8_t* pOutData) {
    uint8_t i, n;

    rc522ClearBitMask(rc522_REG_DIV_IRQ, 0x04);                                                     // CRCIrq = 0
    rc522SetBitMask(rc522_REG_FIFO_LEVEL, 0x80);                                                    // Clear the FIFO pointer
    // Write_rc522(CommandReg, PCD_IDLE);

    // Writing data to the FIFO    
    for (i = 0; i < len; i++) 
    rc522WriteRaw(rc522_REG_FIFO_DATA, *(pIndata+i));

    rc522WriteRaw(rc522_REG_COMMAND, PCD_CALCCRC);

    // Wait CRC calculation is complete
    i = 0xFF;
    do {
        n = rc522ReadRaw(rc522_REG_DIV_IRQ);
        i--;
    } while ((i!=0) && !(n&0x04));                                                                    // CRCIrq = 1

    // Read CRC calculation result
    pOutData[0] = rc522ReadRaw(rc522_REG_CRC_RESULT_L);
    pOutData[1] = rc522ReadRaw(rc522_REG_CRC_RESULT_M);
}

static uint8_t rc522SelectTag(uint8_t* serNum) {
    uint8_t i;
    uint8_t status;
    uint8_t size;
    uint16_t recvBits;
    uint8_t buffer[9]; 

    buffer[0] = PICC_SELECTTAG;
    buffer[1] = 0x70;
    for (i = 0; i < 5; i++) 
    buffer[i+2] = *(serNum+i);
    rc522CalculateCRC(buffer, 7, &buffer[7]);        //??
    status = rc522ToCard(PCD_TRANSCEIVE, buffer, 9, buffer, &recvBits);
    if ((status == MI_OK) && (recvBits == 0x18)) 
    size = buffer[0]; 
    else 
    size = 0;
    return size;
}

static uint8_t rc522Auth(uint8_t authMode, uint8_t blockAddr, uint8_t* sectorKey, uint8_t* serNum) {
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
    status = rc522ToCard(PCD_AUTHENT, buff, 12, buff, &recvBits);
    if ((status != MI_OK) || (!(rc522ReadRaw(rc522_REG_STATUS2) & 0x08))) 
    status = MI_ERR;
    return status;
}

static uint8_t rc522Read(uint8_t blockAddr, uint8_t* recvData) {
    uint8_t status;
    uint16_t unLen;

    recvData[0] = PICC_READ;
    recvData[1] = blockAddr;
    rc522CalculateCRC(recvData,2, &recvData[2]);
    status = rc522ToCard(PCD_TRANSCEIVE, recvData, 4, recvData, &unLen);
    if ((status != MI_OK) || (unLen != 0x90)) status = MI_ERR;
    return status;
}

static uint8_t rc522Write(uint8_t blockAddr, uint8_t* writeData) {
    uint8_t status;
    uint16_t recvBits;
    uint8_t i;
    uint8_t buff[18]; 

    buff[0] = PICC_WRITE;
    buff[1] = blockAddr;
    rc522CalculateCRC(buff, 2, &buff[2]);
    status = rc522ToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);
    if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A)) 
    status = MI_ERR;
    if (status == MI_OK) {
        // Data to the FIFO write 16Byte
        for (i = 0; i < 16; i++) buff[i] = *(writeData+i);
        rc522CalculateCRC(buff, 16, &buff[16]);
        status = rc522ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);
        if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A)) 
        status = MI_ERR;
    }
    return status;
}

void rc522Init(void) {
    unsigned char a;

    rc522Reset();
    rc522WriteRaw(rc522_REG_T_MODE, 0x8D);
    rc522WriteRaw(rc522_REG_T_PRESCALER, 0x3E);
    rc522WriteRaw(rc522_REG_T_RELOAD_L, 30);           
    rc522WriteRaw(rc522_REG_T_RELOAD_H, 0);
    rc522WriteRaw(rc522_REG_RF_CFG, 0x70);                // 48dB gain    
    rc522WriteRaw(rc522_REG_TX_AUTO, 0x40);
    rc522WriteRaw(rc522_REG_MODE, 0x3D);
    a = rc522ReadRaw(rc522_REG_T_RELOAD_L);
    if(a != 30)
        UARTStringPut("### rc522Init: NO RC522 - %d ###\n",a);
    else
        UARTStringPut("### rc522Init: RC522 exist ###\n");
    rc522AntennaOn();                                                                        // Open the antenna
}

static void rc522Reset(void) {
    rc522WriteRaw(rc522_REG_COMMAND, PCD_RESETPHASE);
}

static void rc522AntennaOn(void) {
    uint8_t temp;

    temp = rc522ReadRaw(rc522_REG_TX_CONTROL);
    if (!(temp & 0x03)) 
    rc522SetBitMask(rc522_REG_TX_CONTROL, 0x03);
}

static void rc522AntennaOff(void) {
    rc522ClearBitMask(rc522_REG_TX_CONTROL, 0x03);
}

static void rc522Halt(void) {
    uint16_t unLen;
    uint8_t buff[4]; 

    buff[0] = PICC_HALT;
    buff[1] = 0;
    rc522CalculateCRC(buff, 2, &buff[2]);
    rc522ToCard(PCD_TRANSCEIVE, buff, 4, buff, &unLen);
}
