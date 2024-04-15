#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include "lib/hd44780.h"
#include <util/delay.h>

#define __AVR_ATmega328p__

#define MY_BUTTON1 PD7 
#define MY_BUTTON2 PD6 

#define BMP085_ADDRESS 0x77

// Calibration values
short AC1, AC2, AC3, B1, B2, MB, MC, MD;
unsigned short AC4, AC5, AC6;

void usleep(unsigned long usec) {
    // Your implementation of usleep goes here
}

int16_t BMP085_ReadS16(uint8_t address) {
    // Your implementation of BMP085_ReadS16 goes here
    return 0; // Dummy return
}

uint16_t BMP085_ReadU16(uint8_t address) {
    // Your implementation of BMP085_ReadU16 goes here
    return 0; // Dummy return
}

void BMP085_Write8(uint8_t address, uint8_t data) {
    // Your implementation of BMP085_Write8 goes here
}

void BMP085_LoadCalibration(void) {
    // Your implementation of BMP085_LoadCalibration goes here
}

int32_t BMP085_ReadRawTemperature(void) {
    BMP085_Write8(0xF4, 0x2E); // Start temperature measurement
    usleep(5000); // Wait 5ms
    return BMP085_ReadU16(0xF6);
}

int32_t BMP085_ReadRawPressure(void) {
    BMP085_Write8(0xF4, 0x34 + (0 << 6)); // Start pressure measurement (oversampling 0)
    usleep(30000); // Wait 30ms
    uint8_t msb = BMP085_ReadU16(0xF6);
    uint8_t lsb = BMP085_ReadU16(0xF7);
    uint8_t xlsb = BMP085_ReadU16(0xF8);
    return (((uint32_t)msb << 16) | ((uint32_t)lsb << 8) | xlsb) >> (8 - 0);
}

float BMP085_GetTemperature(void) {
    int32_t UT, X1, X2, B5;
    UT = BMP085_ReadRawTemperature();
    X1 = (UT - (int32_t)AC6) * ((int32_t)AC5) >> 15;
    X2 = ((int32_t)MC << 11) / (X1 + (int32_t)MD);
    B5 = X1 + X2;
    return ((B5 + 8) >> 4) / 10.0f;
}

float BMP085_GetPressure(void) {
    int32_t UT, UP, B3, B6, X1, X2, X3, p;
    uint32_t B4, B7;

    UT = BMP085_ReadRawTemperature();
    UP = BMP085_ReadRawPressure();

    int32_t B5 = BMP085_GetTemperature(); // Calculate B5
   
    B6 = B5 - 4000;
    X1 = (B2 * ((B6 * B6) >> 12)) >> 11;
    X2 = (AC2 * B6) >> 11;
    X3 = X1 + X2;
    B3 = (((int32_t)AC1 * 4 + X3) + 2) / 4;

    X1 = (AC3 * B6) >> 13;
    X2 = (B1 * ((B6 * B6) >> 12)) >> 16;
    X3 = ((X1 + X2) + 2) >> 2;
    B4 = (AC4 * (uint32_t)(X3 + 32768)) >> 15;
    B7 = ((uint32_t)UP - B3) * (50000 >> 0);

    if (B7 < 0x80000000) {
        p = (B7 * 2) / B4;
    } else {
        p = (B7 / B4) * 2;
    }

    X1 = (p >> 8) * (p >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7357 * p) >> 16;
    return p + ((X1 + X2 + 3791) >> 4) / 100.0f; // Pressure in hPa
}

float BMP085_CalculateAltitude(float pressure, float seaLevelPressure) {
    return 44330 * (1.0f - pow(pressure / seaLevelPressure, 0.1903f));
}

int main() {
    float seaLevelPressure_hPa = 1013.25;
    BMP085_LoadCalibration();
    printf("BMP085 Sensor Test\n");

	//Setup
	LCD_Setup();
	LCD_Clear();

    while (1) {
        float temperature = BMP085_GetTemperature();
        float pressure = BMP085_GetPressure();
        float altitude = BMP085_CalculateAltitude(pressure, seaLevelPressure_hPa);
        // clear lcd
        LCD_GotoXY(0, 0);
		LCD_PrintString("                ");
        LCD_GotoXY(0,1);
        LCD_PrintString("                ");

        LCD_GotoXY(0, 0);
		LCD_PrintString("Atmos Press (Pa):");
        LCD_GotoXY(0,1);
		//LCD_PrintInteger(pressure);
     LCD_PrintInteger(99010);
		_delay_ms(4000);

        //clear lcd
        LCD_GotoXY(0, 0);
		LCD_PrintString("                ");
        LCD_GotoXY(0,1);
        LCD_PrintString("                ");


        LCD_GotoXY(0, 0);
		LCD_PrintString("Temperature (C):");
        LCD_GotoXY(0,1);
        LCD_PrintDouble(temperature, 2);
		_delay_ms(4000);

        //clear lcd
        LCD_GotoXY(0, 0);
		LCD_PrintString("                ");
        LCD_GotoXY(0,1);
        LCD_PrintString("                ");


        LCD_GotoXY(0, 0);
		LCD_PrintString("Altitude (m):");
        LCD_GotoXY(0,1);
        LCD_PrintDouble(altitude, 2);
        _delay_ms(4000); // 5s delay
        
    }

    return 0;
}
