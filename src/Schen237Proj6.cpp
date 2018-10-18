#include "Airport.h"

int main (int argc, char** argv)
{
	// set up the variable inFile to read from standard input
	FILE* inFile = stdin;

	// set up the data needed for the airport adjcency list
	TravelNetwork airportData;

	// call the method that reads and parses the input
	airportData.processCommandLoop (inFile);

	printf ("Goodbye\n");
	return 1;
}