//
//  utf8.c
//  Demo
//
//  Created by wjl on 2019/8/31.
//  Copyright © 2019 ycan. All rights not reserved.
//

#include "utf8.h"
#include "stdlib.h"

static unsigned int utf8_wstrlen(wchar_t *s){
    unsigned int count = 0;
    if( s ){
        while(*s++) {
            ++count;
        }
    }
    return count;
}

static unsigned int utf8_strlen(unsigned char *s){
    unsigned int count = 0;
    if( s ){
        while(*s++) {
            ++count;
        }
    }
    return count;
}

static void utf8_encode_code(unsigned char **buffer, unsigned int code)
{
    if( code < 0x80 ){
            // 0xxxxxxx
            // 8 bits
        *(*buffer)++ = code;
    } else if( code < 0x800 ){
            // 110xxxxx 10xxxxxx
            // 2 bits
        *(*buffer)++ = ((code>>6) & 0x1f) | 0xc0;
        *(*buffer)++ = ( code     & 0x3f) | 0x80;
    } else if( code < 0x10000 ){
            // 1110xxxx 10xxxxxx 10xxxxxx
            // 3 bits
        *(*buffer)++ = ((code>>12) & 0x0f) | 0xe0;
        *(*buffer)++ = ((code>>6 ) & 0x3f) | 0x80;
        *(*buffer)++ = ( code      & 0x3f) | 0x80;
    } else if( code < 0x200000 ){
            // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
            // 4 bits
        *(*buffer)++ = ((code>>18) & 0x07) | 0xf0;
        *(*buffer)++ = ((code>>12) & 0x3f) | 0x80;
        *(*buffer)++ = ((code>>6 ) & 0x3f) | 0x80;
        *(*buffer)++ = ( code      & 0x3f) | 0x80;
    } else if( code < 0x4000000 ){
            // 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
            // 5 bits
        *(*buffer)++ = ((code>>24) & 0x03) | 0xf8;
        *(*buffer)++ = ((code>>18) & 0x3f) | 0x80;
        *(*buffer)++ = ((code>>12) & 0x3f) | 0x80;
        *(*buffer)++ = ((code>>6 ) & 0x3f) | 0x80;
        *(*buffer)++ = ( code      & 0x3f) | 0x80;
    } else if( code < 0x80000000 ){
            // 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
            // 6 bits
        *(*buffer)++ = ((code>>30) & 0x01) | 0xfc;
        *(*buffer)++ = ((code>>24) & 0x3f) | 0x80;
        *(*buffer)++ = ((code>>18) & 0x3f) | 0x80;
        *(*buffer)++ = ((code>>12) & 0x3f) | 0x80;
        *(*buffer)++ = ((code>>6 ) & 0x3f) | 0x80;
        *(*buffer)++ = ( code      & 0x3f) | 0x80;
    }
}

static unsigned int utf8_encode_code_lenght(unsigned int code)
{
    if( code < 0x80 ){
            // 0xxxxxxx
            // 8 bits
        return 1;
    } else if( code < 0x800 ){
            // 110xxxxx 10xxxxxx
            // 2 bits
        return 2;
    } else if( code < 0x10000 ){
            // 1110xxxx 10xxxxxx 10xxxxxx
            // 3 bits
        return 3;
    } else if( code < 0x200000 ){
            // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
            // 4 bits
        return 4;
    } else if( code < 0x4000000 ){
            // 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
            // 5 bits
        return 5;
    } else if( code < 0x80000000 ){
            // 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
            // 6 bits
        return 6;
    } else {
            // don't handle this code
        return 0;
    }
}

unsigned char* utf8_encode_string(wchar_t *string, int *length)
{
    if( string ){
        int len = 0;
        if(length){
            if(*length < 0){
                len = utf8_wstrlen(string);
            } else {
                len = *length;
            }
        } else {
            len = utf8_wstrlen(string);
        }
        wchar_t *end = string + len;
        wchar_t *s = string;
        unsigned int buffer_length = 0;
        while( s<end ){
            buffer_length += utf8_encode_code_lenght(*s);
            ++s;
        }
        unsigned char *buffer = NULL;
        if( buffer_length ){
            buffer = malloc(sizeof(unsigned char)*buffer_length + 1);
        }
        if( buffer ){
            unsigned char *tmp_buffer = buffer;
            s = string;
            while( *s ){
                utf8_encode_code(&tmp_buffer, *s);
                ++s;
            }
            *tmp_buffer = 0;
            if( length ){
                *length = buffer_length;
            }
            return buffer;
        }
    }
    if( length ){
        *length = 0;
    }
    return NULL;
}

