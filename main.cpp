#include <iostream>
#include "capacitor.h"


//FUNCTION PROTOTYPES
void voltage_at_time(Capacitor *capacitor, int timesteps, double I, double delta_t, double C);
void current_at_time(Capacitor *capacitor, int timesteps, double V, double R, double C, double delta_t);
void print_timesteps(Capacitor *capacitor, int timesteps, double final_time);


int main(){
	
	
	//Define variables
	double delta_t = 1e-10;                            // time in seconds
	double final_time = 5e-6;                          // time in seconds                   
	double R = 1;                                      // resistance in kΩ              
	double C = 100e-12;                                // capacitance in Farrads    
	double I = 1e-2;                                   // constant current supply in Amps    
	double V = 10.0;                                   // constant voltage supply in Volts    
	int timesteps = 50000;                             // same as 5e-6/1e-10;    


	//Define struct (includes *time, *voltage, *current, C(apacitance)) 
	Capacitor *capacitor = new Capacitor;


	/*dyanmically allocate the time, voltage, and current arrays*/
	capacitor->time = new double [timesteps];    
	capacitor->voltage = new double [timesteps]; 
	capacitor->current = new double [timesteps];
	

	/*Test printing*/
	std::cout << "\n\n\n\n" << std::endl; std::cout << "Lets see if this equals 50000 = " << timesteps << std::endl;
	std::cout << "Lets see what delta_t prints = " << delta_t << std::endl;
	std::cout << "Lets see what final_time prints = " << final_time << std::endl;


	// FUNCTION CALLS
	voltage_at_time(capacitor, timesteps, I, delta_t, C);
	current_at_time(capacitor, timesteps, V, R, C, delta_t);
	print_timesteps(capacitor, timesteps, final_time);  
	

	// Delete allocated memory
	delete[] capacitor->time;
	delete[] capacitor->voltage;    
	delete[] capacitor->current;    
	delete capacitor;
	return 0;
}

//Functions
/*A loop over the number of timesteps will be needed to iterate the voltage and current in time. 
  Start at timestep 1, with timestep 0 being filled with the initial conditions given in the equation details.*/   
  
  void voltage_at_time(Capacitor *capacitor, int timesteps, double I, double delta_t, double C){
	  
	  int t;
	  capacitor->voltage[0] = 0;
	  capacitor->time[0] = 0;

	  for(t = 1; t < timesteps; t++){
		  
		  capacitor->voltage[t + 1] = capacitor->voltage[t] + (I) * (delta_t) * (1 / (C));
		  capacitor->time[t + 1] = capacitor->time[t] + (delta_t);
	    }
		  
		std::cout << "\n\nVoltage at time = 0 is " << capacitor->voltage[0] << " volts." << std::endl;
		std::cout << "Voltage at time = 1 is " << capacitor->voltage[1] << " volts." << std::endl;
		std::cout << "Voltage at time = 200 is " << capacitor->voltage[200] << " volts." << std::endl;
		std::cout << "Voltage at final time is " << capacitor->voltage[timesteps] << " volts.\n\n" << std::endl;
	      
		  // I think I might have to do some time conversions, or change the units here
	
	}
	
	
		// I don't know why, but I don't think this function is working right. 
  void current_at_time(Capacitor *capacitor, int timesteps, double V, double R, double C, double delta_t){
		
		int t;
		capacitor->current[0] = (V / R);
		capacitor->time[0] = 0;
		
		for(t = 1; t < timesteps; t++){
			
			capacitor->current[t + 1] = capacitor->current[t] - (((capacitor->current[t]) / (R * C)) * (delta_t));
			capacitor->time[t + 1] = capacitor->time[t] + (delta_t);
		}	
			
			std::cout << "Current at time = 0 is " << capacitor->current[0] << " amps." << std::endl;
			std::cout << "Current at time = 1 is " << capacitor->current[1] << " amps." << std::endl;
			std::cout << "Current at time = 100 is " << capacitor->current[100] << " amps." << std::endl;
			std::cout << "Current at final time is " << capacitor->current[timesteps] << "amps.\n\n" << std::endl;
	}
		
		
		/*Output resulting current and voltage for the capacitor for the different charging circuits every 200 timesteps*/  
		
	void print_timesteps(Capacitor *capacitor, int timesteps, double final) {    
		
		for (int t = 0; t < timesteps + 1; t++) {        
		
			if (t % 200 == 0) {            
			
				std::cout << "Timestep " << t <<": "<< std::endl;            
				std::cout << "Time = " << capacitor->time[t] << " seconds" << std::endl;            
				std::cout << "Voltage = " << capacitor->voltage[t] << " Volts" << std::endl;            
				std::cout << "Current = " << capacitor->current[t] <<" Amps\n" << std::endl;                 
			}    	
		}    
	}