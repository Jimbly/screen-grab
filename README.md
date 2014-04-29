screen-grab#lightning-dodger
===========

This particular branch is set up to be used to solve the Lighting Dodging game in Final Fantasy X, which can be incredibly challenging in the HD Remaster on modern hardware due to the increased latency of wireless controllers, HD display devices, etc.

Prequisites
-----
* Webcam or other video capture source (anything that gets a low-latency image of your PS3 onto your computer screen)
* Adapter that works with GIMX, I went with the [Kensington Bluetooth USB Micro](http://www.amazon.com/gp/product/B000YA1XU2/ref=oh_details_o01_s00_i00?ie=UTF8&psc=1), more compatible adapters listed on the [GIMX site](http://gimx.fr/wiki/index.php?title=Bluetooth_dongle).

Installation
-----
1. Install [Ubuntu](http://www.ubuntu.com/download/desktop), possibly just onto a [USB stick](http://www.pendrivelinux.com/universal-usb-installer-easy-as-1-2-3/). (Or other Linux variety)
1. Install [GIMX](http://gimx.fr)
1. Configure GIMX to be able to control your PS3, I set up a simple config so I could use WASD for directional keys to ensure it's working.  See the GIMX site for info on configuring GIMX.
1. Get this repository, check out this branch, build it
```
git clone git@github.com:Jimbly/screen-grab.git
cd screen-grab
git checkout lightning_dodger
./make.sh
```
You may need to install some pre-requisites, I probably forgot some, but at least these were needed:
```
sudo apt-get install g++
sudo apt-get install libx11-dev
```

Usage
-----
1. Start a webcam or video input viewer ("Cheese Webcam Booth" that comes pre-installed on Ubuntu works fine)
2. Start FFX, get your character into a corner in the Thunder Plains, I found the little L-shaped hole in the south part of the Thunder Plains worked good because neither dodging nor getting hit could move you out of it (you don't want to end up in a lightning-safe area after a few hundred dodges!)
3. Start GIMX, under the "emu" section, uncheck "auto-start emuclient", click Start.
4.# Run this program
```
cd screen-grab
./grabber.out
```
5. Move the mouse over your video source and leave it on a darker part of the screen (which will turn bright white when lightning strikes).
6. Watch to make sure it dodges a couple lightning strikes in a row.
  * There should be output from this program when it detects a flash and tries to dodge and calls GIMX's emuclient command
  * If there's no errors from GIMX, it should actually doge.
8. ...
9. Profit!




Windows
-------
In theory, with specialized hardware, GIMX works on Windows as well, and it should be very easy for me to convert this to Windows using [Jimbly's VeggieTales](http://www.bigscreensmallgames.com/VeggieTales/) (Windows automation tool), let me know if you're interested once you've actually gotten GIMX working (interfacing with that will be the only unknown part).


Attributions
------------
Some code initially gleaned from [boblight](https://code.google.com/p/boblight/).
