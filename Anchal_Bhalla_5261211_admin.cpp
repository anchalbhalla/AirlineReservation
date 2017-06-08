/* 
Name- Anchal Bhalla 
ID - 5261211 
*/
#include <iostream>  
#include <fstream> // for handling files 
#include <cstring> 
#include <cstdlib> 

using namespace std ;  

struct Info  
{ 
	char AirplaneCode [7]; 
	int TotalRows ;
	int TotalSeats ; 
	int FirstRows ;
	int BusinessRows ; 
	int EconomyRows ; 
} ; Info airplane [100] ; // to store the airplane structre 

int main () 
{ 
	ofstream outdata ;
	outdata.open("admin.dat", ios::out|ios::app| ios::binary) ; // open file and write to it 
	
	if (!outdata) 
	{ 
		cerr << "Error: Unable to open file " ; 
		exit(1) ;		// if unable to open file error and exit program 
	} 
	int i = 0  ; 
	char response ;  
	
	cout << "* Welcome to the Admin program * " << endl  ;
	do 
	{ 	
		cout << "Enter 6 digit Airplane code " << endl ; 
		cin >> airplane[i].AirplaneCode ; // check whether the code entered is of 6 characters long 
		while (strlen(airplane[i].AirplaneCode)>7)   
		{
			cout << "Code entered was more than 6 characters re-enter code " << endl ; 
			cin >> airplane[i].AirplaneCode ; 
		}
		
		cout <<"Enter total rows in the Airplane " << endl ; 
		cin >>  airplane[i].TotalRows ; 
		
		cout << "Enter seats in each rows in the Airplane " << endl ; 
		cin >>  airplane[i].TotalSeats ;  
		
		cout << "Enter rows in each class " << endl ; 
		cout << "1. First class " ; 
		cin >> airplane[i].FirstRows ;   
		cout << "1. Business class " ; 
		cin >> airplane[i].BusinessRows ;  
		cout << "1. Economy class " ; 
		cin >> airplane[i].EconomyRows ;   // enter all the structure elements 
		int sum = airplane[i].FirstRows + airplane[i].BusinessRows + airplane[i].EconomyRows  ; // check uf the sum is equal to the total rows entered by the classes entered 
		
		while (airplane[i].TotalRows!= sum) // if not then enter everything again 
		{ 
			cout << "Total number of rows enter information does not match the classes row information, please re- enter the information " << endl ;   
			
			cout <<"Enter total rows in the Airplane " << endl ; 
			cin >>  airplane[i].TotalRows ; 
		
			cout << "Enter seats in each rows in the Airplane " << endl ; 
			cin >>  airplane[i].TotalSeats ;  
		
			cout << "Enter rows in each class " << endl ; 
			cout << "1. First class " ; 
			cin >> airplane[i].FirstRows ;   
			cout << "1. Business class " ; 
			cin >> airplane[i].BusinessRows ;  
			cout << "1. Economy class " ; 
			cin >> airplane[i].EconomyRows ;   
			sum = airplane[i].FirstRows + airplane[i].BusinessRows + airplane[i].EconomyRows  ;
		} 
		
		
		outdata.write (reinterpret_cast<char *>(&airplane[i]), sizeof(Info)); // write all the information in the file from the structure 
		i++ ; 
		cout << "Do you want to enter another flight information ? Enter y or n " << endl ; 
		cin >> response ;  // response for if another airline entered
		response= toupper(response) ;
		
	} while (response=='y') ;  
	
	outdata.close () ;  // close file 
	cout << "Data entered and file closed successfully " ; 
 return 0 ;	
}
