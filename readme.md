# Arduino CS5460A sketch
Standalone CS5460A sketch. Tested on measurement board from cheap ebay power meter.

![ebay special power meter](https://raw.githubusercontent.com/kolinger/arduino_cs5460a/master/ebay-special-power-meter.jpg)

Based on random pieces found on the internet. Also based on conversions and SPI dumps from https://github.com/zerog2k/power_meter_cs5460a.

# WARNING
Ground reference of PCB inside meter is tied to HOT (Line). It is at mains level. Use galvanic isolation, e.g. optocouplers, etc if you want to wire this up directly to something else. Be sure you know what your are doing around potentially lethal mains-level voltages. Use at your own risk!
