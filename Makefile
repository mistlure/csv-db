CC = gcc
CFLAGS = -I db -Wall -Wextra -std=c11

TARGET = databaze

SRCS = main.c args.c db/csv_base.c db/csv_help.c db/csv_io.c db/csv_math.c db/csv_edit.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) out.csv res.csv result.csv

run: all
	./$(TARGET)