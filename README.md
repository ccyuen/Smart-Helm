# Smart Helm
Attachable helmet accessory that provides sensory and audio feedback to the wearer for navigation and warnings on the street.

#### - Overview -
![Demo](https://github.com/ccyuen/Smart-Helm/blob/master/Media/demo.gif)

#### - Ultrasonic Sensor Testing -
![Demo](https://github.com/ccyuen/Smart-Helm/blob/master/Media/Testing.gif)

## About
The helmet accessory consists of vibrational motors and LED strips to give signals to the wearer and any people around the wearer. Using the LED strips, the wearer can give signals to the surrounding people like stop, slowing down or turning signals using tap actions on the helmet or through the Google maps route that they have chosen. The vibrational motors allow the wearer to receive sensory information about the environment without having to look in their blind spots or worry about incoming traffic. By giving the wearer a buzz (much like the phone vibration) on the head in a specific direction based on the location of the incoming object, the wearer will be notified of the object much earlier and with warning.

The device removes the need for the use of phones when bicycling or doing any agile activities. Since it is qutie dangerous to pull out and gaze at your phone to check your current location along your Google maps route, this device removes that action and receives bluetooth data from your phone (via the app we have created) about your location and route so that it can automatically give you directions when bicycling. 

### Hardware / Software
This project was created with the use of the [Intel Edison](https://software.intel.com/en-us/iot/hardware/edison), a small, Internet of Things (IoT) module that allows users to create IoT or wearable devices. The Arduino and Android Studio IDE were also used as the programming platform to create the interactions with the sensor data and the app on the phone. 
In detail, the breakout board was used for Ultrasonic sensor interrupt signal (Output pin 10) and pulseIn signal (Input pin 13). Meanwhile, Output pin 11 was used for RGB LED Strip. And vibrator and gyro board was also used. Sine vibrator is not I2c device and it shares pin 10 with Ultrasonic interruption, a sequence was used to alternating two devices. In addition, Ultrasonic sensor was driven by external 5V, and 1k resistor was used to protect the board (Xadow kit is 3.3V). 

### Applications
This device was primarily targetted for the hearing impaired especially since there is a lot of stigma regarding the hearing impaired participating in agile activities. With the use of this device, they will be able to receive and send sensory data in their environment when doing activities such as bicycling.

It is also a promotion for the use of bicycle helmets and signalling on the streets because many young riders do not wear helmets and do not signal or follow road laws. This device provides otpimal safety to the wearer and is also a cool add on to the standard helmet!

### Future Feature Add-Ons
- Call 911 when the helmet detects abrupt and unusual motion in the head (e.g. quick accelerations for 2 times in a row)
- Microphone and speaker interface that, through wifi or bluetooth, uses the assistant (Cortana, Siri, Google Assistant, etc) on your phone to allow you to make calls or perform other actions on your phone hands free

### See Us On Devpost
https://devpost.com/software/project-helm

### Credit
Created by [Eren Rudy](https://github.com/eren-rudy), [Ali Toyserkani](https://github.com/alitoyserkani), [Jack Xu](https://github.com/JXproject) and [Clement Yuen](https://github.com/ccyuen) for WearHacks Kitchener-Waterloo 2017
