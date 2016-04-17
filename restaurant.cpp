#include "restaurant.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h> // to use atof() and c_str()
#include <iomanip>  // to setprecision(2)

using namespace std;

// the press_Y_to_continue() function momentairily pauses the execution time
// until the user presses Y.
// the idea of this class is to improve readibility for the user
void Kitchen_Simulator::press_Y_to_continue()
{
	cout << endl << endl;
	char user_input = 'x';
	
	do
	{
		cout <<"...\nPlease press Y followed by Enter to continue :-)\n...\t\t\t\t\t\t  ";
		cin >> user_input;
	}while( (user_input!='Y') && (user_input!='y') );
	
	cout << endl << endl;
}

void Kitchen_Simulator::simulation(vector<double> the)
{
	count_the_rounds(the);
	distribute_the_rounds(the);
	vector<double> pancakes;
	fix_copy();
	int this_index;
//	set_order_prices(copy_of_dist,  vector_of_rounds);
		
	//distribute_the_orders(the);
	//rounds_object.distribute_other_data(round_locations);

//cout << "order ID = " << vector_of_rounds[0].orders[1].order_ID<<endl;

	for(int x = 0 ; x < vector_of_rounds.size() ; x++)
	{
		this_index = x;
		//cout << "this_index " << this_index << endl;
		cout <<"\n\nROUND #"<< vector_of_rounds[x].round_ID<< "---------------\n";
		cout << "The kitchen will process "<< vector_of_rounds[x].amount_of_incoming_orders
		<< " incoming orders and fullfill " << vector_of_rounds[x].amount_of_outgoing_orders<< " outgoing orders\n"
		<< "*** Incoming Orders ***\n";
		
		
	//	int y <= vector_of_rounds[x].amount_of_incoming_orders;
		for (int y =0 ; y < vector_of_rounds[x].amount_of_incoming_orders; y++)
		{
			//cout << "\n\n--------order--------"<<endl<< endl;
			//cout << "x = " << x << "\ny = "<< y << endl;
			
			
			cout << "ORDER #" << vector_of_rounds[x].orders[y].order_ID	
			<< "  (" << vector_of_rounds[x].orders[y].order_type;	
			 
			if (vector_of_rounds[x].orders[y].order_type == "Menu Items"){cout <<"). ";}
			else if (vector_of_rounds[x].orders[y].order_type == "Prix Fixe"){cout <<").  ";}			 
			 cout <<"Priority: " << vector_of_rounds[x].orders[y].order_priority	
			<<". Total Price: $ 0.00"<<endl;
			
		//	cout << "how many prices = " << vector_of_rounds[x].orders[y].how_many_prices<<endl;
		//	cout << "total price = " << vector_of_rounds[x].orders[y].order_total_price<<endl;
			
			
			for (int z = 0 ; z < vector_of_rounds[x].orders[y].how_many_prices ; z++)
			{
			//	cout << "round " << x+1 << " & order " << y+1 << " & price " << z+1 <<
			//	" is = "<< vector_of_rounds[x].orders[y].order_price[z] <<endl<<endl;
				//cout << "size: "<<vector_of_rounds[x].orders[y].order_price.size() << endl<<endl;
				//cout << "order #"<<z+1<<"'s price = " << vector_of_rounds[x].orders[y].order_price[z]<<endl<<endl;	
			}
		
			passer.push_back(vector_of_rounds[x].orders[y]);
		}
	
		if (vector_of_rounds[this_index].orders.size()>0)
		{
			outgoing_orders(vector_of_rounds[x].amount_of_incoming_orders, vector_of_rounds[x].amount_of_outgoing_orders , vector_of_rounds[x].round_ID , this_index );
		}
			passer.clear();
	cout << "The total price of this round's incoming orders is $" << vector_of_rounds[x].total_price_of_incoming_orders_in_this_round<<"."<<endl;
//	cout << "*** Outgoing Orders ***\n";
		//cout << "total price of added menu orders = " << vector_of_rounds[x].total_price_of_added_menu_item_orders_in_the_same_order<<endl;
		this_index++;
	}
/*		
	for (int x = 0 ; x < order.order_price.size() ; x++ )
	{
		cout << " price["<<x<<"] = " << order.order_price[x] << endl;
	}
	
	cout << " size = " << order.order_price.size() << endl;*/



}

