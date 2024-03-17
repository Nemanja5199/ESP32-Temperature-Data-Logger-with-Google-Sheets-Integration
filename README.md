# Editing: Writing Temperature Data to Google Sheets using ESP32

This project demonstrates how to utilize an ESP32 microcontroller to read temperature data from a sensor and send it to a Google Sheets spreadsheet for logging and visualization. This can be particularly useful for environmental monitoring, home automation, or any application where remote temperature monitoring is required.

## Requirements

- ESP32 microcontroller board
- Temperature sensor (e.g., DS18B20, DHT11, DHT22)
- Google account
- Google Sheets API credentials
- Arduino IDE

## Setup

1. **Hardware Setup:**
   - Connect the temperature sensor to the ESP32 board according to its datasheet.
   - Ensure that the ESP32 is connected to the internet via Wi-Fi.

2. **Google Sheets Setup:**
   - Create a new Google Sheets document.
   - Enable the Google Sheets API and generate credentials (OAuth 2.0 client ID) following [these instructions](https://developers.google.com/sheets/api/quickstart).
   - Note down the generated credentials (client ID, client secret, etc.).

3. **Software Setup:**
   - Install the necessary libraries in your Arduino IDE for the ESP32 and the temperature sensor.
   - Clone or download the code repository.

## Usage

1. **Configuration:**
   - Open the Arduino sketch provided in this repository.
   - Enter your Wi-Fi credentials.
   - Configure the sensor pin and other settings according to your setup.
   - Add the Google Sheets API credentials to the sketch.

2. **Upload Sketch:**
   - Compile and upload the sketch to your ESP32 board using the Arduino IDE.

3. **Monitoring:**
   - Open the serial monitor in the Arduino IDE to view temperature data being read from the sensor and sent to Google Sheets.

4. **Data Visualization:**
   - Access your Google Sheets document to view the logged temperature data.
   - Utilize Google Sheets features or integrate with other tools for data visualization and analysis.

## Troubleshooting

- If you encounter any issues, refer to the serial monitor output for debugging information.
- Ensure that your ESP32 is connected to the internet and has proper access to the Google Sheets API.

## Contributing

Contributions to this project are welcome! Feel free to submit bug reports, feature requests, or pull requests.

                                                  ![Temperature](https://github.com/Nemanja5199/ESP32-Temperature-Writing-to-Google-Sheets/assets/91099510/518e70f0-9541-42d7-bf8a-11fda4601cc7)


