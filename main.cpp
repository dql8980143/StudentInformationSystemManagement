#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

#define NAMESIZE 32
#define PWDSIZE 32

#define FILENAMESIZE 32

#define STUDENTNAME 20
#define STUDENTINSTITUTE 20
#define STUDENTMAJOR 30
#define STUDENTNUMBER 20

//ѧ����Ϣ���ݽṹ�����Ͷ���
struct Student
{
	char student_name[STUDENTNAME];//����
	char student_institute[STUDENTINSTITUTE];//Ժ��
	char student_major[STUDENTMAJOR];//רҵ
	char student_number[STUDENTNUMBER];//ѧ��
};

//������洢�ṹ�����Ͷ���
typedef struct Lnode
{
	Student data;//������
	struct Lnode *next;//ָ����
}*LinkedList;

//����StudentData.txt���ݣ�����ѧ����Ϣ������ӿ�ʵ��
LinkedList CreateListFromTxt()
{
	LinkedList head=(LinkedList)malloc(sizeof(struct Lnode));//��̬Ϊͷָ������һ��Lnode����С�Ŀռ�
	head->next=NULL;//��ʼ��ͷָ��

	char filename[FILENAMESIZE]="StudentData.txt";
	FILE *fp=fopen(filename,"rb");
	if(!fp)
	{
		puts("open StudentData.txt fail!");
		Sleep(3000);
		exit(1);
	}else
		puts("open StudentData.txt success!");

	//��巨����������
	struct Lnode *r=head;//����βָ��r��ָ��ͷָ��
	struct Lnode *p=NULL;
	struct Student temp;
	
	//��ֹ���һ������ѧ������
	fread(&temp,sizeof(struct Student),1,fp);
	while(!feof(fp))
	{
		if(!strcmp(temp.student_number,"2017207324XXX"))
			continue;
		p=(struct Lnode*)malloc(sizeof(struct Lnode));
		strcpy(p->data.student_name,temp.student_name);
		strcpy(p->data.student_institute,temp.student_institute);
		strcpy(p->data.student_major,temp.student_major);
		strcpy(p->data.student_number,temp.student_number);
		p->next=NULL;
		r->next=p;
		r=p;
		fread(&temp,sizeof(struct Student),1,fp);
	}
	puts("����StudentData.txt���ݣ�����ѧ����Ϣ������ɹ�!");
	fclose(fp);
	return head;
}

//ѧ����Ϣ�������ӡ����ӿ�ʵ��
void DisplayStudentDataLinkedList(LinkedList head)
{
	LinkedList p=head->next;
	while(p)
	{
		puts("------------------------------");
		printf("����:%s\n",p->data.student_name);
		printf("Ժ��:%s\n",p->data.student_institute);
		printf("רҵ:%s\n",p->data.student_major);
		printf("ѧ��:%s\n",p->data.student_number);
		puts("------------------------------");
		p=p->next;
	}
}

//ѧ����Ϣϵͳ���ܲ˵���ӡ����ӿ�ʵ��
void StudentSystemMenu()
{
	char *system_menu[]={"1-ѧ����Ϣ��ѯ��ӡ�������","2-�洢����ѧ����Ϣ����",
		"3-ѧ����Ϣ�޸Ĺ���","4-ѧ����Ϣɾ������","5-��ӡ���ȫ��ѧ����Ϣ����"};

	puts("------ѧ����Ϣϵͳ���ܲ˵�------");
	for(int i=0;i<sizeof(system_menu)/sizeof(char *);i++)
	{
		printf("%s\n",system_menu[i]);
	}
	puts("--------------------------------");
}

