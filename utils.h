#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

char
*replace(const char *src, const char *from, const char *to,size_t *sz, int type,int limit);

char* concat(int count, ...);

char *
strLWR2(char *str);

#endif // UTILS_H_INCLUDED
