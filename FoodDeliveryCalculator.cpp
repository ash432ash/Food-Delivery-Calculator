#include<bits/stdc++.h>
using namespace std;

void ash(){
    freopen("input.txt", "r", stdin);    
    //freopen("output.txt", "w", stdout); 
} 

class Orders
{
public:
	int orderId;
	vector <char> listofMeals;
    double distance;
    int appetiserTime;
    int mainCourseTime;
    Orders (int a,int b)
    {
    	appetiserTime=a;
    	mainCourseTime=b;
    }
};

//Sample input to be provided in the input.txt file

int main()
{
	ash();//For file input and output

	string s;
	queue<Orders> orderList;//Queue for containing the orders

	//Assuming there are no spaces at start and end of input string
	//This function is for parsing the input string to the Orders object
	while(getline(cin,s))
	{
      
      //Extracting the orderId
      int i=0;
      int orderId=0;
      while(s[i]!=',')
       orderId=10*orderId+(s[i++]-'0');
      i++;

      //Extracting the Meals
      vector<char> listofMeals;
      while(s[i]!=']')
      {
      	if(s[i]=='A'||s[i]=='M')
         listofMeals.push_back(s[i]);
      i++;
      }
      i+=3;
      
      //Extracting the distance
      string t;
      while(s[i])
      	t+=s[i++];
      double distance=stod(t);//Converting string to double

      Orders order(17,29);
      order.orderId=orderId;
      order.listofMeals=listofMeals;
      order.distance=distance;

      orderList.push(order);//Pusing the order into the queue
	 }

     // Creating a vector of slots where each slot will store how much time it will take to complete the meal 
     // Initialized with zero
	 vector<int> restaurantSlots(7,0);

      while(!orderList.empty())
      {
      	Orders order=orderList.front();

      	int slotsRequired=0;
      	double distanceTime=order.distance*8;//Calculating the delivery time

      	int maxMealTime=order.appetiserTime;//It will store the maximum time required for a particular order which will either be appetiserTime or mainCourseTime


      	for(auto i:order.listofMeals) //Calculating the slots required for the ordeer
      		{
               if(i=='A')
               	slotsRequired+=1;
               else
               {
               	slotsRequired+=2;
               	maxMealTime=order.mainCourseTime;
      		   }
            }

      	if(slotsRequired>7)//If more than 7 slots order denied
      		cout<<"Order "<<order.orderId<<" is denied"<<" because the restaurant cannot accommodate it.\n";
      	else
      	{
      		sort(order.listofMeals.begin(),order.listofMeals.end());//Sorting the listofMeals

            int mealTime=restaurantSlots[slotsRequired-1]+maxMealTime;//Meal time will be time taken by the slot when it will be free + maxMealTime for the current order
            
            double orderDeliveryTime=mealTime+distanceTime;//Total Time taken

            if(orderDeliveryTime>150)// If it exceeds 2hr 30 min
              cout<<"Order "<<order.orderId<<" is denied"<<" because it will take more than 2 hour 30 minutes.\n";
            else
            {
            	int start=0;

             for(auto i:order.listofMeals)//Filling the restaurant slot with the time taken by the type of meal
             {
                if(i=='A')
                	restaurantSlots[start++]+=order.appetiserTime;
                else
                {
                	restaurantSlots[start++]+=order.mainCourseTime;
                	restaurantSlots[start++]+=order.mainCourseTime;
                }

             }
             sort(restaurantSlots.begin(),restaurantSlots.end());//Sorting the slots by their time when it will be free

            cout<<"Order "<<order.orderId<<" will be delivered in "<<orderDeliveryTime<<" minutes.\n";
            }

      	  }

      	  orderList.pop();
      	

      }
	
}



