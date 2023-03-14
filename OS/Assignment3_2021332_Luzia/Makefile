all:
	gcc -o p1 q1_a1.c -pthread
	gcc -o p2 q1_a2.c -pthread
	gcc -o p3 q1_b1.c -pthread
	gcc -o p4 q1_b2.c -pthread



	gcc -o p21 q2_p1_fifo.c -pthread
	gcc -o p22 q2_p1_sharedmemory.c  -pthread
	gcc -o p23 q2_p1_socket -pthread
	gcc -o p24 q2_p2_fifo.c  -pthread
	gcc -o p25 q2_p2_shmem.c  -pthread
	gcc -o p26 q2_p2_socket.c  -pthread



run question1:

        run ./p1
        run ./p2
        run ./p3
        run ./p4





run question1_2:

	    run ./p21
        run ./p22
        run ./p23
        run ./p24
        run ./p25
        run ./p26



clean:
	rm -f p1 p2 p3 p4 p21 p22 p23 p24 p25 p26



