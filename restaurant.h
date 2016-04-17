#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Order
{
	public:
		
		int order_ID;
		int order_priority;
		vector<double> order_price;
		string order_type;
		int how_many_rounds_did_this_order_go_through_AKA_order_wait_time;	
		int how_many_prices;
		double order_total_price;
		int order_round;
	
};

class Round
{
	public:
		
		int round_ID ;
		int amount_of_incoming_orders;
		int amount_of_outgoing_orders;
		double temp_price;
		vector<double> tempo_price;
			
		Order order;
		vector<Order> orders;
		
		
		//vector<double> order_dist;
		
		void processor(vector<int> round_locations, vector<double>& the);
		void ttl_price_inc_ords(vector<double>& order_dist);
		void ttl_price_menu_ords(vector<double>& order_dist);
		double total_price_of_incoming_orders_in_this_round;
		double total_price_of_added_menu_item_orders_in_the_same_order;//added by me
		void distribute_the_orders(vector<double> order_dist, int total_orders, vector<double>& copy_of_dist);
		
	//	void set_order_prices(vector<double> order_dist,  vector<Round> vector_of_rounds);
		
	private:
		
		
		
};

class Kitchen_Simulator
{
	public:
		void simulation(vector<double> the);
		
		void print_the_vector(vector<double>& vector_that_holds_the_data);
		
		
		void press_Y_to_continue();
		
		vector<Round> vector_of_rounds;
		vector<Order> backlog;
		vector<Order> passer;
		Round rounds_object;
		vector<int> loc;
		vector<double> copy_of_dist;
		void count_the_rounds(vector<double>& the);
		void distribute_the_rounds(vector<double>& the);
		//void distribute_the_orders(vector<double>& the);
		int the_last_index; 
		void set_order_prices(vector<double> order_dist,  vector<Round> vector_of_rounds);
		double price_helper(int x , int y , int z , vector<Round> vector_of_rounds);
		void fix_copy();
		void outgoing_orders(int incoming, int outgoing, int round_ID, int this_index );
		bool first_round;
		vector<Order> outorders;
		
	private:
		
};

class File_Input_Class
{
	public:
		void put_the_file_data_inside_a_vector(vector<double>& vector_that_holds_the_data);	
	//	void print_the_vector(vector<double>& vector_that_holds_the_data);
		
	private:
		void turn_characters_to_integers(vector<char>& helper_vector , vector<double>& vector_that_holds_the_data);
		void fix_the_decimal_point(vector<string>& vector_that_holds_the_data);
};
