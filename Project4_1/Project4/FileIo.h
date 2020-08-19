/* FileIO.h */
#ifndef FILEIO_H
#define FILEIO_H

int ReadData(FILE *fp, CONTACT **pContacts, int *pMaxCnt, int *pCurCnt);
int WriteData(FILE *fp, const CONTACT *contacts, int maxCnt, int curCnt);

#endif FILEIO_H