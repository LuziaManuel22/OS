all:
	gcc -o p1 q1_q1_a.c -pthread
	./p1
	
	gcc -o p2 q1_q1_b_semaph.c -pthread
	./p1

	gcc -o p3 p3.c -pthread

clean:
	rm -f p1 p2 p3