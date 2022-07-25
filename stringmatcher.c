#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int counter = 0;
int lenPattern = 0;

char alphabet[256];
int alphaT[256];
char pattern[256];

int stringLnegth(char *str)
{
    int i = 0;
    while (*(str + i) != '\0')
        i++;
    return i;
}

char *duplicater(char *str)
{
    int n = stringLnegth(str);
    char *temp = malloc((n + 1) * sizeof(char));

    for (int i = 0; i < n; i++)
    {
        *(temp + i) = *(str + i);
    }
    *(temp + n) = '\0';
    return temp;
}

void printLine(char *name)
{
    int i = 0;
    while (*(name + i) != '\0')
    {
        printf("%c", *(name + i));
        i++;
    }
    printf("\n");
}

int HpIndexOf(char k)
{
    int i = 0;
    while (*(alphabet + i) != '\0')
        if (*(alphabet + i) == k)
            return *(alphaT + i);
        else
            i++;
    return lenPattern;
}

void capitalize(char *str)
{
    int i = 0;
    while (*(str + i) != '\0')
    {
        *(str + i) = toupper(*(str + i));
        i++;
    }
}

char *lineReader(FILE *fp)
{
    int n = 0;
    char *c = (char *)malloc(1 * sizeof(char));
    *c = fgetc(fp);

    while (*(c + n) != '\n' && *(c + n) != EOF)
    {
        n++;
        c = realloc(c, (n + 1) * sizeof(char));
        *(c + n) = getc(fp);
    }
    *(c + n) = '\0';

    return c;
}

void getAlpha()
{
    int n = 0;
    while (*(pattern + n) != '\0')
    {
        int j = 0;
        int k = 1;
        while (*(alphabet + j) != '\0')
            if (*(pattern + n) == *(alphabet + j))
            {
                k = 0;
                break;
            }
            else
            {
                k = 1;
                j++;
            }
        if (k == 1)
            *(alphabet + j) = *(pattern + n);
        n++;
    }
}

void getAlphaT()
{
    int i = 0;
    while (*(alphabet + i) != '\0')
    {
        *(alphaT + i) = lenPattern;
        for (int j = lenPattern - 2; j >= 0; j--)
            if (*(pattern + j) == *(alphabet + i))
            {
                *(alphaT + i) = lenPattern - j - 1;
                break;
            }
        i++;
    }
}

int horspool(char *text)
{
    int lenText = stringLnegth(text);

    int tempCount = 0;
    int k;
    int pos = 0;
    while (pos <= lenText - lenPattern)
    {
        k = lenPattern - 1;
        while (k >= 0 && *(text + pos + k) == *(pattern + k))
            k = k - 1;
        if (k < 0)
            tempCount++;

        pos = pos + HpIndexOf(*(text + pos + lenPattern - 1));
    }
    free(text);
    counter = counter + tempCount;
    if (tempCount > 0)
        return 1;
    else
        return 0;
}

int main()
{
    FILE *fp = fopen("modules2.txt", "r");

    char *text = NULL;
    char *Dtext = NULL;
    int n;

    printf("enter pattern : ");
    scanf(" %s", pattern);
    capitalize(pattern);
    lenPattern = stringLnegth(pattern);

    getAlpha();
    getAlphaT();

    while (feof(fp) == 0)
    {
        text = lineReader(fp);
        Dtext = duplicater(text);
        capitalize(Dtext);
        if (horspool(Dtext))
            printLine(text);
    }
    printf("\nCount is : %d\n", counter);
}