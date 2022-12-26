#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)
#define MAX_NUM 100

typedef struct person { // 전화번호 구조체 선언
	char name[21];	//이름
	char phone_number[16];	//핸드폰 번호
	char birthday[9];	//생일
}person;

void showMenu();	//메뉴 출력 함수
void sort_by_name(person* p, int count);//전화번호 들어올 때마다 이름순으로 정렬하기
void Registration(person* p, int* count);//전화번호 등록함수
void ShowAll(person* p, int count);//모든 사람 출력 함수
void Delete(person* p, int* count);//삭제 함수
void FindByBirth(person* p, int count); //월 검색하여 찾는 함수


int main() {

	person p[MAX_NUM]; // 구조체 생성(최대 100)
	int count = 0;

	while (1) {

		showMenu(); //메뉴 출력 함수

		int choice;
		scanf("%d", &choice); //1 2 3 4 5중 선택
		getchar();

		switch (choice) {
		case 1:
			Registration(&p, &count); // 전화번호부 등록
			break;
		case 2:
			ShowAll(&p, count); //전화번호부 출력
			break;
		case 3:
			Delete(&p, &count);	//전화번호부 삭제
			break;
		case 4:
			FindByBirth(&p, count); // 월 검색 후 출력
			break;
		case 5:	//프로그램 종료
			return 0;
		}
	}

	return 0;
}

void showMenu() {	//메뉴 출력 함수
	printf("*****Menu*****\n");
	printf("<1.Registration><2.ShowAll><3.Delete><4.FindByBirth><5.Exit>\n");
	printf("Enter_the_menu_number:");
}

void sort_by_name(person* p, int count) {	//전화번호 들어올 때마다 이름순으로 정렬하기

	for (person* q = p; q < p + count - 1; q++) {
		for (person* r = p; r < p + count - 1; r++) {
			if (strcmp(r->name, (r + 1)->name) > 0) {
				person temp = *r;
				*r = *(r + 1);
				*(r + 1) = temp;
			}
		}
	}
}

void Registration(person* p, int* count) { //전화번호 등록함수
	if (*count >= 100) { //100명이면 overflow출력 후 리턴
		printf("OVERFLOW\n");
		return;
	}

	printf("Name:");
	gets((p + *count)->name);	//이름입력
	printf("Phone_number:");
	gets((p + *count)->phone_number); //전화번호 입력
	printf("Birth:");
	gets((p + *count)->birthday);	//생일 입력

	(*count)++;	//인원추가
	printf("<<%d>>\n", *count);
	sort_by_name(p, *count); //방금 입력한 사람 이름 순으로 정렬
}

void ShowAll(person* p, int count) {	//모든 사람 출력 함수

	for (person* q = p; q < p + count; q++) {	//이름순으로 저장된 목록 전부 출력
		printf("%s %s %s\n", q->name, q->phone_number, q->birthday);
	}
}

void Delete(person* p, int* count) { //삭제 함수

	if (*count == 0) { //저장된 정보가 없을 시 no member출력 후 리턴
		printf("NO MEMBER\n");
		return;
	}

	char target_name[21];
	printf("Name:");
	gets(target_name);	//삭제할 이름 입력
	for (person* q = p; q < p + *count; q++) {
		if (!strcmp(target_name, q->name)) {	//삭제할 이름 찾았다면
			for (person* r = q; r < p + *count - 1; r++) {
				*r = *(r + 1); // 한 칸씩 앞으로 밀어 삭제하기
			}
			(*count)--; //인원 감소하고 종료
			break;
		}
	}
}


void FindByBirth(person* p, int count) { //월 검색하여 찾는 함수

	int target_month;
	printf("Birth:");
	scanf("%d", &target_month); // 찾을 월 입력

	for (person* q = p; q < p + count; q++) {
		char temp[4] = { 0 };
		int month;
		strncpy(temp, q->birthday + 4, 2);	// 20001106일때 월 정보가 저장되어 있는 5,6 번째 칸을 temp에 저장
		month = atoi(temp);	// 숫자로 바꿔 입력한 찾을 월과 비교

		if (month == target_month) //월이 같다면 정보 출력
			printf("%s %s %s\n", q->name, q->phone_number, q->birthday);
	}
}