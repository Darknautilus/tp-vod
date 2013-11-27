CC=g++
CFLAGS=
LDFLAGS=
EXEC=INSAVoD
SRC= 
OBJ=$(SRC:.cpp=.o)

all: $(EXEC)

AnaLog: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)
