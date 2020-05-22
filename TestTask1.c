#include <stdio.h>

int * func(int * stairs, int * numStair) {
	int count = 0, index = 1, *pCount;
	while (index<=*stairs) {
		index += *numStair + 1;
		count++;
	}
	pCount = &count;
	return pCount;
}


 int main (int argc, char * argv[]) {
    if (argc > 3) {
    	printf("Too many arguments\n");
	} else if (argc < 3) {
		printf("Too few arguments\n");
	} else {
		int stairs  = atoi(argv[1]), numStair = atoi(argv[2]);
    	const int *answer = func(&stairs, &numStair);
    	printf("%d\n", *answer);
	}
     return 0;
}






