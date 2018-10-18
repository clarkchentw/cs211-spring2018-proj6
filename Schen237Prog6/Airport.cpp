/*
        Name: Clark Chen
        NetID: schen237
        Date: 4/19/2018
        Project #: 6
        Term: Spring 2018
*/

#include "Airport.h"

///////////////////////////////////////////////////////////////////////////////////
// Node Class: Linked List element
///////////////////////////////////////////////////////////////////////////////////
// Default Constructor for Node Class
Node::Node(){
	value = -1;
	pNext = NULL;
}

///////////////////////////////////////////////////////////////////////////////////
// Get value of the node (Arrival Airport)
int Node::getValue(){
	return value;
}

///////////////////////////////////////////////////////////////////////////////////
// Set Value of the node (Arrival Airport)
void Node::setValue(int inputValue){
	value = inputValue;
}

///////////////////////////////////////////////////////////////////////////////////
// Get next pointer
Node* Node::getNext(){
	return pNext;
}

///////////////////////////////////////////////////////////////////////////////////
// Set Next pointer
void Node::setNext(Node* inputNext){
	pNext = inputNext;
}



///////////////////////////////////////////////////////////////////////////////////
// List Class: For linked list control
///////////////////////////////////////////////////////////////////////////////////
// Default Constructor for List Class
List::List()
{
	hd = NULL; // set to null
}

///////////////////////////////////////////////////////////////////////////////////
// Add flight
void List::add(int inputValue){
	// Input Check
	if (inputValue <= 0){
		printf("Invalid airport number input <= 0");
		return;
	}
	
	if (hd == NULL){
		hd = new Node();
		hd->setValue(inputValue);
		return;
	}
	Node* temp = new Node();
	temp->setValue(inputValue);
	temp->setNext(hd);
	hd = temp;
}

///////////////////////////////////////////////////////////////////////////////////
// Remove a flight by arrival airport
bool List::remove(int arrival){
	if (hd == NULL){
		return false;
	}
	Node* curr = hd;
	Node* prev = NULL;
	if (hd->getValue() == arrival){
		delete hd;
		hd = NULL;
		return true;
	}
	while (curr != NULL){
		printf("Removing search at %d\n", curr->getValue());
		printf("Removing looking for %d\n", arrival);
		printf("Removing result is %d\n", curr->getValue() == arrival);
		if (curr->getValue() == arrival){
			prev->setNext(curr->getNext());
			delete curr;
			curr = NULL;
			return true;
		}
		curr = curr->getNext();
		prev = curr;
	}
	
	return false;
}

///////////////////////////////////////////////////////////////////////////////////
// Print the list
void List::print(){
	if (hd == NULL){
		printf("Empty\n");
		return;
	}
	Node* curr = hd;
	while(curr != NULL){
		printf("%d ", curr->getValue());
		curr = curr->getNext();
	}
	printf("\n");
}

///////////////////////////////////////////////////////////////////////////////////
// Clear the list
void List::clear(){
	while (hd != NULL){
		Node* temp = hd->getNext();
		delete hd;
		hd = temp;
	}
	hd = NULL; // Set to null
}

///////////////////////////////////////////////////////////////////////////////////
// Get the length of the list
int List::getListLength(){
	Node* curr = hd;
	int count = 0;
	while(curr != NULL){
		count++;
		curr = curr->getNext();
	}
	return count;
}

///////////////////////////////////////////////////////////////////////////////////
// get nth value
int List::getNthValue(int index){
	Node* curr = hd; // This is the first element
	for (int i = 2; i <= index; i++){ // Run only if index >= 2
		curr = curr->getNext();
	}
	return curr->getValue();

}



///////////////////////////////////////////////////////////////////////////////////
// Airport Class: To group flight by airport
///////////////////////////////////////////////////////////////////////////////////
// Default Constructor for Airport Class
Airport::Airport()
{
	adjAirport = new List();
	visited = false;
}

