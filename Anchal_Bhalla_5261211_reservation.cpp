/* 
Name-	Anchal Bhalla  
Id- 	5261211 
*/

#include <iostream> 
#include <fstream> // for the input and output of files 
#include <cstring> 
#include <cstdlib>  
#include <cstdio> 
#include <string> 
#include <iomanip> // for setw functions 
#include <cctype> //for toupper functions 

using namespace std ;   

struct Info  
{ 
	char AirplaneCode [7]; // storing the airlines of 6 characters 
	int TotalRows ;       // storing the total number of rows in the airline 
	int TotalSeats ;     // storing the total number of seats in the airline 
	int FirstRows ;     // stroing the number of first class rows in the airline 
	int BusinessRows ; // stroing the number of business class rows in the airline 
	int EconomyRows ; //stroing the number of economy class rows in the airline 
};
Info airplane;  // this structure stores the all the airline information from the admin file  

struct Passengers 
{ 
	char airline [7] ;          //airline code selected by the user 
	char UserReservecode [7] ; // personal user reservation of the user 	 
	int seatsrow ;            // stroing the seat row entered  
	int seatscolumn;         // stroing the seat column entered 
};
Passengers user; // this structure is storing the user information 

char grid [100][100] ;   // the main grid showing the all flight information 
int globalpassengers ;  // used for storing the number of passengers for a user 
char usercode[7];       // used to store the user airline code selected 
int fillrowseats [100] ; //filling the array with the rows selected by the user to book seats 
char fillrowcolumnseats[100]; //filling the array with the rows selected by the user to book seats  

//function prototypes 
void ShowOptionsCode () ;  // reads from the admin file and shows all the flights available 
void ReadingUserInfo () ; // reading user information  
int IsValidCode();                                 // to check whether the code entered by the user for the airline is from the existing options
void EmptySeatAssign (char a[100][100]) ; // assigning the grid to empty that is * 
void PassengerSeats () ;                 // asking the user which seats they want to book 
void DisplayFlights () ;                // displaying the grid for the flight information 
void AssigningTakenSeats () ;          // reading from reservation2 file and assigning all the booked seats to X 
int TakenSeats (char columnnumber, int rownumber) ; // a validation to see if the seat the user is entering has been available and not booked 
int IsInRange(char column, int row) ;              // to check if the seat entered is the range of the grid  
void PrintReport ();                              // prints the summary of the bookings by the user  


int main () 
{ 
	char response ;  //response if there more users to be entered 
	char option ;    // to print the report 
	do 
	{
		EmptySeatAssign (grid) ;  // assign grid to empty 
		cout << "*Welcome to the reservation program*" << endl ; 
		cout << "Enter airplane code from the options given below " << endl ;  
		
		ShowOptionsCode () ;  
		cout << endl; 
		ReadingUserInfo () ; 
		AssigningTakenSeats () ;  
		DisplayFlights() ;
		PassengerSeats() ; 
		DisplayFlights() ; // calling out all the functions 
		cout << endl;    
		cout << "Do you want to print the report " ; 
		cin>> option ;  
		option = toupper(option);  
		if(option=='Y')  
		{ 
			PrintReport() ; 
		} 
		cout << "Are there any more users, enter Y or N (Yes/No) " ; 
		cin >> response ; 
		response= toupper(response) ; // convert to uppercase 
	} while (response=='Y') ;
	system("pause") ; 
	return 0 ;
}   


void EmptySeatAssign (char a[100][100]) 
{ 
	for (int i=0; i<100; i++) 
	{
		for (int j=0 ; j<100; j++) 
		
		{
		  a[i][j] = '*'; // all the elements of the array to empty * 
		
		} 
	}
}   


void ShowOptionsCode () 
{
	ifstream indata ;   // will be used for reading from the admin file 
	indata.open("admin.dat", ios::in| ios::binary) ;  	 // open the admin binary file for reading 
	indata.read(reinterpret_cast<char *>(&airplane), sizeof(Info)) ; // read from the file 
	
	while (!indata.eof())  // until end of file eached keep looping 
	{ 
		cout << airplane.AirplaneCode << endl; // print out the airplane codes 
		indata.read(reinterpret_cast<char *>(&airplane), sizeof(Info)) ;
	}
} 


