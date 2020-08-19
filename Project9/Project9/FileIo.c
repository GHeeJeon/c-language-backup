/* FileIO.c */
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include "Contact.h"
#include "FileIO.h"

int ReadData(FILE *fp, CONTACT **pContacts, int *pMaxCnt, int *pCurCnt)
{
    int res;

    res = fread(pMaxCnt, sizeof(int), 1, fp);
    if( res == 0 )
        return 0;

    res = fread(pCurCnt, sizeof(int), 1, fp);
    if( res == 0 )
        return 0;

    *pContacts = malloc(sizeof(CONTACT) * *pMaxCnt);
    res = fread(*pContacts, sizeof(CONTACT), *pCurCnt, fp);
    if( res < *pCurCnt )
        return 0;

    return 1;
}

int WriteData(FILE *fp, const CONTACT *contacts, int maxCnt, int curCnt)
{
    fwrite(&maxCnt, sizeof(int), 1, fp);
    fwrite(&curCnt, sizeof(int), 1, fp);
    fwrite(contacts, sizeof(CONTACT), curCnt, fp);

    return 0;
}