#include<stdio.h>
#include<stdlib.h>
#include <wchar.h>
#include <locale.h>
#include<string.h> //for memsete
#include<unistd.h>//stdin readin
#include <assert.h>
#include <string.h>
#include "dict.h"
#include "langdt.h"
#include "langdt2.h"
#include "langdt3.h"
#include "utils.h"
#include "data.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>


#define TOTAL_ALFS 33
#define IMAGERY 200
#define MAX_COUNT 40
#define UTF8_MAX 1114112 //Max value of a UTF-8 character
#define LATIN(t) ((t>=65 && t<=687) || (t>=7424 && t<=7455) || (t>=11360 && t<=11391) || (t>=42790 && t<=43007))
#define ARABIC(t) ((t>=1536 && t<=1791) || (t>=64320 && t<=65017) || (t>=65152 && t<=65276))
#define RUSSIAN(t) (t>=1024 && t<=1279)
#define GREEK(t) ((t>=902 && t<=1023) || (t>=7936 && t<=8188))
#define HEBREW(t) (t>=1408 && t<=1503)
#define ARMENIAN(t) (t>=1312 && t<=1407)
#define BURMESE(t) (t>=4096 && t<=4255)
#define HANGUL(t) ((t>=44032 && t<=55291) || (t>=65441 && t<=65470) || (t>=12576 && t<=12671) || (t>=4352 && t<=4607) || (t>=12800 && t<=12830) || (t>=12896 && t<=12927))
#define JAPANESE(t) ((t>=65376 && t<=65439) || (t>=12992 && t<=13151) || (t>=12672 && t<=12703) || (t>=12352 && t<=12447) || (t>=12449 && t<=12543))
#define MONGOLIAN(t) (t>=6144 && t<=6386)
#define MALAYALAM(t) (t>=3328 && t<=3455)
#define CHINESE(t) ((t>=12544 && t<=12575) || (t>=12704 && t<=12735))
#define CJK(t) ((t>=12736 && t<=12799) || (t>=12832 && t<=12863) || (t>=12928 && t<=12959) || (t>=13152 && t<=40917))
#define DEVANAGARI(t) (t>=2304 && t<=2431)
#define BENGALI(t) (t>=2432 && t<=2559)
#define GURMUKHI(t) (t>=2560 && t<=2687)
#define GUJARATA(t) (t>=2688 && t<=2815)
#define ORIYA(t) (t>=2816 && t<=2943)
#define TAMIL(t) (t>=2944 && t<=3071)
#define TELUGU(t) (t>=3072 && t<=3199)
#define KANNADA(t) (t>=3200 && t<=3327)
#define SINHALA(t) (t>=3456 && t<=3583)
#define SINHALA(t) (t>=3456 && t<=3583)
#define THAI(t) (t>=3584 && t<=3711)
#define LAO(t) (t>=3712 && t<=3839)
#define TIBETAN(t) (t>=3840 && t<=4095)
#define GEORGIAN(t) (t>=4256 && t<=4351)
#define ETHIOPIC(t) (t>=4608 && t<=5023)
#define CHEROKEE(t) (t>=5024 && t<=5119)
#define CANADIAN(t) (t>=5120 && t<=5759)
#define TAGALOG(t) (t>=5888 && t<=5919)
#define TAGBANWA(t) (t>=5984 && t<=6015)
#define KHMER(t) (t>=6016 && t<=6143)
#define LIMBU(t) (t>=6400 && t<=6463)

//Hashtable for matching characters and their number of occurences. Priority assigned based on the order in which t//he characters appear.
struct tableCount {
    int value;
    wchar_t key;
    int priority;
};

char *
receiveLangCode(char * text,char *setText,int indexCode);

int mainRes(int argc, char** argv) {
     printf("hello world\n");
return 0;

}

