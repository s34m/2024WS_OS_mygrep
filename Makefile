hello: main.o
	gcc -o mygrep main.o

main.o: main.c
	gcc -c -o main.o main.c


clean:
	rm main.o mygrep
