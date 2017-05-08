#define     CS5460A_GLOBALS

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif 

#include    "cs5460a.h"


void configCS5460A(void)
{
  sbi(CS5460A_SCK_DDR, CS5460A_SCK);
  sbi(CS5460A_SDI_DDR, CS5460A_SDI);
  cbi(CS5460A_SDO_DDR, CS5460A_SDO);
  sbi(CS5460A_RST_DDR, CS5460A_RST);

  sbi(CS5460A_SCK_PORT, CS5460A_SCK);
  cbi(CS5460A_SDI_PORT, CS5460A_SDI);

  cbi(CS5460A_RST_PORT, CS5460A_RST);
  delay(20);
  sbi(CS5460A_RST_PORT, CS5460A_RST);
}


void initCS5460A(void)
{
  writeCS5460A(CS5460A_CFG_POWER_UP);

  readCS5460A(CS5460A_CFG_READ);

  writeCS5460A(CS5460A_CFG_GAIN0);
  writeCS5460A(CS5460A_CFG_GAIN1);
  writeCS5460A(CS5460A_CFG_GAIN2);
  writeCS5460A(CS5460A_CFG_GAIN3);

  writeCS5460A(CS5460A_CFG_IGN0);
  writeCS5460A(CS5460A_CFG_IGN1);
  writeCS5460A(CS5460A_CFG_IGN2);
  writeCS5460A(CS5460A_CFG_IGN3);

  writeCS5460A(CS5460A_CFG_VGN0);
  writeCS5460A(CS5460A_CFG_VGN1);
  writeCS5460A(CS5460A_CFG_VGN2);
  writeCS5460A(CS5460A_CFG_VGN3);

  readCS5460A(CS5460A_CFG_READ);

  readCS5460A(CS5460A_CFG_READ_IGN);
   
  readCS5460A(CS5460A_CFG_READ_VGN);

  readCS5460A(CS5460A_CFG_READ_CYCLE);

  writeCS5460A(CS5460A_START_CONV);

  return;
}

void writeCS5460A(uint8_t data)
{
  uint8_t i;
  //cbi(CS5460A_CS_PORT, CS5460A_CS);

  delayMicroseconds(5);	 
  
  for(i = 0; i < 8; i++)
  {
    cbi(CS5460A_SCK_PORT, CS5460A_SCK);
    delayMicroseconds(5);      																																																																																																																																																																																														
    
    if(data & 0x80) {
      sbi(CS5460A_SDI_PORT, CS5460A_SDI);
    } else {
      cbi(CS5460A_SDI_PORT, CS5460A_SDI);
    }
    
    delayMicroseconds(5);	   
    sbi(CS5460A_SCK_PORT, CS5460A_SCK);
    delayMicroseconds(15);	         
		
		data <<= 1;   
  } 
  
	//sbi(CS5460A_CS_PORT, CS5460A_CS);
  delayMicroseconds(2);  
	
	return;
}

uint32_t readCS5460A(uint8_t cmdData)
{
  uint8_t i;
	volatile uint32_t data = 0;
 
  writeCS5460A(cmdData); 
	
	cbi(CS5460A_SCK_PORT, CS5460A_SCK);
 
	delayMicroseconds(5);

	for(i = 0; i < 24; i++)        
  {
		data <<= 1;
		sbi(CS5460A_SDI_PORT, CS5460A_SDI);
		delayMicroseconds(15);
    cbi(CS5460A_SCK_PORT, CS5460A_SCK);
		delayMicroseconds(15);
		sbi(CS5460A_SCK_PORT, CS5460A_SCK);//
		delayMicroseconds(11);
    
		if((CS5460A_SDI_PIN & (1 << CS5460A_SDO)) == (1 << CS5460A_SDO))    
		{
			data |= 0x01;
    }
  }
	
	if(cmdData == CS5460A_TRUE_POWER)
	{
    if((data & 0x00100000))
		{
      data = (~data) + 1; 
	    data &= 0xffffff;
    }
  }
  
	//sbi(CS5460A_CS_PORT, CS5460A_CS);     
  
  return data;
} 