void Kitchen_Simulator::outgoing_orders(int incoming, int outgoing, int round_ID, int this_index)
{

	
	int stop_here = (incoming + outgoing);
	
	for (int x = 0; x < passer.size() ; x ++)
	{
	//	cout << "\n\t"<<passer[x].order_ID; 
	//	cout << "\t"<< passer[x].order_priority<< endl;
	}

		cout << endl;
		




	vector<int> max_index;
	max_index.push_back(0);
	
	
	/*if (passer[x+1].order_priority< min[x]) //MIGHT BE OLD AND INCORRECT
		{
			min.clear();
			min.push_back(passer[x+1].order_priority);
		}
	*/	
	int max_pri = passer[0].order_priority;
	//for (int x = 0 , y = outgoing; y > 0; y--, x++)//takes the index of backlog where the highest priority is;
	for (int x = 0 ; x+1 < passer.size(); x++) //finds the maximum priority
	{
	//	cout << " x = " << x << endl;
		
//		cout << "\norder "<<x+2<<"'s priority = " << passer[x+1].order_priority << " and order "<<x+1<<"'s priority = " << passer[x].order_priority << "\n\n";
		
	//	cout << "if (order "<<x+2<<"'s priority< order "<<x+1<<"'s priority)\n{\n";
		
		if (passer[x+1].order_priority> max_pri)
		{
	//		cout << "\tthe_min[0] = "<<x+1<<";\n";
			max_index[0]= x+1;
			max_pri = passer[x+1].order_priority;
		
		}
	}	
	
	//	cout << "the_min[0]" << the_min[0] << endl;
	//	cout << "The maximum is order " << passer[max_index[0]].order_ID << ", with priority " << passer[max_index[0]].order_priority <<endl;
	
	vector<int> max_indeces;
	max_indeces.push_back(max_index[0]);
	int count = 1;
	
	
	for (int x = 0 ; x < passer.size(); x++) //counts how many equal max priorities we have
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
	//	cout << "count = " << count << endl << endl;
	
	
	/*cout << "max_indeces = ";
	for (int x = 0 ; x <max_indeces.size(); x++) //prints all the max indeces
	{
		//cout << (max_indeces[x]) + 1<< ", ";
	}
	cout << endl << endl;
	*/
/*	HERE HERE HERE MAX PRICE FOR LOOP
	int max_price = passer[max_indeces[0]].order_total_price;
	int max_price_index = 0;
	for (int x = 1 ; x < passer.size(); x++) //figure out which repeat max index has the largest price
	{
		if (x != max_indeces[0])
		{
			if (passer[max_indeces[x]].order_total_price > max_price)
			{
				max_price = passer[max_indeces[x]].order_total_price;
				max_price_index = max_indeces[x];
				//this should be a sorted vector of prices;
			}
		}
	}
*/
	vector<int> sorted_pri_indeces;
	//this should later work with a sorted vector of prices, not max indeces vector
	//cout << "sorted : ";
	if(max_indeces.size()>1)//if we have repeated, do this
	{
		for (int x = 0 ; x < max_indeces.size(); x++) //absorbs sorted repeated max priorities
		{
			sorted_pri_indeces.push_back(max_indeces[x]);
	//		cout << (sorted_pri_indeces[x]) +1<< ", ";
		}
		
		
		int next_max = 0;
	
		for (int x = 0, count = (passer.size() - max_indeces.size()) ; count > 0; x++) //counts how many equal max priorities we have
		{
			if (x != max_indeces[x])
			{
				if (passer[x].order_priority > next_max)
				{
					sorted_pri_indeces.push_back(x);
					count--;
				}
			}
		}
	}
	
	else //if we don't, do this
	{
//	cout << "here" << endl;
		sorted_pri_indeces.push_back(max_index[0]);
		
		
	/*	
		for (int x = 0 ; x < passer.size(); x++) //counts how many equal max priorities we have
		{
			if (x != max_index[0])
			{
				if (passer[x].order_priority > next_max)
				{
					sorted_pri_indeces.push_back(x);
					max_indeces.push_back(x);
					count++;
				}
			}
		}
	*/	
		int next_max = 0;
		
		for (int x = 1, count = (passer.size() - sorted_pri_indeces.size()) ; count > 0; x++) //counts how many equal max priorities we have
		{
		//	if (x != max_index[x])
		//	{
				//if ((passer[x].order_priority > next_max) && (x < (passer.size() - 1)) )
				if (passer[x].order_priority > next_max)
				{
				//	cout << "here" << endl;
					sorted_pri_indeces.push_back(x);
					count--;
					next_max = passer[x].order_priority;
				}
		//	}
		}
	
	}
	
	cout << endl;
	
	//now, which is the next maximum priority, and where is it?
	

	
//	cout << "sorted : ";
	for (int x = 0 ; x < sorted_pri_indeces.size(); x++) //absorbs sorted repeated max priorities
	{
		//sorted_pri_indeces.push_back(max_indeces[x]);
//		cout << (sorted_pri_indeces[x]) +1<< ", ";
	}
	
	
	//	for (int x = 0; x < passer.size() ; x ++) //passes values perfectly from passer to backlog
//	{
//		backlog.push_back(passer[x]);
	//	cout << "\n\t"<<backlog[x].order_ID; 
	//	cout << "\t"<< backlog[x].order_priority<< endl;
//	}
	

}


