#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define M 569
#define MM 568

typedef struct List{
    char word[20];
}List;

int main(){
    int i, j, k,u; //döngü indisleri için kullanılan değişkenler
    int start;//arama için kullanılan tablonun aramaya başlanılan noktasını tutan değişken
    List *L;//hash tablosu 
    int key, key2, len;//üretilen keyler için gerekli değişkenler
    int cmp;//strcmp fonksiyonunun sonucunu tutan değişken
    char C[20], A[20];//kelimeleri okumaya yarayan ve dışardan kelime alan değişken
    int count;//arama işlemi sayısını tutan sayı
    char opt[1];//menü için kullanıcıdan değer alan değişken
    FILE *f=NULL;//file pointer
    
    f = fopen("smallDictionary.txt", "r");//dosya açıldı
    if(!f){
        printf("Dosya acilamadi");
        return -1;
    }
    
    L=(struct List *)malloc(M*sizeof(struct List));//tablo için hafızada yer ayrıldı
    rewind(f);//file pointerı başa alan fonksiyon

    strcpy(A,"");//A stringi boş atanıyor, kelime karşılaştırmaları için gerekli
    
    while(!feof(f)){//file pointer dosyanın sonuna kadar ilerler
        fscanf(f,"%s",C);//gelen kelimeler tek tek okunur
        len=strlen(C);//gelen kelimenin uzunluğu bulunur
        key=0;//key değerinin başlangıç değeri atanır
        for(k=0;k<len;k++){//1. keyi hesaplayan kod
            key=key+(C[k]-'a')*26*k;
        }
        key=key%M;//1. key hesaplanır
        j=0;
        if((cmp=strcmp(L[key].word, A))==0){//tablodaki yerin boş olup olmadığı araştırılır
            strcpy(L[key].word, C);
        }
        else{
            start=key; //1. key değeri saklanır, döngüden çıkmak için gerekli
            j=0;
            while((cmp=strcmp(L[key].word, A))!=0){//2. key hesaplanır
                j++;//iterasyon sayısı
                key2=1+key%MM;
                key=(key+j*key2)%M;
        
                if(start==key){//Eğer başlanılan yere geri dönülürse bu kelime hash tablosuna yerleştirilemez
                    printf("\n %s KELIMESI ICIN TABLODA YER BULUNAMADI", C);
                    break;
                }  
            }
            if((cmp=strcmp(L[key].word, A))==0){
                 strcpy(L[key].word, C);//eğer üretilen key müsaitse kelime tablonun ilgili gözüne yerleştirilir
             }           
        }       
    }
    u=0;
    for(i=0;i<=M;i=i+2){//hash tablosu ekrana yazdırılır
        printf("\n%d %s\t\t\t\t%d %s",i, L[i].word, i+1, L[i+1].word);
    }
    for(i=0;i<=M;i++){//yerleştirilien kelime sayısı bulunur
         if(cmp=strcmp(L[i].word, A)!=0){
            u++;
        }
    }
    printf("\n, YERLESTIRILEN KELIME SAYISI==%d",u);
    
    //KELIME ARAMA
    strcpy(opt,"e");
    printf("%c",opt[0]);
    printf("\nARAMA İŞLEMİ");
    while((opt[0]-'e'==0) ||opt[0]-'E'==0 ){
    
        printf("\nARAMAK ISTEDIGINIZ KELIMEYI GIRINIZ\n");
        scanf("%s",C);

        len=strlen(C);
        key=0;
        count=0;
        for(k=0;k<len;k++){//1. key üretilir ve arama yapılır
             key=key+(C[k]-'a')*26*k;
        }
        key=key%M;
        count++;
        if(cmp=strcmp(L[key].word, C)==0){
            printf("\nTEBRIKLER, ARADIĞINIZ KELIMEYI \n'%d' ARAMADA BULDUNUZ,\n TABLONUN %d. SIRASINDA",count, key);
            printf("\n\n");
            printf("\nARAMAYA DEVAM ETMEK ICIN 'E' VEYA 'e' GIRINIZ\n ÇIKMAK ICIN 'H' VEYA 'h' GIRINIZ");
            scanf("%s", opt);
        }
        else{            //2. keyler üretilir ve arama yapılır
                start=key;
                j=0;
                while((cmp=strcmp(L[key].word, C))!=0){

                    count++;
                    j++;//iterasyon sayısı
                    key2=1+key%MM;
                    key=(key+j*key2)%M;

                    if(start==key){
                        printf("\n %s KELIMESI TABLODA BULUNAMADI", C);
                        printf("\nARAMAYA DEVAM ETMEK ICIN 'E' VEYA 'e' GIRINIZ\n ÇIKMAK ICIN 'H' VEYA 'h' GIRINIZ");
                        scanf("%s", opt);
                        break;  
                    }  
                }
                if((cmp=strcmp(L[key].word, C))==0){
                    printf("\nTEBRIKLER, ARADIĞINIZ KELIMEYI \n'%d' ARAMADA BULDUNUZ,\n TABLONUN %d. SIRASINDA", count, key);
                    printf("\n\n");
                    printf("\nARAMAYA DEVAM ETMEK ICIN 'E' VEYA 'e' GIRINIZ\n ÇIKMAK ICIN 'H' VEYA 'h' GIRINIZ");
                    scanf("%s", opt);
                }   
            }
    }
    printf("\nKELIME ONERILMESINI ISTER MISINIZ? E/e/H/h");
    scanf("%s",opt);
    if((opt[0]-'h'==0) || (opt[0]-'H'==0)){
        return -2;
    }
    strcpy(A,C);//Aradığımız kelime değişeceği için saklamalıyız
   // KELIME ONERME
    len=strlen(C);
    for(i=0;i<len;i++){//Harflerini değiştireceğimiz kelimenin uzunluğu kadar gidilmeli
        strcpy(C,A);
        for(j=0;j<26;j++){//harfler arasında A-Z değişikliği yapıluyor 
            C[i]='a'+j;
            //printf("\n%s",C);
            key=0;
            for(k=0;k<len;k++){//1. key üretiliyor ve bu keye göre arama yapılıyor
                key=key+(C[k]-'a')*26*k;
             }
            key=key%M;
            if((cmp=strcmp(C,L[i].word))==0){//kelime önerisi verilip programdan çıkılıyor 
                printf("\nARADIGINIZ KELIME '%s' OLABILIR", L[key].word);
                return -1;
              }
            else{
            u=0;    
            start=key;
            while(1){//2. key üretiliyor 
                u++;//iterasyon sayısı
                key2=1+key%MM;
                key=(key+u*key2)%M;
                
                if((cmp=strcmp(L[key].word, C))==0){//2. keye göre arama yapılıyor, uygun değer bulunursa programdan cıkılıyor
                      printf("\nARADIĞINIZ KELIME '%s' OLLABILIR",L[key].word);
                      return -2;
                         }
                if(key==start){
                    break;
                        }
                      }
                 }
             }
        }
    free(L);
    fclose(f);
    return 0;
}