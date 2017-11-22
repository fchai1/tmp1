#include <stdio.h>

int a[1];
int *ptr = NULL;

int fangming(int a){
	a = a + 1;

	return 0;
}

int main(){
	a[0] = fangming(2);
	printf("fm's test 0\n");
	a[2] = 0;
	memset(a, 0, 100);
	*ptr = 1;
	printf("fm's test\n");
}

