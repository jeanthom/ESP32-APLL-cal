# ESP32 APLL calculator

ESP-IDF's built-in APLL (audio PLL) configurator is not very precise. This calculator use a bruteforce approach to get more accurate values.

The target values and parameters (target frequency, chip revision, Xtal) are hardcoded in `src/main.c`.

## Building ESP32-APLL-cal

```
$ make
$ ./esp32-apll-cal
```
