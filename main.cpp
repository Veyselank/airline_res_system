#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <random>
#include <set>
using namespace std;
int airplane[2][50]; // Matrix M with size 2x50
int turn = 0; // variable of busy waiting algorithm
static int seatCount = 0; // threades will terminate when counter reaches 100
int randNum1(const int& seatCount)
{
	srand(time(NULL));
	int x = rand() % 100 + 1; //assigning random int
	return x;
}
int randNum2(const int& seatCount)
{
	int y = rand() % 100 + 1;
	return y;
}
void *agency1( void* )
{
	while (seatCount < 100)
	{
		int x = randNum1(seatCount); // assigning random variables to 
		/// DO STEP A ///
		while (turn != 0) {}
		/// DO STEP B ///
		cout << "Agency 1 Entered Critical Region\n";
		if (x <= 50 && airplane[0][x-1] == 0)
		{
			airplane[0][x-1] = 1;
			seatCount++;
			cout << "Seat Number "<< x << " is reserved by Agency 1\n";
		}	
		else if (x > 50 && airplane[1][x-51] == 0)
		{
			 airplane[1][x-51] = 1;
			 seatCount++;
			 cout << "Seat Number "<< x << " is reserved by Agency 1\n";
		}
		cout << "Agency 1 Exit Critical Region\n";
		cout << endl;
		turn = 1;
	}
	
	return 0;
}
void *agency2( void *)
{
	while (seatCount < 100)
	{
		int y = randNum2(seatCount);
		/// DO STEP A ///
		while (turn != 1) {}
		/// DO STEP B ///
		cout << "Agency 2 Entered Critical Region\n";
		if (y <= 50 && airplane[0][y-1] == 0) 
		{
			airplane[0][y-1] = 2;
			seatCount++;
			cout << "Seat Number " << y << " is reserved by Agency 2\n";
		}
		else if (y > 50 && airplane[1][y-51] == 0)
		{
			 airplane[1][y-51] = 2;
			 seatCount++;
			 cout << "Seat Number " << y << " is reserved by Agency 2\n";
		}
		cout << "Agency 2 Exit Critical Region\n";
		cout << endl;
		turn = 0;
	}
	return 0;
}
int main()
{
	pthread_t TravelAgency1, TravelAgency2; // threads which will represent travel agencies
	for (int i = 0; i != 2; i++) // filling matrix with 0s which will represent empty seats
	{
		for (int j = 0; j != 50; j++)
		{
			airplane[i][j] = 0;
		}
	}
	pthread_create(&TravelAgency1, NULL, agency1, NULL); // creation of POSIX thread for travel agency 1
	pthread_create(&TravelAgency2, NULL, agency2, NULL); // creation of POSIX thread for travel agency 2

	pthread_join(TravelAgency1, NULL);
	pthread_join(TravelAgency2, NULL);

	cout << "Plane is full: \n" << endl;
	for (int i = 0; i != 2; i++) // prints the matrix
	{
		for (int j = 0; j != 50; j++)
		{
			cout << airplane[i][j] << " ";
		}
		cout << endl;
	}
}