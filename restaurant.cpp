#include "restaurant.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h> // to use atof() and c_str()
#include <iomanip>  // to setprecision(2)

using namespace std;

void Kitchen_Simulator::simulation(vector<double> the)
{
	count_the_rounds(the);
	distribute_the_rounds(the);
	vector<double> pancakes;
	fix_copy();
	int this_index;
	bool first_loop=false;

	for(int x = 0 ; x < vector_of_rounds.size() ; x++)
	{
		this_index = x;
		if (x == 0){cout <<"------------------------------ROUND #"<< vector_of_rounds[x].round_ID<< "----------------------------------------\n";}
		else{cout <<"\n\n------------------------------ROUND #"<< vector_of_rounds[x].round_ID<< "----------------------------------------\n";		};
		cout << "The kitchen will process "<< vector_of_rounds[x].amount_of_incoming_orders
		<< " incoming orders and fullfill " << vector_of_rounds[x].amount_of_outgoing_orders<< " outgoing orders\n"
		<< "*** Incoming Orders ***\n";
		
		for (int y =0 ; y < vector_of_rounds[x].amount_of_incoming_orders; y++)
		{
			cout << "ORDER #" << vector_of_rounds[x].orders[y].order_ID	
			<< "  (" << vector_of_rounds[x].orders[y].order_type;	
			 
			if (vector_of_rounds[x].orders[y].order_type == "Menu Items"){cout <<"). ";}
			else if (vector_of_rounds[x].orders[y].order_type == "Prix Fixe"){cout <<").  ";}			 
			 cout <<"Priority: " << vector_of_rounds[x].orders[y].order_priority	
			<<". Total Price: $"<< vector_of_rounds[x].orders[y].order_total_price<<endl;
		
			passer.push_back(vector_of_rounds[x].orders[y]);
		}
	
		cout << "The total price of this round's incoming orders is $" 
			 << vector_of_rounds[x].total_price_of_incoming_orders_in_this_round<<"."<<endl;
			
		outgoing_orders(vector_of_rounds[x].amount_of_incoming_orders, vector_of_rounds[x].amount_of_outgoing_orders , vector_of_rounds[x].round_ID , this_index );
			
		passer.clear();
	
		this_index++;
	}
}