///////////////////////////////////////////////////////////////////////////////////
// Check if isvisited
bool Airport::isVisited(){
	return visited;
}

///////////////////////////////////////////////////////////////////////////////////
// Set visited status
void Airport::setVisited(bool inputVisited){
	visited = inputVisited;
}

///////////////////////////////////////////////////////////////////////////////////
//Get the list of Adjcent Airport
List* Airport::getAdjAirport(){
	return adjAirport;
}



///////////////////////////////////////////////////////////////////////////////////
// TravelNetwork Class: To Control the whole travel network
///////////////////////////////////////////////////////////////////////////////////
// Default Constructor for TravelNetwork Class
TravelNetwork::TravelNetwork()
{
	airports = new Airport*[0];
	numOfAirport = 0;
	doResize(10);
}

///////////////////////////////////////////////////////////////////////////////////
// To get the next input
// Return -1 for error encountered
int TravelNetwork::getAirportInput(){
	int input = 0;
	
	// get an integer value from the input
	char* next = strtok (NULL, " \n\t");
	if ( next == NULL )
	{
		printf ("Integer value expected\n");
		return -1;
	}
	input = atoi ( next );
	if ( input == 0 && strcmp (next, "0") != 0)
	{
		printf ("Integer value expected\n");
		return -1;
	}
	if (input > numOfAirport){
		printf("Airport %d is out of range\n", input);
		return -1;
	}
	return input;
}

///////////////////////////////////////////////////////////////////////////////////
// The main loop for reading in input
void TravelNetwork::processCommandLoop (FILE* inFile)
{
	char  buffer[300];
	char* input;
	
	input = fgets ( buffer, 300, inFile );   // get a line of input
	
	// loop until all lines are read from the input
	while (input != NULL)
	{
		// process each line of input using the strtok functions 
		char* command;
		command = strtok (input , " \n\t");
		
		printf ("*%s*\n", command);
		
		if ( command == NULL )
			printf ("Blank Line\n");

		else if ( strcmp (command, "q") == 0) 
			exit(1);

		else if ( strcmp (command, "?") == 0) 
			showCommands();

		else if ( strcmp (command, "t") == 0) 
			doTravel();

		else if ( strcmp (command, "r") == 0) 
			doResize();

		else if ( strcmp (command, "i") == 0) 
			doInsert();

		else if ( strcmp (command, "d") == 0) 
			doDelete();

		else if ( strcmp (command, "l") == 0) 
			doList();

		else if ( strcmp (command, "f") == 0) 
			doFile();

		else if ( strcmp (command, "#") == 0) 
			;

		else
			printf ("Command is not known: %s\n", command);

		printf("\n");
		input = fgets ( buffer, 300, inFile );   // get the next line of input

	}
}

///////////////////////////////////////////////////////////////////////////////////
// Show Commands
void TravelNetwork::showCommands()
{
	printf ("The commands for this project are:\n");
	printf ("  q \n");
	printf ("  ? \n");
	printf ("  # \n");
	printf ("  t <int1> <int2> \n");
	printf ("  r <int> \n");
	printf ("  i <int1> <int2> \n");
	printf ("  d <int1> <int2> \n");
	printf ("  l \n");
	printf ("  f <filename> \n");
}

///////////////////////////////////////////////////////////////////////////////////
// Method to check if travel is valid
void TravelNetwork::doTravel()
{
	int val1 = getAirportInput();
	int val2 = getAirportInput();
	if (val1 == -1 || val2 == -1){
		return;
	}

	printf ("Performing the Travel Command from %d to %d\n", val1, val2);
	depthFirstSearchHelper(val1, val2);
	
}

