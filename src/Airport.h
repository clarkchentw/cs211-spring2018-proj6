#include <cstdio>
#include <cstring>
#include <cstdlib>

class Node
{
	private:
		int value;
		Node* pNext;
	public:
		Node();
		int getValue();
		void setValue(int inputValue);
		Node* getNext();
		void setNext(Node* inputNext);
};

class List
{
	private:
		Node* hd;
	public:
		List();
		void add(int inputValue);
		bool remove(int arrival);
		void print();
		void clear();
		int getListLength();
		int getNthValue(int index);
};

class Airport
{
	private:
		List* adjAirport;
		bool visited;
	public:
		Airport();
		bool isVisited();
		void setVisited(bool inputVisited);
		List* getAdjAirport();
};

class TravelNetwork
{
	private:
		// Create the Data Members for the Travel Network here
		Airport** airports;
		int numOfAirport;
		
		// To get the next input
		// Return -1 for error encountered
		int getAirportInput();
	public:
		// Use a constructor to initialize the Data Members for Travel Network
		TravelNetwork();
		// The main loop for reading in input
		void processCommandLoop (FILE* inFile);
		void showCommands();
		void doTravel();
		void doResize(int newSize = -1);
		void doInsert();
		void doDelete();
		void doList();
		void doFile();
		bool dfs (int a, int b);
		void depthFirstSearchHelper (int x, int y);

};