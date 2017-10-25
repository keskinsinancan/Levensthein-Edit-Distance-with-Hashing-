#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 267557

typedef struct List{
    char word[50];
    int adr;
}List;
void read_array_from_file(List *);
void search_from_array(List *);
void distance(List *, char * , FILE * );
int main()
{
    List *dictionary;

    dictionary=(struct List *)malloc(M*sizeof(struct List));
     if(!dictionary){
        printf("yer ayrilamadi");
        return -1;
     }

    read_array_from_file(dictionary);
    search_from_array(dictionary);

    free(dictionary);
    return 0;
}
void distance (List *dct,char *tmp_to_distance, FILE *f){
    int len1;
    int len2;
    int k = 0;
    int i,j;
    char word1[50];
    char word2[50];
    int min_edit_distance = 100;
    int most_similar_word_addr = 0;
    char newLine = '\n';
    char space = '\t';
    char none[5];
    int matrix[50][50];
    int tmp_matrix[50][50];
    char sub[10];
    char ins[10];
    char del[10];

    strcpy(word2,tmp_to_distance);
    strcpy(none,"NONE");
    strcpy(sub,"(CHANGE)");
    strcpy(ins,"(INSERT)");
    strcpy(del,"(DETELE)");

    while(k < M && min_edit_distance > 1){

        strcpy(word1,dct[k].word);
        len1 = strlen(word1);
        len2 = strlen(word2);


        for (i = 0; i <= len1; i++) {
            matrix[i][0] = i;
        }
        for (i = 0; i <= len2; i++) {
            matrix[0][i] = i;
        }
        for (i = 1; i <= len1; i++) {
            int j;
            char c1;

            c1 = word1[i-1];
            for (j = 1; j <= len2; j++) {
                char c2;

                c2 = word2[j-1];
                if (c1 == c2) {
                    matrix[i][j] = matrix[i-1][j-1];
                }
                else {
                    int delete;
                    int insert;
                    int substitute;
                    int minimum;

                    delete = matrix[i-1][j] + 1;
                    insert = matrix[i][j-1] + 1;
                    substitute = matrix[i-1][j-1] + 2;
                    minimum = delete;
                    if (insert < minimum) {
                        minimum = insert;
                    }
                    if (substitute < minimum) {
                        minimum = substitute;
                    }
                    matrix[i][j] = minimum;
                }
            }
        }
        if(matrix[len1][len2] < min_edit_distance){
            min_edit_distance = matrix[len1][len2];
            most_similar_word_addr = dct[k].adr;

            for(i = 0; i <= len1; i++){
                for(j = 0; j<= len2; j++){
                    tmp_matrix[i][j]=matrix[i][j];
                }
            }
        }
        k++;
   }
   // printf("\n%s  %s",dct[most_similar_word_addr].word, word2);
    printf("  min edit distance%d\n",min_edit_distance);
    if(min_edit_distance < 5){
        fputs(word2, f);
        fputc(space,f);
        fputc(space,f);
        fputs(dct[most_similar_word_addr].word, f);
        strcpy(word1,dct[most_similar_word_addr].word);

        len1 = strlen(word1);
        len2 = strlen(word2);
        i = len1;
        j = len2;
        int min;
        int next;

        while (i >= 1 && j >= 1){
            if(word1[i]==word2[j]){
                i--;
                j--;
            }
            else if(tmp_matrix[i-1][j-1] < tmp_matrix[i][j-1] && tmp_matrix[i-1][j-1] < tmp_matrix[i-1][j]){

                    min = tmp_matrix[i-1][j-1];
                    next = tmp_matrix[i][j];
                    if(next==(min+2)){
                        fputc(space,f);
                        fputc(space,f);
                        fputc(word2[j],f);
                        fputc(word1[i],f);
                        fputc(space,f);
                        fputc(space,f);
                        fputs(sub,f);
                    }
                    i--;
                    j--;
                    //sub
                }else if(tmp_matrix[i][j-1] < tmp_matrix[i-1][j]){
                       min = tmp_matrix[i][j-1];
                       next = tmp_matrix[i][j];

                       if(next == (min+1)){
                            fputc(space,f);
                            fputc(space,f);
                            fputc(word2[j],f);
                            fputc(word1[i],f);
                            fputc(space,f);
                            fputc(space,f);
                            fputs(ins,f);
                       }
                          j--;
                        //insert
                }
                else if(tmp_matrix[i-1][j] < tmp_matrix[i][j-1]){
                    min = tmp_matrix[i-1][j];
                    next = tmp_matrix[i][j];
                    if(next==(min +1)){
                        fputc(space,f);
                        fputc(space,f);
                        fputc(word2[j],f);
                        fputc(word1[i],f);
                        fputc(space,f);
                        fputc(space,f);
                        fputs(del,f);
                    }
                    //delete
                    i--;
                }

         }
        fputc(newLine,f);
    }
    else{
        fputs(word2, f);
        fputc(space,f);
        fputc(space,f);
        fputs(none, f);
        fputc(newLine,f);
    }

}
void search_from_array(List *dct){
    FILE *f1,*f2;
    char tmp_word[50];
    int len;
    int key;
    int start;
    char newLine = '\n';
    char space = '\t';
    char done[5];
    char none[5];
    char test[5];
    int k;
    int cmp;
    int found;
    char *tmp_to_distance;
    char sozluk1[50];
    char sozluk2[50];
    char sozluk3[50];

    strcpy(sozluk1,"EN YAKIN KELIME");
    strcpy(sozluk2,"ARANAN KELIME");
    strcpy(test,"");
    strcpy(sozluk3,"DONUSUM");
    strcpy(done,"OK  ");
    strcpy(none,"NONE");

    f1 = fopen("test_for_demo.txt","r");
    if(!f1){
        printf("dosya acilamadi...");
        exit(-1);
    }
    f2 = fopen("test_out.txt","w");
    if(!f2){
        printf("dosya acilamadi...");
        exit(-2);
    }

    fputs(sozluk2,f2);
    fputc(space,f2);
    fputc(space,f2);
    fputs(sozluk1,f2);
    fputc(space,f2);
    fputc(space,f2);
    fputs(sozluk3,f2);
    fputc(newLine,f2);
    fputc(newLine,f2);

    printf("\nArama islemi basladi..\n");
    while(!feof(f1)){
        fscanf(f1,"%s",tmp_word);
       // fscanf(f1, "%d", &tmp_int);
        key = 0;
        found = 0;
        len = strlen(tmp_word);

        for(k=0;k<len;k++){//1. keyi hesaplayan kod
            key=key+tmp_word[k]*26*k;
        }
        key = key%M;

        if((cmp=strcmp(dct[key].word, tmp_word))==0){
            fputs(dct[key].word,f2);
            fputc(space,f2);
            fputs(done, f2);
            fputc(newLine,f2);
            printf("\n%s %s",dct[key].word, tmp_word);
        }
        else{
            start = key;
            while((cmp=strcmp(dct[key].word, tmp_word))!=0 && found==0){
                start = key;
                key++;
                key = key%M;

                if((cmp=strcmp(dct[key].word, tmp_word))==0){
                    fputs(dct[key].word,f2);
                    fputc(space,f2);
                    fputs(done, f2);
                    fputc(newLine,f2);
                    found = 1;
                    }

                if((cmp=strcmp(dct[key].word, test))==0){ //karþýlaþtýrýlan eleman boþsa kelime dizide yoltur,
                    tmp_to_distance=(char *)malloc(50*sizeof(char));
                    strcpy(tmp_to_distance,tmp_word);
                    distance(dct,tmp_to_distance, f2);

                    found = 1;
                    }
                if(start==key){ //eðer aramaya baþladýðýmýz noktaya gelmiþsek kelime dizide yoktur
                        printf("\nbasa dondu");//döngüden çýkýlýr
                        distance(dct,tmp_to_distance, f2);
                        found = 1;
                    }
            }
            free(tmp_to_distance);
        }
    }
    printf("\nArama islemi tamamlandi, sonuclar output dosyasina kaydedildi..\n");
    fclose(f1);
    fclose(f2);
}
void read_array_from_file(List *dct){

    char tmp_word[50];
    int tmp_int;
    FILE * f1;

    f1 = fopen("dictionary_array.txt","r");
    if(!f1){
        printf("dosya acilamadi...");
        exit(-3);
    }
     printf("\nveriler dosyadan okunuyor..");

    while(!feof(f1)){
        fscanf(f1,"%s",tmp_word);
        fscanf(f1, "%d", &tmp_int);

        strcpy(dct[tmp_int].word,tmp_word);
        dct[tmp_int].adr = tmp_int;

        //printf("\n%d %s",dct[tmp_int].adr, dct[tmp_int].word);
    }
    printf("\nveriler okundu, diziye alindi\n");
    fclose(f1);
}
