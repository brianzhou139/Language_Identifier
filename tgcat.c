#include "tgcat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "language2.h"
#include "category.h"
#include "utils.h"
#include <locale.h>

#define MAX_LEN 9000
#define MAX_COUNT 40
#define TOTAL_ALFS 33
#define IMAGERY 200
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

int tgcat_init() {
  return 0;
}


int tgcat_detect_language(const struct TelegramChannelInfo *channel_info,
                          char language_code[6]) {

//set locale
//setlocale("");
  // choose a text with the longest length
  const char *text = channel_info->title;
  size_t text_len = strlen(channel_info->title);
  if (strlen(channel_info->description) > text_len) {
    text = channel_info->description;
    text_len = strlen(channel_info->description);
  }
  size_t i;


  const char *myStr=channel_info->description;
  size_t current_size=0;

  //variables
  int alphabets[TOTAL_ALFS]={0};


  for (i = 0; i < channel_info->post_count; i++) {

    myStr=replace(channel_info->posts[i],"\n"," ",&current_size,1,MAX_LEN);
    char *string= strLWR2(strdup(myStr));
    //Extract the first token
    char * token = strtok(string, " ");
    int tokenCounter=0;

    unsigned int uni;//This is where the codepoint is stored.
    int num ;

    /***************************************************************/

    while( token != NULL && tokenCounter<MAX_COUNT) {
    //counter occurances here
    num = convertUTF8(token, &uni);
    if LATIN(uni){++alphabets[0];};
    if ARABIC(uni){++alphabets[1];};
    if RUSSIAN(uni){++alphabets[2];};
    if GREEK(uni){++alphabets[3];};
    if HEBREW(uni){++alphabets[4];};
    if ARMENIAN(uni){++alphabets[5];};
    if BURMESE(uni){++alphabets[6];};
    if HANGUL(uni){++alphabets[7];};
    if JAPANESE(uni){++alphabets[8];};
    if MONGOLIAN(uni){++alphabets[9];};
    if MALAYALAM(uni){++alphabets[10];};
    if CHINESE(uni){++alphabets[11];};
    if CJK(uni){++alphabets[12];};
    if DEVANAGARI(uni){++alphabets[13];};
    if BENGALI(uni){++alphabets[14];};
    if GURMUKHI(uni){++alphabets[15];};
    if GUJARATA(uni){++alphabets[16];};
    if ORIYA(uni){++alphabets[17];};
    if TAMIL(uni){++alphabets[18];};
    if TELUGU(uni){++alphabets[19];};
    if KANNADA(uni){++alphabets[20];};
    if SINHALA(uni){++alphabets[21];};
    if THAI(uni){++alphabets[22];};
    if LAO(uni){++alphabets[23];};
    if TIBETAN(uni){++alphabets[24];};
    if GEORGIAN(uni){++alphabets[25];};
    if ETHIOPIC(uni){++alphabets[26];};
    if CHEROKEE(uni){++alphabets[27];};
    if CANADIAN(uni){++alphabets[28];};
    if TAGALOG(uni){++alphabets[29];};
    if TAGBANWA(uni){++alphabets[30];};
    if KHMER(uni){++alphabets[31];};
    if LIMBU(uni){++alphabets[32];};

    token = strtok(NULL, " ");
    ++tokenCounter;

    }//end of while_Loop
    /**************************************************************/
    //get the Longest Text Yes
    if (current_size > text_len) {
      text = myStr;
      text_len = strlen(channel_info->posts[i]);
      //Do the magice Here
      //printf("**********************************************************************************\n",text);
    }

  }//end of for Loop_Here

      //add tagbawa and tagbanwa
    alphabets[29]=alphabets[29]+alphabets[30];

    int j;
    int largest=0;
    int highest_index=0;
    char result_code[600];

    for(j=0;j<TOTAL_ALFS;++j){
        if(alphabets[j]>largest){
            largest=alphabets[j];
            highest_index=j;
        }
    }


  if (text_len != 0) {
    if(highest_index==0){
        //check latin languages
        char *defText="other";
        strcpy(result_code,receiveLangCode(text,defText,highest_index));
    }else if(highest_index==1){
        //check arabic languages
        //printf("checking Latin Languages \n....... ");
        char *defText="ar";
        strcpy(result_code,receiveLangCode(text,defText,highest_index));
    }else if(highest_index==2){
        char *defText="ru";
        strcpy(result_code,receiveLangCode(text,defText,highest_index));
    }else if(highest_index==3){
        memcpy(language_code, "el", 3);
        return 0;
    }else if(highest_index==4){
        //check hebrew
        memcpy(language_code, "he", 3);
        return 0;
    }else if(highest_index==5){
        //check Amernian
        memcpy(language_code, "hy", 3);
        return 0;
    }else if(highest_index==6){
        //checkBurmeses
        memcpy(language_code, "my", 3);
        return 0;
    }else if(highest_index==7){
        //check Korean
        memcpy(language_code, "ko", 3);
        return 0;
    }else if(highest_index==8){
        //check japanese
        memcpy(language_code, "ja", 3);
        return 0;
    }else if(highest_index==9){
        //check MONGOLIAN
        memcpy(language_code, "mn", 3);
        return 0;
    }else if(highest_index==10){
        //check Malayalams
        memcpy(language_code, "ml", 3);
        return 0;
    }else if(highest_index==11){
        //Check Chinesw Languages
        memcpy(language_code, "zh", 3);
        return 0;
    }else if(highest_index==12){
        //Check CHK, ChinesKorean,Japanese,
        char *defText="zh";
        strcpy(result_code,receiveLangCode(text,defText,highest_index));
    }else if(highest_index==13){
        //Check DEVANAGARI
        char *defText="hi";
        strcpy(result_code,receiveLangCode(text,defText,highest_index));
    }else if(highest_index==14){
        //Check BENGALI LNAGUAGEs
        memcpy(language_code, "bn", 3);
        return 0;
    }else if(highest_index==15){
        //Check GURMUKHI LANGUAGEs
        memcpy(language_code, "pa", 3);
        return 0;
    }else if(highest_index==16){
        //Check GUJARATA
        memcpy(language_code, "gu", 3);
        return 0;
    }else if(highest_index==17){
        //Check ORIYA LANGUAGES
        memcpy(language_code, "or", 3);
        return 0;
    }else if(highest_index==18){
        //Check TAMIL Language
        memcpy(language_code, "ta", 3);
        return 0;
    }else if(highest_index==19){
        //Check TELEGU Language
        memcpy(language_code, "te", 3);
        return 0;
    }else if(highest_index==20){
        //Check KANNADA
        memcpy(language_code, "kn", 3);
        return 0;
    }else if(highest_index==21){
        //Check SINHALA;
        memcpy(language_code, "si", 3);
        return 0;
    }else if(highest_index==22){
        //Check THAI
        memcpy(language_code, "th", 3);
        return 0;
    }else if(highest_index==23){
        //Check LAO
        memcpy(language_code, "lo", 3);
        return 0;
    }else if(highest_index==24){
        //Check TIBETAN
        memcpy(language_code, "dz", 3);
        return 0;
    }else if(highest_index==25){
        //Check GEORGIAN
        memcpy(language_code, "ka", 3);
        return 0;
    }else if(highest_index==26){
        //Check ETHIOPIC
        char *defText="am";
        strcpy(result_code,receiveLangCode(text,defText,highest_index));
    }else if(highest_index==27){
        //Check CHEROKEEE
        memcpy(language_code, "other", 6);
        return 0;
    }else if(highest_index==28){
        //Check CANADIAN
        memcpy(language_code, "cr", 3);
        return 0;
    }else if(highest_index==29){
        //Check TAGALOG
        memcpy(language_code, "tl", 3);
        return 0;
    }else if(highest_index==30){
        //Check TAGBANWA
        memcpy(language_code, "tl", 3);
        return 0;
    }else if(highest_index==31){
        //Check KHMER (sanscript)
        memcpy(language_code, "sa", 3);
        return 0;
    }else if(highest_index==32){
        //Check LIMBU (nepali lang)
        memcpy(language_code, "ne", 3);
        return 0;
    }


    if(strcmp(result_code,"other")==0){
        char *defaultTxt="en";
        strcpy(result_code,receiveLangCode(text,defaultTxt,IMAGERY));
        memcpy(language_code,result_code, 3);
        return 0;
    }else{
        memcpy(language_code, result_code, 3);
        return 0;
    }

    memcpy(language_code,result_code, 3);

    return 0;
  }//end of if statement

  memcpy(language_code, "other", 6);
  return 0;

}


