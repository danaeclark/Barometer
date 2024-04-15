# Barometer
## ECE484 - Dana Clark

The files provided are used to operate the BMP180 (Barometric Pressure Chip). 
This is a demonstration of interfacing with the BMP180 sensor to read temperature, pressure, and calculate altitude. 
It uses the AVR ATmega328p microcontroller and the provided HD44780 LCD library to display sensor readings on an LCD screen.
The barometer.zip file contains all of the code needed for this project. View the [wiki](https://github.com/danaeclark/Barometer/wiki)!

### Prerequisites:
- AVR ATmega328p microcontroller
- BMP180 sensor
- LCD display
- AVR-GCC compiler

### Usage:
    Compile the code using an AVR-GCC compiler.
    Upload the compiled code to the AVR ATmega328p microcontroller.
    Ensure the BMP180 sensor is connected correctly.
    Power on the system.
    The LCD will display the atmospheric pressure, temperature, and altitude readings in a loop.

### Files Provided:
#### barometer.c 

    Functions
    
        BMP085_ReadRawTemperature(): Reads the raw temperature from the sensor.
        BMP085_ReadRawPressure(): Reads the raw pressure from the sensor.
        BMP085_GetTemperature(): Calculates the temperature in Celsius.
        BMP085_GetPressure(): Calculates the pressure in hPa.
        BMP085_CalculateAltitude(): Calculates the altitude in meters based on pressure and sea level pressure.
        
    Main Loop
        The main loop of the code continuously reads temperature, pressure, and altitude from the BMP085 sensor and displays them on the LCD display.
        
        1. Reads temperature, pressure, and altitude
        2. Displays atmospheric pressure (Pa) on the LCD
        3. Displays temperature (Celsius) on the LCD
        4. Displays altitude (meters) on the LCD
        5. Repeat the loop
        
#### compile_script.py

    This compile script is compatible with Mac computers. 
    Line 35, " path_win_avr = '/usr/local/avr/bin/' " will need to be adapted depending on the path of the user.
    The folllowing line can be used in the terminal to compile the code: "python3 compile_script.py 4 /dev/cu.usbmodem14201" 
    (change the ending number depending on the port connectred to the arduino)

#### lib

    I pulled the LCD library used in past labs in ECE 484 (Embedded Systems - Dr. Jamieson, Miami University) 
    The file in the library called "HD44780_Settings.h" needs to be changed if the wiring is different from what I used.