void ReadingUserInfo () 
{ 
	fstream indata; 
	indata.open("admin.dat", ios::in| ios::binary) ; 
	int a=0; // counter for breaking out in the while loop 
	cout << "Please select the flight code and enter one of the code (6 characters) " << endl ;  
	cin >> user.airline; // enter the airplane code 
	while (!IsValidCode()) // check to see if the code is valid that is from the existing options 
	{ 
		cout << "Invalid code enter again " << endl ; 	 
		cout << "Please select the flight code and enter one of the code (6 characters) " << endl ;  
		cin >> user.airline; 
	}
	for(int i=0; i<7; i++)
	usercode[i] = user.airline[i]; // copying the airline code to a variable 
	 	 
	indata.read(reinterpret_cast<char *>(&airplane), sizeof(Info)) ; // read admin file into airplane structure 
		
	while (!indata.eof() && a==0)  // read until end of the file 
	{ 
		if((string) user.airline == (string)airplane.AirplaneCode) // if the user entered airline code is equal to one of the airline code 
		{
			a=1; 
			break;                                               // then set the counter to 1 and break out of the loop 
		}
		
			indata.read(reinterpret_cast<char *>(&airplane), sizeof(Info)) ; // keep reading the file and putting it in the structure 
	}
	indata.close(); 
}
	
	
int IsValidCode() 
{ 
	fstream check ; 
	check.open("admin.dat", ios::in| ios::binary) ;
	check.read(reinterpret_cast<char *>(&airplane), sizeof(Info)) ; 
	while (!check.eof())	 
	{ 
		if ((string)user.airline==(string)airplane.AirplaneCode)  // if the user entered airline code is equal to one of the airline code then return true  
		return 1 ; 
		check.read(reinterpret_cast<char *>(&airplane), sizeof(Info)) ;
	} 
	return 0; 
	check.close();	
}	


void DisplayFlights () 
{ 
	cout << "Flight Number : " << airplane.AirplaneCode << endl ;
	 
	int first = airplane.FirstRows;       // counter variable for storing first class rows 
	int business = airplane.BusinessRows; // counter variable for storing business class rows 
	int economy = airplane.EconomyRows ; //counter variable for storing economy class rows  
	int total = airplane.TotalRows;  //variable for storing total rows 
	int seats = airplane.TotalSeats; //variable for storing seats 
	
	cout <<setw(28) << setfill(' ')<< " " ;
	for (char r = 'A' ; r< (char)seats+65; r++) // print letters from A till how many columns that is seats are there  
	{
		cout << r << "  ";   
	}
	cout << endl<<endl; 
	for (int a=0; a<total; a++ ) // loop till the end of the total rows 
	{ 
		if (first>0)  // if the first rows are greater than 0 then print and reduce the counter first 
		{
			cout << "  First  Class Row  " ;
			cout <<setw(1) << setfill(' ')<< a+1 << "  "<<setw(6)<<setfill(' ');  
			first--;  
		}
		else if (business>0) // if the business rows are greater than 0 then print and reduce the counter business
		{
			cout << "Business Class Row "  ;  
			cout <<setw(2) << setfill(' ')<< a+1 << "  "<<setw(6)<< setfill(' ');  
			business--; 
		}
		else if (economy>0)  // if the economy rows are greater than 0 then print and reduce the counter economy
		{
			cout << "Economy  Class Row "  ;  
			cout <<setw(2) << setfill(' ')<< a+1 << "  "<<setw(6)<< setfill(' ');  
			economy--;   
		}
		for (int i=0; i<seats; i++)
			cout << grid[a][i]<< "  ";  // and print the grid elements in the row 
		cout<<endl; 
	}
}   


