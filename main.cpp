#include <iostream>
#include <fstream>
#include <vector>
#include "restaurant.cpp" 
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


	//file_input_object.print_the_vector(vector_that_holds_the_data);
	


	
//	cout <<vector_that_holds_the_data.size();
//	cout << somevector.size() <<endl;	
	
//	kitchen_simulator.print_the_vector(vector_that_holds_the_data);
//cout << vector_that_holds_the_data[0]<< endl;

//	cout << "this here = "<< kitchen_simulator.vector_of_rounds[0].orders[0].order_ID<<endl;
