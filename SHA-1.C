#include<stdio.h>
#include <stdlib.h>
#include <string.h>


char plainText[64];
unsigned char plain[64];
unsigned long w[80];
int choice;

int ReadFile(char* Text) {
	char path[100] = { 0x0 };
	printf("�������ļ���·��:");
	gets_s(path);
	FILE* fp1 = fopen(path, "r");
	if (fp1 == NULL) {
		printf("���ܴ��ļ�!");
		return -1;
	}
	fseek(fp1, 0, SEEK_END);
	int len = ftell(fp1);
	char* data = (char*)malloc(sizeof(char) * len + 1);
	if (data == NULL) {
		printf("�����ڴ�ռ�ʧ��");
		return -2;
	}
	rewind(fp1);
	fread(data, sizeof(char), len, fp1);
	data[len] = '\0';
	memcpy(Text, data, len);
	fclose(fp1);
}

void CreatW()
{
	int i, j; unsigned long temp, temp1;
	for (i = 0; i < 16; i++)
	{
		j = 4 * i;
		w[i] = ((long)plain[j]) << 24 | ((long)plain[1 + j]) << 16 | ((long)plain[2 + j]) << 8 | ((long)plain[3 + j]) << 0;

	}
	for (i = 16; i < 80; i++)
	{
		w[i] = w[i - 16] ^ w[i - 14] ^ w[i - 8] ^ w[i - 3];
		temp = w[i] << 1;
		temp1 = w[i] >> 31;
		w[i] = temp | temp1;

	}
}
void Padding() {
	int len = strlen(plainText);
	memcpy(plain, plainText, len);
	plain[len] = 0x80;
	memset(plain + len + 1, 0x0, 62);
	plain[63] = len * 8;
}
void Process() {
	unsigned long H0 = 0x67452301, H1 = 0xefcdab89, H2 = 0x98badcfe, H3 = 0x10325476, H4 = 0xc3d2e1f0;
	unsigned long  A, B, C, D, E,temp, temp1,k, f; int i, flag;
	A = H0; B = H1; C = H2; D = H3; E = H4;
	for (i = 0; i < 80; i++)//���ܹ��̸������ġ��������д�ĺÿ�����
	{
		flag = i / 20;
		switch (flag)
		{
		case 0: k = 0x5a827999; f = (B & C) | (~B & D); break;
		case 1: k = 0x6ed9eba1; f = B ^ C ^ D; break;
		case 2: k = 0x8f1bbcdc; f = (B & C) | (B & D) | (C & D); break;
		case 3: k = 0xca62c1d6; f = B ^ C ^ D; break;
		}
		temp1 = (A<<5) | (A>>27);
		temp = temp1 + f + E + w[i] + k;
		E = D;D = C;
		C = (B<<30) | (B>>2);
		B = A;
		A = temp;
	}
	H0 = H0 + A;
	H1 = H1 + B;
	H2 = H2 + C;
	H3 = H3 + D;
	H4 = H4 + E;
	printf("SHA-1 CODE:%lx%lx%lx%lx%lx\n", H0, H1, H2, H3, H4);
}
void UI() {
	printf("=========SHA-1�㷨==========\n");
	printf("=========1����������=========\n");
	printf("=========2���ļ�����=========\n");	
	printf("=========0���˳�    =========\n");
	printf("============================\n");
	printf("��������Ҫ��ѡ��\n");
	printf("���ѡ���ǣ�");
	scanf_s("%d", &choice);
	getchar();
}
void Sha1() {
	while (true)
	{
		UI();
		if (choice != 1 && choice != 2 && choice != 0) { continue; }
		if (choice == 0) { break; }
		if (choice == 1) {
			printf("������Ҫ����SHA-1���ַ�����\n");
			gets_s(plainText);
		}
		else if (choice == 2) { ReadFile(plainText); }
		Padding();
		CreatW();
		Process();
	}
}
int main()
{
	Sha1();
	//getchar();
	return 0;
}