void PassengerSeats () 
{ 

	fstream userfile;
	userfile.open("reservation2.dat",ios::binary| ios::app) ; // open the file reservation2 for storing the information of the reservations 
	
	if(!userfile)
	cout << "error" ;  // if cant open file then error 
	int numbers=0;    // stores the number of passengers               
	char column;     // store the alphabetical column seat  
	int row;        // store the seat row 
	cout << "how many passengers ? "; 
	cin >> numbers;
	
	globalpassengers=numbers;  // set the globalpassengers to the numbers to be used later 
	
	cout << "enter reservation code : ";
	cin >> user.UserReservecode; 
	
	for(int i=0; i<7; i++)
		user.airline[i] = usercode[i];  // copying variable usercode into  airline code
	 
	
	
	for(int j=0; j< numbers; j++) // loop till the number of passengers to ask seats 
	{
		cout << "enter column and row : ";
		cin >> column;
			cin >> row ;
			column = toupper(column); 
			
		while((int)column-65 > airplane.TotalSeats || row > airplane.TotalRows) // row should be between the total rows for the flight type and same for columns 
		{
			cout << "invalid enter again :" ; 
			cin >> column;
				column = toupper(column);
				cin >> row;
		} // to check where it is the range or not 
	 

		while(TakenSeats (column, row)) // while the entered seats are taken keep entering another seats and also check their range 
		{
			cout<< "Invalid enter again "<<endl ;
			cout << "enter column and row : ";
			cin >> column;
			column = toupper(column); 
			cin >> row; 
				while((int)column-65 > airplane.TotalSeats || row > airplane.TotalRows)
		{
			cout << "invalid enter again :" ; 
			cin >> column;
				column = toupper(column);
				cin >> row;
		} 
		}  
		user.seatscolumn = int (column) - 65; // storing the seats column and row in the structure 
		user.seatsrow = row-1;
		
		fillrowseats [j] = row ;          //fill the array with rows selected 
	    fillrowcolumnseats[j] = column ; //fill the array with column selected
	
	    userfile.write(reinterpret_cast<char *>(&user), sizeof(Passengers)) ; // keeping writing the file from the passenger structure 
		grid[user.seatsrow][user.seatscolumn] = 'U'; // and then put a 'U' in that row and column 
}   
	userfile.close() ;
}


int TakenSeats (char columnnumber, int rownumber) 
{
	columnnumber= (int)columnnumber-65 ; 
	rownumber= rownumber-1; 
	if (grid [rownumber][(int)columnnumber]=='X' || grid [rownumber][(int)columnnumber]=='U') // if the seat is taken or user reserved then return true indicating already taken 
	return 1;  	
	else 
	return 0 ; 
}  


void AssigningTakenSeats ()  
{ 
	fstream inputfile ; 
	inputfile.open("reservation2.dat", ios::in| ios::binary) ; // open the reseravtion2 file for reading 
	if (!inputfile)                                           // if file not open then error 
	cerr<< "Error opening the file " ; 
	
	inputfile.read(reinterpret_cast<char *>(&user), sizeof(Passengers)) ; // read the file and put into the passengers user structure 
	
	while (!inputfile.eof()) // until end of file 
	{
		if ((string)usercode==(string)user.airline)  // if the airline code in the file is equal to the usercode then place a take (X) in the grid array 
		{
		grid[user.seatsrow][user.seatscolumn] = 'X' ;

	}
			inputfile.read(reinterpret_cast<char *>(&user), sizeof(Passengers)) ; // keep reading the file 
	
	} 

} 


void PrintReport () 
{ 
	cout << "The following were your bookings " << endl ; 
	cout << "----------------------------------------------" <<endl ; 
	cout << " Airline selected - " << user.airline <<endl ; 
	cout << "User reservation code - " << user.UserReservecode << endl ; 
	cout << "Seats taken "  ;
	for (int i=0; i<globalpassengers; i++) 
	{ 
		cout << fillrowcolumnseats[i] << fillrowseats [i]  << "   " ; // loop until the number of passengers entered by the user 
	} 
	cout << endl ; 
	cout << "-------------------------------------------------" <<endl ; 	

}
