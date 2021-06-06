#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "dict.h"
#include "langdt.h"
#include "langdt2.h"
#include "langdt3.h"
#include "utils.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

#define MAX_LEN 9000




char *
receiveLanguageCode(char * text,char *setText,int classNum);

char *
strLWR(char *str);

char
*strfromchar(char source);

void testGetFile();

int valid_identifier_start(char ch);

/*
int mainSupp(){


}

int valid_identifier_start(char ch)
{
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ||
            ((unsigned char)ch >= 0xC0));
}

char *
receiveLanguageCode(char * text,char *setText,int classNum){
    int TOTAL_APPS=3;
    //adding to list vars
    int found=0;
    int count=0;
    char buf[900];
    int c=1;

    int current_Count=0;
    char final_lang[400];
    //set final_lang to set_text
    strcpy(final_lang,setText);

    Dict DATA,RESULT_DICT;

    if(classNum==1){
        DATA=getClassALanguages();
    }else if(classNum==2){
        DATA=getClassBLanguages();
    }else{
        DATA=getClassCLanguages();
    }

    RESULT_DICT=DictCreate();
    //DictInsert(d, "foo", "hello world");
    //to lowercase and writable
    char *string= strLWR(strdup(text));
    //Extract the first token
    char * token = strtok(string, " ");

    while( token != NULL ) {
      ++count;
      //break if sentences too long > 300 words
      if(count==300){
        //if count
        break;
      }

      char* fromDict=DictSearch(DATA,token);
      //checking in Data
      if(fromDict==0){
            //printf("%s : Not found\n",token);
        }else{
            //printf("%s >> %s: found\n",token,fromDict);
            //set the lang to the found lang
            if(classNum==1){
                strcpy(final_lang,fromDict);
            }else if(strcmp(final_lang,"other")==0){
                strcpy(final_lang,fromDict);
            }

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
                    found=1;
                    break;
                }
            }//2nd if

      }//end of main_if
      //firs
      //check if the word is in LangFiles
      token = strtok(NULL, " ");
    }

    if(found==1){
        DictDestroy(DATA);
        DictDestroy(RESULT_DICT);
        return final_lang;
    }else if(classNum==1 && found==0){
        //printf("********Opening Class2\n");
        DictDestroy(DATA);
        DictDestroy(RESULT_DICT);
        return receiveLanguageCode(text,final_lang,++classNum);
    }else if(classNum==2 && found==0){
        //printf("**********Check for chinese please please >> %s\n",final_lang);
        DictDestroy(DATA);
        DictDestroy(RESULT_DICT);
        //free(word);
        return receiveLanguageCode(text,final_lang,++classNum);
    }else{
        return final_lang;
    }

}



char *
receiveLanguageCode2(char * text){
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
    char *string= strLWR(strdup(text));
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

char *
strLWR(char *str){
    unsigned char*p=(unsigned char*)str;

    while(*p){
    *p=tolower((unsigned char)*p);
    p++;
    }
    return str;
}


char
*strfromchar(char source)
{
	char *destination;

	destination = malloc(2 * sizeof(char)); // just to be clear

	if (destination == NULL)
    {
		// very heavy-handed error handling
		printf("Memory allocation failed in strfromchar.\n");
		exit(EXIT_FAILURE);
    }

	destination[0] = source;	// copy the character into the string
	destination[1] = '\0';		// null-terminate the string

	return destination;			// common convention for str functions
}


int
mainRss()
    {
       Dict d;
       char buf[512];
       int i;

       d = DictCreate();

       DictInsert(d, "foo", "hello world");
       DictInsert(d, "sport", "1");
       DictInsert(d, "sports", "1");
       DictInsert(d, "sex", "2");
       DictInsert(d, "porn", "2");
       DictInsert(d, "ball", "2");
       DictInsert(d, "brian", "77");
       DictInsert(d, "zhou", "41");

       char *res=DictSearch(d, "zhou");
       printf("%s\n",res);
       //puts(DictSearch(d, "foo"));
       //DictInsert(d, "foo", "hello world2");
       //puts(DictSearch(d, "foo"));
       //DictDelete(d, "foo");
       //puts(DictSearch(d, "foo"));
       //DictDelete(d, "foo");
       //DictDelete(d, "foo");

       DictDestroy(d);
       return 0;
   }

   */
