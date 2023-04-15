EXE = lrf60m_10ph
SRC = src
OBJ = build

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

FLAGS = -g

$(EXE): $(OBJS)
	gcc $(OBJS) $(FLAGS) -o $(EXE)

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	gcc -c $(FLAGS) $< -o $@

$(OBJ)/%.o: $(SRC)/%.c
	gcc -c $(FLAGS) $< -o $@

clean:
	-rm $(EXE)
	-rm $(OBJ)/*.o