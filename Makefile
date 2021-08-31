CC=g++
IFLAGS=-I .

default:
	$(CC) -o acc alice_cascade.cpp $(IFLAGS)
	$(CC) -o bcc bob_cascade.cpp $(IFLAGS)

run:
	./acc
	./bcc

clean:
	rm -f acc
	rm -f bcc
	rm -f alice_cascade_state_*.txt
	rm -f mbf_*