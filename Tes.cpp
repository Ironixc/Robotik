#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, max = 0, index;
    scanf("%d",&a);
    int number[100];
    int many[100] = {0};
    for (int i = 0 ; i < a; i++){
        scanf("%d", &number[i]);
    }
    for (int i = 0; i < a; i++){
        many[number[i]]++;
    }
    for (int i = 0; i < 100; i++){
        if (many[i] > index){
        index = many[i];
        }
    }

    for(int i = 0; i < 100; i++){
        if (index == many[i]){
            printf("%d " , i);
            if (i > max){
                max = i;
            }
        }
    }
    printf("\n%d", max);

}
