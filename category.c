#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "dict.h"
#include "utils.h"
#include "catlang.h"
#include "catdt1.h"
#include <stdlib.h>

double *
receiveTitleCategory(char *text,int *Ttotal,int *Ctotal,int *count,int lang);

double *
receiveDescriptionCategory(char *text,int *Ttotal,int *Ctotal,int *count,int lang);

double *
receivePostCategory(char *text,int *Ttotal,int *Ctotal,int *count,int limit,int lang);

int
getEngOrRuss(char * text);


int mainREs(){
    /**/
    //Check the language first :
    char *joke="";
    char *title="";
    char *description="";
    char *post="fuck boy football goal liverpool";

    double *titleCat;
    int titleTot=0;
    int totalDiv=0;
    int k;
    int titleCount=0;
    titleCat=receiveTitleCategory(title,&titleTot,&totalDiv,&titleCount,0);

    double *descriptionCat;
    int descriptionTot=0;
    int descriptionDiv=0;
    int descriptionCount=0;
    descriptionCat=receiveDescriptionCategory(description,&descriptionTot,&descriptionCat,&descriptionCount,0);

    double *postsCat;
    int postsTot=0;
    int postsDiv=0;
    int postCount=0;
    int postLimit=5;
    postsCat=receivePostCategory(post,&postsTot,&postsDiv,&postCount,postLimit,0);

    double tempTitle=0,titleProb=0;
    double tempDescription=0,descriptionProb=0;
    double tempPosts=0,postsProb=0;
    double FINAL_PROB=0;

    for(k=0;k<42;k++){

        if(titleTot!=0){
            tempTitle=*(titleCat + k);
            titleProb=tempTitle/titleTot;
        }

        if(descriptionTot!=0){
            tempDescription=*(descriptionCat+k);
            descriptionProb=tempDescription/descriptionTot;
        }

        if(postsTot!=0){
            tempPosts=*(postsCat+k);
            postsProb=tempPosts/postsTot;
        }

        //IF posts are not necessary
        if(titleTot!=0 && descriptionTot!=0 && postsTot==0){
            FINAL_PROB=(titleProb+descriptionProb)/2;
        }

        //Prob if both params are set
        if(titleTot!=0 && descriptionTot!=0 && postsTot!=0){
            FINAL_PROB=(titleProb*0.4)+(descriptionProb*0.4)+(postsProb*0.2);
        }

        //if there is no description
        if(titleTot!=0 && descriptionTot==0 && postsTot!=0){
            FINAL_PROB=(titleProb*0.6)+(postsProb*0.4);
        }

        //if  the is no description and title
        if(titleTot==0 && descriptionTot==0 && postsTot!=0){
            FINAL_PROB=postsProb;
        }
        printf( "title : %f(%f), descrip : %f(%f), posts : %f(%f) fin >> %f\n",tempTitle,titleProb,tempDescription,descriptionProb,tempPosts,postsProb,FINAL_PROB);
        //FINAL_PROB[i]=()
    }
    //printf("title Counter : %d\n",titleTot);

}

double *
receivePostCategory(char *text,int *Ttotal,int *Ctotal,int *count,int limit,int lang) {
   static double  prob[42];
   int i;

    Dict DATA;

    if(lang==0){
        DATA=getCatA();
    }else{
        DATA=getCatB();
    }
    //DictInsert(d, "foo", "hello world");
    //to lowercase and writable
    char *string= strLWR2(strdup(text));
    //Extract the first token
    char * token = strtok(string, " ");
    int category_index=0;

    while(token != NULL && *(count)<limit) {
        //printf("post word : %s\n",token);
      (*count)++;
      char* resultFromData=DictSearch(DATA,token);
      //checking in Data
      if(resultFromData==0){
            //printf("%s : Not found\n",token);
        }else{
            (*Ttotal)++;
            category_index=atoi(resultFromData);
            if(prob[category_index]==0){
                (*Ctotal)++;
            }
            prob[category_index]++;
      }//end of main_if

      //firs
      //check if the word is in LangFiles
      token = strtok(NULL, " ");
    }

   DictDestroy(DATA);
   return prob;

}

/* function to get probabilies */
double *
receiveDescriptionCategory(char *text,int *Ttotal,int *Ctotal,int *count,int lang) {
   static double  prob[42];
   int i;

    Dict DATA;

    if(lang==0){
        DATA=getCatA();
    }else{
        DATA=getCatB();
    }
    //DictInsert(d, "foo", "hello world");
    //to lowercase and writable
    char *string= strLWR2(strdup(text));
    //Extract the first token
    char * token = strtok(string, " ");
    int category_index=0;

    while(token != NULL ) {
        (*count)++;
      char* resultFromData=DictSearch(DATA,token);
      //checking in Data
      if(resultFromData==0){
            //printf("%s : Not found\n",token);
        }else{
            (*Ttotal)++;
            category_index=atoi(resultFromData);
            if(prob[category_index]==0){
                (*Ctotal)++;
            }
            prob[category_index]++;
      }//end of main_if

      //firs
      //check if the word is in LangFiles
      token = strtok(NULL, " ");
    }

   DictDestroy(DATA);
   return prob;

}

