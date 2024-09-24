#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcb.h"
#include "data.h"
#include "queue.h"
#include "sjf.h"
#include "RR.h"
#include "fcfs.h"

int main()
{
	FILE* out;
	Data* data;

	out = fopen("processes.out", "w");
	if (out == NULL) {
    printf("Error: Unable to open processes.out for writing.\n");
    return 1;
    }
	data = parseFile("C:\\Users\\ATUL DANADE\\OneDrive\\Desktop\\Placement\\1.CV prev & interview prep\\CV prep\\project\\process scheduling algo\\process.in");

	if (data == NULL) {
    printf("Error: Failed to read data from file.\n");
    fclose(out);
    return 1;
    }
	if (strcmp(data->algorithm, "sjf") == 0)
	{
		shortestJobFirst(data, out);
	}
	else if (strcmp(data->algorithm, "rr") == 0)
	{
		rr(data, out);
	}
	else if (strcmp(data->algorithm, "fcfs") == 0)
	{
		firstComeFirstServed(data, out);
	}

	destroyData(data);
	fclose(out);
	return 0;
}