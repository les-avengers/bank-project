CC = clang
CFLAGS = -Wall -Wextra -Werror

SRCS = account.c deserialize.c linked_list.c main.c serialize.c user.c
TARGET = système_bancaire

all: $(TARGET)

$(TARGET): $(SRCS:.c=.o)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) *.o

fclean: clean
	make all

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean fclean run
