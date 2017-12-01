#ifndef STRING_C
#define STRING_C

int strlen(char *s)
{
  int i = 0;
  while(*s){
    i++; s++;
  }
  return i;
}

int strcmp(char *s1, char *s2)
{
  while((*s1 && *s2) && (*s1==*s2)){
      s1++; s2++;
  }
  if ((*s1==0) && (*s2==0))
    return 0;
  return(*s1 - *s2);

}

int strcpy(char *dest, char *src)
{
  while(*src){
    *dest++ = *src++;
  }
  *dest = 0;
}

char *my_strcpy(char *destination, const char *source) {
	int i = 0;
	while (source[i] != '\0') {
		destination[i] = source[i];
		i++;
	}
	destination[i] = '\0';
	return destination;
}

int my_strlen(char *string) {
	int length = 0;
	while( string[length] != '\0') {
		length++;
	}
	return length;
}

char * mystrtok(char *str, char *delim){
    char buf[2048];
    int pos = 0;
    char *s;

    int 
}

#endif