///////////////////////////////////////////////////////////////////////////////////
// Method to resize the airports array
void TravelNetwork::doResize(int newSize)
{
	if (newSize == -1){
		char* next = strtok (NULL, " \n\t");
		newSize = atoi ( next );
		printf ("Performing the Resize Command with %d\n", newSize);
	}
	if (newSize < 0){
		printf("Resize value is < 0\n");
		return;
	}
	// Clear the array
	if (airports != NULL){
		for (int i = 1; i <= numOfAirport; i++){
			if (airports[i] != NULL){
				airports[i]->getAdjAirport()->clear();
				delete[] airports[i];
				airports[i] = NULL; // set back to null
			}
			else{
				printf("Something weir happaned during the resize:clear process...");
				return;
			}
		}
		delete[] airports;
		airports = NULL; // set back to null
		
	}
	
	airports = new Airport*[newSize+1]; //left 0 empty, easier to manage
	for (int i = 1; i <= newSize; i++){
			airports[i] = new Airport();
	}
	numOfAirport = newSize;
}

///////////////////////////////////////////////////////////////////////////////////
// Method to insert flight
void TravelNetwork::doInsert()
{
	// Insert a flight
	int val1 = getAirportInput();
	int val2 = getAirportInput();
	if (val1 == -1 || val2 == -1){
		return;
	}

	printf ("Performing the Insert Command from %d to %d\n", val1, val2);
	airports[val1]->getAdjAirport()->add(val2); //Insert flight from val1 to val2
}

///////////////////////////////////////////////////////////////////////////////////
// Method to Delete Flight
void TravelNetwork::doDelete()
{
	// Remove a flight
	int val1 = getAirportInput();
	int val2 = getAirportInput();
	if (val1 == -1 || val2 == -1){
		return;
	}


	printf ("Performing the Delete Command from %d to %d\n", val1, val2);
	//Delete flight from val1 to val2
	if (!airports[val1]->getAdjAirport()->remove(val2)){
		printf("Error occur while deleting flight from %d to %d\n", val1, val2);
	} 
}

///////////////////////////////////////////////////////////////////////////////////
// Method to List flight
void TravelNetwork::doList()
{
	for (int i = 1; i <= numOfAirport; i++){
		printf("Airport %d: ", i);
		airports[i]->getAdjAirport()->print();
	}
}

///////////////////////////////////////////////////////////////////////////////////
// Method to process input file
void TravelNetwork::doFile()
{
	
	// get a filename from the input
	char* fname = strtok (NULL, " \n\t");
	if ( fname == NULL )
	{
		printf ("Filename expected\n");
		return;
	}

	printf ("Performing the File command with file: %s\n", fname);
	
	FILE* newInput;
	
	// next steps:  (if any step fails: print an error message and return ) 
	//  1. verify the file name is not currently in use
	
	
	//  2. open the file using fopen creating a new instance of FILE*
	newInput = fopen ( fname, "r");
	if (newInput == NULL){
		printf("Invalid filename\n");
		return;
	}
	
	//  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
	processCommandLoop ( newInput );
	
	//  4. close the file when processCommandLoop() returns
	fclose ( newInput );
	
}

///////////////////////////////////////////////////////////////////////////////////
// depthFirstSearch recursion
bool TravelNetwork::dfs (int a, int b)
{
	int c;
	//for (each airport c that can be reached from a in one flight)
	for (int i = 1; i <= airports[a]->getAdjAirport()->getListLength(); i++)
	{
		c = airports[a]->getAdjAirport()->getNthValue(i);
		if (c == b)
		{
			return true;
		}
		if (!airports[c]->isVisited())
		{
			//mark airport c as visited;
			airports[c]->setVisited(true);
			if ( dfs (c, b) == true )
			{
				return true;
			}
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////
// To control depthFirstSearch
// Take in x, y, x is from, y is to. 
// Print result for whether there is a possible route from x to y
void TravelNetwork::depthFirstSearchHelper (int x, int y)
{
	//mark all airports as unvisited;
	for (int i = 1; i <= numOfAirport; i++){
		airports[i]->setVisited(false);
	}
	
	if ( dfs (x, y) == true)
	{
		printf ("You can get from airport %d to airport %d in one or more flights\n", x, y);
	}
	else
	{
		printf ("You can NOT get from airport %d to airport %d in one or more flights\n", x, y);
	}
}