#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)
#define MAX_NUM 100

typedef struct person { // ��ȭ��ȣ ����ü ����
	char name[21];	//�̸�
	char phone_number[16];	//�ڵ��� ��ȣ
	char birthday[9];	//����
}person;

void showMenu();	//�޴� ��� �Լ�
void sort_by_name(person* p, int count);//��ȭ��ȣ ���� ������ �̸������� �����ϱ�
void Registration(person* p, int* count);//��ȭ��ȣ ����Լ�
void ShowAll(person* p, int count);//��� ��� ��� �Լ�
void Delete(person* p, int* count);//���� �Լ�
void FindByBirth(person* p, int count); //�� �˻��Ͽ� ã�� �Լ�


int main() {

	person p[MAX_NUM]; // ����ü ����(�ִ� 100)
	int count = 0;

	while (1) {

		showMenu(); //�޴� ��� �Լ�

		int choice;
		scanf("%d", &choice); //1 2 3 4 5�� ����
		getchar();

		switch (choice) {
		case 1:
			Registration(&p, &count); // ��ȭ��ȣ�� ���
			break;
		case 2:
			ShowAll(&p, count); //��ȭ��ȣ�� ���
			break;
		case 3:
			Delete(&p, &count);	//��ȭ��ȣ�� ����
			break;
		case 4:
			FindByBirth(&p, count); // �� �˻� �� ���
			break;
		case 5:	//���α׷� ����
			return 0;
		}
	}

	return 0;
}

void showMenu() {	//�޴� ��� �Լ�
	printf("*****Menu*****\n");
	printf("<1.Registration><2.ShowAll><3.Delete><4.FindByBirth><5.Exit>\n");
	printf("Enter_the_menu_number:");
}

void sort_by_name(person* p, int count) {	//��ȭ��ȣ ���� ������ �̸������� �����ϱ�

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

void Registration(person* p, int* count) { //��ȭ��ȣ ����Լ�
	if (*count >= 100) { //100���̸� overflow��� �� ����
		printf("OVERFLOW\n");
		return;
	}

	printf("Name:");
	gets((p + *count)->name);	//�̸��Է�
	printf("Phone_number:");
	gets((p + *count)->phone_number); //��ȭ��ȣ �Է�
	printf("Birth:");
	gets((p + *count)->birthday);	//���� �Է�

	(*count)++;	//�ο��߰�
	printf("<<%d>>\n", *count);
	sort_by_name(p, *count); //��� �Է��� ��� �̸� ������ ����
}

void ShowAll(person* p, int count) {	//��� ��� ��� �Լ�

	for (person* q = p; q < p + count; q++) {	//�̸������� ����� ��� ���� ���
		printf("%s %s %s\n", q->name, q->phone_number, q->birthday);
	}
}

void Delete(person* p, int* count) { //���� �Լ�

	if (*count == 0) { //����� ������ ���� �� no member��� �� ����
		printf("NO MEMBER\n");
		return;
	}

	char target_name[21];
	printf("Name:");
	gets(target_name);	//������ �̸� �Է�
	for (person* q = p; q < p + *count; q++) {
		if (!strcmp(target_name, q->name)) {	//������ �̸� ã�Ҵٸ�
			for (person* r = q; r < p + *count - 1; r++) {
				*r = *(r + 1); // �� ĭ�� ������ �о� �����ϱ�
			}
			(*count)--; //�ο� �����ϰ� ����
			break;
		}
	}
}


void FindByBirth(person* p, int count) { //�� �˻��Ͽ� ã�� �Լ�

	int target_month;
	printf("Birth:");
	scanf("%d", &target_month); // ã�� �� �Է�

	for (person* q = p; q < p + count; q++) {
		char temp[4] = { 0 };
		int month;
		strncpy(temp, q->birthday + 4, 2);	// 20001106�϶� �� ������ ����Ǿ� �ִ� 5,6 ��° ĭ�� temp�� ����
		month = atoi(temp);	// ���ڷ� �ٲ� �Է��� ã�� ���� ��

		if (month == target_month) //���� ���ٸ� ���� ���
			printf("%s %s %s\n", q->name, q->phone_number, q->birthday);
	}
}