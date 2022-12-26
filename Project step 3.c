#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)
#define MAX_NUM 100

typedef struct person { // 전화번호 구조체 선언
	char* name;	//이름
	char* phone_number;	//핸드폰 번호
	char* birthday;	//생일
}person;

void showMenu();	//메뉴 출력 함수
void sort_by_name(person*** p, int cnt);//전화번호 들어올 때마다 이름순으로 정렬하기
void Registration(person*** p, int* cnt, int max_num);//전화번호 등록함수
void ShowAll(person** p, int count);//모든 사람 출력 함수
void Delete(person*** p, int* count);//삭제 함수
void FindByBirth(person** p, int count); //월 검색하여 찾는 함수
void person_init(person*** p, int N); //person 구조체 포인터배열 할당
void free_all(person*** p, int count, int max_num);// 메모리 할당해준 구조체 포인터 배열 메모리 해제
void RegFromFile(person*** p, int* cnt, int max_num); // PHONE_BOOK.txt에 저장된 사람을 구조체에 저장하기
void Update(person** p, int cnt);	// 구조체에 저장된 사람을 PHONE_BOOK.txt에 저장하기

int main() {

	person** p = NULL; // 구조체 생성(최대 100)
	int count = 0, max_num;// 현재 사람 수 count, 최대 사람 수 max_num

	printf("Max_num:");
	scanf("%d", &max_num);
	getchar();
	person_init(&p, max_num); // 최대 사람수 만큼 구조체 포인터 배열 초기화

	while (1) {

		showMenu(); //메뉴 출력 함수

		int choice;
		scanf("%d", &choice); //1 2 3 4 5중 선택
		getchar();

		switch (choice) {
		case 1:
			Registration(&p, &count, max_num); // 전화번호부 등록
			break;
		case 2:
			ShowAll(p, count); //전화번호부 출력
			break;
		case 3:
			Delete(&p, &count);	//전화번호부 삭제
			break;
		case 4:
			FindByBirth(p, count); // 월 검색 후 출력
			break;
		case 5:
			RegFromFile(&p, &count, max_num);
			break;
		case 6:	//프로그램 종료
			Update(p, count);
			free_all(&p, count, max_num); //할당해준 메모리 모두 제거
			return 0;
		}
	}

	return 0;
}

void showMenu() {	//메뉴 출력 함수
	printf("*****Menu*****\n");
	printf("<1.Registration><2.ShowAll><3.Delete><4.FindByBirth><5.RegFromFile><6.Exit>\n");
	printf("Enter_the_menu_number:");
}

void sort_by_name(person*** p, int cnt) {	//전화번호 들어올 때마다 이름순으로 정렬하기

	for (int i = 0; i < cnt - 1; i++) { //버블정렬로 이름 순으로 정렬하기
		for (int j = 0; j < cnt - 1; j++) {
			if (strcmp((*p)[j]->name, (*p)[j + 1]->name) > 0) {
				person* temp = (*p)[j];
				(*p)[j] = (*p)[j + 1];
				(*p)[j + 1] = temp;
			}
		}
	}
}

void Registration(person*** p, int* cnt, int max_num) {	//학생 등록함수

	if (max_num <= *cnt) {	//max_num까지 사람이 꽉 찼다면 overflow출력 후 종료
		printf("OVERFLOW\n");
		return;
	}

	(*p)[*cnt] = (person*)malloc(sizeof(person));	//포인터 배열 메모리 할당
	if ((*p)[*cnt] == NULL) {
		printf("NULL");
		return -1;
	}
	char temp[100];

	printf("Name:");
	gets(temp);	//이름 입력받고
	(*p)[*cnt]->name = (char*)malloc(strlen(temp) + 1); //이름 + 1만큼 할당해서 이름 저장
	strcpy((*p)[*cnt]->name, temp);

	printf("Phone_number:");
	gets(temp);	//핸드폰 번호 입력받고
	(*p)[*cnt]->phone_number = (char*)malloc(strlen(temp) + 1); // 번호 + 1만큼 할당해서 번호 저장
	strcpy((*p)[*cnt]->phone_number, temp);

	printf("Birth:");
	gets(temp);	//생일 입력받고
	(*p)[*cnt]->birthday = (char*)malloc(strlen(temp) + 1); //생일 + 1만큼 할당해서 생일 저장
	strcpy((*p)[*cnt]->birthday, temp);
	(*cnt)++;	//사람 수 + 1, 출력
	printf("<<%d>>\n", *cnt);
	sort_by_name(p, *cnt);	//이름순으로 정렬하기
}

void ShowAll(person** p, int count) {	//모든 사람 출력 함수

	for (int i = 0; i < count; i++) {	//저장된 사람 수 만큼 이름, 번호, 생일 출력
		printf("%s %s %s\n", p[i]->name, p[i]->phone_number, p[i]->birthday);
	}
}

