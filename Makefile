CC=g++
IFLAGS=-I .

default:

	$(CC) -o acc alice_cascade.cpp buffered_file_out.cpp message_bunch_writer.cpp $(IFLAGS)
	$(CC) -o bcc bob_cascade.cpp message_bunch_reader.cpp buffered_file_in.cpp buffered_file_out.cpp response_message_writer.cpp $(IFLAGS)


run:
	./acc
	./bcc

clean:
	rm -f acc
	rm -f bcc
	rm -f alice_cascade_state_*.txt
	rm -f bob_cascade_state_*.txt
	rm -f *.bin

cleanbob:
	rm -f bcc
	rm -f bob_cascade_state_*.txt
	rm -f bob*.bin

cleanalice:
	rm -f acc
	rm -f alice_cascade_state_*.txt
	rm -f alice*.bin