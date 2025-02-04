## files to be used 
SRC=./src/*.c 
INC=./include/ 
OBJ=./*.o 
 
## variables (change for your liking) 
COMPFLAGS=-Wall -Wextra -pedantic 
LINKFLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
TARGET=temp 
 
## the actual important stuff 
all:$(TARGET) 
 
$(TARGET): obj 
	cc -o $@ $(OBJ) $(LINKFLAGS) 
 
obj: 
	cc $(COMPFLAGS) -I $(INC) -c $(SRC) 
 
clean: 
	rm -f $(OBJ) $(TARGET)
