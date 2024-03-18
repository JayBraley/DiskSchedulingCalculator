#ifndef UTILS_H
#define UTILS_H

int compare(const void *a, const void *b);
int findMinDistance(int currentPos, int requests[], int requestSize, int processed[]);
void checkForRequest(int requestSize, int requests[], int processed[], int pos);
int allRequestsProcessed(int processed[], int processedSize);
int determineDirection(int prevPos, int currentPos);
int serveRequests(int *requests, int *servedFlags, int requestSize, int currentPos, int direction, int *lastServedPos);
int hasUnservedRequests(int *requests, int *servedFlags, int requestSize, int currentPos, int direction);

#endif
