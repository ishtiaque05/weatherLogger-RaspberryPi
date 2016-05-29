#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>


#define MAX_TIME 85
#define DHT11PIN 7
#define ATTEMPTS 5
int dht11_val[5]={0,0,0,0,0};

int dht11_read_val()
{
	uint8_t lststate=HIGH;
	uint8_t counter=0;
	uint8_t j=0,i;
	for(i=0;i<5;i++)
		dht11_val[i]=0;
	pinMode(DHT11PIN,OUTPUT);
	digitalWrite(DHT11PIN,LOW);
	delay(18);
	digitalWrite(DHT11PIN,HIGH);
	delayMicroseconds(40);
	pinMode(DHT11PIN,INPUT);
	for(i=0;i<MAX_TIME;i++)
	{
		counter=0;
		while(digitalRead(DHT11PIN)==lststate)
		{	counter++;
			delayMicroseconds(1);
			if(counter==255)
			break;
		}
	
	lststate=digitalRead(DHT11PIN);
	
	if(counter==255)
		break;
	
	// top 3 transistions are ignored
	if((i>=4)&&(i%2==0)){
		dht11_val[j/8]<<=1;

	if(counter>16)
		dht11_val[j/8]|=1;
	j++;
	}
}

// verify checksum and print the verified data
	if((j>=40)&&(dht11_val[4]==((dht11_val[0]+dht11_val[1]+dht11_val[2]+dht11_val[3])& 0xFF)))
	{	
		time_t result = time(NULL);
		printf("Relative Humidity: %d.%d,Temperature: %d.%d on %s",dht11_val[0],dht11_val[1],dht11_val[2],dht11_val[3],asctime(localtime(&result)));
		
		
		
		FILE *fp;
		fp = fopen("Data.txt", "a");
		if(fp==NULL)
		{	
			printf("File could not be opened\n");
		}
		else
		{
			fprintf(fp, "%d.%d %d.%d %s",dht11_val[0],dht11_val[1],dht11_val[2],dht11_val[3],asctime(localtime(&result)));
			fclose(fp);
		}
		return 1;
	}
	else
		return 0;
	}

int main(void)
{
		int a = 0;
		int attempts=ATTEMPTS;
		if(wiringPiSetup()==-1)
		exit(1);
		for(a=0; a<5; )
		{
			int success = dht11_read_val();
			if (success) {
				a++;
				delay(5000);
				
			}
		//attempts--;
		}
		
		
	

return 0;
}

