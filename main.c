#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "dict.h"
#include "langdt.h"
#include <stdlib.h>

char *
receiveLanguageCode(char * text);

int main(){
    char *text= "are would could monday tuesday friday wednesday 再见 Hello! We are lear'ning about strtok the است we ";
    char language_code[6];
    strcpy(language_code,receiveLanguageCode(text));

    printf("Language >> %s \n",language_code);

}


char *
receiveLanguageCode(char * text){
    int TOTAL_APPS=3;
    //adding to list vars
    char buf[512];
    int c=1;

    int current_Count=0;
    char final_lang[6]="other";

    Dict DATA,RESULT_DICT;
    DATA=getClassLanguages();
    RESULT_DICT=DictCreate();
    //DictInsert(d, "foo", "hello world");

    //to lowercase and writable
    char *string= strlwr(strdup(text));
    //Extract the first token
    char * token = strtok(string, " ");
    //char * word=;


    //DictInsert(RESULT_DICT, "foo", "45");
    //int count=atoi(DictSearch(RESULT_DICT,"foo"));
    //printf("%d\n",count);

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
mainRed()
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