void Kitchen_Simulator::outgoing_orders(int incoming, int outgoing, int round_ID, int this_index)
{
	int stop_here = (incoming + outgoing);

	for (int x = 0; x < passer.size() ; x ++)
	{
		outorders.push_back(passer[x]);
	}

	vector<int> max_index;
	max_index.push_back(0);
	int max_pri = passer[0].order_priority;

	for (int x = 0 ; x+1 < passer.size(); x++) //finds the maximum priority WORKS
	{
		if (passer[x+1].order_priority> max_pri)
		{
			max_index[0]= x+1;
			max_pri = passer[x+1].order_priority;
		}
	}	

	vector<int> max_indeces;
	max_indeces.push_back(max_index[0]);
	int count = 1;
	
	
	for (int x = 0 ; x < passer.size(); x++) //counts how many equal max priorities we have WORKS
	{
		if (x != max_index[0])
		{
			if (passer[x].order_priority == max_pri)
			{
				max_indeces.push_back(x);
				count++;
			}
		}
	}
	
	
	vector<int> sorted_pri_indeces;
	for (int x = 0 ; x < max_indeces.size(); x++) //gives the variables to sorted pri_indeces WORKS
	{
		sorted_pri_indeces.push_back(max_indeces[x]);
	}
	
	bool skip = false;	
	int next_max_index = 0;
	int cur_max_index = -1;

	for (int x = 0, count = (passer.size() - sorted_pri_indeces.size());(count>0) ; x++) //WORKS adds the remaining priorities
	{
		for (int y = 0; y < max_indeces.size() ; y++) //is this index of passer within max indices?
		{
			if (x == max_indeces[y]) 
			{
				skip = true;
			}
		}
		
		if (skip ==false)
		{
			if (x>cur_max_index)
			{
				cur_max_index = x;
			}
			skip = true;
		}
		
		if (x == (passer.size() - 1) )
		{
			count--;
			x = 0;
			max_indeces.push_back(cur_max_index);
			sorted_pri_indeces.push_back(cur_max_index);
			cur_max_index = -1;
		}
		
	
		skip = false;
	}

	vector<int> this_index_next;
	for (int x = (sorted_pri_indeces.size() - 1), y = 0; y < sorted_pri_indeces.size(); x--, y++) //WORKS reverses sorted pri indeces
	{
		this_index_next.push_back(sorted_pri_indeces[x]);
	}

	int this_value;
	int passer_index, test_index;
	int passer_pri, test_pri;
	vector<Order> sorted;
	bool nomorex = false , nomorey = false;
	bool backaid_first = true;
	int m = 0;
	bool done1 = false;
	bool done2 = false;
	int get = 0;
	int reset;
	
	vector<Order>backaid;
	for (int x = 0 ; x<backlog.size();  x ++) //passes sorted values to backlog
	{
		backaid.push_back(backlog[x]);

	}
		
	if(backaid.size() > 0)
	{
		for (int x = 0;(x<backaid.size()) || (m<passer.size()) ;x++ ) //WORKS adds the remaining priorities
		{
			if(x<backaid.size())
			{
				for (int z = m; z < passer.size() ; z++) //is this index of passer within max indices?
				{
					if (backaid[x].order_priority >= passer[this_index_next[z]].order_priority) 
					{
						backaid_first = false;
						get = z;
						m = z;
						z = passer.size();
						x--;
					}
				}
			}
				
			if (backaid_first == false)
			{
				sorted.push_back(passer[this_index_next[get]]);
				m++;
				backaid_first = true;
			}
			
			else
			{
				if(x>=backaid.size())
				{
					break;
				}
				
				sorted.push_back(backaid[x]);
				
			}
		}
	
		backlog.clear(); 
	
		for (int x = 0 ; x<sorted.size();  x ++) //passes sorted values to backlog
		{
			backlog.push_back(sorted[x]);
			outorders.push_back(sorted[x]);
		}
	}
	
	
	else
	{
		int some;
		for (int x = 0 ; x<passer.size();  x ++) //passes sorted values to backlog
		{
			backlog.push_back(passer[this_index_next[x]]);
		}
	}

		int deletion = outgoing;
	
		for ( ; deletion > 0 ; deletion-- ) //deletes outgoing orders
		{
			if(backlog.size()>0){backlog.pop_back();}
		}
		
		int print = outgoing;
		vector<double> price_checker;
	
		cout << "*** Outgoing Orders ***\n";

		for ( int y = outorders.size()-1; print > 0 ; print--, y-- ) //prints outgoing orders
		{
			if(outorders.size()>0)
			{
			cout << "ORDER #" << outorders[y].order_ID << "  (" << outorders[y].order_type;	
			 
			     if (outorders[y].order_type == "Menu Items"){cout <<"). ";}
			
			else if (outorders[y].order_type == "Prix Fixe" ){cout <<").  ";}			 
			 
			cout <<"Priority: " << outorders[y].order_priority
				 <<". Total Price: $"<< outorders[y].order_total_price
				 <<" Round ordered: #"<< outorders[y].order_round <<endl
				 <<"Wait time: "<<(round_ID - outorders[y].order_round)<< " rounds."<<endl;
			}
		}
		
		backlog.clear();
		for (int x = 0 ; x<passer.size();  x ++) //passes sorted values to backlog
		{
			backlog.push_back(passer[this_index_next[x]]);
			outorders.push_back(passer[this_index_next[x]]);
		}

		if(backlog.size()==0)
		{
			cout <<"The kitchen has "<<backlog.size()<<" orders";
		}
		
		else
		{
			cout <<"The kitchen has "<<backlog.size()<<" orders (";
		}
		
		for (int x = 0 ; x<backlog.size();  x ++) //passes sorted values to backlog
		{
			if(x == passer.size()-1)
			{
				cout << "#"<<backlog[x].order_ID;
			}
			
			else
			{
				cout << "#"<<backlog[x].order_ID<< ", ";
			}
		}
		
		if(backlog.size()==0)
		{
			cout <<" in its backlog\n";
		}
		
		else
		{
			cout <<") in its backlog\n";
		}
}


