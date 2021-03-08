#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//this function gets characters from a file and puts them into a specified char array *info
//ex: get_fileinfo_char("testio.txt",&char_array,30)
int get_fileinfo_char(const char file_name[15], char *info,int read_amt)
{
	FILE *read_file;
	read_file = fopen(file_name,"r");
	if (read_file == NULL) { return -1; }
	int charnum = 0;
	while (charnum <= read_amt)
	{
        printf("here");
		*(info+charnum) = fgetc(read_file); //reads the character
		if (*(info+charnum) == EOF) {charnum = read_amt + 1;}
		charnum += 1;
	}
	fclose(read_file);
	return 1;
}

//gets a specific line,stores in whatever character array is passed to it through lineinfo
//ex: get_fileline("testio.txt",&char_array,2)
int get_fileline(const char file_name[15], char *lineinfo,int linenum)
{
	FILE *read_file;
	read_file = fopen(file_name,"r");
	if (read_file == NULL) { return -1; }
	int charnum = 0;
	int line = 1;
	while (line != linenum)
	{
	    *lineinfo = fgetc(read_file);
	    if (*lineinfo == '\n') { line += 1; }
	}
	while (line != 0)
	{
		*(lineinfo+charnum) = fgetc(read_file); //reads the character
		printf("%c",*(lineinfo+charnum));
		if (*(lineinfo+charnum) == EOF || *(lineinfo+charnum) == '\n') {line = 0;}
		charnum += 1;
	}
	fclose(read_file);
	return 1;
}
