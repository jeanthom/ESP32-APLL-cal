# ESP32 APLL calculator

ESP-IDF's built-in APLL (audio PLL) configurator is not very precise. This calculator use a bruteforce approach to get more accurate values.

The target values and parameters (target frequency, chip revision, Xtal) are hardcoded in `src/main.c`.

## Building ESP32-APLL-cal

```
$ make
$ ./esp32-apll-cal
f=24575996.4 Hz, ∆f=3.6 Hz (relative: 0.0000%)
sdm0=149, sdm1=212, sdm2=5, odiv=6
```

## Documentation

 * [ESP32 Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
 * [ESP32 ECO and Workarounds for Bugs](https://www.espressif.com/sites/default/files/documentation/eco_and_workarounds_for_bugs_in_esp32_en.pdf)