static unsigned int utf8_decode_character_count(unsigned char *string, int length)
{
    unsigned char *n = string;
    unsigned int count = 0;
    if( length < 0 ){
        length = utf8_strlen(string);
    }
    unsigned char *end = string + length;
    while( n<end ){
        if(n[0]<0x80){
                // 0xxxxxxx
                // 1 bits
            ++n;
        } else if(n[0]<0xe0){
                // 110xxxxx 10xxxxxx
                // 2 bits
            if((n[0]&0xe0)==0xc0 &&
               (n[1]&0xc0)==0x80    )
                {
                n += 2;
                } else {
                    break;
                }
        } else if(n[0]<0xf0){
                // 1110xxxx 10xxxxxx 10xxxxxx
                // 3 bits
            if((n[0]&0xf0)==0xe0 &&
               (n[1]&0xc0)==0x80 &&
               (n[2]&0xc0)==0x80    )
                {
                n += 3;
                } else {
                    break;
                }
        } else if(n[0]<0xf8){
                // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
                // 4 bits
            if((n[0]&0xf8)==0xf0 &&
               (n[1]&0xc0)==0x80 &&
               (n[2]&0xc0)==0x80 &&
               (n[3]&0xc0)==0x80    )
                {
                n += 4;
                } else {
                    break;
                }
        } else if(n[0]<0xfc){
                // 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
                // 5 bits
            if((n[0]&0xfc)==0xf8 &&
               (n[1]&0xc0)==0x80 &&
               (n[2]&0xc0)==0x80 &&
               (n[3]&0xc0)==0x80 &&
               (n[4]&0xc0)==0x80    )
                {
                n += 5;
                } else {
                    break;
                }
        } else if(n[0]<0xfe){
                // 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
                // 6 bits
            if((n[0]&0xfe)==0xfc &&
               (n[1]&0xc0)==0x80 &&
               (n[2]&0xc0)==0x80 &&
               (n[3]&0xc0)==0x80 &&
               (n[4]&0xc0)==0x80 &&
               (n[5]&0xc0)==0x80    )
                {
                n += 5;
                } else {
                    break;
                }
        } else {
            break;
        }
        ++count;
    }
    return count;
}

wchar_t* utf8_decode_string(unsigned char *string, int *length)
{
    if(string){
        int len = 0;
        if( length ){
            if( *length < 0 ){
                len = utf8_strlen(string);
            } else {
                len = *length;
            }
        } else {
            len = utf8_strlen(string);
        }
        unsigned int buffer_length = utf8_decode_character_count(string, len);
        wchar_t *buffer = NULL;
        if(buffer_length){
            buffer = malloc((buffer_length + 1)*sizeof(wchar_t));
        }
        if(buffer){
            unsigned char *n = string;
            unsigned char *end = string + len;
            wchar_t *s = buffer;
            while (n<end) {
                if(n[0]<0x80 ){
                        // 0xxxxxxx
                        // 1 bits
                    *s = n[0];
                    ++n;
                } else if(n[0]<0xe0 ){
                        // 110xxxxx 10xxxxxx
                        // 2 bits
                    if((n[0]&0xe0)==0xc0 &&
                       (n[1]&0xc0)==0x80    )
                        {
                        *s =
                        ((n[0]&0x1f)<<6)|
                        ( n[1]&0x3f    );
                        n += 2;
                        } else {
                            break;
                        }
                } else if(n[0]<0xf0 ){
                        // 1110xxxx 10xxxxxx 10xxxxxx
                        // 3 bits
                    if((n[0]&0xf0)==0xe0 &&
                       (n[1]&0xc0)==0x80 &&
                       (n[2]&0xc0)==0x80    )
                        {
                        *s =
                        ((n[0]&0x0f)<<12)|
                        ((n[1]&0x3f)<<6 )|
                        ( n[2]&0x3f     );
                        n += 3;
                        } else {
                            break;
                        }
                } else if(n[0]<0xf8){
                        // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
                        // 4 bits
                    if((n[0]&0xf8)==0xf0 &&
                       (n[1]&0xc0)==0x80 &&
                       (n[2]&0xc0)==0x80 &&
                       (n[3]&0xc0)==0x80    )
                        {
                        *s =
                        ((n[0]&0x07)<<18)|
                        ((n[1]&0x3f)<<12)|
                        ((n[2]&0x3f)<<6 )|
                        ( n[3]&0x3f     );
                        n += 4;
                        } else {
                            break;
                        }
                } else if(n[0]<0xfc ){
                        // 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
                        // 5 bits
                    if((n[0]&0xfc)==0xf8 &&
                       (n[1]&0xc0)==0x80 &&
                       (n[2]&0xc0)==0x80 &&
                       (n[3]&0xc0)==0x80 &&
                       (n[4]&0xc0)==0x80    )
                        {
                        *s =
                        ((n[0]&0x03)<<24)|
                        ((n[1]&0x3f)<<18)|
                        ((n[2]&0x3f)<<12)|
                        ((n[3]&0x3f)<<6 )|
                        ( n[4]&0x3f     );
                        n += 5;
                        } else {
                            break;
                        }
                } else if(n[0]<0xfe ){
                        // 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
                        // 6 bits
                    if((n[0]&0xfe)==0xfc &&
                       (n[1]&0xc0)==0x80 &&
                       (n[2]&0xc0)==0x80 &&
                       (n[3]&0xc0)==0x80 &&
                       (n[4]&0xc0)==0x80 &&
                       (n[5]&0xc0)==0x80    )
                        {
                        *s =
                        ( 1         <<30)| // ((n[0]&0x01)<30) |
                        ((n[1]&0x3f)<<24)|
                        ((n[2]&0x3f)<<18)|
                        ((n[3]&0x3f)<<12)|
                        ((n[4]&0x3f)<<6 )|
                        ( n[5]&0x3f     );
                        n += 6;
                        } else {
                            break;
                        }
                } else {
                    break;
                }
                ++s;
            }
            *s = 0;
            if( length ){
                *length = buffer_length;
            }
            return buffer;
        }
    }
    if( length ){
        *length = 0;
    }
    return NULL;
}
