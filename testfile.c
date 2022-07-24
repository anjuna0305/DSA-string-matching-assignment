#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int counter = 0;
char alphabet[256];
int alphaT[256];

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

void printLineInt(int *name)
{
    int i = 0;
    while (*(name + i) != '\0')
    {
        printf("%d", *(name + i));
        i++;
    }
    printf("\n");
}

int indexOf(char k, char *arr)
{
    int i = 0;
    while (*(arr + i) != k)
        i++;
    return i;
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

void getAlpha(char *pattern, char *text)
{
    int lenPattern = stringLnegth(pattern);
    int lenText = stringLnegth(text);

    int p = lenPattern + lenText;
    char *concater = malloc((p + 1) * sizeof(char));

    for (int i = 0; i < p; i++)
    {
        if (i < lenPattern)
            *(concater + i) = *(pattern + i);
        else
            *(concater + i) = *(text + (i - lenPattern));
    }
    *(concater + p) = '\0';
    // printLine(concater);

    alphabet[0] = *(concater + 0);
    int n = 1;
    for (int i = 1; i < p; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (*(concater + i) == alphabet[j]) // making alphabet
                break;
            else if (j == n - 1)
            {
                alphabet[n] = *(concater + i);
                n++;
            }
        }
    }
    alphabet[n] = '\0';
}

void getAlphaT(char *pattern)
{
    int lenPat = stringLnegth(pattern);
    int n = 0;
    while (*(alphabet + n) != '\0')
    {
        *(alphaT + n) = lenPat;
        n++;
    }
    // *(alphaT + n) = '\0';

    for (int i = 0; i < lenPat - 1; i++)
        for (int j = 0; j < n; j++)
            if (*(pattern + i) == *(alphabet + j))
                *(alphaT + j) = lenPat - i - 1;
}

int horspool(char *pattern, char *text)
{
    int lenText = stringLnegth(text);
    int lenPattern = stringLnegth(pattern);

    getAlpha(pattern, text);
    getAlphaT(pattern);

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
        pos = pos + alphaT[indexOf(*(text + pos + lenPattern - 1), alphabet)];
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
    FILE *fp = fopen("modules.txt", "r");

    char *text = NULL;
    char *Dtext = NULL;
    char pattern[100];

    printf("enter pattern : ");
    scanf(" %s", pattern);
    capitalize(pattern);

    while (feof(fp) == 0)
    {
        text = lineReader(fp);
        Dtext = duplicater(text);
        capitalize(Dtext);
        if (horspool(pattern, Dtext))
            printLine(text);
    }
    printf("\nCount is : %d\n", counter);
}