#include <stdio.h>


int * func(int * spans, int * distance) {
	int length, *pLength;
	length = *distance * *spans * (1 + *spans)/2;
	pLength = &length;
	return pLength;
}

int main (int argc, char * argv[]) {
    if (argc > 3) {
    	printf("Too many arguments\n");
	} else if (argc < 3) {
		printf("Too few arguments\n");
	} else {
		int spans  = atoi(argv[1]), distance = atoi(argv[2]);
    	const int *answer = func(&spans, &distance);
    	printf("%d\n", *answer);
	}
     return 0;
}











