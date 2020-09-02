# ESP32 Wifi Tank web control code

Esp32 webserver robot tank control. Uses only one Jostick to control the movement. Based on TB6612FNG motor driver and smars project robot, uses async HTML protocol. 

## Configuration

You need to modify your password and SSID to a personal one, and set your TB6612FNG Driver pins.

src/config.h contains the setup.

## More info

You can find more detailed info about how it works and hoy to modify it in the following [blog post](https://nkmakes.github.io/2020/09/02/esp32-tank-robot-joystick-http-web-control/), and see it in action in the following [youtube video](https://www.youtube.com/watch?v=uIImwilvI2s).


## Used Libraries and acknowledgements

Uses the following libraries and couldn't be done withouth the following posts
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [TB6612_ESP32](https://github.com/pablopeza/TB6612FNG_ESP32)
- [jostick JS library from bobbotek](https://github.com/bobboteck/JoyStick)
- [Differential control](https://www.impulseadventure.com/elec/robot-differential-steering.html)
- [Async service](https://github.com/neonious/lowjs_esp32_examples/blob/master/neonious_one/cellphone_controlled_rc_car/www/index.html)
- [web baker](https://gchq.github.io/CyberChef/#recipe=Gzip('Dynamic%20Huffman%20Coding','index.html.gz','',false)To_Hex('0x',0)Split('0x',',0x'))

Huge thanks to the authors, feel free to donate them!