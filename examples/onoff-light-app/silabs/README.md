# Matter EFR32 OnOff Light Example Application

This example demonstrates a Matter OnOff Light device on the Silicon Labs EFR32 platform.

## Features
- Matter OnOff cluster implementation
- LED fast blinking during commissioning phase
- Thread networking support
- Matter commissioning support

## Building and Running
Follow the standard Silicon Labs Matter build process:

```
cd ~/repos/connectedhomeip
source scripts/activate.sh
gn gen out/onoff-light-app-efr32
ninja -C out/onoff-light-app-efr32
```

## LED Indicators
- LED fast blinking (100ms on/off): Device is in commissioning mode
- LED solid on: Light is on
- LED off: Light is off
