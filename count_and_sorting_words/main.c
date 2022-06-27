#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//bugramurat
typedef struct wordNode{
int count;
char * word;
struct wordNode * next;

}node;

node * first , *last = NULL;

void Print(node * r){
    int i=1;
    while(r!=NULL){
        printf("%d. %s: %d", i, r->word, r->count);
        r = r->next;
        i++;
        printf("\n");
    }
}

node * addToFirst( int count, char * word){

    node * newNode = (node*)malloc(sizeof(node));
    newNode->word = word;
    newNode ->count = count;

    if(first == NULL){

        first = newNode;
        last = newNode;
        last->next = NULL;

        return newNode;
    }
    else{
         newNode->next = first;
         first = newNode;

        if(first ->next ->next == NULL){
            first->next = last;
        }

        return newNode;
    }
}

node * add(node * r, int count, char * word){  //Buradaki r bir önceki dugum

    node* newNode = (node*)malloc(sizeof(node));
    newNode->word = word;
    newNode->count = count;

    newNode->next = r->next;
    r->next = newNode;
}

void addToEnd( int count, char * word){

        node * newNode = (node*)malloc(sizeof(node));
        newNode->word = word;
        newNode->count = count;

        newNode->next = NULL;
        last->next = newNode;
        last = newNode;
    }



void addSequentially(int count, char * tempWord){
    node * iter = first;

    char *word =(char*)malloc(sizeof (char)*100);
    strcpy(word,tempWord);

  while(iter != NULL){
        if(strcmp(iter->word, word)==0){
            return;
        }
        iter=iter->next;
    }

   iter=first;

   if(first == NULL){
        addToFirst(count, word);
    }
    else{
        while( iter->next != NULL && ( ( iter->next->count > count ) || ( iter->next->count == count ) ) ){ //Araya ekle fonksiyonu calismasi icin iter'in next'inin sayaciyla karsilastiriyor
            iter= iter->next;
        }

          if(iter->next == NULL){
                if(count>iter->count){
                    addToFirst(count,word);

                }
                else{
                    addToEnd(count,word);

            }
          }


    else if(count > iter->count){
        addToFirst(count, word);

    }
        else{

            add(iter,count,word);
        }
    }
}

int main(){

    int wordCount = 1;

    FILE * file = fopen("text.txt", "r");

    FILE * copyFile = fopen("text.txt", "r");

    long fileLocation=0;

    char tempWord1[50];
    char tempWord2[50];

    while (fscanf(file, " %50s", tempWord1) == 1) {

        fileLocation = ftell(file);
        fseek(copyFile,fileLocation,SEEK_CUR);
        while (fscanf(copyFile, " %50s", tempWord2) == 1) {


          for(int i = 0; tempWord1[i]; i++){
            tempWord1[i] = tolower(tempWord1[i]);
            }

            for(int i = 0; tempWord2[i]; i++){
            tempWord2[i] = tolower(tempWord2[i]);
            }


            if(strcmp(tempWord1,tempWord2) == 0){
                wordCount++;
            }
        }
        addSequentially(wordCount,tempWord1);

        rewind(copyFile);
        wordCount=1;
    }


    Print(first);

    fclose(file);
    fclose(copyFile);

    return 0;
}
