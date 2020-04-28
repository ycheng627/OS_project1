setup:
	sudo -s

all:
	dmesg --clear
	gcc -Wall -g -c ./src/main.c
	gcc -Wall -g -c ./src/process.c
	gcc -Wall -g -c ./src/SJF.c
	gcc -Wall -g -c ./src/FIFO.c
	gcc -Wall -g -c ./src/RR.c
	gcc -Wall -g -c ./src/PSJF.c
	gcc -Wall -g -c ./src/pqueue.c
	gcc -Wall -g -c ./src/queue.c
	gcc -o main.out main.o process.o SJF.o FIFO.o RR.o PSJF.o pqueue.o queue.o -lm
	rm *.o
	


debug:
	dmesg --clear
	gcc -g -c ./src/main.c
	gcc -g -DDEBUG -c ./src/process.c
	gcc -g -c ./src/SJF.c
	gcc -g -c ./src/FIFO.c
	gcc -g -c ./src/RR.c
	gcc -g -c ./src/PSJF.c
	gcc -g -c ./src/pqueue.c
	gcc -g -c ./src/queue.c
	gcc -o main.out main.o process.o SJF.o FIFO.o RR.o PSJF.o pqueue.o queue.o -lm
	rm *.o