void Kitchen_Simulator::count_the_rounds(vector<double>& the)
{
	int x = 0;
	for (int y = 0 ; x < the.size() ; x++)
	{
		if ( (the[x]==4000) || ( x == 0) )
		{
			if(  (the[x+1]!=1000) && (the[x+1]!=2000) && (x<the.size()-1 ) )
			{
				y++;				
				if(x == 0){loc.push_back(x);}
				
				else{loc.push_back(x+1);}
			}
		}		
	}
	
	int m = 1;

	the_last_index = 0;
	bool done = false;
	
	for ( int h = 1 ; done == false ; h++)
	{
		if (the[the.size()-h] != 4000)
		{
			the_last_index = the.size()-h;
			done = true;
		}
	}
}

void Kitchen_Simulator::distribute_the_rounds(vector<double>& the)
{
	int orders_left;
	int this_order =0;
	int next_order=0;
	int y = 0;
	int z= 0;
	int max = loc[loc.size()-1]; 
	rounds_object.order.order_ID = 0;
	vector<double> helper;
	int decider = 0;
	int start;
	int end;
	
	rounds_object.round_ID = 0;
	
	for (int x = 0 ; next_order < the_last_index; x++)
	{
		rounds_object.amount_of_incoming_orders = the[loc[x]];
		rounds_object.amount_of_outgoing_orders = the[loc[x]+2];
		rounds_object.round_ID++;
		this_order = loc[x];
		vector<double> order_dist;
		
		if( this_order != max){next_order = loc[x+1];}
		else{next_order = 9000;}

		if (next_order != 9000)
		{
			for (int y = this_order ; y<next_order ; y++)
			{	
				if ( (the[y] == 1000) || (the[y] == 2000))
				{
					rounds_object.order.order_ID++;
					
					if (the[y] == 1000)
					{
						order_dist.push_back(rounds_object.order.order_ID);				
						order_dist.push_back(the[y]);
						order_dist.push_back(the[y+2]);
						decider = the[y+4];
						order_dist.push_back(the[y+4]);
						for (int m = 0 ; decider != 0 ; decider--, m=m+2){order_dist.push_back(the[y+6+m]);}
						decider = 0;
						order_dist.push_back(77777);
					}
					else if (the[y] == 2000)
					{
						order_dist.push_back(rounds_object.order.order_ID);				
						order_dist.push_back(the[y]);
						order_dist.push_back(the[y+2]);
						order_dist.push_back(1);
						order_dist.push_back(the[y+4]);
						order_dist.push_back(77777);
					}
				}
			}
		}
		
				else
				{
					if ( (the[y] == 1000) || (the[y] == 2000))
					{
						if (the[y] == 1000)
						{
							if(rounds_object.order.order_ID != 1){order_dist.push_back(77777);}
							decider = the[y+4];
							order_dist.push_back(the[y]);
							order_dist.push_back(the[y+4]);
							for (int m = 0 ; decider != 0 ; decider--, m=m+2){order_dist.push_back(the[y+6+m]);}
							decider = 0;
						}
				
						else if (the[y] == 2000)
						{
							if(order_dist.size()!=0){order_dist.push_back(77777);}
							order_dist.push_back(the[y]);
							order_dist.push_back(1);
							order_dist.push_back(the[y+4]);
						}
					}
				}
		
		order_dist.push_back(88888);
		rounds_object.ttl_price_inc_ords(order_dist);
		rounds_object.distribute_the_orders(order_dist, rounds_object.amount_of_incoming_orders,copy_of_dist);
		vector_of_rounds.push_back(rounds_object);
	}
}

