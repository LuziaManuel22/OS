all:
	mkdir build
	gcc parta.c -o build/shell1
	gcc partb.c -o build/shell2 -pthread

shell2:
	mkdir build

	gcc partb.c -o build/shell2 -pthread

shell1:
	mkdir build
	gcc parta.c -o build/shell1

clean:
	rm build -r