//ѧ����Ϣ��ѯ��ӡ����ӿ�ʵ��
void FindStudentInformation(char student_number[])
{
	puts("ִ��ѧ����Ϣ��ѯ��ӡ�������");
	char filename[FILENAMESIZE]="StudentData.txt";
	FILE *fp=fopen(filename,"rb");
	if(!fp)
	{
		puts("open StudentData.txt fail!");
		Sleep(3000);
		exit(2);
	}else
		puts("open StudentData.txt success!");

	struct Student temp;
	fread(&temp,sizeof(struct Student),1,fp);
	bool key=false;
	while(!feof(fp))
	{
		if(!strcmp(student_number,temp.student_number))
		{
			printf("%s��ѧ����Ϣ����:\n",student_number);
			puts("------------------------------");
			printf("����:%s\n",temp.student_name);
			printf("ԺУ:%s\n",temp.student_institute);
			printf("רҵ:%s\n",temp.student_major);
			printf("ѧ��:%s\n",temp.student_number);
			puts("------------------------------");
			key=true;
			break;
		}
		fread(&temp,sizeof(struct Student),1,fp);
	}
	if(!key)
	{
		printf("û�в�ѯ��ѧ��:%s��ѧ����Ϣ!\n",student_number);
	}
	fclose(fp);
	puts("ѧ����Ϣ��ѯ��ӡ�������ִ�н���!");
}

//�洢����ѧ����Ϣ�ӿ�ʵ��
void StoreNewStudentInformation(struct Student student)
{
	puts("ִ�д洢����ѧ����Ϣ����");
	char filename[FILENAMESIZE]="StudentData.txt";
	FILE *fp=fopen(filename,"ab");
	if(!fp)
	{
		puts("open StudentData.txt fail!");
		Sleep(3000);
		exit(3);
	}else
		puts("open StudentData.txt success!");
	fwrite(&student,sizeof(struct Student),1,fp);
	fclose(fp);
	puts("�洢����ѧ����Ϣ����ִ�н���!");
}

//ѧ����Ϣ�޸Ľӿ�ʵ��
void ModificationStudentInformation(char student_number[])
{
	puts("ִ��ѧ����Ϣ�޸Ĺ���");
	char filename[FILENAMESIZE]="StudentData.txt";
	FILE *fp=fopen(filename,"rb+");
	if(!fp)
	{
		puts("open StudentData.txt fail!");
		Sleep(3000);
		exit(4);
	}else
		puts("open StudentData.txt success!");

	struct Student temp;
	fread(&temp,sizeof(struct Student),1,fp);
	bool key=false;
	while(!feof(fp))
	{
		if(!strcmp(student_number,temp.student_number))
		{
			fseek(fp,-sizeof(struct Student),SEEK_CUR);//����ǰָ���ƶ���ǰһ��Student����λ��
			printf("�������޸ĵ�����:");
			scanf("%s",temp.student_name);
			printf("�������޸ĵ�Ժ��:");
			scanf("%s",temp.student_institute);
			printf("�������޸ĵ�רҵ:");
			scanf("%s",temp.student_major);
			strcpy(temp.student_number,student_number);
			fwrite(&temp,sizeof(struct Student),1,fp);
			puts("�޸ĳɹ�!\n");
			key=true;
			break;
		}
		fread(&temp,sizeof(struct Student),1,fp);
	}
	if(!key)
	{
		printf("û�в�ѯ��ѧ��:%s��ѧ����Ϣ!\n",student_number);
	}
	fclose(fp);
	puts("ѧ����Ϣ�޸Ĺ���ִ�н���!");
}

void DelectStudentInformation(char student_number[])
{
	puts("ִ��ѧ����Ϣɾ������");
	char filename[FILENAMESIZE]="StudentData.txt";
	FILE *fp=fopen(filename,"rb+");
	if(!fp)
	{
		puts("open StudentData.txt fail!");
		Sleep(3000);
		exit(5);
	}else
		puts("open StudentData.txt success!");

	struct Student temp;
	bool key=false;
	fread(&temp,sizeof(struct Student),1,fp);
	while(!feof(fp))
	{
		if(!strcmp(student_number,temp.student_number))
		{
			fseek(fp,-sizeof(struct Student),SEEK_CUR);
			strcpy(temp.student_number,"2017207324XXX");
			fwrite(&temp,sizeof(struct Student),1,fp);
			puts("ɾ���ɹ�!\n");
			key=true;
			break;
		}
		fread(&temp,sizeof(struct Student),1,fp);
	}
	if(!key)
	{
		printf("û�в�ѯ��ѧ��:%s��ѧ����Ϣ!\n",student_number);
	}
	fclose(fp);
	puts("ѧ����Ϣɾ������ִ�н���!");
}

