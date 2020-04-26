
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
