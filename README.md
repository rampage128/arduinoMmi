# arduinoMmi

> Connect your Audi MMI to your Arduino

This is a library for [Arduino](https://www.arduino.cc/en/Main/Products#entrylevel) devices. 
It allows connecting an [Audi Multi Media Interface](https://de.wikipedia.org/wiki/Audi_MMI) 
to your arduino, to read button events and toggle its lights.

__Please make sure to read the [requirements](#requirements)__!

## Background

The [Audi MMI](https://de.wikipedia.org/wiki/Audi_MMI) is sometimes used for custom car projects.
This library aims at providing a simple layer to integrate the MMI into any code project.

## Requirements

- [Arduino](https://www.arduino.cc/en/Main/Products#entrylevel) 
  (Should also work on teensy and other arduino compatible platforms!)
- [Audi MMI](https://de.wikipedia.org/wiki/Audi_MMI)
- [arduinoIO](https://github.com/rampage128/arduinoIO), a library for button events

## Installation
### Releases

No releases, you have to clone or download [From source](#from-source)

### From source

1. Get your favourite [Arduino IDE](https://www.arduino.cc/en/main/software)
2. Clone the repository into your library directory  
   ```
   git clone https://github.com/rampage128/arduinoMmi.git
   ```
3. Start a new sketch and add the library to it

## Usage

__IMPORTANT:__ First make sure you installed [arduinoIO](https://github.com/rampage128/arduinoIO#installation) 
library aswell! Unfortunately the arduino IDE does not resolve library dependencies
automatically. So you will have to make sure you [installed](https://github.com/rampage128/arduinoIO#installation) 
and [included](https://github.com/rampage128/arduinoIO#usage) it yourself!

After importing `#import <arduinoMmi.h>`, you can create a new MMI:
```
Mmi mmi(HardwareSerial *serial, uint32_t mode, uint8_t bufferSize, uint8_t buttonCount, uint8_t wheelCount);
```
- `serial`: a pointer to the serial port you want to use: for example `&Serial`.
- `mode`: the serial mode to use for communication. On most MMIs `SERIAL_8N2_RXINV` is used.
- `bufferSize`: the size in bytes of the serial communication buffer. `16` Sounds like a good choice.
- `buttonCount`: the number of buttons your MMI has. Most MMIs have `17` buttons.
- `wheelCount`: the number of wheels your MMI has. Usually that is `2`.

To make the mmi work, you should update the mmi in every loop:
```
mmi.update(mmiEvent);
```
The update method takes a callback function which you can define as follows:
```
void mmiEvent(uint8_t code) {
  ...
}
```
This callback function will be called by the MMI whenever there is a system event happening. This
includes the following events:
- `0x35`: Triggered after the MMI was fully activated
- `0x38`: Power button is pressed
- `0xff`: Power is turned on (12v)

To be able to use the MMI properly, you will have to activate it. Since some people might want to
only activate it under certain conditions, the library does not automatically do this.
It can easily be done in the update callback by calling `enableKeys()`:
```
void mmiEvent(uint8_t code) {
  if (code == 0xff || code == 0x38) {
    mmi.enableKeys();
  }
}
```
If you do not call this, the MMI will not be usable. Also you can not call this whenever you want,
the keys can only be enabled within 10-20 seconds after a power on event or a power button event 
was sent from the MMI.

Now you can use the following features:

### Buttons

You can create buttons by using their IDs:
```
MmiButton *mmiNavButton = mmi.createButton(0x05);
```
- `0x01`: pressing the big wheel
- `0x02`: media button
- `0x03`: name button
- `0x04`: tel button
- `0x05`: nav button
- `0x06`: info button
- `0x07`: car button
- `0x08`: setup button
- `0x0A`: top left button
- `0x0B`: bottom left button
- `0x0C`: previous button
- `0x0D`: top right button
- `0x0E`: bottom right button
- `0x0F`: return button
- `0x10`: next button
- `0x18`: radio button
- `0x38`: pressing the small wheel

The buttons can then be used in the same way as buttons from the [arduinoIO library](https://github.com/rampage128/arduinoIO#advanced-input).

### Wheels

Wheels are created in the same way as buttons:
```
MmiWheel *mmiSmallWheel = mmi.createWheel(0x40);
```
- `0x40`: small wheel
- `0x50`: big wheel

You can check interaction with a wheel like this:
```
if (mmiSmallWheel->wasTurned()) {
  if (mmiSmallWheel->getAmount() < 0) {
    // turned left
  }
  else {
    // turned right
  }
}
```

### Lights

Lights work in a similar fashion. But you need to hand in a pointer to your previously created MMI object:
```
MmiLight mmiMediaLight(0x02, &mmi);
```
The lights use the same IDs as their corresponding buttons.

__Important note:__ in order to use the lights, you have to set the illumination levels on the MMI first.

You can do that after the MMI was activated:
```
void mmiEvent(uint8_t code) {
  if (code == 0x35) {
	mmi.setIllumination(0xFF);
    mmi.setHighlightLevel(0x99);
  }
```
- `setIllumination()`: sets the intensity of the global backlight from `0` (off) to `255` (full brightness).
- `setHighlightLevel()`: sets the intensity of the button highlights from `0` (off) to `255` (full brightness).

You do not need to call `setIllumination()` for the highlight lights to work. But without calling `setHighlightLevel()`
they will not work.

You can interact with the lights like this:
- `setOn()`: switches the light on.
- `setOff()`: switches the light off.
- `set(boolean state)`: switches the light on or off depending on the provided `state`.
- `toggle()`: toggles the light on if it is off and vice versa.
- `isOn()`: returns `true` if the light is currently on.

For more information, please refer to the [source](https://github.com/rampage128/arduinoMmi).

## Contribute

Feel free to [open an issue](https://github.com/rampage128/arduinoIO/issues) or submit a PR

Also, if you like this or other of my projects, please feel free to support me using the Link below.

[![Buy me a beer](https://img.shields.io/badge/buy%20me%20a%20beer-PayPal-green.svg)](https://www.paypal.me/FrederikWolter/1)

## Dependencies

- [arduinoIO](https://github.com/rampage128/arduinoIO) to make the buttons work