#include "BoneHeader.h"
#include <signal.h>
#define CARRIER_FREQ 38000
#define BIT_RATE 1000
#define DUTY_PERCENT 50
#define TRANSMIT_PWM "ehrpwm.1:0"

int keepgoing = 1;

void signal_handler(int signo){
	if (signo == SIGINT){
		keepgoing = 0;
	}
}

int main(int argc, char** argv){

	int i;

	set_mux_value("gpmc_a2", 6);	
	
	signal(SIGINT, signal_handler);
	
	while(keepgoing){
		for(i=0;i< sizeof(char)*8; i++){
			if((('c' & (0x80 >> i)) >> (sizeof(char)*8-1-i)))
				set_pwm(TRANSMIT_PWM, CARRIER_FREQ, DUTY_PERCENT);
			else
				unset_pwm(TRANSMIT_PWM);
			usleep(BIT_RATE);
		}		
	}
	
	set_mux_value("gpmc_a2", 7);

	return 0;
}