void Kitchen_Simulator::count_the_rounds(vector<double>& the)
{
	//how many rounds do I have?
	//and where in my vector are my round's located?
	
	//vector<int> round_locations;//amount of indeces = how many rounds I have
								//content of indeces = where those rounds are
				
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
	
	//loc.push_back(loc[loc.size()-1]+2);

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
	
//	cout << the_last_index << endl;
	//	cout << the_last_value << endl;
	//for (int m = 1 ; the[the.size()-m]!=4000 ; m++)
	//{
	//	cout <<the[the.size()-m]<<endl;
	//	if (the[the.size()-m]!=4000)
	//	{
			//the_last_value = the[the.size()-m];
	//	}
		//cout << "round "<<x+1<<" is in "<< loc[x]<<endl;
	//}
	
	//cout << "the last value:  "<<the_last_value<<endl;
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
		rounds_object.amount_of_incoming_orders = the[loc[x]];//cout << " incoming: "<<rounds_object.amount_of_incoming_orders <<endl;
		rounds_object.amount_of_outgoing_orders = the[loc[x]+2];//cout << " outgoing: "<< rounds_object.amount_of_outgoing_orders <<endl;
		rounds_object.round_ID++;//cout <<"rounds_object.round_ID : " << rounds_object.round_ID<<endl;
	//cout <<"\n\n---------------Round "<< rounds_object.round_ID<< "---------------\n\n";
		this_order = loc[x];
		vector<double> order_dist;
		
		if( this_order != max){next_order = loc[x+1];}
		else{next_order = 9000;}
	//	cout <<" this :" << this_order << endl 
	//	<<" next: " << next_order << endl;
		if (next_order != 9000)
		{
			for (int y = this_order ; y<next_order ; y++)
			{	
				//cout <<"["<<y<<"] = " << the[y]<<endl;
				if ( (the[y] == 1000) || (the[y] == 2000))
				{
					rounds_object.order.order_ID++;	//cout << rounds_object.order.order_ID << endl;
					
					if (the[y] == 1000)
					{
						order_dist.push_back(rounds_object.order.order_ID);				
						//rounds_object.order.order_type = "M";//cout <<rounds_object.order.order_type <<endl;
						order_dist.push_back(the[y]);
						//rounds_object.order.order_priority = the[y+2];//cout<<rounds_object.order.order_priority <<endl;
						order_dist.push_back(the[y+2]);
						
						//if(rounds_object.order.order_ID != 1){rounds_object.order.order_price.push_back(77777);}
						decider = the[y+4];
						//rounds_object.order.order_price.push_back(the[y]);
						order_dist.push_back(the[y+4]);
						for (int m = 0 ; decider != 0 ; decider--, m=m+2){order_dist.push_back(the[y+6+m]);}
						decider = 0;
						//if(rounds_object.order.order_ID != 1){rounds_object.order.order_price.push_back(77777);}
						order_dist.push_back(77777);
					}
					else if (the[y] == 2000)
					{
						order_dist.push_back(rounds_object.order.order_ID);				
						//rounds_object.order.order_type = "P";//cout <<rounds_object.order.order_type <<endl;
						order_dist.push_back(the[y]);
						//rounds_object.order.order_priority = the[y+2];//cout<<rounds_object.order.order_priority <<endl;
						order_dist.push_back(the[y+2]);
						order_dist.push_back(1);
						//if(rounds_object.order.order_ID != 1){rounds_object.order.order_price.push_back(77777);}
						order_dist.push_back(the[y+4]);//14.25 repeatscout<<rounds_object.order.order_price[0]<<endl;
						//if(rounds_object.order.order_ID != 1){rounds_object.order.order_price.push_back(77777);}
						order_dist.push_back(77777);
					}
				}
			}
		}
		
				else
				{//cout <<"["<<y<<"] = " << the[y]<<endl;
					if ( (the[y] == 1000) || (the[y] == 2000))
					{
						//rounds_object.order.order_ID++;	//cout << rounds_object.order.order_ID << endl;
						if (the[y] == 1000)
						{
							//rounds_object.order.order_type = "M";//cout <<rounds_object.order.order_type <<endl;
							//rounds_object.order.order_priority = the[y+2];//cout<<rounds_object.order.order_priority <<endl;
							if(rounds_object.order.order_ID != 1){order_dist.push_back(77777);}
							decider = the[y+4];
							order_dist.push_back(the[y]);
							order_dist.push_back(the[y+4]);
							for (int m = 0 ; decider != 0 ; decider--, m=m+2){order_dist.push_back(the[y+6+m]);}
							decider = 0;
						}
						else if (the[y] == 2000)
						{
							//rounds_object.order.order_type = "P";//cout <<rounds_object.order.order_type <<endl;
							//rounds_object.order.order_priority = the[y+2];//cout<<rounds_object.order.order_priority <<endl;
							if(order_dist.size()!=0){order_dist.push_back(77777);}
							order_dist.push_back(the[y]);
							order_dist.push_back(1);
							order_dist.push_back(the[y+4]);//14.25 repeatscout<<rounds_object.order.order_price[0]<<endl;
						}
					}
				}
		
	//	if(rounds_object.order.order_price.size()!=0){rounds_object.order.order_price.push_back(77777);}
		order_dist.push_back(88888);
		//if(order_dist[0] == 88888){order_dist.pop_back();}
		//rounds_object.orders.push_back(rounds_object.order);
	//	rounds_object.order.order_ID= 0;
	//	rounds_object.order.order_priority = 0;
		
		//start = 0;
		//end = ( rounds_object.order.order_price.size() ) - 1; 
		rounds_object.ttl_price_inc_ords(order_dist);
	
	//	rounds_object.ttl_price_menu_ords(rounds_object.order_dist);
		
		for(int x = 0 ; x < order_dist.size() ; x++)
		{
	//	cout << "order dist vector index[" << x <<"] = " << order_dist[x]<<endl;
		//cout <<"[" << order_dist[x]<<"]" ;
		}
		
		//Order object;
		rounds_object.distribute_the_orders(order_dist, rounds_object.amount_of_incoming_orders,copy_of_dist);
	//	rounds_object.set_order_prices(order_dist);
				
		vector_of_rounds.push_back(rounds_object);
	
	//	order_dist.clear();
		//cout <<"\n\nRound "<< rounds_object.round_ID+1<< "\n\n";
		//order_dist.clear();
		//	rounds_object.order.order_price.clear();
	}
}

