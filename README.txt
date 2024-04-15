The files provided are used to operate the BMP180 (Barometric Pressure Chip). 
This is a demonstration of interfacing with the BMP180 sensor to read temperature, pressure, and calculate altitude. 
It uses the AVR ATmega328p microcontroller and the provided HD44780 LCD library to display sensor readings on an LCD screen.
For information regarding wiring, video examples and more go to https://github.com/danaeclark/Barometer .

Prerequisites:
1. AVR ATmega328p microcontroller
2. BMP180 sensor
3. LCD display
4. AVR-GCC compiler

Usage
    Compile the code using an AVR-GCC compiler.
    Upload the compiled code to the AVR ATmega328p microcontroller.
    Ensure the BMP180 sensor is connected correctly.
    Power on the system.
    The LCD will display the atmospheric pressure, temperature, and altitude readings in a loop.

Files Provided:
barometer.c 
    Functions
        BMP085_ReadRawTemperature(): Reads the raw temperature from the sensor.
        BMP085_ReadRawPressure(): Reads the raw pressure from the sensor.
        BMP085_GetTemperature(): Calculates the temperature in Celsius.
        BMP085_GetPressure(): Calculates the pressure in hPa.
        BMP085_CalculateAltitude(): Calculates the altitude in meters based on pressure and sea level pressure.
        
    Main Loop
        The main loop of the code continuously reads temperature, pressure, and altitude from the BMP085 sensor and displays them on the LCD display.

        Reads temperature, pressure, and altitude
        Displays atmospheric pressure (Pa) on the LCD
        Displays temperature (Celsius) on the LCD
        Displays altitude (meters) on the LCD
        Repeat the loop


