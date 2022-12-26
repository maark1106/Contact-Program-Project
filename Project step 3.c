#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)
#define MAX_NUM 100

typedef struct person { // ��ȭ��ȣ ����ü ����
	char* name;	//�̸�
	char* phone_number;	//�ڵ��� ��ȣ
	char* birthday;	//����
}person;

void showMenu();	//�޴� ��� �Լ�
void sort_by_name(person*** p, int cnt);//��ȭ��ȣ ���� ������ �̸������� �����ϱ�
void Registration(person*** p, int* cnt, int max_num);//��ȭ��ȣ ����Լ�
void ShowAll(person** p, int count);//��� ��� ��� �Լ�
void Delete(person*** p, int* count);//���� �Լ�
void FindByBirth(person** p, int count); //�� �˻��Ͽ� ã�� �Լ�
void person_init(person*** p, int N); //person ����ü �����͹迭 �Ҵ�
void free_all(person*** p, int count, int max_num);// �޸� �Ҵ����� ����ü ������ �迭 �޸� ����
void RegFromFile(person*** p, int* cnt, int max_num); // PHONE_BOOK.txt�� ����� ����� ����ü�� �����ϱ�
void Update(person** p, int cnt);	// ����ü�� ����� ����� PHONE_BOOK.txt�� �����ϱ�

int main() {

	person** p = NULL; // ����ü ����(�ִ� 100)
	int count = 0, max_num;// ���� ��� �� count, �ִ� ��� �� max_num

	printf("Max_num:");
	scanf("%d", &max_num);
	getchar();
	person_init(&p, max_num); // �ִ� ����� ��ŭ ����ü ������ �迭 �ʱ�ȭ

	while (1) {

		showMenu(); //�޴� ��� �Լ�

		int choice;
		scanf("%d", &choice); //1 2 3 4 5�� ����
		getchar();

		switch (choice) {
		case 1:
			Registration(&p, &count, max_num); // ��ȭ��ȣ�� ���
			break;
		case 2:
			ShowAll(p, count); //��ȭ��ȣ�� ���
			break;
		case 3:
			Delete(&p, &count);	//��ȭ��ȣ�� ����
			break;
		case 4:
			FindByBirth(p, count); // �� �˻� �� ���
			break;
		case 5:
			RegFromFile(&p, &count, max_num);
			break;
		case 6:	//���α׷� ����
			Update(p, count);
			free_all(&p, count, max_num); //�Ҵ����� �޸� ��� ����
			return 0;
		}
	}

	return 0;
}

void showMenu() {	//�޴� ��� �Լ�
	printf("*****Menu*****\n");
	printf("<1.Registration><2.ShowAll><3.Delete><4.FindByBirth><5.RegFromFile><6.Exit>\n");
	printf("Enter_the_menu_number:");
}

void sort_by_name(person*** p, int cnt) {	//��ȭ��ȣ ���� ������ �̸������� �����ϱ�

	for (int i = 0; i < cnt - 1; i++) { //�������ķ� �̸� ������ �����ϱ�
		for (int j = 0; j < cnt - 1; j++) {
			if (strcmp((*p)[j]->name, (*p)[j + 1]->name) > 0) {
				person* temp = (*p)[j];
				(*p)[j] = (*p)[j + 1];
				(*p)[j + 1] = temp;
			}
		}
	}
}

void Registration(person*** p, int* cnt, int max_num) {	//�л� ����Լ�

	if (max_num <= *cnt) {	//max_num���� ����� �� á�ٸ� overflow��� �� ����
		printf("OVERFLOW\n");
		return;
	}

	(*p)[*cnt] = (person*)malloc(sizeof(person));	//������ �迭 �޸� �Ҵ�
	if ((*p)[*cnt] == NULL) {
		printf("NULL");
		return -1;
	}
	char temp[100];

	printf("Name:");
	gets(temp);	//�̸� �Է¹ް�
	(*p)[*cnt]->name = (char*)malloc(strlen(temp) + 1); //�̸� + 1��ŭ �Ҵ��ؼ� �̸� ����
	strcpy((*p)[*cnt]->name, temp);

	printf("Phone_number:");
	gets(temp);	//�ڵ��� ��ȣ �Է¹ް�
	(*p)[*cnt]->phone_number = (char*)malloc(strlen(temp) + 1); // ��ȣ + 1��ŭ �Ҵ��ؼ� ��ȣ ����
	strcpy((*p)[*cnt]->phone_number, temp);

	printf("Birth:");
	gets(temp);	//���� �Է¹ް�
	(*p)[*cnt]->birthday = (char*)malloc(strlen(temp) + 1); //���� + 1��ŭ �Ҵ��ؼ� ���� ����
	strcpy((*p)[*cnt]->birthday, temp);
	(*cnt)++;	//��� �� + 1, ���
	printf("<<%d>>\n", *cnt);
	sort_by_name(p, *cnt);	//�̸������� �����ϱ�
}

void ShowAll(person** p, int count) {	//��� ��� ��� �Լ�

	for (int i = 0; i < count; i++) {	//����� ��� �� ��ŭ �̸�, ��ȣ, ���� ���
		printf("%s %s %s\n", p[i]->name, p[i]->phone_number, p[i]->birthday);
	}
}

