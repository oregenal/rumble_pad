# Rumble_Pad
Simple console app to rumble by the gamepad.  
Developed special for *DualShock 4*, but must work on any.  

## Usage
```console
$ rumble_pad ffff ffff 200 3
```
First two parameters `ffff` is 16bit hexadecimal - rumble power. First for low
and second for high rumble motor respectively.  
Third parameter `200` is 32bit decimal - duration in milliseconds.  
Forth parameter `3` is 32bit decimal - times.

## Dependencies
- [SDL2](https://www.libsdl.org/)
