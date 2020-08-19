/* Contact.h */
#ifndef CONTACT_H
#define CONTACT_H

#define MAX_STR 32

enum ringtone { old_phone, piano, marimba, harp };

typedef struct contacts {
	char name[MAX_STR];   	 // �̸�
	char phone[MAX_STR];	     // ��ȭ��ȣ
	enum ringtone ring;  // ���Ҹ�
} CONTACT;

CONTACT* Initialize(int totalCnt);
int AddContactInfo(CONTACT *contacts, int maxCnt, int *pCurCnt);
void ListByName(CONTACT *contacts, int cnt);
void PrintAllContacts(const CONTACT *contact, int cnt);
int CompareByName(const void* e1, const void* e2);
CONTACT* ExpandContacts(CONTACT *contacts, int *pMaxCnt);
void FindContact(CONTACT *contacts, int *pCurCnt);
void PhoneContact(CONTACT* contacts, int* pCurCnt);

#endif