char *
receiveLangCode(char * text,char *setText,int indexCode){
    int TOTAL_APPS=1;
    int isCHK=0;
    //adding to list vars
    char buf[900];
    int c=1;

    int current_Count=0;
    char final_lang[400]="other";
    //set final_lang to set_text
    strcpy(final_lang,setText);

    Dict DATA,RESULT_DICT;
    //DATA=getClassALanguages();
    if(indexCode==0){
        DATA=getLatinLanguages();
    }else if(indexCode==1){
        DATA=getArabicLanguages();
    }else if(indexCode==2){
        DATA=getRussianLanguages();
    }else if(indexCode==3){
        DATA=getGreekLanguages();
    }else if(indexCode==12){
        DATA=getCHKLanguages();
        isCHK=1;
    }else if(indexCode==13){
        DATA=getDevanagariLanguages();
    }else if(indexCode==26){
        DATA=getEthiopicLanguages();
    }else{
        DATA=getExtraLanguages();
    }

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
            if(isCHK==0){
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

void getAlphabet(int index,int count){
    switch(index){
    case 0:
        printf("Latin : %d\n",count);break;
    case 1:
        printf("Arabic : %d\n",count);break;
    case 2:
        printf("Russian : %d\n",count);break;
    case 3:
        printf("Greek : %d\n",count);break;
    case 4:
        printf("Hebrew : %d\n",count);break;
    case 5:
        printf("Armenian : %d\n",count);break;
    case 6:
        printf("Burmess : %d\n",count);break;
    case 7:
        printf("HANGUL : %d\n",count);break;
    case 8:
        printf("JAPANESE : %d\n",count);break;
    case 9:
        printf("Mongolian : %d\n",count);break;
   case 10:
        printf("Malayalam : %d\n",count);break;
   case 11:
        printf("Chinese : %d\n",count);break;
   case 12:
        printf("CJK : %d\n",count);break;
   case 13:
        printf("DEVANAGARI : %d\n",count);break;
   case 14:
        printf("BENGALI : %d\n",count);break;
   case 15:
        printf("GURMUKHI : %d\n",count);break;
   case 16:
        printf("GUJARATA : %d\n",count);break;
   case 17:
        printf("ORIYA : %d\n",count);break;
   case 18:
        printf("TAMIL : %d\n",count);break;
   case 19:
        printf("TELUGU : %d\n",count);break;
   case 20:
        printf("KANNADA : %d\n",count);break;
   case 21:
        printf("SINHALA : %d\n",count);break;
   case 22:
        printf("THAI : %d\n",count);break;
   case 23:
        printf("LAO : %d\n",count);break;
   case 24:
        printf("TIBETAN : %d\n",count);break;
   case 25:
        printf("GEORGIAN : %d\n",count);break;
   case 26:
        printf("ETHIOPIC : %d\n",count);break;
   case 27:
        printf("CHEROKEE : %d\n",count);break;
   case 28:
        printf("CANADIAN : %d\n",count);break;
   case 29:
        printf("TAGALOG : %d\n",count);break;
   case 30:
        printf("TAGBANWA: %d\n",count);break;
   case 31:
        printf("KHMER : %d\n",count);break;
   case 32:
        printf("LIMBU : %d\n",count);break;
    default:
        printf("defat getAlphabte()");
    }
}

//Comparator for the qsort() later. Characters with higher number of appearances
//come first. If ties occur, sort based on their priority, assigned during the conversion step.
int comparator(const void* p, const void* q) {
    int left = ((struct tableCount *)p)->value;
    int right = ((struct tableCount *)q)->value;

    int diff =  (right - left);

    if (diff == 0) {//tiebreaker
	    if (((struct tableCount *)p)->priority < ((struct tableCount *)q)->priority) diff = -1;

	    else {
		    diff = 1;
	    }
    }

    return diff;
}

/*Converts the input utf8 character and stores it in the result array.
 *returns the number of bytes of each utf8 character */
//Force unsigned int since this value is going to be used as index in an array later.
int convertUTF8 (char* utf8, unsigned int* result) {

    int length = 0;
    unsigned char* temp = (unsigned char*)utf8;
    *result = 0;

    if (*utf8 >= 0) { //This byte starts with a 0, therefore is a single byte unicode.
        *result = *utf8;
        return 1;
    }


    else if ((temp[0]&0b11100000) == 0b11000000) {
        length = 2;
        *result = temp[0]&0b11111; //keep the last 5 bits to convert to unicode
                                //exclude [110]
    }

    else if ( (temp[0]&0b11110000) == 0b11100000 ) {
        length = 3;
        *result = temp[0]&0b1111;//keep the last 4 bits to convert to unicode, exclude [1110]
    }

    else {
        length = 4;
        *result = temp[0]&0b111;//Keep the last 3 bits. Exclude [1110]
    }
    int i;
	for (i = 1; i < length; i++)     {
        *result = (*result<<6) | (temp[i]&0b111111); //get rid of leading bits (10)
	}//Get subsequent bytes and perform bit manipulation to get unicode conversion (in hex).
}

