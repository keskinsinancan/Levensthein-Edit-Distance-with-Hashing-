#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 267557

typedef struct List{
    char word[50];
    int adr;
}List;

int main()
{
    FILE *f1, *f2;
    List *dictionary;
    char tmp[50];
    int k;
    int len;
    int key = 0;
    char test[50];
    int cmp;

    char newLine = '\n';
    char space = ' ';

    f1 = fopen("dictionary_new.txt", "r");//dosya açýldý
    if(!f1){
        printf("Dosya acilamadi");
        return -1;
    }
    f2 = fopen("dictionary_array.txt", "w+");//dosya açýldý
    if(!f2){
        printf("Dosya acilamadi");
        return -1;
    }

     dictionary=(struct List *)malloc(M*sizeof(struct List));
     if(!dictionary){
        printf("yer ayrilamadi");
        return -1;
     }
    int count = 0;
    strcpy(test,"");
    while(!feof(f1)){
        key = 0;
        fscanf(f1,"%s",tmp);
        len = strlen(tmp);
        for(k=0;k<len;k++){//1. keyi hesaplayan kod
            key=key+(tmp[k]-'a')*26*k;
        }

        key = key%M;
        if(key<0){
            key = key + M;
        }

        if((cmp=strcmp(dictionary[key].word, test))==0){//tablodaki yerin boþ olup olmadýðý araþtýrýlýr
            strcpy(dictionary[key].word, tmp);//yer boþsa kelime yerleþtirilir
            dictionary[key].adr = key;
            count ++;
        }
        else{
            while((cmp=strcmp(dictionary[key].word, test))!=0){//yer boþ deðilse yeni key üretilir
                key = (key+1)%M;
                if(key<0){
                    key = key + M;
                }
            }
            strcpy(dictionary[key].word, tmp); //boþ göz bulunduktan sonra kelime yerleþtirilir
            dictionary[key].adr = key;
            count ++;
        }
        fputs(dictionary[key].word,f2);
        fputc(space,f2);
        fprintf(f2, "%d", dictionary[key].adr);
        fputc(newLine,f2);
    }
    printf("\n------%d",count);

    free(dictionary);
    fclose(f1);
    fclose(f2);
    return 0;
}
