# Alternating Blink: Using the CTC interrupt to keep the light on longer than it's off

A simple `C` program to toggle the on-board LED of an Arduino Uno board on for 2 seconds, then off for 1 second.

## To build and flash

Ensure hardware and software pre-reqs are met by reviewing [this](https://github.com/rubberduck203/embedded-101#hardware) section.

1. Ensure board is connected via USB.
2. Verify `default_serial` field in your `.avrduderc` file is correct.
3. Grant execution permissions to the `compile.sh` in this directory.
4. Run it and verify from terminal output the program built and flashed correctly.

## Timer Math

### 1024 Prescaler on 16mhz processor

| Metric | Formula | Result |
| ------ |:-------:| ------:|
| Ticks per second | 16,000,000 / 1024 - 1 | 15,624 |
| Prescale Resolution | 1024 / 16,000,000 | 0.000064 |
| Overflow Time (seconds) | 65,535 * 0.000064 | 4.19424 |
