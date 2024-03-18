CC=gcc
CFLAGS=-I.

OBJ = DiskSchedulingCalculator.o utils.o distanceCalcs.o 

DiskSchedulingCalculator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

DiskSchedulingCalculator.o: DiskSchedulingCalculator.c utils.h distanceCalcs.h
	$(CC) -c -o $@ $< $(CFLAGS)

utils.o: utils.c utils.h
	$(CC) -c -o $@ $< $(CFLAGS)	

distanceCalcs.o: distanceCalcs.c distanceCalcs.h
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) DiskSchedulingCalculator