//����Ա��������ӿ�ʵ��
void InputPwd(char pwd[])
{
	char ch;
	int i=0;
	printf("���������Ա����:");
	while((ch=getch())!='\r' && i<PWDSIZE-1)//PWDSIZE-1��Ϊ��'\0'
	{
		pwd[i++]=ch;
		putchar('*');
	}
	pwd[i]='\0';
	putchar('\n');
}

//����Ա�˺Ż�����Υ���ַ����ӿ�ʵ��
bool DetectionNameOrPwd(char *p)
{
	bool judge_mark=true;
	while(*p!='\0')
	{
		if(!isalpha(*p) && !isdigit(*p))
		{
			judge_mark=false;
			break;
		}
		p++;
	}
	return judge_mark;
}

//����Ա�˺š�������֤�ӿ�ʵ��
bool VerifyNameAndPwd(char name[],char pwd[])
{
	char name_temp[NAMESIZE];
	char pwd_temp[PWDSIZE];

	char filename[FILENAMESIZE]="RootRecord.txt";
	FILE *fp_root=fopen(filename,"r");
	if(!fp_root)
	{
		puts("open RootRevord.txt fail!");
		Sleep(3000);
		exit(6);
	}else
		puts("open RootRevord.txt success!");
	do
	{
		fscanf(fp_root,"%s\t%s\n",name_temp,pwd_temp);
		if(!strcmp(name,name_temp) && !strcmp(pwd,pwd_temp))
		{
			return true;
		}
	}while(!feof(fp_root));

	return false;
}

//����Ա��½�ӿ�ʵ��
void Login()
{
	char name[NAMESIZE];//����Ա�˺�
	char pwd[PWDSIZE];//����Ա����

	do
	{
		NAME:
			printf("���������Ա�˺�:");
			scanf("%s",name);
			if(!DetectionNameOrPwd(name))
			{
				printf("����Ĺ���Ա�˺ź��зǷ��ַ�\n");
				Sleep(2000);
				goto NAME;
			}
		PWD:
			InputPwd(pwd);
			if(!DetectionNameOrPwd(pwd))
			{
				printf("����Ĺ���Ա���뺬�зǷ��ַ�\n");
				Sleep(2000);
				goto PWD;
			}
		if(VerifyNameAndPwd(name,pwd))
		{
			printf("login success!\n");
			break;
		}else
		{
			printf("login failed!\n");
			continue;
		}
	}while(true);
	system("cls");
}

int main(void)
{
	int key=true;
	int function_number;//���幦�ܱ��
	char student_number[STUDENTNUMBER];
	struct Student student;

	Login();
	LinkedList head=CreateListFromTxt();
	while(key)
	{
		StudentSystemMenu();
		printf("��������Ҫ���еĹ��ܱ��:");
		scanf("%d",&function_number);
		switch(function_number)
		{
		case 1:
			printf("��������Ҫ��ѯ��ѧ��ѧ��:");
			scanf("%s",student_number);
			FindStudentInformation(student_number);
			break;
		case 2:
			printf("����������������:");
			scanf("%s",student.student_name);
			printf("������������ԺУ:");
			scanf("%s",student.student_institute);
			printf("������������רҵ:");
			scanf("%s",student.student_major);
			printf("������������ѧ��:");
			scanf("%s",student.student_number);
			StoreNewStudentInformation(student);
			break;
		case 3:
			printf("��������Ҫ�޸ĵ�ѧ��ѧ��:");
			scanf("%s",student_number);
			ModificationStudentInformation(student_number);
			break;
		case 4:
			printf("��������Ҫɾ����ѧ��ѧ��:");
			scanf("%s",student_number);
			DelectStudentInformation(student_number);
			break;
		case 5:
			DisplayStudentDataLinkedList(head);
			break;
		default:
			puts("�����function_number����!");
		}
		printf("�Ƿ����ִ����������?    0-exit,1-insist:");
		scanf("%d",&key);
		system("cls");
	}
	system("pause");
	return 0;

}