CC=g++
IFLAGS=-I ./include


#list all the source c++ files
SRCS := $(wildcard src/*.cpp)

#create the object file names with directory prefix
OBJS := $(SRCS:src/%.cpp=obj/%.o)

#create all the headerfile names with directory prefix
DEPS := $(SRCS:src/%.cpp=include/%.h)

#implicite rules to create .o file from compiled .cpp files
# $< selects the first entry form the conditions src/%.cpp include/%.h to be compiles. 
#which is the source file. The %.h file in the condition ensures that the relevant object
#file is recompiled when the .h file changes. 
obj/%.o: src/%.cpp include/%.h
	$(CC) -c -o $@ $< $(IFLAGS)


#.PHONY tells tha all does not actually mean any output file. Rather it is a pseudo target. 
# however it perfroms the condition checks on acc and bcc. And if any of those are outdated
# the relevant chaine of file are recompiled  
all : acc bcc 
.PHONY: all

#create the executable for Alice
acc: $(OBJS) alice_cascade.cpp $(DEPS)
	$(CC) -o acc alice_cascade.cpp $(OBJS) $(IFLAGS)

#create the executable for Bob
bcc: $(OBJS) bob_cascade.cpp $(DEPS)
	$(CC) -o bcc bob_cascade.cpp  $(OBJS) $(IFLAGS)

.PHONY: run
run: acc bcc
	./acc
	./bcc
.PHONY: clean

clean:
	rm -f obj/*.o
	rm -f acc
	rm -f bcc
	rm -f messages/*.bin
	rm -f working*.txt
	rm -f *state*