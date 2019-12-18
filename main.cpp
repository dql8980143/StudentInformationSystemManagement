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

//学生信息数据结构体类型定义
struct Student
{
	char student_name[STUDENTNAME];//姓名
	char student_institute[STUDENTINSTITUTE];//院部
	char student_major[STUDENTMAJOR];//专业
	char student_number[STUDENTNUMBER];//学号
};

//单链表存储结构体类型定义
typedef struct Lnode
{
	Student data;//数据域
	struct Lnode *next;//指针域
}*LinkedList;

//导入StudentData.txt数据，建立学生信息单链表接口实现
LinkedList CreateListFromTxt()
{
	LinkedList head=(LinkedList)malloc(sizeof(struct Lnode));//动态为头指针申请一块Lnode结点大小的空间
	head->next=NULL;//初始化头指针

	char filename[FILENAMESIZE]="StudentData.txt";
	FILE *fp=fopen(filename,"rb");
	if(!fp)
	{
		puts("open StudentData.txt fail!");
		Sleep(3000);
		exit(1);
	}else
		puts("open StudentData.txt success!");

	//后插法创建单链表
	struct Lnode *r=head;//定义尾指针r并指向头指针
	struct Lnode *p=NULL;
	struct Student temp;
	
	//防止多读一边最后的学生数据
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
	puts("导入StudentData.txt数据，建立学生信息单链表成功!");
	fclose(fp);
	return head;
}

//学生信息单链表打印输出接口实现
void DisplayStudentDataLinkedList(LinkedList head)
{
	LinkedList p=head->next;
	while(p)
	{
		puts("------------------------------");
		printf("姓名:%s\n",p->data.student_name);
		printf("院部:%s\n",p->data.student_institute);
		printf("专业:%s\n",p->data.student_major);
		printf("学号:%s\n",p->data.student_number);
		puts("------------------------------");
		p=p->next;
	}
}

//学生信息系统功能菜单打印输出接口实现
void StudentSystemMenu()
{
	char *system_menu[]={"1-学生信息查询打印输出功能","2-存储新增学生信息功能",
		"3-学生信息修改功能","4-学生信息删除功能","5-打印输出全部学生信息功能"};

	puts("------学生信息系统功能菜单------");
	for(int i=0;i<sizeof(system_menu)/sizeof(char *);i++)
	{
		printf("%s\n",system_menu[i]);
	}
	puts("--------------------------------");
}

//学生信息查询打印输出接口实现
void FindStudentInformation(char student_number[])
{
	puts("执行学生信息查询打印输出功能");
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
			printf("%s的学生信息如下:\n",student_number);
			puts("------------------------------");
			printf("姓名:%s\n",temp.student_name);
			printf("院校:%s\n",temp.student_institute);
			printf("专业:%s\n",temp.student_major);
			printf("学号:%s\n",temp.student_number);
			puts("------------------------------");
			key=true;
			break;
		}
		fread(&temp,sizeof(struct Student),1,fp);
	}
	if(!key)
	{
		printf("没有查询到学号:%s的学生信息!\n",student_number);
	}
	fclose(fp);
	puts("学生信息查询打印输出功能执行结束!");
}

//存储新增学生信息接口实现
void StoreNewStudentInformation(struct Student student)
{
	puts("执行存储新增学生信息功能");
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
	puts("存储新增学生信息功能执行结束!");
}

//学生信息修改接口实现
void ModificationStudentInformation(char student_number[])
{
	puts("执行学生信息修改功能");
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
			fseek(fp,-sizeof(struct Student),SEEK_CUR);//将当前指针移动至前一个Student数据位置
			printf("请输入修改的姓名:");
			scanf("%s",temp.student_name);
			printf("请输入修改的院部:");
			scanf("%s",temp.student_institute);
			printf("请输入修改的专业:");
			scanf("%s",temp.student_major);
			strcpy(temp.student_number,student_number);
			fwrite(&temp,sizeof(struct Student),1,fp);
			puts("修改成功!\n");
			key=true;
			break;
		}
		fread(&temp,sizeof(struct Student),1,fp);
	}
	if(!key)
	{
		printf("没有查询到学号:%s的学生信息!\n",student_number);
	}
	fclose(fp);
	puts("学生信息修改功能执行结束!");
}

void DelectStudentInformation(char student_number[])
{
	puts("执行学生信息删除功能");
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
			puts("删除成功!\n");
			key=true;
			break;
		}
		fread(&temp,sizeof(struct Student),1,fp);
	}
	if(!key)
	{
		printf("没有查询到学号:%s的学生信息!\n",student_number);
	}
	fclose(fp);
	puts("学生信息删除功能执行结束!");
}

//管理员密码输入接口实现
void InputPwd(char pwd[])
{
	char ch;
	int i=0;
	printf("请输入管理员密码:");
	while((ch=getch())!='\r' && i<PWDSIZE-1)//PWDSIZE-1因为有'\0'
	{
		pwd[i++]=ch;
		putchar('*');
	}
	pwd[i]='\0';
	putchar('\n');
}

//管理员账号或密码违规字符检测接口实现
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

//管理员账号、密码验证接口实现
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

//管理员登陆接口实现
void Login()
{
	char name[NAMESIZE];//管理员账号
	char pwd[PWDSIZE];//管理员密码

	do
	{
		NAME:
			printf("请输入管理员账号:");
			scanf("%s",name);
			if(!DetectionNameOrPwd(name))
			{
				printf("输入的管理员账号含有非法字符\n");
				Sleep(2000);
				goto NAME;
			}
		PWD:
			InputPwd(pwd);
			if(!DetectionNameOrPwd(pwd))
			{
				printf("输入的管理员密码含有非法字符\n");
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
	int function_number;//定义功能编号
	char student_number[STUDENTNUMBER];
	struct Student student;

	Login();
	LinkedList head=CreateListFromTxt();
	while(key)
	{
		StudentSystemMenu();
		printf("请输入你要运行的功能编号:");
		scanf("%d",&function_number);
		switch(function_number)
		{
		case 1:
			printf("请输入你要查询的学生学号:");
			scanf("%s",student_number);
			FindStudentInformation(student_number);
			break;
		case 2:
			printf("请输入新生的姓名:");
			scanf("%s",student.student_name);
			printf("请输入新生的院校:");
			scanf("%s",student.student_institute);
			printf("请输入新生的专业:");
			scanf("%s",student.student_major);
			printf("请输入新生的学号:");
			scanf("%s",student.student_number);
			StoreNewStudentInformation(student);
			break;
		case 3:
			printf("请输入你要修改的学生学号:");
			scanf("%s",student_number);
			ModificationStudentInformation(student_number);
			break;
		case 4:
			printf("请输入你要删除的学生学号:");
			scanf("%s",student_number);
			DelectStudentInformation(student_number);
			break;
		case 5:
			DisplayStudentDataLinkedList(head);
			break;
		default:
			puts("输入的function_number错误!");
		}
		printf("是否继续执行其他功能?    0-exit,1-insist:");
		scanf("%d",&key);
		system("cls");
	}
	system("pause");
	return 0;

}