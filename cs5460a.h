 
#ifdef  CS5460A_GLOBALS
    #define  CS5460A_EXT 
#else
    #define  CS5460A_EXT    extern
#endif

#ifdef ARDUINO
  #include "Arduino.h"
#endif

#include <stdint.h>
#include <stdio.h>


//#define    CS5460A_CS_DDR       DDRB
#define  CS5460A_SCK_DDR      DDRB
#define  CS5460A_SDI_DDR      DDRB
#define  CS5460A_SDO_DDR      DDRB
#define  CS5460A_RST_DDR      DDRB

//#define  CS5460A_CS_PORT       PORTB
#define  CS5460A_SCK_PORT      PORTB
#define  CS5460A_SDI_PORT      PORTB
#define  CS5460A_SDO_PORT      PORTB
#define  CS5460A_RST_PORT      PORTB

#define    CS5460A_SDI_PIN       PINB

//#define  CS5460A_CS               0          //PORTB0
#define  CS5460A_SCK              1          //PORTB1
#define  CS5460A_SDI              2          //PORTB2
#define  CS5460A_SDO              3          //PORTB3
#define  CS5460A_RST              4          //PORTB4

#define  CS5460A_RMS_VOLTAGE     0x18
#define  CS5460A_RMS_CURRENT     0x16
#define  CS5460A_TRUE_POWER      0x14	


#define  CS5460A_CFG_READ        0x00  //reg read: config
#define  CS5460A_CFG_READ_IGN    0x04  //reg read: Ign
#define  CS5460A_CFG_READ_VGN    0x08  //reg read: Vgn
#define  CS5460A_CFG_READ_CYCLE  0x0a  //reg read: cycle count

#define  CS5460A_CFG_POWER_UP    0xa0  // power-up/halt

#define  CS5460A_CFG_GAIN0       0x40  // reg write: config. PGA Gain 50x, IHPF=1, VHPF=1
#define  CS5460A_CFG_GAIN1       0x01
#define  CS5460A_CFG_GAIN2       0x00
#define  CS5460A_CFG_GAIN3       0x61

#define  CS5460A_CFG_IGN0        0x44  // reg write: Ign [current chan gain]. value: 1.15935
#define  CS5460A_CFG_IGN1        0x4a
#define  CS5460A_CFG_IGN2        0x32
#define  CS5460A_CFG_IGN3        0xdf

#define  CS5460A_CFG_VGN0        0x48  // reg write: Vgn [voltage chan gain]. value: 0.97823
#define  CS5460A_CFG_VGN1        0x3e
#define  CS5460A_CFG_VGN2        0x9b
#define  CS5460A_CFG_VGN3        0x5a

#define  CS5460A_START_CONV    0xe8  // start conversion, continuous


  

#ifdef __cplusplus
extern "C" {
#endif

CS5460A_EXT void configCS5460A(void);

CS5460A_EXT void initCS5460A(void);

CS5460A_EXT uint32_t readCS5460A(uint8_t IdData);

CS5460A_EXT void writeCS5460A(uint8_t ComndData);

#ifdef __cplusplus
}
#endif

