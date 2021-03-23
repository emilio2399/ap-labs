
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int numcmp(char *str1, char *str2){
	int num1, num2;
	num1 = atoi(str1);
	num2 = atoi(str2);
	if (num1 > num2){
		return 1;
	}else if (num1 < num2){
		return -1;
	}else{
		return 0;
	}
}

void merge(char **elements, int left, int right, int (*comp)(char *, char*), int size){
	char **temp = (char **) malloc(sizeof(char *) * size);
	for(int i = left; i <= right;i++){
		temp[i] = elements[i];
	}
	int pointer1 = left;
	int pointer2 = ((left + right)/2) + 1;
	int pointer3 = left; 
	while(pointer1 <= ((left + right)/2) && pointer2 <= right) {
		if(comp(temp[pointer1], temp[pointer2]) <= 0){
			elements[pointer3] = temp[pointer1];
			pointer1++;
		}else {
			elements[pointer3] = temp[pointer2];
			pointer2++;
		}
		pointer3++;
	}
	while(pointer1 <= ((left + right)/2)) {
		elements[pointer3] = temp[pointer1];
		pointer1++;
		pointer3++;
	}
	free(temp);
}


void mergeSrt(char **arr, int left, int right, int (*comp)(char *, char *), int size){
	if (left < right){
		int mid = (left + right)/2;
		mergeSrt(arr, left, mid, comp, size);
		mergeSrt(arr, mid + 1, right, comp, size);
		merge(arr, left, right, comp, size);
	}
}


int main (int argc, char **argv){
	int numeric = 0;
	if (argc > 1 && strcmp(argv[1], "-n") == 0){
		numeric = 1;
	}
	mergeSrt(argv + 1 + numeric, 0, argc -(numeric ? 3:2), numeric ? numcmp:strcmp, argc - (numeric ? 2:1));
	for(int i = 1 + numeric; i < argc; i++){
                printf("%s ", argv[i]);
       }
        printf("%s", "\n");
	return 0;
}