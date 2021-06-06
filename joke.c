#include<stdio.h>
#include<stdlib.h>
#include <wchar.h>
#include <locale.h>
#include<string.h> //for memsete
#include<unistd.h>//stdin readin

#define UTF8_MAX 1114112 //Max value of a UTF-8 character

//Hashtable for matching characters and their number of occurences. Priority assigned based on the order in which t//he characters appear.
struct tableCount {
    int value;
    wchar_t key;
    int priority;
};

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


int main(int argc, char** argv) {

char* input ="㠀㠀hexx mwari";

//unsigned char c = (unsigned char)text[0];
//unsigned char next_c = (unsigned char)text[1];

setlocale(LC_CTYPE, "");//to print characters propertly
unsigned int unicodeStore;//This is where the codepoint is stored.

int num = convertUTF8(input, &unicodeStore);

printf(">> %d\n",unicodeStore);

return 0;
}