void Delete(person*** p, int* count) { //���� �Լ�

	if (*count == 0) { //����� ������ ���� �� no member��� �� ����
		printf("NO MEMBER\n");
		return;
	}

	char target_name[21];
	person* del_person = NULL; // ������ �������

	printf("Name:");
	gets(target_name);	//������ �̸� �Է�
	for (int i = 0; i < *count; i++) {
		if (!strcmp(target_name, (*p)[i]->name)) {	//������ �̸� ã�Ҵٸ�
			del_person = (*p)[i]; //���� �� ����� del_person�� �ּҸ� �����ϰ�
			for (int j = i; j < *count - 1; j++) {	// ��ĭ�� ����ֱ�
				(*p)[j] = (*p)[j + 1];
			}
			(*count)--; //�ο� �����ϰ� ����
			break;
		}
	}
	free(del_person->name);	//���� �� ��� �̸� �޸�����
	free(del_person->birthday);	//���� �޸� ����
	free(del_person->phone_number);	// �ڵ��� ��ȣ �޸� ����
	free(del_person);// ���� �� ��� ����
}


void FindByBirth(person** p, int count) { //�� �˻��Ͽ� ã�� �Լ�

	int target_month;
	printf("Birth:");
	scanf("%d", &target_month); // ã�� �� �Է�

	for (int i = 0; i < count; i++) {
		char temp[4] = { 0 };
		int month;
		strncpy(temp, p[i]->birthday + 4, 2);	// 20001106�϶� �� ������ ����Ǿ� �ִ� 5,6 ��° ĭ�� temp�� ����
		month = atoi(temp);	// ���ڷ� �ٲ� �Է��� ã�� ���� ��

		if (month == target_month) //���� ���ٸ� ���� ���
			printf("%s %s %s\n", p[i]->name, p[i]->phone_number, p[i]->birthday);
	}
}

void person_init(person*** p, int N) {	//��� ����ü �ʱ�ȭ �Լ�

	*p = (person**)malloc(sizeof(person*) * N);	//�Է¹��� N��ŭ �޸� �Ҵ�
	if (*p == NULL) {
		printf("-1");
		return -1;
	}
}

void free_all(person*** p, int count, int max_num) { //�Ҵ��� �޸� ��� ����

	for (int i = 0; i < count; i++) {	//����� count ��ŭ(max_count��ŭ ���� �ʴ� ������ ������ �� �޸𸮸� �Ҵ����ָ� delete�� �� �̹� �޸𸮸� ��������� ����)
		free((*p)[i]->name);	//�̸� ���� �޸� ����
		free((*p)[i]->phone_number);	//��ȭ��ȣ ���� �޸� ����
		free((*p)[i]->birthday);	//���ϰ��� �޸� ����
		free((*p)[i]);	//p[i]����ü �޸� ����
	}
	free(*p);	//������ �迭 �޸� ����
}

void RegFromFile(person*** p, int* cnt, int max_num) { //���Ͽ� ����� ��� ����ü�� �����ϱ�

	FILE* fp = fopen("PHONE_BOOK.txt", "r"); // PHONE_BOOK.txt ���� �б���� ����
	char temp[100] = { 0 };

	
	while (1) {

		fgets(temp, 100, fp);//PHONE_BOOK�� ����� �� �� �޾ƿ���
		char temp_name[30], temp_phone[30], temp_birth[30];
		int len = strlen(temp);

		for (char* q = temp; *q != 0; q++) {
			if (*q == ' ' || *q == '\n')
				*q = NULL;
		}
		char* q = temp;
		q = temp;
		strcpy(temp_name, q);//�� ���� �̸� �κ� ����
		q += strlen(q) + 1;
		strcpy(temp_phone, q);//�� ���� ��ȭ��ȣ �κ� ����
		q += strlen(q) + 1;
		strcpy(temp_birth, q);// �� ���� ���� �κ� ����
		(*p)[*cnt] = (person*)malloc(sizeof(person));	//������ �迭 �޸� �Ҵ�
		(*p)[*cnt]->name = (char*)malloc(strlen(temp_name) + 1); //�̸� + 1��ŭ �Ҵ��ؼ� �̸� ����
		strcpy((*p)[*cnt]->name, temp_name);

		(*p)[*cnt]->phone_number = (char*)malloc(strlen(temp_phone) + 1); // ��ȣ + 1��ŭ �Ҵ��ؼ� ��ȣ ����
		strcpy((*p)[*cnt]->phone_number, temp_phone);

		(*p)[*cnt]->birthday = (char*)malloc(strlen(temp_birth) + 1); //���� + 1��ŭ �Ҵ��ؼ� ���� ����
		strcpy((*p)[*cnt]->birthday, temp_birth);
		(*cnt)++;	//��� �� + 1, ���
		sort_by_name(p, *cnt);	//�̸������� �����ϱ�
		if (feof(fp))	//fp�� ������ ���̸� ����
			break;
	}
	fclose(fp);	//���� �ݱ�
}

void Update(person** p, int cnt) { //���α׷� ���� �� ��ȭ��ȣ�� ����ü�� ����� ���� PHONE_BOOK.txt.�� ������Ʈ�ϱ�
	FILE* fp = fopen("PHONE_BOOK.txt", "w");	//PHONE_BOOK.txt. ������� ����
	for (int i = 0; i < cnt; i++) {	// ����ü�� ����� ��� �� ��ŭ
		fputs(p[i]->name, fp);	//�̸� ����
		fputs(" ", fp);
		fputs(p[i]->phone_number, fp);	//��ȭ��ȣ ����
		fputs(" ", fp);
		fputs(p[i]->birthday, fp);	// ���� ����
		if (cnt - 1 == i)
			break;
		fputs("\n", fp);
	}
	fclose(fp);	//���� �ݱ�
}