void Round::distribute_the_orders(vector<double> order_dist, int total_orders, vector<double>& copy_of_dist)
{
	orders.clear();
	int counter = 0;
	//int total_orders = 0;
	int inc = 0;
	int inc2 = 0;
	int inc3 = 0;
	int order_ID=1;
	double counter2 = 0, counter3;
//	cout << endl;
//	cout << "passed vector: \n\n";
//	cout << "size = " << order_dist.size()<<endl;
	for (int x = 0 ; x < order_dist.size(); x++)
	{
		//cout << "["<<order_dist[x]<<"]"<<endl;
		copy_of_dist.push_back(order_dist[x]);
		
	}
	
	for (int x = 0 ; x < tempo_price.size(); x++)
	{
	//	cout << "tempo order["<<x<<"] = " <<tempo_price[x]<<endl;
		//copy_of_dist.push_back(order_dist[x]);
		
	}
	
//	cout << endl << endl;
	
	//order_dist[x] != 88888
	
//	total_orders = order_dist[x+3];
//	x < order_dist.size()
int y = 0 ;
	for (int x = 0 ; x < order_dist.size(); x++)
	{
	//	cout <<"\n\n-------order-------\n\n";
		if(order_dist[x] == 88888){break;}
		//cout << "x =" << x << endl;
		order.order_ID = order_ID;
	//	cout << "order ID: " << order_ID << endl;
		
		if (order_dist[x+1] == 1000)
		{
			order.order_type = "Menu Items";//	cout << "order type: " << order.order_type << endl;
			order.how_many_prices = order_dist[x+3];
		//	cout <<"\nbeginning of loop\n";
			if (counter2 == 0)
			{
				counter2 = tempo_price[0];
				counter3 = counter2;
			}
			
			counter2 = tempo_price[0];
				counter3 = counter2;
		//	cout << "this\n";
		

		
		//(counter2)/1000;
			
		//	for (int g = 0, v = 1 ; g < (counter2 / 1000) && g < tempo_price.size(); g++, v++)
		//	{
		
		
		// && tempo_price[y] <500 //another one y < tempo_price.size() //&& tempo_price[y] < 800
	/*	for (; y < (counter2 / 1000)  ; y++)
		{
			if (tempo_price[y+1] > 800)
			{
				counter = y+1;
				break;
			}
			cout << "y = " << y << endl;
			cout << "(counter2 / 1000)"<<(counter2 / 1000);
					
			//cout << "y\n";
		
			//	cout << "(tempo_price[x]) / 1000 = " <<(tempo_price[x]) / 1000 <<endl;
			
			cout << "price to input: " << tempo_price[y+1] << endl;
			
			y++;
		
		}	*/
		//	counter3 = tempo_price[counter2];
		//	cout <<"\nend of loop\n";
		}
		
		else if (order_dist[x+1] == 2000)
		{
			order.order_type = "Prix Fixe";
		//	cout << "order type: " << order.order_type << endl;
			order.how_many_prices = order_dist[x+3];
		}
		
		order.order_priority = order_dist[x+2];
		//cout << "order priority: " << order.order_priority << endl;
		
		counter = order_dist[x+3]; // order list at  3, which is 6
		
		inc = x+4; //equals 4
		
		while(counter > 0)
		{
			order.order_price.push_back(order_dist[inc]);//order at 4
		//	cout << "price = " << order_dist[inc]<<endl;
			//cout << "order's price vector: " << order.order_price[inc] << endl;
			
			inc2++;
			inc++;
			counter--;
		}
		
		x = inc;
		
		//cout << "and this should be 7777: " << order_dist[inc] <<
		
		//cout << "above inc 3 temp price = " << temp_price << endl;
		//--->	
		//	cout << "inc3 = " << inc3 <<"\n total orders = " << total_orders <<endl;
		if (inc3 < total_orders)
		{
		//	cout << "inc3 = " << inc3 <<"\n total orders = " << total_orders <<endl;
		//	cout << "order object order ID = "<< order.order_ID << endl;
			//order.order_total_price = temp_price;
		//	cout << "inc 3 temp price = " << temp_price << endl;
			orders.push_back(order);
		//	cout << "orders["<<inc3<<"].orderID = " << orders[inc3].order_ID << endl;
		}	
		
		order_ID++;
		inc3++;
		
	}
	//go from order 1 to last individual order price from the order dist vector
		//place each data in the Round's order object
		//place that object in a vector of orders
		//reset all of the order object's variables
	
//	for (int x = 0 ; x < order.order_price.size() ; x++ )
//	{
//		cout << " price["<<x<<"] = " << order.order_price[x] << endl;
//	}
	
//	cout << " size = " << order.order_price.size() << endl;
	order.order_price.clear();//order at 4
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
		cout <<"\n\n---------------Round "<< x+1<< "---------------\n\n";
			
		for (int y =0 ; y < vector_of_rounds[x].amount_of_incoming_orders; y++)
		{
			cout << "\n\n--------order--------"<<endl<< endl;
				
			for (int z = 0 ; z < vector_of_rounds[x].orders[y].how_many_prices ; z++)
			{
			//	cout << "round " << x+1 << " & order " << y+1 << " & price " << z+1 <<endl<<endl;
			//	" is = "<< vector_of_rounds[x].orders[y].order_price[z] <<endl<<endl;
				price_helper(x+1,y+1,z+1,vector_of_rounds);
			
			/*	for( int m = 0 ; m < copy_of_dist.size()  ; m++ )
				{
			
					if(order_dist[m] == 77777){m = m + 1;}
					if(order_dist[m] == 88888){m++;break;}
					if(order_dist[m] == 77777){m = m + 1;}
					if(order_dist[m] == 88888){m++;break;}
					if( (order_dist[m+1] == 1000)|| (copy_of_dist[m+1] == 2000) ){m = m + 4;}
					
					cout <<"m = "<<m <<endl;
					cout << "order_dist["<<m<<"] = " <<copy_of_dist[m] << endl;				
					//total_price_of_incoming_orders_in_this_round += order_dist[x];
					//vector_of_rounds[x].orders[y].order_price.push_back(order_dist[x]);
				}
			*/	
			//	if(order_dist[m] == 88888){break;}
				
				//vector_of_rounds[x].orders[y].order_price.push_back(5);
				
				//cout << "size: "<<vector_of_rounds[x].orders[y].order_price.size() << endl<<endl;
				//cout << "order #"<<z+1<<"'s price = " << vector_of_rounds[x].orders[y].order_price[z]<<endl<<endl;	
				//vector_of_rounds[x].orders[y].order_price.push_back(5);
			}
			//if(order_dist[m] == 88888){break;}
		}
	//	if(order_dist[m] == 88888){break;}
	}
	

}

