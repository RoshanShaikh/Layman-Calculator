#include <stdio.h>
#include <ctype.h>
#include <string.h>
char keyword[6][10] = {"ANSWER", "ASSIGN", "RESULT", "DECLARE", "#START", "#END"};
char operation[4][5] = {"ADD", "SUB", "DIV", "MUL"};
int isKeyword(char *str)
{
    for (int i = 0; i < 6; i++)
        if (!strcmp(str, keyword[i]))
            return 1;
    return 0;
}
int isOperation(char *str)
{
    for (int i = 0; i < 4; i++)
        if (!strcmp(str, operation[i]))
            return 1;
    return 0;
}
int isNumber(char *str)
{
    for (int i = 0; i < strlen(str); i++)
        if (!isdigit(str[i]) && str[i] != '.')
            return 0;
    return 1;
}
int isWord(char *str)
{
    for (int i = 0; i < strlen(str); i++)
        if (!isupper(str[i]))
            return 0;
    return 1;
}
int isID(char *str)
{
    if (strlen(str) == 2)
        if (isupper(str[0]))
            if (isdigit(str[1]))
                return 1;
    return 0;
}
int isComment(char *str)
{
    if (strlen(str) >= 2)
        if (str[0] == '*' && str[1] == '*')
            return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage of command : ./(executable file) filename\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Error : file can't open.\n");
        return 2;
    }
    char str[32];
    while (fscanf(fp, "%s", str) != EOF)
    {
        if (str[0] == '.' || str[0] == '?')
            printf("<End of Line>, ");
        else if (isComment(str))
        {
            printf("<Comment : \'%s ", str + 2);
            char tmp;
            while ((tmp = getc(fp)) != '\n')
                printf("%c", tmp);
            printf("\'>, ");
        }
        else if (isKeyword(str))
            printf("<Keyword : \'%s\'>, ", str);
        else if (isOperation(str))
            printf("<Operation : \'%s\'>, ", str);
        else if (isNumber(str))
            printf("<Number : \'%s\'>, ", str);
        else if (isID(str))
            printf("<ID : \'%s\'>, ", str);
        else if (isWord(str))
            printf("<Word : \'%s\'>, ", str);
        else
            printf("<Invalid token : \'%s\'>, ", str);
    }
    printf("END OF FILE.\n\n");
    fclose(fp);
    return 0;
}