/* function to get probabilies */
double *
receiveTitleCategory(char *text,int *Ttotal,int *Ctotal,int *count,int lang) {
   static double  prob[42];
   int i;

    Dict DATA;

    if(lang==0){
        DATA=getCatA();
    }else{
        DATA=getCatB();
    }
    //DictInsert(d, "foo", "hello world");
    //to lowercase and writable
    char *string= strLWR2(strdup(text));
    //Extract the first token
    char * token = strtok(string, " ");
    int category_index=0;

    while(token != NULL ) {
        (*count)++;
      char* resultFromData=DictSearch(DATA,token);
      //checking in Data
      if(resultFromData==0){
            //printf("%s : Not found\n",token);
        }else{
            (*Ttotal)++;
            category_index=atoi(resultFromData);
            if(prob[category_index]==0){
                (*Ctotal)++;
            }
            prob[category_index]++;
      }//end of main_if

      //firs
      //check if the word is in LangFiles
      token = strtok(NULL, " ");
    }

   DictDestroy(DATA);
   return prob;

}

/*Lets do this*/
int
getEngOrRuss(char * text){
    int TOTAL_APPS=1;
    //adding to list vars
    char buf[900];
    int c=1;

    int current_Count=0;
    char final_lang[400]="other";

    Dict DATA,RESULT_DICT;
    DATA=getCategoryLanguage();
    RESULT_DICT=DictCreate();
    //DictInsert(d, "foo", "hello world");

    //to lowercase and writable
    char *string= strLWR2(strdup(text));
    //Extract the first token
    char * token = strtok(string, " ");

    int en=0;
    int rus=0;

    while( token != NULL ) {
      //printf( "%s\n", token );
      char* fromDict=DictSearch(DATA,token);
      //checking in Data
      if(fromDict==0){
            //printf("%s : Not found\n",token);
            printf("%s\n",fromDict);
        }else{

            if(en==2){
                return 0;
            }

            if(rus==2){
                return 1;
            }

            if(strcmp(fromDict,"en")==0){
                en++;
            }
            if(strcmp(fromDict,"ru")==0){
                rus++;
            }
      }//end of main_if

      //firs
      //check if the word is in LangFiles
      token = strtok(NULL, " ");
    }

    DictDestroy(DATA);
    DictDestroy(RESULT_DICT);
    //free(word);
    return -1;
}


char *
receiveCategoryCode2(char * text){
    int TOTAL_APPS=2;
    //adding to list vars
    char buf[900];
    int c=1;

    int current_Count=0;
    char final_lang[400]="other";

    Dict DATA,RESULT_DICT;
    DATA=getClassALanguages();
    RESULT_DICT=DictCreate();
    //DictInsert(d, "foo", "hello world");

    //to lowercase and writable
    char *string= strLWR2(strdup(text));
    //Extract the first token
    char * token = strtok(string, " ");

    while( token != NULL ) {
      //printf( "%s\n", token );
      char* fromDict=DictSearch(DATA,token);
      //checking in Data
      if(fromDict==0){
            //printf("%s : Not found\n",token);
        }else{
            //printf("%s >> %s: found\n",token,fromDict);
            char* fromResult=DictSearch(RESULT_DICT,fromDict);
            if(fromResult==0){
                //Add to the list
                sprintf(buf, "%d", c);
                //DictInsert(RESULT_DICT, buf, buf);
                DictInsert(RESULT_DICT,fromDict,buf);
            }else{
                //Increase counter
                current_Count=atoi(DictSearch(RESULT_DICT,fromDict));
                //printf("%s count >> %d\n",fromDict,current_Count);
                sprintf(buf, "%d", ++current_Count);
                DictInsert(RESULT_DICT,fromDict,buf);

                if(current_Count>TOTAL_APPS){
                    //printf("Target here >> %s ***********\n",fromDict);
                    strncpy(final_lang,fromDict,sizeof(fromDict));
                    break;
                }
            }//2nd if

      }//end of main_if

      //firs
      //check if the word is in LangFiles
      token = strtok(NULL, " ");
    }

    DictDestroy(DATA);
    DictDestroy(RESULT_DICT);
    //free(word);
    return final_lang;
}



int
mainRed3()
    {
       Dict d;
       char buf[512];
       int i;

       d = DictCreate();

       DictInsert(d, "foo", "hello world");
       //puts(DictSearch(d, "foo"));
       //DictInsert(d, "foo", "hello world2");
       //puts(DictSearch(d, "foo"));
       //DictDelete(d, "foo");
       //puts(DictSearch(d, "foo"));
       //DictDelete(d, "foo");
       assert(DictSearch(d, "foo") == 0);
       //DictDelete(d, "foo");

       for(i = 0; i < 10000; i++) {
           sprintf(buf, "%d", i);
           DictInsert(d, buf, buf);
       }

       DictDestroy(d);

       return 0;
   }