void Delete(person*** p, int* count) { //삭제 함수

	if (*count == 0) { //저장된 정보가 없을 시 no member출력 후 리턴
		printf("NO MEMBER\n");
		return;
	}

	char target_name[21];
	person* del_person = NULL; // 삭제할 사람저장

	printf("Name:");
	gets(target_name);	//삭제할 이름 입력
	for (int i = 0; i < *count; i++) {
		if (!strcmp(target_name, (*p)[i]->name)) {	//삭제할 이름 찾았다면
			del_person = (*p)[i]; //삭제 할 사람을 del_person에 주소를 저장하고
			for (int j = i; j < *count - 1; j++) {	// 한칸씩 당겨주기
				(*p)[j] = (*p)[j + 1];
			}
			(*count)--; //인원 감소하고 종료
			break;
		}
	}
	free(del_person->name);	//삭제 할 사람 이름 메모리해제
	free(del_person->birthday);	//생일 메모리 해제
	free(del_person->phone_number);	// 핸드폰 번호 메모리 해제
	free(del_person);// 삭제 할 사람 삭제
}


void FindByBirth(person** p, int count) { //월 검색하여 찾는 함수

	int target_month;
	printf("Birth:");
	scanf("%d", &target_month); // 찾을 월 입력

	for (int i = 0; i < count; i++) {
		char temp[4] = { 0 };
		int month;
		strncpy(temp, p[i]->birthday + 4, 2);	// 20001106일때 월 정보가 저장되어 있는 5,6 번째 칸을 temp에 저장
		month = atoi(temp);	// 숫자로 바꿔 입력한 찾을 월과 비교

		if (month == target_month) //월이 같다면 정보 출력
			printf("%s %s %s\n", p[i]->name, p[i]->phone_number, p[i]->birthday);
	}
}

void person_init(person*** p, int N) {	//사람 구조체 초기화 함수

	*p = (person**)malloc(sizeof(person*) * N);	//입력받은 N만큼 메모리 할당
	if (*p == NULL) {
		printf("-1");
		return -1;
	}
}

void free_all(person*** p, int count, int max_num) { //할당한 메모리 모두 해제

	for (int i = 0; i < count; i++) {	//저장된 count 만큼(max_count만큼 하지 않는 이유는 생성할 때 메모리를 할당해주며 delete할 때 이미 메모리를 해제해줬기 때문)
		free((*p)[i]->name);	//이름 공간 메모리 해제
		free((*p)[i]->phone_number);	//전화번호 공간 메모리 해제
		free((*p)[i]->birthday);	//생일공간 메모리 해제
		free((*p)[i]);	//p[i]구조체 메모리 해제
	}
	free(*p);	//포인터 배열 메모리 해제
}

void RegFromFile(person*** p, int* cnt, int max_num) { //파일에 저장된 사람 구조체에 저장하기

	FILE* fp = fopen("PHONE_BOOK.txt", "r"); // PHONE_BOOK.txt 파일 읽기모드로 열기
	char temp[100] = { 0 };

	
	while (1) {

		fgets(temp, 100, fp);//PHONE_BOOK에 저장된 한 줄 받아오기
		char temp_name[30], temp_phone[30], temp_birth[30];
		int len = strlen(temp);

		for (char* q = temp; *q != 0; q++) {
			if (*q == ' ' || *q == '\n')
				*q = NULL;
		}
		char* q = temp;
		q = temp;
		strcpy(temp_name, q);//한 줄의 이름 부분 저장
		q += strlen(q) + 1;
		strcpy(temp_phone, q);//한 줄의 전화번호 부분 저장
		q += strlen(q) + 1;
		strcpy(temp_birth, q);// 한 줄의 생일 부분 저장
		(*p)[*cnt] = (person*)malloc(sizeof(person));	//포인터 배열 메모리 할당
		(*p)[*cnt]->name = (char*)malloc(strlen(temp_name) + 1); //이름 + 1만큼 할당해서 이름 저장
		strcpy((*p)[*cnt]->name, temp_name);

		(*p)[*cnt]->phone_number = (char*)malloc(strlen(temp_phone) + 1); // 번호 + 1만큼 할당해서 번호 저장
		strcpy((*p)[*cnt]->phone_number, temp_phone);

		(*p)[*cnt]->birthday = (char*)malloc(strlen(temp_birth) + 1); //생일 + 1만큼 할당해서 생일 저장
		strcpy((*p)[*cnt]->birthday, temp_birth);
		(*cnt)++;	//사람 수 + 1, 출력
		sort_by_name(p, *cnt);	//이름순으로 정렬하기
		if (feof(fp))	//fp가 파일의 끝이면 종료
			break;
	}
	fclose(fp);	//파일 닫기
}

void Update(person** p, int cnt) { //프로그램 종료 시 전화번호부 구조체에 저장된 내용 PHONE_BOOK.txt.에 업데이트하기
	FILE* fp = fopen("PHONE_BOOK.txt", "w");	//PHONE_BOOK.txt. 쓰기모드로 열기
	for (int i = 0; i < cnt; i++) {	// 구조체에 저장된 사람 수 만큼
		fputs(p[i]->name, fp);	//이름 저장
		fputs(" ", fp);
		fputs(p[i]->phone_number, fp);	//전화번호 저장
		fputs(" ", fp);
		fputs(p[i]->birthday, fp);	// 생일 저장
		if (cnt - 1 == i)
			break;
		fputs("\n", fp);
	}
	fclose(fp);	//파일 닫기
}