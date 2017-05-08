#include <stdint.h>
#include <stdio.h>
#include "cs5460a.h"


#define VOLTAGE_RANGE 0.250                 // full scale V channel voltage
#define CURRENT_RANGE 0.050                 // full scale I channel voltage (PGA 50x instead of 10x)
#define VOLTAGE_DIVIDER 450220.0 / 220.0    // input voltage channel divider (R1+R2/R2)
#define CURRENT_SHUNT 620                   // empirically obtained multiplier to scale Vshunt drop to I    
#define FLOAT24 16777216.0                  // 2^24 (converts to float24)
#define POWER_MULTIPLIER 1 / 512.0          // Energy->Power divider; not sure why, but seems correct. Datasheet not clear about this.

#define VOLTAGE_MULTIPLIER   (float)  (1 / FLOAT24 * VOLTAGE_RANGE * VOLTAGE_DIVIDER)
#define CURRENT_MULTIPLIER   (float)  (1 / FLOAT24 * CURRENT_RANGE * CURRENT_SHUNT)

double voltage = 0;
double current = 0;
double true_power = 0;
double apparent_power = 0;
double power_factor = 0;


void setup()
{
  Serial.begin(9600);

  configCS5460A();
  
  initCS5460A();
}


void loop()
{
  delay(1000);
  
  uint32_t data = readCS5460A(0x1e);
  
  if(data != 0x9003c1) {
    return;
  }
  
  voltage = readCS5460A(CS5460A_RMS_VOLTAGE) * VOLTAGE_MULTIPLIER;
  current = readCS5460A(CS5460A_RMS_CURRENT) * CURRENT_MULTIPLIER;
  
  true_power = (double) readCS5460A(CS5460A_TRUE_POWER) * POWER_MULTIPLIER;
  apparent_power = voltage * current;
  
  power_factor = true_power / apparent_power;

  
  Serial.print("voltage: ");
  Serial.print(voltage, 4);
  
  Serial.print(", current: ");
  Serial.print(current, 4);
  
  Serial.print(", true power: ");
  Serial.print(true_power, 4);
  
  Serial.print(", apparent power: ");
  Serial.print(apparent_power, 4);
  
  Serial.print(", power factor: ");
  Serial.print(power_factor, 2);
  
  Serial.print("\n");
}

