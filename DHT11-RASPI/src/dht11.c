/*********************************************
* DHT11 Software for embedded-linux
*
* By Víctor Malumbres - victormalum@gmail.com
**********************************************/

#include "dht11.h"


/*************************************
* Temperature variable
**************************************/
float temperature;

/*************************************
* Humidity variable
**************************************/
float humidity;

/*************************************
* Pin conected to data pin of dht11
**************************************/
int pin;


/*************************************
* Function to ask a measure to dht11
**************************************/
int ask_measure(int pin){

	// wait 1 second
	delay(1000);

	// Pin as output
	pinMode(pin, OUTPUT);

	// Low 
	digitalWrite(pin, LOW);

	delay(Ask_Measure_T);

	// High
	digitalWrite(pin, HIGH);

	// Some us delay ()
	delayMicroseconds(40);

	// Pin as input
	pinMode(pin, INPUT);

	return DHTLIB_OK;
}

/*************************************
* Function to setup wiring pi
**************************************/
int setup(){
   return wiringPiSetup();
}

/*************************************
* Function to setup pinout of dht11
**************************************/
int setPin(int number){
   pin = number;
   return 0;
}

/*************************************
* Function to get dht11 data pinout
**************************************/
int getPin(){
  return pin;
}

/***************************************
* Function to get temperature from dht11
****************************************/
float getTemperature(){
  return temperature;
}

/*************************************
* Function to get humidity from dht11
**************************************/
float getHumidity(){
 return humidity;
}


/*************************************
* Function to read data from dht11
* Version 1.0
**************************************/
int read_dht11()
{
	// Data format: 8bit integral RH data + 8bit decimal RH data + 8bit integral T data + 8bit decimal T data + 8bit check sum. 

	// Buffer 
	uint8_t data[N_Bytes];


	// Ask for measures
	int rlst = ask_measure(pin); 

        // Check sensor response signal
	uint8_t check_time = 0;

	// Check for low state
	while(digitalRead(pin) == LOW){

		check_time ++;
		delayMicroseconds(1);

		if(check_time > Response_Signal_T) return DHTLIB_ERROR_TIMEOUT;
	}

	// Check for high state
	check_time = 0;
	while(digitalRead(pin) == HIGH){

		check_time ++;
		delayMicroseconds(1);

		if(check_time > Response_Signal_T) return DHTLIB_ERROR_TIMEOUT;
	}


	// Start data transmission
	for (int i=0; i < N_Bytes; i++)
	{
		// Read a byte
		for(int read_bits=0; read_bits<8;read_bits++){

			// Wait for start transmission bit
			check_time = 0;
			while(digitalRead(pin) == LOW){

				check_time ++;
				delayMicroseconds(1);

				if(check_time > Start_Transmission_Bit_T) return DHTLIB_ERROR_TIMEOUT;
			}

			// Data bit (26/28 us is 0, 70 us is)
			check_time = 0;
			while(digitalRead(pin) == HIGH){
				check_time ++;
				delayMicroseconds(1);
			}

			// Determine if bit is 0 or 1. Add to ByteOfBits buffer
			if(check_time>30){
				// Bit is one
				data[i]+= pow(2,(8-read_bits));
			}
			
		}

	}

	// Reading is finished

      
        // Check sum
	if ((data[0]+data[1]+data[2]+data[3]) == data[N_Bytes-1]){

		// Get Humidity
		humidity = data[0];
		humidity += ((float)data[1])/1000;

		// Get Tempereature
		temperature = data[2];
		temperature += ((float)data[3])/1000;


	} else{
		return DHTLIB_ERROR_CHECKSUM;
	}


	return DHTLIB_OK;

}



/*************************************
* Function to read data from dht11 
* Version 2.0
**************************************/
int read_dht11_v2(){

	uint8_t laststate= HIGH;
	uint8_t counter =  0;
	uint8_t j = 0;
        uint8_t i = 0;
        int data[N_Bytes];

	data[0] = data[1] = data[2] = data[3] = data[4] = 0;
 
	/* pull pin down for 18 milliseconds */
	pinMode(pin, OUTPUT );
	digitalWrite(pin, LOW );
	delay( 18 );
 
	/* prepare to read the pin */
	pinMode(pin, INPUT );
 
	/* detect change and read data */
	for ( i = 0; i < 85; i++ )
	{
		counter = 0;
		while ( digitalRead(pin) == laststate )
		{
			counter++;
			delayMicroseconds( 1 );
			if ( counter == 255 )
			{
				break;
			}
		}
		laststate = digitalRead(pin);
 
		if ( counter == 255 )
			break;
 
		/* ignore first 3 transitions */
		if ( (i >= 4) && (i % 2 == 0) )
		{
			/* shove each bit into the storage bytes */
			data[j / 8] <<= 1;
			if ( counter > 16 )
				data[j / 8] |= 1;
			j++;
		}
	}
 
	/*
	 * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
	 * print it out if data is good
	 */
	if ( (j >= 40) &&
	     (data[4] == ( (data[0] + data[1] + data[2] + data[3]) & 0xFF) ) )
	{
		humidity = (float)((data[0] << 8) + data[1]) / 10;
		if ( humidity > 100 )
		{
			humidity = data[0];	// for DHT11
		}
		temperature = (float)(((data[2] & 0x7F) << 8) + data[3]) / 10;
		if ( temperature > 125 )
		{
			temperature = data[2];	// for DHT11
		}
		if ( data[2] & 0x80 )
		{
			temperature = -temperature;
		}
		
		
	}else  {
		return -1;
		printf( "Data not good, skip\n" );
	}

    return 0;
}
