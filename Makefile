CC = gcc
CFLAGS = -I. -g -std=c99 -Wall

all: dbscan

dbscan: dbscan.c
	$(CC) -o $@ $^ $(CFLAGS) -lm

clean:
	rm -f dbscan