double Kitchen_Simulator::price_helper(int x , int y , int z , vector<Round> vector_of_rounds)
{
	//total_price_of_incoming_orders_in_this_round = 0;
	
	x = 3;
	y = 1;
	z = 1;
	int round = 1;
	for( int m = 0 ; m < copy_of_dist.size()  ; m++ )
	{
		cout << "m = " << m << endl;
		if(x==1)
		{
			
		}
		else
		{
			for( int p = 0 ; copy_of_dist[p] < copy_of_dist.size()  ; p++ )
			{
				cout << "p = " << p << endl;
				if (copy_of_dist[p]==88888)
				{
					round++;
					if(round == y)
					{
						for( int s = p+1 ; copy_of_dist[s] != 88888  ; p++ )
						{
							cout << "s = " << m << endl;
							if (copy_of_dist[s]==z)
							{
								cout << "dddddd"<<copy_of_dist[s] << endl;
							}		
						}
					}
				}
			}
		
		}
			if (copy_of_dist[m]==777777)
			{
				if (copy_of_dist[m+1]==x)
				{
					for( int r = m+2 ; r != 77777  ; r++ )
					{
						if (copy_of_dist[4]==y)
						{
							for( int s = 0 ; s != 77777  ; s++ )
							{
								if (copy_of_dist[s]==z)
								{
									cout << "dddddd"<<copy_of_dist[s] << endl;
								}		
							}
						}
					}
				}
			}	

	}
	
			//if(copy_of_dist[m] == 77777){m = m + 1;}
		//if(copy_of_dist[m] == 88888){;break;}
		//if(copy_of_dist[m] == 77777){m = m + 1;}
		//if(copy_of_dist[m] == 88888){;break;}
		//if( (copy_of_dist[m+1] == 1000)|| (copy_of_dist[m+1] == 2000) ){m = m + 4;}
	
		//	cout <<"m = "<<m <<endl;
		//	cout << "order_dist["<<m<<"] = " <<copy_of_dist[m] << endl;				
			//total_price_of_incoming_orders_in_this_round += order_dist[x];
			//vector_of_rounds[x].orders[y].order_price.push_back(order_dist[x]);
	//cout << "total price var = " <<total_price_of_incoming_orders_in_this_round << endl;
					
}

void Kitchen_Simulator::fix_copy()
{
	int x = 2;
	for( int m = 0 ; m < copy_of_dist.size()  ; m++ )
	{
		if(copy_of_dist[m] ==88888)
		{
			//cout << copy_of_dist[m] << endl;
		//	cout << x <<endl;
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
				//	cout << "m price = "<<order_dist[y+z]<<endl;
					//order.order_total_price = order_dist[y+z];
					temp_price = order_dist[y+z];
					tempo_price.push_back(order_dist[y+z]);
				//	cout << " temp price in function = " << temp_price << endl;
				}
				
				x = x + 4;
			}
			
			if(order_dist[x+1] == 2000) 
			{
				x = x + 4;
			
			}
			//cout << "order_dist["<<x<<"] = " <<order_dist[x] << endl;				
			total_price_of_incoming_orders_in_this_round += order_dist[x];
		}
	}
	
	//cout << "total price var = " <<total_price_of_incoming_orders_in_this_round << endl;
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

