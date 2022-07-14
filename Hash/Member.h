#define _CRT_SECURE_NO_WARNINGS
#pragma once
#ifndef ___Member
#define ___Member

typedef struct
{
	int no;
	char name[20];

}Member;

#define MEMBER_NO 1
#define MEMBER_NAME 2
int MemberNoCmp(const Member* x, const Member* y);
int MemberNameCmp(const Member* x, const Member* y);
int PrintMember(const Member* x);
int PrintLnMember(const Member* x);

Member ScanMember(const char* messag4e, int sw);
#endif
