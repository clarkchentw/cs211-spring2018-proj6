/*
        Name: Clark Chen
        NetID: schen237
        Date: 4/19/2018
        Project #: 6
        Term: Spring 2018
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

///////////////////////////////////////////////////////////////////////////////////
// Node Class: Linked List element
// value: For arrival airport ID
// pNext: next pointer
class Node
{
	private:
		int value; // value (arrival airport)
		Node* pNext; // next pointer
		
	public:
		Node(); // Default Constructor
		int getValue(); // Get value of the node (Arrival Airport)
		void setValue(int inputValue); // Set Value of the node (Arrival Airport)
		Node* getNext(); // Get next pointer
		void setNext(Node* inputNext); // Set Next pointer
};

///////////////////////////////////////////////////////////////////////////////////
// List Class: For linked list control
// hd: head pointer
class List
{
	private:
		Node* hd; // Head pointer
		
	public:
		List(); // Default Constructor
		void add(int inputValue); // Add flight
		bool remove(int arrival); // Remove a flight by arrival airport
		void print(); // Print the list
		void clear(); // Clear the list
		int getListLength(); // Get the length of the list
		int getNthValue(int index); // get nth value
};

///////////////////////////////////////////////////////////////////////////////////
// Airport Class: To group flight by airport
// adjAirport: list of destination airport from this airport
// visited: For depthFirstSearch use.
class Airport
{
	private:
		List* adjAirport; // Adjcent Airport
		bool visited; //visit status
	public:
		Airport(); // Default Constructor
		bool isVisited(); // Check if isvisited
		void setVisited(bool inputVisited); // Set visited status
		List* getAdjAirport(); //Get the list of Adjcent Airport
};

///////////////////////////////////////////////////////////////////////////////////
// TravelNetwork Class: To Control the whole travel network
// airports: dynamic array, can be resize easily
// numOfAirport: To define number of airport available to use
class TravelNetwork
{
	private:
		Airport** airports; // Airport Array
		int numOfAirport; // Number of Airport
		
		// Method to get the next input
		// Return -1 for error encountered
		int getAirportInput();
	public:
		TravelNetwork(); // Default Constructor
		void processCommandLoop (FILE* inFile); // Main Loop for the Program
		void showCommands(); // Show Commands
		void doTravel(); // Method to check if travel is valid
		void doResize(int newSize = -1); // Method to resize the airports array
		void doInsert(); // Method to insert flight
		void doDelete(); // Method to Delete Flight
		void doList(); // Method to List flight
		void doFile(); // Method to process input file
		bool dfs (int a, int b); // depthFirstSearch recursion
		void depthFirstSearchHelper (int x, int y); // To control depthFirstSearch

};