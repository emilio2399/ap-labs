#include <stdio.h>

#define IN   1   /* inside a word */
#define OUT  0   /* outside a word */

#define ARRAY_LENGHT 100






int main()

{

    int pos=0;
    char c, word[ARRAY_LENGHT];
    


    while ((c = getchar()) != EOF) {  
	if (c == '\n'){  
        for(int j=pos; j>=0; j--){
        printf("%c", word[j]);
        }
        //pos=0;
    }else{
        word[pos] = c;
        pos++;
        }
    }

    return 0;
}