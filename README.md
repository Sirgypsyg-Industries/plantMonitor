# Plant Monitor


![image](https://github.com/Sirgypsyg-Industries/plantMonitor/assets/107400417/f493cef6-806c-4c37-b063-08c905dbb127)



Plant Monitor is a comprehensive system designed for monitoring the well-being of your plants. It utilizes LabVIEW for communication and control, allowing users to set thresholds for temperature and soil humidity, triggering alerts and actions such as activating a buzzer or indicating current status. The system includes an OLED SSD1306 display, temperature and humidity sensors, a buzzer, a button for user interaction.

## Features

- Real-time monitoring of temperature and soil humidity.
- LabVIEW integration for adjusting thresholds and controlling connected devices.
- OLED SSD1306 display for displaying plant status.
- Buzzer alerts for low temperature and soil humidity.


## Calibration Process

Upon startup, Plant Monitor initiates a calibration process to ensure accurate readings. Follow these steps:

1. Place the sensor in a dry environment.
2. Press the button to confirm the dry condition reading.
3. Immerse the sensor in water to achieve 100% humidity.
4. Press the button to confirm the wet condition reading.

## Usage

### LabVIEW Communication

The LabVIEW application facilitates communication with Plant Monitor, providing the following functionalities:

- Adjust temperature and humidity thresholds.
- Enable/disable the buzzer based on user preferences.

### Real-Time Monitoring

The OLED SSD1306 display provides real-time information about the plant's condition, including:

- Current temperature.
- Soil humidity.
- Status alerts:
  - "TOO COLD" for temperatures below the critical threshold.
  - "WATER ME" for insufficient soil humidity.

## Setup

1. Connect the OLED SSD1306 display, temperature sensor, humidity sensor, buzzer, button.

2. Install the required dependencies specified in the project's documentation.

3. Upload the Plant Monitor code to your microcontroller.

4. Run the LabVIEW application to establish communication with the Plant Monitor.

5. Calibrate the system following the steps outlined in the calibration process section.

## Future Improvements

- Implement additional sensors for more comprehensive plant monitoring.
- Enhance LabVIEW interface for user-friendly configuration.
- Integrate with a mobile app for remote monitoring.
- Optimize the water pump system for efficient and controlled watering.
- Water pump for automatic plant watering.

## Contributors

- sirgypsyg
- Velshart

## Demo

![image](https://github.com/Sirgypsyg-Industries/plantMonitor/assets/107400417/a90a35b9-6be8-48d7-9c7d-5dbe7b189353)

## Circuit
![diagram](https://github.com/Sirgypsyg-Industries/plantMonitor/assets/107400417/0dd5e46a-7ed0-4d9d-9df2-3a6385271237)

## Labview
![afafaf](https://github.com/Sirgypsyg-Industries/plantMonitor/assets/107400417/6ed08f18-b243-49ff-b2cb-3579bd9cfd6c)
![fafaa](https://github.com/Sirgypsyg-Industries/plantMonitor/assets/107400417/d5266de5-93e7-495a-88ec-6fe02ccdfd7c)
![lalal](https://github.com/Sirgypsyg-Industries/plantMonitor/assets/107400417/42e0c8ae-4057-436f-ae7b-24bc4697e59a)
![stop](https://github.com/Sirgypsyg-Industries/plantMonitor/assets/107400417/5d8a07bb-1e57-4561-820f-4edb8037b238)
![fafPNG](https://github.com/Sirgypsyg-Industries/plantMonitor/assets/107400417/b2622cc4-6ab5-4fe5-a406-f08a0b8b8d61)

