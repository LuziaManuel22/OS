# This contains:

## A single Makefile to build all programs.


## How to compile

  run make




## How to run

1. Program question1:
        run ./p1
        run ./p2
        run ./p3
        run ./p4

 
2. Program question2: 
        run ./p21
        run ./p22
        run ./p23
        run ./p24
        run ./p25
        run ./p26



## How to clean

go to cd ..
run make clean


## How the program works



## Program for q1_a1.c :
In this program, each philosopher thread first thinks for a while, then acquires the two forks that it needs to eat using mutexes. 

After eating, the philosopher signals the condition variables associated with the forks to indicate that they are available, and releases the mutexes. 

This allows the other philosopher threads to acquire the forks without having to worry about the specific order in which they are acquired.



## Program for q1_a2.c :
In this program that simulates the philosophers using threads and the forks using global variables,  and resolves the deadlock using semaphores:

Each philosopher thread first thinks for a while, then acquires the two forks that it needs to eat using semaphores. After eating, the philosopher releases the forks. This ensures that only one philosopher can access each fork at a time, preventing any conflicts or deadlocks.

I have  used thread to simulate the philosophers, and each thread will use the same resource, in this case each element inside the forks array.

I used functions like sem_post(), sem_wait(), sem_destroy in order to take fork and put fork respectively.




## Program for q1_b1:

This solution uses strict ordering of resource requests and introduces two sauce bowls as additional resources that the philosophers can use to eat
This solution creates a semaphore for each fork and sauce bowl, and uses the semaphores to ensure that each philosopher can only access one fork and one sauce bowl at a time. In order to solve this deadlock, we have just reduce the number of bowls, and everytime the philosopher will take a fork, he will also take the bowl.
 Now, if we have assume that the philosopher needs only one fork and access to one of the 2 sauces bowls to eat, there will be deadlock yes.


## Program for q1_b2:

In this program, each philosopher thread first thinks for a while, then acquires the two forks and one sauce bowl that it needs to eat using semaphores. After eating, the philosopher releases the forks and the sauce bowl. This ensures that only one philosopher can access each fork and sauce bowl at a time, preventing any conflicts or deadlocks.

In order to solve this deadlock, we have just reduce the number of bowls, and everytime the philosopher will take a fork, he will also take the bowl.

We have used thread to simulate the philosophers, and each thread will use the same resource, in this case each element inside the forks array.

I used functions like sem_post(), sem_wait() in order to take fork and put fork respectively.




## Program for q2_p1_fifo:

## Program for q2_p1_fifo:

## Program for q2_p1_socket:

## Program for q2_p2_fifo:

## Program for q2_p2_shmem:

## Program for q2_p2_socket:

