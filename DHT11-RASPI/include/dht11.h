/*  DHT11 Temperature & Humidity Sensor
*	
*	Weather Station Project v.01
*
*
*	By Víctor Malumbres Talles
*/
#include <inttypes.h>
#include <wiringPi.h>
#include <math.h>
#include <stdio.h>

#ifndef dht11_h
#define dht11_h

#define DHTLIB_VERSION           "2.0"

#define DHTLIB_OK				   0
#define DHTLIB_ERROR_CHECKSUM	  -1
#define DHTLIB_ERROR_TIMEOUT	  -2

#define N_Bytes                    5
#define N_Bits                    40

#define Start_Transmission_Bit_T  50 // in us
#define Response_Signal_T         80 // in us
#define Ask_Measure_T             18// in us


/*************************************
* Function to setup dht11
**************************************/
int setup();
        
/*************************************
* Function to setup data pin of dht11
**************************************/
int setPin(int number);
        
/*************************************
* Function to get dht11's data pinout
**************************************/
int getPin();
        
/*************************************
* Function to get temperature
**************************************/
float getTemperature();

/*************************************
* Function to get humidity
**************************************/
float getHumidity();

/*************************************
* Function to read data from dht11
* Version 1.0
**************************************/	
int read_dht11();

/*************************************
* Function to read data from dht11
* Version 2.0
**************************************/ 
int read_dht11_v2();



#endif
