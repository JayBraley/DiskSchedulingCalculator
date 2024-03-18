#ifndef DISTANCE_CALCS_H
#define DISTANCE_CALCS_H

int fcfsDist(int currentPos, int requests[], int requestSize);
int sstfDist(int currentPos, int requests[], int requestSize);
int scanDist(int currentPos, int requests[], int requestSize, int diskSize, int direction);
int lookDist(int currentPos, int requests[], int requestSize, int direction);

#endif