int tgcat_detect_category34(const struct TelegramChannelInfo *channel_info,
                          double category_probability[TGCAT_CATEGORY_OTHER + 1]) {
  (void)channel_info;
  memset(category_probability, 0, sizeof(double) * (TGCAT_CATEGORY_OTHER + 1));

  /*Handle Channel Details Here*/
  size_t text_len = strlen(channel_info->title);
  size_t longest_text_len = strlen(channel_info->title);
  size_t description_len = strlen(channel_info->description);

  // choose a text with the longest length
  const char *longest_text = channel_info->title;
  const char *title = channel_info->title;
  const char *description = channel_info->description;

  //printf("title : %s size: %d\n",title,text_len);
  //printf("description : %s size : %d\n",description,description_len);

    size_t i;

    const char *myStr=channel_info->description;
    size_t current_size=0;

    //variables
    int alphabets[TOTAL_ALFS]={0};

  for (i = 0; i < channel_info->post_count; i++) {

    myStr=replace(channel_info->posts[i],"\n"," ",&current_size,1,MAX_LEN);

    char *string= strLWR2(strdup(myStr));
    //Extract the first token
    char * token = strtok(string, " ");
    int tokenCounter=0;

    unsigned int uni;//This is where the codepoint is stored.
    int num ;

    /***************************************************************/

    while( token != NULL && tokenCounter<MAX_COUNT) {
    //counter occurances here
    num = convertUTF8(token, &uni);
    if LATIN(uni){++alphabets[0];};
    if RUSSIAN(uni){++alphabets[1];};

    token = strtok(NULL, " ");
    ++tokenCounter;

    }//end of while_Loop

    if (current_size > longest_text_len) {
      longest_text = myStr;
      longest_text_len=strlen(channel_info->posts[i]);
      //Do the magice Here
    }

  }//end of for LOOOp

  //Do the magic Here yeah yeah

  if (longest_text_len != 0) {
    //Check for the Language
    int lang=-1;    if(alphabets[0]>0 || alphabets[1]>0){
        lang=getEngOrRuss(longest_text);
    }else{
        lang=-1;
    }
    //now check for the probabilities

    if(lang==0 || lang==1){
        const char *post=longest_text;
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
        category_probability[k]=FINAL_PROB;
        //FINAL_PROB[i]=()
    }//end of for loop
    return 0;

    }else{
        category_probability[41]=0.1;
        return 0;
    }

  }//end if if

  return 0;

}

