How to build and install the multi pin mod
  
You have to use platformio to get this compiled correctly:
  
(I'm using windows 10, but these tools are all cross platform:)
  
Prereqs:  
1. Install Python  
2. Install git  
3. Install Visual Studio Code  
4. Reboot  
5. Install PlatformIO Extension inside Visual Studio code  
6. Clone the multipin fork repo:  

```
cd ~  
git clone https://github.com/peacepenguin/WLED  
```
  
Now inside Visual Studio Code, click the PlatformIO option in the left menu.  
From PlatformIO home, click "Open Project" Browse to the WLED code downloaded from git.  
    In Linux: "/home/username/WLED"   or Windows: "c:\users\username\WLED"
  
In the file: /wled00/NpbWrapper.h adjust these params to match your setup:
  
```
NUM_STRIPS          # set this value to the total # of pins you want to output on
  
STRIP1_PIN          # set what GPIO pin to output on for each strip
STRIP2_PIN          #
...
  
STRIP1_LEDCOUNT     # total leds attached to STRIP1's gpio pin
STRIP2_LEDCOUNT     # total leds attached to STRIP2's gpio pin
...
   
```
  
Then click the Project Tasks section of Platformio, click "Upload" to build and upload to your ESP32, assuming its attached via serial.
  
Configure WLED as normal, make sure to set the WEB gui's LED quantity to match your Total LED count in the system. Then save and reboot the ESP32. Use WLED as normal.

Note: 8-pin is possible on ESP32. 2-pin is possible on ESP8622.  

If using ESP8622 you must adjust the PIXELMETHOD params for the 2-pins you can use:
```
STRIP1_PIXELMETHOD NeoEsp8266Uart1Ws2812xMethod
STRIP2_PIXELMETHOD NeoEsp8266DmaWs2812xMethod
```
  
Then configure /platformio.ini for your specific board type. Comment out the default_envs = esp32dev, and set default_envs to your board. 
Example:  
```
; default_envs = esp32dev
default_envs = d1_mini_ota
```
  
ADVANCED USAGE:
  
For mixed GRB / RGB strips on different pins. You need to adjust the color order for specific strips in the code itself.
  
Example to change only strip 4's color order from the default GRB that most common ws2812 led's operate at into RGB color order.
  
Find the strip 4 set color code in the NpbWrapper.h file:
```
_pGrb4->SetPixelColor((indexPixel -= STRIP4_STARTLED), RgbColor(col.R,col.G,col.B));
```
Change the color order after "RgbColor("

From this:
```
RgbColor(col.R,col.G,col.B))
```
Into this:
```
RgbColor(col.G,col.R,col.B))
```

