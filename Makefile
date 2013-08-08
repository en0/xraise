BIN=xraise
OBJ=$(patsubst %.c, %.o, $(wildcard *.c))

$(BIN) : $(OBJ)
	$(CC) -lX11 -o $@ $^

%.o : %.c
	$(CC) -o $@ -c $<

.PHONY : clean

clean :
	$(RM) $(OBJ) $(BIN)

