#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    FILE *f;
    FILE *f2;

    f = fopen("dictionary.txt", "r");//dosya açýldý
    if(!f){
        printf("Dosya acilamadi");
        return -1;
    }

    f2 = fopen("dictionary_new.txt","w");
        if(!f2){
            printf("Dosya acilamadi");
            return -2;
        }

    char word[50];
    char tmp;
    char newLine = '\n';

    while(!feof(f)){
        fscanf(f,"%s",word);
        printf("\n%s",word);
        while((tmp=fgetc(f)!='\n')&&!(feof(f))){
        }
        strlwr(word);
        fputs(word,f2);
        fputc(newLine,f2);

    }
    fclose(f);
    fclose(f2);
    return 0;
}
