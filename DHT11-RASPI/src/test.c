/*********** Script for getting measures *******************
************ of temperature & humidity *********************
************ by using dht11 in raspberry pi 4 **************
************ By Victor Malumbres ***************************/

// Basic libraries
#include <dht11.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

// Handling time
#include <time.h>

int main(void){

    // Local vars
    time_t TimeStamp;

    // Set pin where sensor is connected
    setPin(30);
	
    // Set up of dht11 sensor
    if(setup() < 0){
      printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
      exit(-1);
    }

    while(1){
 
     // Get time
     time(&TimeStamp);

     // If data is ok, print to console
     if(read_dht11_v2()== 0)
     {
      printf("*************** DATA FROM DHT11 *******************");
      printf("*Temperature: %f [Celsius]\n*Humidity: %f [.pcg]\n*Date: %s",getTemperature(), getHumidity(), ctime(&TimeStamp));
      printf("***************************************************");
     }

     //Wait 5 seconds
     usleep(5000000);
	
    }


    return 0;
}
