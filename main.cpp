#include <iostream>
#include <fstream>
#include <vector>
#include "restaurant.cpp" 
//#include "sector.cpp" 
//#include "sector2.cpp" 
using namespace std;


int main()
{
	File_Input_Class file_input_object; //create an object to extract the file's data
	Kitchen_Simulator kitchen_simulator;// and an object to simulate the restaurant process
		
	vector<double> vector_that_holds_the_data; //create a vector to hold the file's data
	
	file_input_object.put_the_file_data_inside_a_vector(vector_that_holds_the_data);	//collect the file's data
	
	kitchen_simulator.simulation(vector_that_holds_the_data); //simulate the restaurant process

	return 0;
}


