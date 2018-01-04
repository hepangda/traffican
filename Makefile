traffican:clean
	-mkdir data
	g++ *.cpp -o traffican -I ./include
clean:
	-rm traffican