int tgcat_detect_category(const struct TelegramChannelInfo *channel_info,
                          double category_probability[TGCAT_CATEGORY_OTHER + 1]) {
  (void)channel_info;
  memset(category_probability, 0, sizeof(double) * (TGCAT_CATEGORY_OTHER + 1));

  int i;
  for (i = 0; i < 10; i++) {
    //category_probability[rand() % (TGCAT_CATEGORY_OTHER + 1)] += 0.1;
     category_probability[i]=0;
  }

  return 0;
}


int tgcat_detect_language2(const struct TelegramChannelInfo *channel_info,
                          char language_code[6]) {
  // choose a text with the longest length
  const char *text = channel_info->title;
  size_t text_len = strlen(channel_info->title);
  if (strlen(channel_info->description) > text_len) {
    text = channel_info->description;
    text_len = strlen(channel_info->description);
  }
  size_t i;

  for (i = 0; i < channel_info->post_count; i++) {
    if (strlen(channel_info->posts[i]) > text_len) {
      text = channel_info->posts[i];
      text_len = strlen(channel_info->posts[i]);

      //Do the magice Here
      //printf("**********************************************************************************\n",text);
      //printf("%s\n",text);
      //printf("***********************************************************************************\n",text);
      //Do the Magic Here

    }
  }

  if (text_len != 0) {
    // guess language based on the first character
    // don't try this at home
    unsigned char c = (unsigned char)text[0];
    if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
      memcpy(language_code, "en", 3);
      return 0;
    }

    unsigned char next_c = (unsigned char)text[1];
    if ((c == 0xD0 && (next_c == 0x81 || next_c >= 0x90)) || (c == 0xD1 && next_c <= 0x91)) {
      memcpy(language_code, "ru", 3);
      return 0;
    }

  }

  memcpy(language_code, "other", 6);
  return 0;
}
