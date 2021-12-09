# xmas-lights-inverted-pwm
Run one or two strings of Christmas lights from an Arduino.

This sketch is intended to control the type of lights that have a string of LEDs wired in reversed pairs. When current flows one way all the even LEDs light, and when the current is reversed the odd LEDs light.

This code attaches pairs of pins to the same PWM timer, with one pin inverted so that outputting 0-255 controls both "sides" of each string of lights. At 0 one set of LEDs is on, at 255 the other set is on. At 128, both sets are illuminated together by the — effectively — AC voltage.

This allows for some gentle crossfades between lights on the same string.

You'll need some sort of h-bridge to power the LEDs themselves, the voltage and current required would be the last thing the poor arduino ever saw ✝