void Round::distribute_the_orders(vector<double> order_dist, int total_orders, vector<double>& copy_of_dist)
{
	orders.clear();
	int counter = 0;
	int inc = 0;
	int inc2 = 0;
	int inc3 = 0;
	int order_ID=1;
	double counter2 = 0, counter3;

	for (int x = 0 ; x < order_dist.size(); x++)
	{
		copy_of_dist.push_back(order_dist[x]);
	}

int y = 0 ;
int price_count; 
	for (int x = 0 ; x < order_dist.size(); x++)
	{
		if(order_dist[x] == 88888){break;}
		order.order_ID = order_ID;
		order.order_round = round_ID;
	
		if (order_dist[x+1] == 1000)
		{
			order.order_total_price = 0.0;
			order.order_type = "Menu Items";
			order.how_many_prices = order_dist[x+3];
		
			price_count = order_dist[x+3];
			
			for (int m = price_count, n = (x+4) ; m > 0 ; m-- , n++)
			{
				order.order_total_price += order_dist[n];
			}
			
			if (counter2 == 0)
			{
				counter2 = tempo_price[0];
				counter3 = counter2;
			}
			
			counter2 = tempo_price[0];
			counter3 = counter2;
		}
		
		else if (order_dist[x+1] == 2000)
		{
			order.order_total_price = 0.0;
			order.order_type = "Prix Fixe";
			order.how_many_prices = order_dist[x+3];
			order.order_total_price = order_dist[x+4];
		}
		
		order.order_priority = order_dist[x+2];
		counter = order_dist[x+3];
		inc = x+4; 
		
		while(counter > 0)
		{
			order.order_price.push_back(order_dist[inc]);
			inc2++;
			inc++;
			counter--;
		}
		
		x = inc;
		
		if (inc3 < total_orders)
		{
			orders.push_back(order);
		}	
		
		order_ID++;
		inc3++;
	}
	order.order_price.clear();
}

void Kitchen_Simulator::set_order_prices(vector<double> order_dist , vector<Round> vector_of_rounds)
{
	for (int x = 0 ; x < order_dist.size(); x++)
	{
		cout << "["<<x<<"] = "<<copy_of_dist[x]<<endl;
	}
	int m = 0;
	for(int x = 0 ; x < vector_of_rounds.size() ; x++)
	{
		for (int y =0 ; y < vector_of_rounds[x].amount_of_incoming_orders; y++)
		{
			for (int z = 0 ; z < vector_of_rounds[x].orders[y].how_many_prices ; z++)
			{
				price_helper(x+1,y+1,z+1,vector_of_rounds);
			}
		}
	}
}

double Kitchen_Simulator::price_helper(int x , int y , int z , vector<Round> vector_of_rounds)
{
	x = 3;
	y = 1;
	z = 1;
	int round = 1;
	for( int m = 0 ; m < copy_of_dist.size()  ; m++ ){
		if(x==1){}
		else{
			for( int p = 0 ; copy_of_dist[p] < copy_of_dist.size()  ; p++ ){
				if (copy_of_dist[p]==88888){round++;
					if(round == y){
						for( int s = p+1 ; copy_of_dist[s] != 88888  ; p++ ){
							if (copy_of_dist[s]==z){}		
						}
					}
				}
			}
		}
			if (copy_of_dist[m]==777777){
				if (copy_of_dist[m+1]==x){
					for( int r = m+2 ; r != 77777  ; r++ ){
						if (copy_of_dist[4]==y){
							for( int s = 0 ; s != 77777  ; s++ ){
								if (copy_of_dist[s]==z){}		
							}
						}
					}
				}
			}	
		}
}

void Kitchen_Simulator::fix_copy()
{
	int x = 2;
	for( int m = 0 ; m < copy_of_dist.size()  ; m++ )
	{
		if(copy_of_dist[m] ==88888)
		{
			copy_of_dist[m] = x;
			x++;
		}
	}
}

