                                                                                                
#define CS        PORTEbits.RE2

//################################### ADE7758 ################################//

#define AWATTHR   0x01
#define BWATTHR   0x02
#define CWATTHR   0x03
#define AVARHR    0x04
#define BVARHR    0x05
#define CVARHR    0x06
#define AVAHR     0x07
#define BVAHR     0x08
#define CVAHR     0x09
#define AIRMS     0x0A
#define BIRMS     0x0B
#define CIRMS     0x0C
#define AVRMS     0x0D
#define BVRMS     0x0E
#define CVRMS     0x0F
#define FREQ      0x10
#define TEMP      0x11
#define WFORM     0x12
#define OPMODE    0x13
#define MMODE     0x14
#define WAVMODE   0x15
#define COMPMODE  0x16
#define LCYCMODE  0x17
#define MASK      0x18
#define STATUS    0x19
#define RSTATUS   0x1A
#define ZXTOUT    0x1B
#define LINECYC   0x1C
#define SAGCYC    0x1D
#define SAGLVL    0x1E
#define VPINTLVL  0x1F
#define IPINTLVL  0x20
#define VPEAK     0x21
#define IPEAK     0x22
#define GAIN      0x23
#define AVRMSGAIN 0x24
#define BVRMSGAIN 0x25
#define CVRMSGAIN 0x26
#define AIGAIN    0x27
#define BIGAIN    0x28
#define CIGAIN    0x29
#define AWG       0x2A
#define BWG       0x2B
#define CWG       0x2C
#define AVARG     0x2D
#define BVARG     0x2E
#define CVARG     0x2F
#define AVAG      0x30
#define BVAG      0x31
#define CVAG      0x32
#define AVRMSOS   0x33
#define BVRMSOS   0x34
#define CVRMSOS   0x35
#define AIRMSOS   0x36
#define BIRMSOS   0x37
#define CIRMSOS   0x38
#define AWAITOS   0x39
#define BWAITOS   0x3A
#define CWAITOS   0x3B
#define AVAROS    0x3C
#define BVAROS    0x3D
#define CVAROS    0x3E
#define APHCAL    0x3F
#define BPHCAL    0x40
#define CPHCAL    0x41
#define WDIV      0x42
#define VADIV     0x44
#define VARDIV    0x43
#define APCFNUM   0x45
#define APCFDEN   0x46
#define VARCFNUM  0x47
#define VARCFDEN  0x48
#define CHKSUM    0x7E
#define VERSION   0x7F

#define PHASE		0x10	// Phase One, Data Read on falling edge of CLK
//*******************************DATA READ************************************//
unsigned char SPI_Read(unsigned char REG_ADDR)
{
    unsigned char recv_data=0;
    
    CS = 0;//CS ENABLE
    Delay1TCY(1);   //SOME DELAY TO STABALIZE CHIP SELECT
    WriteSPI(REG_ADDR);
    _delay(10);
    WriteSPI(0x00);
    recv_data=SSPBUF;
    Delay1TCY(1);   //SOME DELAY TO STABALIZE CHIP SELECT
    CS = 1;//CS_DISABLE
    
    return ( recv_data );      // RETURN READ DATA 
}
//*******************************DATA WRITE************************************//
void SPI_Write(unsigned char REG_ADDR,unsigned char DATA)
{
    CS = 0;//CS ENABLE
    Delay1TCY(1);   //SOME DELAY TO STABALIZE CHIP SELECT
    
    //WriteSPI(SPI_SLAVE_ID_W_WRITE);//SENDING DEVICE ADDRESS(0X40) WITH READ BIT(WRITE=1))
    WriteSPI(REG_ADDR);//SENDING DEVICE REGISTER CONTROL BYTE TO SLAVE DEVICE
    WriteSPI(DATA);//SEND DATA INTO SLAVE
    
    Delay1TCY(1);   //SOME DELAY TO STABALIZE CHIP SELECT
    CS = 1;//CS_DISABLE

    
}

unsigned long read16bits(char REG_ADDR)
{
    
    unsigned int ret1=0;
    unsigned char ret2=0;
    unsigned long x=0;
 
    CS=0;
    
    _delay(10);
    WriteSPI(REG_ADDR);
    _delay(10);
    WriteSPI(0x00);
    ret1=SSPBUF;
    _delay(2);
    WriteSPI(0x00);
    ret2=SSPBUF;
    _delay(2);
    
    CS=1;
    
    x= ((unsigned int)ret1<<8)|ret2;
    return x;
}

unsigned long read24bits(char REG_ADDR)
{
    CS=0;
    unsigned long ret=0;
    unsigned int ret1=0;
    unsigned char ret0=0;
    unsigned long x=0;
    
    _delay(10);
    WriteSPI(REG_ADDR);
    _delay(10);
    WriteSPI(0x00);
    ret=SSPBUF;
    _delay(2);
    WriteSPI(0x00);
    ret1=SSPBUF;
    _delay(2);
    WriteSPI(0x00);
    ret0=SSPBUF;
    _delay(1);
    
    CS=1;

    x= ((unsigned long)ret<<16)|((unsigned int)ret1<<8)|ret0;
    return x;
    
}
//**************************INITIALIZE SPI AND MCU PORT************************//
void INTI_ADE7758()
{
  CloseSPI(); //TURN OFF SPI MODULE IF IT WAS OPEN 
   
//*********************CONFIGURE SPI MASTER DEVICE'S HARDWARE******************//
  
  OpenSPI(SPI_FOSC_64,MODE_10,SMPMID);

//******************INITIALIZE HARDWARE I/O PINS FOR SLAVE DEVICE***********//

  TRISEbits.TRISE2 = 0;   // /CS - Output (Chip Select)
  TRISCbits.TRISC5 = 0;   // /SDO - Output (Serial Data Out)
  TRISCbits.TRISC4 = 1;   // /SDI - Input (Serial Data In)
  TRISCbits.TRISC3 = 0;   // /SCK - Output (Clock)
  TRISCbits.TRISC1 = 0;   // /RST - Output (MCP23S18 Hardware Reset)
  
  CS = 1;                                        // DISABLE MSC28S18 !CS 
  Delay1TCYx (40);       // WAIT TO STABALIZE VOLTAGE @ ADE7758
  
}
