# An IoT based health monitoring device #

<img alt="Static Badge" src="https://img.shields.io/badge/IoT-blue"> <img alt="Static Badge" src="https://img.shields.io/badge/Node--MCU-blue"> <img alt="Static Badge" src="https://img.shields.io/badge/Mini_Project-blue">
![1](assets/1.jpg)

`A Node-MCU based device that monitors user's health parameters such as body temperature, blood pressure and blood oxygen % (SpO2) and shares them on the user's smart-phone in realtime.
Built in my Second year as part of academic mini-project.`

- [x] `An ultrasonic sensor detects an approaching person and signals the controller which turns the servo motor attached to the door and also wakes up the monitoring system.`
- [x] `The Max30100 and lm35 sensors measure the pulse-rate, blood oxygen level and body temperature of the person.`
- [x] `The data can be viewed on the person's smartphone when connected to the same Wi-Fi`


![1](assets/2.jpg)
![1](assets/3.jpg)

Circuit Connections:-
![4](assets/4.jpg)

Design Sketch:-
![5](assets/5.jpg)

Actual System:-
![6](assets/6.jpg)
![7](assets/7.jpg)

Smartphone Screen:-
<br>![image](assets/8.jpg)


`Source Code is written using Arduino IDE.`

*References*:
<br>https://randomnerdtutorials.com/esp32-ssd1306-oled-display-arduino-ide/
<br>https://randomnerdtutorials.com/esp32-servo-motor-web-server-arduino-ide/
<br>https://esp32io.com/tutorials/esp32-ultrasonic-sensor
<br>https://iotprojectsideas.com/esp32-based-max30100-pulse-oximeter-webserver/
<br>https://www.electronicwings.com/esp32/lm35-sensor-interfacing-with-esp32
<br>https://www.instructables.com/IoT-Project-Using-ESP32-NodeMCU-Network-With-Blynk/
