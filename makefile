
debug:
	gcc -Wall -DDEBUG -g -c main.c
	gcc -Wall -DDEBUG -g -c scheduler.c
	gcc -Wall -DDEBUG -g -c process.c
	gcc -o main.out main.o scheduler.o process.o -lm
	sudo ./main.out < ./OS_PJ1_Test/FIFO_5.txt

fifo:
	gcc -Wall -g -c main.c
	gcc -Wall -g -c process.c
	gcc -Wall -g -c FIFO.c
	gcc -o main.out main.o process.o FIFO.o -lm
	sudo ./main.out < ./OS_PJ1_Test/FIFO_5.txt

sjf_debug:
	gcc -Wall -g -DDEBUG -c main.c
	gcc -Wall -g -DDEBUG -c process.c
	gcc -Wall -g -DDEBUG -c SJF.c
	gcc -Wall -g -DDEBUG -c FIFO.c
	gcc -o main.out main.o process.o SJF.o FIFO.o -lm
	sudo ./main.out < ./OS_PJ1_Test/SJF_4.txt

sjf:
	dmesg --clear
	gcc -Wall -g -c main.c
	gcc -Wall -g -c process.c
	gcc -Wall -g -c SJF.c
	gcc -Wall -g -c FIFO.c
	gcc -o main.out main.o process.o SJF.o FIFO.o -lm
	rm *.o
	sudo ./main.out < ./OS_PJ1_Test/SJF_1.txt

rr:
	dmesg --clear
	gcc -Wall -g -c main.c
	gcc -Wall -g -DDEBUG -c process.c
	gcc -Wall -g -c SJF.c
	gcc -Wall -g -c FIFO.c
	gcc -Wall -g -c RR.c
	gcc -o main.out main.o process.o SJF.o FIFO.o RR.o -lm
	rm *.o
	sudo ./main.out < ./OS_PJ1_Test/RR_5.txt

psjf:
	dmesg --clear
	gcc -Wall -g -c main.c
	gcc -Wall -g -DDEBUG -c process.c
	gcc -Wall -g -c SJF.c
	gcc -Wall -g -c FIFO.c
	gcc -Wall -g -c RR.c
	gcc -Wall -g -c PSJF.c
	gcc -Wall -g -c pqueue.c
	gcc -Wall -g -c queue.c
	gcc -o main.out main.o process.o SJF.o FIFO.o RR.o PSJF.o pqueue.o queue.o -lm
	rm *.o
	sudo ./main.out < ./OS_PJ1_Test/PSJF_5.txt