void Round::ttl_price_inc_ords(vector<double>& order_dist)
{
	total_price_of_incoming_orders_in_this_round = 0;
	
	int counter = 0;
	
	if (order_dist.size() > 0)	
	{
		for( int x = 0 ; x < order_dist.size()  ; x++ )
		{
			
			if(order_dist[x] == 77777){x = x + 1;}
			if(order_dist[x] == 88888){break;}
			if(order_dist[x] == 77777){x = x + 1;}
			if(order_dist[x] == 88888){break;}
			if(order_dist[x+1] == 1000)
			{
				counter =  order_dist[x+3];
				tempo_price.push_back(counter*1000);
				for (int y =0 , z = x+4 ; counter > 0 ; counter--, y = y+1)
				{
					temp_price = order_dist[y+z];
					tempo_price.push_back(order_dist[y+z]);
				}
				
				x = x + 4;
			}
			
			if(order_dist[x+1] == 2000) 
			{
				x = x + 4;
			
			}

			total_price_of_incoming_orders_in_this_round += order_dist[x];
		}
	}
}

void Round::ttl_price_menu_ords(vector<double>& order_price)
{
	total_price_of_added_menu_item_orders_in_the_same_order = 0;

	if (order_price.size() > 0){
		for( int xy = 0 ; xy < order_price.size()  ; xy++ ){
			//these 2000's and 77777's are not repeated here by mistake
			//the loop needs to go through several rounds of these in order to work properly
			if(order_price[xy] == 2000){xy = xy + 3;}
			if(order_price[xy] == 77777){xy = xy + 1;}
			if(order_price[xy] == 2000){xy = xy + 3;}			
			if(order_price[xy] == 77777){xy = xy + 1;}
			if(order_price[xy] == 2000){xy = xy + 3;}
			if(order_price[xy] == 77777){xy = xy + 1;}
			if(order_price[xy] == 2000){xy = xy + 3;}
			if(order_price[xy] == 77777){xy = xy + 1;}
			if(order_price[xy] == 2000){xy = xy + 3;}
			if(order_price[xy] == 77777){xy = xy + 1;}
			if(order_price[xy] == 2000){xy = xy + 3;}
			if(order_price[xy] == 77777){xy = xy + 1;}
			if(order_price[xy] == 2000){xy = xy + 3;}
			if(order_price[xy] == 77777){xy = xy + 1;}
			if(order_price[xy] == 2000){xy = xy + 3;}
			if(order_price[xy] == 77777){xy = xy + 1;}
			
			if(order_price[xy] == 1000){xy = xy + 2;}
			if(order_price[xy] == 88888){break;}//	cout << "order price index " << order_price[xy] << endl;
			total_price_of_added_menu_item_orders_in_the_same_order += order_price[xy];}}//	cout << "total menu var = " <<total_price_of_added_menu_item_orders_in_the_same_order << endl;
}

