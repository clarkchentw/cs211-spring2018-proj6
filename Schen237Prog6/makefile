proj6: Schen237Proj6.o Airport.o
	g++ -o proj6 Schen237Proj6.o Airport.o

Schen237Proj6.o: Schen237Proj6.cpp Airport.h
	g++ -c Schen237Proj6.cpp

Airport.o: Airport.cpp Airport.h
	g++ -c Airport.cpp

clean:
	rm proj6 Schen237Proj6.o Airport.o

run:
	./proj6