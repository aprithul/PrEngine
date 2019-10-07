#include "Utils.h"

// removes white spaces from left and right
// partially modifies original string
char* strip(char* str)
{
    int len = strlen(str);
    int _i = 0; 
    while(isspace(str[0]))
    {
        str++; 
    }
    
    len = strlen(str);
    char* _str = str+len-1;
    while( isspace(*_str) && len>0)
    {
        len--;
        _str--;
    }
    if(len>0)
    {
        *(_str+1) = '\0';
    }

    return str;
}

// replaces consecutive ' ' character with single ' ' character
// modifies original string
char* make_singly_spaced(char* str)
{
    int len = strlen(str);
    char* buffer = (char*)malloc(sizeof(char)*(len+1));
    int _i = 0;
    int _j = 0;
    int flag = 0;
    for( ; _i<=len; _i++)
    {
        if(str[_i] != ' ')
        {
            flag = 0;
            buffer[_j] = str[_i];
            _j++;
        }
        else if(!flag)
        {
            flag = 1;
            buffer[_j] = str[_i];
            _j++;
        } 
    } 
    memcpy(str,buffer,_j);
    free(buffer); 
    return str;
}

//splits string str_a using delimite del. stores number of new strings in length and returns them as a char**
char** split(const char* str_a, const char* del, int* length)
{
    char** tokens = malloc(sizeof(char*));
    int _i = 0;
    int start = 0;
    *length = 0; 
    while(str_a[_i] != '\0')
    {
        if( char_in_del(del, str_a[_i]))
        {
            if(_i-start > 0)
            {
                tokens[*length] = malloc( (sizeof(char)*(_i-start))+1);
                memcpy(tokens[*length], &str_a[start], _i-start);
                tokens[*length][_i-start] = '\0';
                //printf("%s\n", tokens[*length]);
                (*length)++;

                tokens = realloc(tokens, sizeof(char*)*((*length)+1));
            }
            //while(str_a[_i] == del)
            while(char_in_del(del, str_a[_i]) )
                _i++;
            start = _i;
            _i--; 
        } 
        _i++;
    }    
    if(_i-start > 0)
    { 
        tokens[*length] = malloc( (sizeof(char)*(_i-start))+1);
        memcpy(tokens[*length], &str_a[start], _i-start+1);
        (*length)++; 
    }
    return tokens; 
}

// finds if char is in char pointer
// ignores '\0'
int char_in_del(const char* del, char c)
{
    int len = strlen(del);
    int _i = 0;
    for(;_i<len;_i++)
        if(del[_i] == c)
            return 1; 
    return 0;
}

// frees up memory allocated when calling split function
void free_split_text(char** split_text, int length)
{
    for(;length>0;length--)
    {
        free(split_text[length-1]);
    }
    free(split_text);
}

// assigs float value to all elemets in array
void set_value_f(float* array, int count, float value)
{
    while((--count) >= 0)
    {
        array[count] = value;
    } 
}


// assigs int  value to all elemets in array
void set_value_i(int* array, int count, int value)
{
    while((--count) >= 0)
    {
        array[count] = value;
    } 
}

// writes text to file in append mode
// doesn't automaticlaly close file
// file pointer needs to be provided so file can be closed when writing is finished
FILE* write_to_file(char* text, char* file_name, FILE *fp)
{
    if(fp == NULL)
    {
        fp = fopen(file_name, "a");
    }
    fputs(text, fp); 
    return fp;
}

// reads content of file_name, character by character
// stores in buffer and returns
// dynamically increases in size if needed
char* read_file(char* file_name)
{
    int n = 1024;
    FILE *fp;
    char* buffer = (char*)malloc(n*sizeof(char));
    int read_char_count = 0;
    fp = fopen(file_name, "r");
    
    if(fp!=NULL)
    {
        int ch;
        while((ch = fgetc(fp)) != EOF)
        {
            read_char_count++;
            if(read_char_count > n)
            {
                n*=2;
                buffer = realloc(buffer, sizeof(char)*n);
            }
            *(buffer+read_char_count-1) = ch; 
        }
        fclose(fp); 
    }
    else
        buffer = NULL;
   
    *(buffer+read_char_count) = '\0'; 
    return buffer;
}

// checks if text is made up of only whitespaces
int is_text_whitespace(char* text)
{
    while (*text != '\0') 
    {
        if (!isspace(*text))
        {
            return 0;
        }
        text++;
    }
    return 1;

}

// returns the number of occurance of character c in str
int get_char_count(char c, char* str)
{
    int count = 0;
    int i=0;
    while((*str) != '\0')
    {
        if((*str) == c)
            count++;
        str++;
    } 
    return count;
}