// the put_the_file_data_inside_a_vector will place a file's data within a vector of doubles
// it will do this by using several for loops
void File_Input_Class::put_the_file_data_inside_a_vector(vector<double>& vector_that_holds_the_data)
{
	ifstream The_File;								 //create fstream object
	The_File.open("test_output_1459971517[0].data"); //open the file
	
	//These vector, character variable, and for loop 
	//will initially put the The_File's data in a vector of strings
	vector<string> helper_vector;
	string helper_string; //loop variable
	
	
	for ( int i = 0 ; The_File.eof()==false ; i++)
	{
		helper_string = The_File.get();
		helper_vector.push_back(helper_string);
	}

	The_File.close(); //close the file. The data has now been absorbed by the vector of strings.
	
	// The vector of strings index 0-3 may contain the following: [5][.][9][5]
	// The following variables and for loop will place 5.95 within index 0
	// and remove indeces 1-3
	string tens, ones, period, tenths, hundredths;
	string added_number;

 	int counter1 = 0;
 	int holderofy = 0;
 	int holderofsize = 0;
 	int temp = 0;
 	string y_plus_three = "";
 	
 	int counter2 = 0;
 	int holderofy2 = 0;
 	int holderofsize2 = 0;
 	int temp2 = 0;
 	string y_plus_three2 = "";

	for ( int x = 0  ;  x < helper_vector.size(); x++)
	{
		if( (helper_vector[x] == ".") && (helper_vector[x-2] != " "))
		{
			tens       = (helper_vector[x-2]);
			ones       = (helper_vector[x-1]);
			period     = (helper_vector[x]);
			tenths     = (helper_vector[x+1]); 
			hundredths = (helper_vector[x+2]);
		
			added_number = tens + ones + period +tenths + hundredths;
			helper_vector[x-2] = added_number;
			temp = x;
						
			for ( int y = x ; temp < helper_vector.size() && (y+3) < helper_vector.size() ; temp++, y++)
			{
				holderofy = y+3;
				holderofsize = helper_vector.size();
				if ( holderofy <holderofsize)
				{				
					y_plus_three = helper_vector[y+3];
					helper_vector[y-1] = y_plus_three;
				}
			}
			counter1 = counter1 + 1;
			x = x-2;
		}

		else if( (helper_vector[x] == ".") && (helper_vector[x-2] == " ")) 
		{
			ones       = (helper_vector[x-1]);
			period     = (helper_vector[x]);
			tenths     = (helper_vector[x+1]); 
			hundredths = (helper_vector[x+2]);

			added_number = ones + period +tenths + hundredths;
			helper_vector[x-1] = added_number;
			temp2 = x;
								
			for ( int y = x ; temp2 < helper_vector.size() && (y+3) < helper_vector.size() ; temp2++, y++)
			{
				holderofy2 = y+3;
				holderofsize2 = helper_vector.size();
				if ( holderofy2 <holderofsize2)
				{				
					y_plus_three2 = helper_vector[y+3];
					helper_vector[y] = y_plus_three2;
				}
			}
			counter2 = counter2 + 1;
			x= x-1;
		}	
	}	
	
	//These variables and for loop now delete the unwanted indeces in the string vector
	int counter3 = 0;
	counter1 = counter1* 4;
	counter2 = counter2*3;
	counter3 = counter1 + counter2;
		
	for ( int z = 1 ; z <=counter3 ; z++)
	{
		helper_vector.pop_back();
	}
	
	//Finally, this for loop transfers the data from the string vector to the vector of doubles
	//using certain values for non-integer values such as the value 1000 for the letter M
	double temp_double;
	string temp_string;

	for ( int x = 0 ; x < helper_vector.size() ; x++)
	{
		vector_that_holds_the_data.push_back('\0');
		if(helper_vector[x] == "M"){vector_that_holds_the_data[x] = 1000.0;}
		else if(helper_vector[x] == "P"){vector_that_holds_the_data[x] = 2000.0;}
		else if(helper_vector[x] == " "){vector_that_holds_the_data[x] = 3000.0;}
		else if(helper_vector[x] == "\n"){vector_that_holds_the_data[x] = 4000.0;}
		
		else
		{
			temp_string = helper_vector[x];
			temp_double = atof(temp_string.c_str());
			vector_that_holds_the_data[x] = temp_double;
		}
	
	}
	
	//this while loop handles a small size glitch within the above for loop
	while (vector_that_holds_the_data.size() >= helper_vector.size()){vector_that_holds_the_data.pop_back();}
}
// the print_the_vector function will print out the contents of the inputed file
// by printing out each index of the vector that holds the file's data
//void File_Input_Class::print_the_vector(vector<double>& vector_that_holds_the_data)
void Kitchen_Simulator::print_the_vector(vector<double>& vector_that_holds_the_data)
{
	//cout<<showbase;
	//cout<<fixed<<showpoint<<setprecision(2);
	
	if(vector_that_holds_the_data.size()<2)
	{
		cout<<"\n\nYour vector is currently empty :-(\n"
			<<"Fill it up using the 	put_the_file_data_inside_a_vector function\n"
			<<"and try again! :-)\n\n";
	}
	
	else
	{
		for (int x = 0 ; x < vector_that_holds_the_data.size() ; x++)
		{
			if     ( vector_that_holds_the_data[x] == 1000){cout <<  "M";}
			else if( vector_that_holds_the_data[x] == 2000){cout << "P";}
			else if( vector_that_holds_the_data[x] == 3000){cout << " ";}	
			else if( vector_that_holds_the_data[x] == 4000){cout << "\n";}
			else
			{
			//	cout <<setprecision(2)<<setfill('0')<< vector_that_holds_the_data[x];
			//	cout <<"["<<x<<"] = " << vector_that_holds_the_data[x]<<endl;	
			}
		}
	}
}

