#include "bank.h"
/********************************链表函数定义******************************************/
void DeleteList(List L)//链表删除函数
{
	Position P,q;
	P = L->next;           //取链表头后的所有结点
	L->next = NULL;        //链表头指向空结点
	while (P != NULL);       //依次释放链表头后所有结点的空间
	{
		q=P;	
		P = P->next;
		free(q);
	}
}
void DeleteList1(List1 L)
{
	Position1 p,q;
	p = L->next;           //取链表头后的所有结点
	L->next = NULL;        //链表头指向空结点
	while (P != NULL);       //依次释放链表头后所有结点的空间
	{
		q=p;
		p = p->next;
		free(q);
	}
}
List MakeEmpty(List L)//空链表创建函数
{
	if (L)                                      //相当于 if(L!=NULL) ,即指针L指向的空间不为空
		DeleteList(L);                       //删除原先链表
	L = (List)malloc(sizeof(struct Client));   //创建新的空链表
	if (!L)                                     //相当于 if(L==NULL) ,即指针L指向的空间为空
	{
		printf("创建失败,内存不足!!!");        //创建失败，提示内存不足
		char buf[1024]={0};
		fgets(buf,1024,stdin);
		system("clear");                       //暂停屏幕显示
		return NULL;                           //返回上一级菜单
	}
	L->next = NULL;                              //Next指针指向空
	return L;                                  //返回链表头
}
List1 MakeEmpty1(List1 L)
{
	if (L)                                               //相当于 if(L!=NULL) ,即指针L指向的空间不为空
		DeleteList1(L);                                //删除原先链表
	L = (List1)malloc(sizeof(struct Records));             //创建新的空链表
	if (!L)                                              //相当于 if(L==NULL) ,即指针L指向的空间为空
	{
		printf("创建失败,内存不足!!!");                  //创建失败，提示内存不足
		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");                                 //暂停屏幕显示
		return NULL;                                     //返回上一级菜单
	}
	L->next = NULL;                                        //Next指针指向空
	return L;                                           //返回链表头
}
void TravelList(List L)//遍历链表函数
{
	Position p = L->next;
	printf("\n客户信息如下:\n");
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	printf("账号\t\t\t姓名\t\t电话\t\t办卡地址\t余额\t\t状态                  \n");
	while (p)
	{
		printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
		printf("%-20s\t%-10s\t%-11s\t%-10s\t%-.2lf\t\t%-5s\n", p->num, p->name, p->tel, p->loc, p->money,p->sd);
		p = p->next;
	}
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- - - - -\n");
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}
void TravelList1(List1 L)
{
	printf("\n\t\t\t\t收支记录如下:\n");
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	printf("账号\t\t\t姓名\t\t操作日期\t\t存取款                  \n");
	Position1 p = L->next;
	while (p)
	{
		printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
		printf("%-20s\t%-10s\t%-18s\t%-.2lf          \n", p->num, p->name, p->time, p->rmb);
		p = p->next;
	}
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - - - - - -\n");
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}

/********************************文件函数定义******************************************/
List Load(List L)//初始化函数
{
	FILE *fp;
	Position a;
	int num = 0;
	fp = fopen("Customer.txt", "r+");
	if (fp == NULL)
	{
		printf("\n\t\t无法打开文件或文件不存在\n");         //提示错误
		printf("\n\t\t正在尝试创建新文件....\n");
		fp = fopen("Customer.txt", "w");                     //创建客户信息文件
		if ((fp = fopen("Customer.txt", "r+")) == NULL)
		{
			printf("\t\t文件创建失败!!!\n");
			char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");                                //暂停屏幕显示
			return NULL;
		}
	}
	fp = fopen("Customer.txt", "r+");                           //以可读可写的方式打开"Customer.txt"文本文件
	L = MakeEmpty(L);                                          //创建链表，以便存储文本文件中的信息
	while (1)
	{
		a = (List)malloc(sizeof(struct Client));                    //创建新结点
		if (a == NULL)
		{
			printf("\n\t\t文件信息读取失败，系统内存不足！");
			char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");                                 //暂停屏幕显示
			return NULL;
		}
		if (fscanf(fp, "%s %s %s %s %s %s %lf %s %d %d %s", a->num, a->ID, a->name, a->tel, a->password, a->loc, &a->money, a->time, &a->type, &a->point, a->sd)<0)
			break;                                        //将客户信息录入文件
		a->next = L->next;                                   //头插法
		L->next = a;
		num++;
	}
	printf("\n\t\t客户信息读取完成，目前共有%d名客户\n", num);
	fclose(fp);
	return L;
}
List1 Load1(List1 L)
{
	FILE *fp;
	Position1 a;
	int num = 0;
	fp = fopen("Record.txt", "r+");
	if (fp == NULL)
	{
		printf("\n\t\t无法打开文件或文件不存在\n");         //提示错误
		printf("\n\t\t正在尝试创建新文件....\n");
		fp = fopen("Record.txt", "w");                     //创建客户信息文件
		if ((fp = fopen("Record.txt", "r+")) == NULL)
		{
			printf("\t\t文件创建失败!!!\n");
			char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
			return NULL;                                //暂停屏幕显示
		}
	}
	fp = fopen("Record.txt", "r+");                           //以只读的方式打开"Record.txt"文本文件
	L = MakeEmpty1(L);                                          //创建链表，以便存储文本文件中的信息
	while (1)
	{
		a = (List1)malloc(sizeof(struct Records));                    //创建新结点
		if (a == NULL)
		{
			printf("\n\t\t文件信息读取失败，系统内存不足！");
			char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");                                 //暂停屏幕显示
			return NULL;
		}
		if (fscanf(fp, "%s %s %s %s %lf %s\n", a->num, a->name, a->time, a->ID, &a->rmb, a->sd)<0)
			break;                                        //将客户收支记录录入文件
		a->next = L->next;                                   //头插法
		L->next = a;
		num++;
}
	fclose(fp);
	printf("\n\t\t操作记录信息读取完成，目前共有%d条操作记录\n", num);
	return L;
}
void Save(List L)//信息保存函数
{
	FILE *fp;
	Position p = L;
	if ((fp = fopen("D:\\Customer.txt", "w+")) == NULL)         //可读可写的方式打开文件 
	{
		printf("打开文件失败\n");
		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
		return;
	}
	fp = fopen("Customer.txt", "w+");
	//fprintf(fp,"账号\t身份证\t姓名\t电话\t密码\t办卡地址\t\t 余额\t时间\t办卡类型\t信用分\t 状态\n");
	while (p->next != NULL)
	{
		p = p->next;
		if (fprintf(fp, "%s\t %s\t %s\t %s\t %s\t %s\t\t %.2lf\t %s\t %d\t %d\t %s\n", p->num, p->ID, p->name, p->tel, p->password, p->loc, p->money, p->time, p->type, p->point, p->sd)<0)
			break;                           //将信息写入文件 
	}
	printf("\n\t\t客户信息录入成功！\n");
	fclose(fp);
	return;
}
void Save1(List1 L)
{
	FILE *fp;
	Position1 p = L;
	if ((fp = fopen("D:\\Record.txt", "w+")) == NULL)
	{
		printf("打开文件失败\n");
		exit(0);
	}
	fp = fopen("Record.txt", "w+");
	for (; p->next != NULL;)
	{
		p = p->next;
		if (fprintf(fp, "%s\t %s\t %s\t %s\t %.2lf\t %s\n", p->num, p->name, p->time, p->ID, p->rmb, p->sd)<0)
			break;                           //将信息写入文件 
	}
	printf("\n\t\t客户收支记录信息录入成功！\n");
	fclose(fp);
}
void MakeFileEmpty()//清空文件函数
{
	FILE *fp;
	fp = fopen("Customer.txt", "w");       //新建一个文件，并将之前的文件删除
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		exit(0);
	}
	printf("信息清空成功!\n"); 
	char buf[1024]={0};
	fgets(buf,1024,stdin);
	system("clear");
	fclose(fp);
}
void MakeFileEmpty1()
{
	FILE *fp;
	fp = fopen("Record.txt", "w");       //新建一个文件，并将之前的文件删除
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		exit(0);
	}
	printf("信息清空成功!\n");
	char buf[1024]={0};
	fgets(buf,1024,stdin);
	system("clear");
	fclose(fp);
}

/********************************菜单函数定义******************************************/
void Choose()//访客选择身份 @
{
	printf("\n\t\t**         选择您的身份          **");
	printf("\n\t\t**                               **");
	printf("\n\t\t**          1.管理员             **");
	printf("\n\t\t**          2.客户               **");
	printf("\n\t\t**          0.退出系统           **");
	printf("\n\t\t**                               **");
	printf("\n\n\t\t\t请输入您的选择:");
}
void MainMeun1(List L, List1 L1)//管理员主菜单
{
	printf("\033c");
	printf("\n\t\t**            主菜单                  **");//
	printf("\n\t\t**                                    **");//
	printf("\n\t\t**         1.注册账户                 **");//
	printf("\n\t\t**         2.注销账户                 **");//
	printf("\n\t\t**         3.查询客户信息             **");//
	printf("\n\t\t**         4.查询客户操作记录         **");//
	printf("\n\t\t**         5.修改客户信息             **");//
	printf("\n\t\t**         6.信息查看                 **");//
	printf("\n\t\t**         7.客户后台操作             **");//
	printf("\n\t\t**         8.重置系统                 **");//
	printf("\n\t\t**         9.账户解锁，挂失，取消挂失 **");//
	printf("\n\t\t**         0.返回上一层               **");//
	printf("\n\t\t**                                    **");
	printf("\n\n\t\t\t请输入您的选择:");
	int x;
	scanf("%d", &x);
while (1)
	{
		printf("\033c");                      //实现清屏
		x = Testl(x, 0, 9);
		fflush(stdin);                      //清除键盘缓冲区
		switch (x)
		{
		case 1:  printf("\033c");  Add(L);    printf("\033c");  MainMeun1(L, L1);          //注册账户
		case 2:  printf("\033c");  Delete(L, L1);    printf("\033c");  MainMeun1(L, L1);    //注销账户
		case 3:  printf("\033c");  ViewMeun(L, L1);      printf("\033c");  MainMeun1(L, L1);                          //查询客户信息
		case 4:  printf("\033c");  RecordMeun(L1);      return;                         //查询客户存取款信息
		case 5:  printf("\033c");  ModMeun(L, L1);         return;                       //修改客户信息
		case 6:  printf("\033c");  OrderMeun(L, L1);     return;                         //信息查看
		case 7:  {printf("\033c"); 
			Position p = Logon(L); MainMeun2(p->num, L, L1); MainMeun1(L, L1);} break;     //客户存取款,修改密码等操作
		case 8:  printf("\033c");  getchar();printf("是否需要重置系统，回复'Y'/'N'\n");
			if (getchar() == 'Y')
			{
				MakeFileEmpty(), MakeFileEmpty1(); printf("\033c"); return;
			}//重置系统
			MainMeun1(L, L1);
		case 9:  printf("\033c");  jiesuo(L, L1); MainMeun1(L, L1); break;                     //返回上一层
		case 0:  printf("\033c");  main();   break;                     //返回上一层
		}
		return;
	}
}
void MainMeun2(char num[], List L, List1 L1)//客户主菜单
{
	//char a[20]; 
	Position p = L->next;
	Position1 p1 = L1->next;
	char sj[20]="00", b[20] = "00";
	while (p1 != NULL && strcmp(num, p1->num) != 0)
		p1 = p1->next;
	while (p != NULL && strcmp(num, p->num) != 0)
		p = p->next;
	printf("\n\t\t**           主菜单              **");
	printf("\n\t\t**                               **");
	if (p->type == 1)
		printf("\n\t\t**         1.存取款              **");//
	else
		printf("\n\t\t**         1.消费与还款          **");//
	printf("\n\t\t**         2.操作记录查询        **");//
	printf("\n\t\t**         3.个人信息查询        **");//
	printf("\n\t\t**         4.修改密码            **");//
	printf("\n\t\t**         5.退出客户系统        **");//
	printf("\n\t\t**                               **");
	if(p->type==2){
		printf("\n\t\t最迟还款日期:%s",p->time);
		printf("\n\t\t信用分:%d",p->point);
	}
	printf("\n\n\t\t当前操作时间为:\n");	
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);//获取系统时间
	printf("\t\t%4d/%02d/%02d-%02d.%02d.%02d\n", 1900 + timeinfo->tm_year, 1 + timeinfo->tm_mon,
		timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	sprintf(sj,"%4d/%02d/%02d-%02d.%02d.%02d",1900 + timeinfo->tm_year, 1 + timeinfo->tm_mon,
		timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	if (p->money<0 && strcmp(p->time,sj)<=0)//超时未还款信用分为负 
	{
		p->point = -1;
		//p->money = 1.1*p->money;
	}
	if (p->money>0)
	{
		strcpy(p->time, b);
		p->point=0; 
		Save(L);
	}
	printf("\n\n\t\t\t请输入您的选择:");
	int x;
	scanf("%d", &x);
	getchar();
	while (1)
	{
		printf("\033c");                      //实现清屏
		x = Testl(x, 1, 5);
		fflush(stdin);                 //清除键盘缓冲区
		switch (x)
		{
		case 1:  printf("\033c");  Add1(sj, p, L, L1);   printf("\033c"); MainMeun2(p->num, L, L1);                //存款
		case 2:  printf("\033c");  if (p1 == NULL)
		{
			printf("\n无操作记录： ");
			char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
			return;
		}
				 ViewNum1(num, L1);  printf("\033c"); MainMeun2(p->num, L, L1);                //操作记录查询
		case 3:  printf("\033c");  ViewNum(num, L);    printf("\033c"); MainMeun2(p->num, L, L1);               //个人信息查询
		case 4:  printf("\033c");  ModPassword(p, L);  printf("\033c"); MainMeun2(p->num, L, L1);              //修改密码
		case 5:  printf("\033c");  main();  break;                          //返回上一层
		}
		return;
	}
}
void OrderMeun(List L, List1 L1)//信息查看菜单
{
	printf("\n\t\t**           信息查看             **");
	printf("\n\t\t**                                **");
	printf("\n\t\t**    1.按账号排序(客户信息)      **");//@	
    printf("\n\t\t**    2.按余额排序(客户信息)      **");//@
	printf("\n\t\t**    3.按账号排序(操作记录)      **");//@
	printf("\n\t\t**    4.按时间排序(操作记录)      **");//@
	printf("\n\t\t**    5.返回上一级菜单            **");//
	printf("\n\t\t**                                **");
	printf("\n\n\t\t\t请输入您的选择:");
	int x;
	scanf("%d", &x);
	while (1)
	{
		printf("\033c");                      //实现清屏
		x = Testl(x, 1, 5);
		fflush(stdin);                      //清除键盘缓冲区
		switch (x)
		{
		case 1:  printf("\033c");  L = SortNum(L);      printf("\033c");  OrderMeun(L, L1);              //按账号排序
		case 2:  printf("\033c");  L = SortMoney(L);    printf("\033c");  OrderMeun(L, L1);           //按余额排序
		case 3:  printf("\033c");  L1 = SortNum1(L1);   printf("\033c");  OrderMeun(L, L1);                 //按账号排序
		case 4:  printf("\033c");  L1 = SortTime1(L1);  printf("\033c");  OrderMeun(L, L1);                //按时间排序
		case 5:  printf("\033c");  MainMeun1(L, L1);                                    //返回上一层
		}
	}
}
void ViewMeun(List L, List1 L1)//查询客户信息菜单
{
	printf("\n\t\t**        查询客户信息            **");
	printf("\n\t\t**                                **");
	printf("\n\t\t**        1.按账号查询            **");//@
	printf("\n\t\t**        2.按身份证查询          **");//@
	printf("\n\t\t**        3.按姓名查询            **");//@
	printf("\n\t\t**        4.按电话查询            **");//@
	printf("\n\t\t**        5.按电话和姓名查询      **");//@
	printf("\n\t\t**        6.返回上一层            **");//@
	printf("\n\t\t**                                **");
	printf("\n\n\t\t\t请输入您的选择:");
	int x;
	scanf("%d", &x);
	getchar();
	while (1)
	{
		printf("\033c");                      //实现清屏
		x = Testl(x, 1, 6);
		fflush(stdin);                      //清除键盘缓冲区
		switch (x)
		{
		case 1:  printf("\033c");  char num[30]; printf("\n请输入所要查询的账号:  ");
			gets(num); ViewNum(num, L);      printf("\033c");  ViewMeun(L, L1);   break;   //按账号查询
		case 2:  printf("\033c");  char ID[20]; printf("\n请输入需要查询的身份证： ");
			gets(ID); ViewID(ID, L);         printf("\033c");  ViewMeun(L, L1);   break;   //按身份证号查询
		case 3:  printf("\033c");  char name[10]; printf("\n请输入需要查询的姓名： ");
			gets(name); ViewName(name, L);  printf("\033c");  ViewMeun(L, L1);    break;  //按姓名查询
		case 4:  printf("\033c");  char tel[20]; printf("\n请输入需要查询的电话： ");
			gets(tel); ViewTel(tel, L);      printf("\033c");  ViewMeun(L, L1);   break;   //按电话查询
		case 5:  printf("\033c"); ViewCom(L);  MainMeun1(L, L1);    break;                   //按电话和姓名查询
		case 6:  printf("\033c");  MainMeun1(L, L1); break;                   //返回上一层
		}
	}
}
void RecordMeun(List1 L1)//查询客户存取款记录菜单
{
	printf("\n\t\t**       查询客户操作记录         **");
	printf("\n\t\t**                                **");
	printf("\n\t\t**        1.按账号查询            **");//@
	printf("\n\t\t**        2.按姓名查询            **");//@
	printf("\n\t\t**        3.按账号和操作时间查询  **");//@
	printf("\n\t\t**        4.返回上一层            **");//@
	printf("\n\t\t**                                **");
	printf("\n\n\t\t\t请输入您的选择:");
	int x;
	List L = NULL;
	L = Load(L);
	char num[30], name[10];
	scanf("%d", &x);
	while (1)
	{
		printf("\033c");                      //实现清屏
		x = Testl(x, 1, 4);
		fflush(stdin);                      //清除键盘缓冲区
		switch (x)
		{
		case 1:  printf("\033c");getchar();  printf("\n请输入所要查询的账号:  "); gets(num); ViewNum1(num, L1);
			printf("\033c");  RecordMeun(L1);
		case 2:  printf("\033c");getchar();  printf("\n请输入所要查询的姓名:  "); gets(name); ViewName1(name, L1);
			printf("\033c");  RecordMeun(L1);
		case 3:  printf("\033c");getchar();  ViewCom1(L1);  MainMeun1(L, L1);    break;                   //按账号和操作时间查询
		case 4:  printf("\033c");  MainMeun1(L, L1);                                    //返回上一层
		}
	}
}
void ModMeun(List L, List1 L1)//修改菜单
{
	printf("\n\t\t**        修改客户信息            **");
	printf("\n\t\t**                                **");
	printf("\n\t\t**        1.按账号查询修改        **");//
	printf("\n\t\t**        2.按姓名查询修改        **");//
	printf("\n\t\t**        3.按电话查询修改        **");//
	printf("\n\t\t**        4.按身份证号查询修改    **");//
	printf("\n\t\t**        5.返回上一层            **");//
	printf("\n\t\t**                                **");
	printf("\n\n\t\t\t请输入您的选择:");
	int x;

	char name[10], tel[20], ID[20], num[30], a[20];
	Position p = L->next;
	scanf("%d", &x);
	getchar();
	while (1)
	{
		printf("\033c");                      //实现清屏
		x = Testl(x, 1, 5);
		fflush(stdin);                      //清除键盘缓冲区
		switch (x)
		{
		case 1:  printf("\033c");  printf("\n请输入查询修改的账号: ");     gets(num);      //按账号查询
			while (p)  //判断P的Next指针是否为空，且P的下一个结点的客户电话是否为查找账号
			{
				if (strcmp(num, p->num) == 0)
				{
					PrintClient(p);
					printf("\n是否是您想修改的账户：回复'Y'/'N'\n");
					if (getchar() == 'Y')
					{
						strcpy(a, p->password);
						Mimayincan(a);
						ModMeun1(p, L, L1);
					}
					else
					{
						printf("未找到您想要修改的账号~\n");
						char buf[1024]={0};
						fgets(buf,1024,stdin);
						system("clear"); printf("\033c");  ModMeun(L, L1);
					}
				}
				p = p->next;
				if (!p)
				{
					printf("\n该账号不存在： ");
					char buf[1024]={0};
					fgets(buf,1024,stdin);
					system("clear"); printf("\033c");  ModMeun(L, L1);
				}
			}
			printf("\033c");  ModMeun(L, L1);
		case 2:  printf("\033c");  printf("\n请输入查询修改的姓名: ");     gets(name);      //按姓名查询
			CircleName(name, p, L, L1);                printf("\033c");  ModMeun(L, L1);
		case 3:  printf("\033c");  printf("\n请输入查询修改的电话: ");     gets(tel);       //按电话查询
			CircleTel(tel, p, L, L1);                  printf("\033c");  ModMeun(L, L1);
		case 4:  printf("\033c"); printf("\n请输入查询修改的身份证号: "); gets(ID);        //按身份证查询
			CircleID(ID, p, L, L1);                   printf("\033c");  ModMeun(L, L1);
		case 5:  printf("\033c");  MainMeun1(L, L1);                             //返回上一层
		}
	}
}
void ModMeun1(Position p, List L, List1 L1)//修改客户信息菜单
{
	printf("\n\t\t**        修改客户信息            **");
	printf("\n\t\t**                                **");
	printf("\n\t\t**        1.修改姓名              **");//
	printf("\n\t\t**        2.修改密码              **");//
	printf("\n\t\t**        3.修改电话              **");//
	printf("\n\t\t**        4.返回上一层            **");//
	printf("\n\t\t**                                **");
	printf("\n\n\t\t\t请输入您的选择:");
	int x;
	scanf("%d", &x);
	while (1)
	{
		printf("\033c");                      //实现清屏
		x = Testl(x, 1, 4);
		fflush(stdin);                      //清除键盘缓冲区
		switch (x)
		{
		case 1:  printf("\033c");  ModName(p, L, L1);   printf("\033c");  ModMeun1(p, L, L1);                //修改姓名
		case 2:  printf("\033c");  ModPassword(p, L);  printf("\033c");  ModMeun1(p, L, L1);                //修改密码
		case 3:  printf("\033c");  ModTel(p, L);       printf("\033c");  ModMeun1(p, L, L1);                //修改电话
		case 4:  printf("\033c");  ModMeun(L, L1);                            //返回上一层
		}
	}
}

/********************************客户管理函数声明********************************************/
//信息录入函数与删除
void Add(List L)//客户信息
{
	getchar();
	Position p,q = L->next;
	char num[20], a[10] = "Normal", b[20] = "00";
	int t;
	printf("\n请输入所要创建的账号:  ");                         //提示输入账号
	gets(num);
	while (q != NULL && strcmp(num, q->num) != 0)
		q = q->next;
	if (q)
	{
		printf("\n该账号已创建\n");
		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
		return;
		
	}
	p = (Position)malloc(sizeof(struct Client));                   //创建新结点
	if (p == NULL)
	{
		printf("\n添加失败,内存不足!!!\n\n");                    //添加失败，提示内存不足
		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");                                         //暂停屏幕显示
		return;                                                  //返回上一级菜单
	}
	strcpy(p->num, num);                                                  //保存账号
	printf("\n请输入您需要办理的卡类型(1.储蓄卡2.信用卡)： ");
	
	scanf("%d", &t);
	t = Testl(t, 1, 2);
	p->type = t;
	printf("\n请输入客户身份证号:  ");                               //保存身份证号
	scanf("%s", p->ID);
	printf("\n请输入客户电话:  ");                                         //保存电话
	scanf("%s", p->tel);
	printf("\n请输入客户的姓名： ");                             //保存姓名
	scanf("%s", p->name);
	printf("\n请输入客户密码： ");                               //保存密码
	scanf("%s", p->password);
	printf("\n请输入客户办卡地址:  ");                           //保存办卡地址
	scanf("%s", p->loc);
	p->money = 0.00;                                             //余额
	p->point = 0;                                                //信用积分
	strcpy(p->time, b);                                           //还款日期
	strcpy(p->sd, a);                                             //状态
	p->next = L->next;                                             //将结点p用头插法插入到链表中
	L->next = p;
	Save(L); 
	getchar();                                                    //调用 信息保存函数
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
	return;
}
void Add1(char sj[], Position p, List L, List1 L1)//收支记录
{
	char a[10] = "Normal", b[20] = "00";
	Position1 p1;
	p1 = (Position1)malloc(sizeof(struct Records));                   //创建新结点
	if (p == NULL)
	{
		printf("\n添加失败,内存不足!!!\n\n");                    //添加失败，提示内存不足
		char buf[1024]={0};
		fgets(buf,1024,stdin);
		system("clear");                                         //暂停屏幕显示
	}
	strcpy(p1->num, p->num);
	strcpy(p1->name, p->name);
	strcpy(p1->ID, p->ID);
	strcpy(p1->time, sj);
	if (p->type == 1)//储蓄卡
	{
		printf("\n您的当前余额为:%lf\n",p->money); 
		printf("\n请输入存取款金额(带符号)： ");                       //保存存取款
		scanf("%lf", &p1->rmb);
		getchar();
		if (p->money + p1->rmb < 0)
		{
			printf("\n余额不足！");
			char buf[1024]={0};
			fgets(buf,1024,stdin);
			system("clear"); return;
		}
		p->money = p->money + p1->rmb;
	}
	else if (p->type == 2)//信用卡
	{
		printf("\n您的当前余额为:%lf\n",p->money); 
		printf("\n请输入消费或还款金额(带符号)");
		scanf("%lf", &p1->rmb);
		//getchar();
		if (p1->rmb<0)//消费金额超过透支额度
		{
			if (p1->rmb+p->money >	-5000 && p->point == 0)//透支额度不够时
			{
				printf("\n您本月还可以消费%.2lf元", 5000 + p->money+p1->rmb);
				char buf[1024]={0};
				fgets(buf,1024,stdin);
				system("clear"); //return;
			}
			else if (p->point==-1)
			{
				printf("\n您的信用分不够，请先还款哦！您需要还款%.2lf元。", p->money);
				char buf[1024]={0};
				fgets(buf,1024,stdin);
				system("clear"); return;
			}
			
			else if(p->money==-5000){
				getchar();
				printf("\n您的消费达到本月的最大消费额度，本月已无法再消费，若需要再次消费，请及时还款\n"); 
				char buf[1024]={0};
				fgets(buf,1024,stdin);
				system("clear"); return; 
			}
			else if(p->money+p1->rmb<-5000){
				getchar();
				printf("您本月最多还可以消费%.2lf元",5000+p->money);
				char buf[1024]={0};
				fgets(buf,1024,stdin);
				system("clear"); return;
			}
			if (p->money+p1->rmb<0 && p->point == 0)
			{
				time_t rawtime;
				struct tm * timeinfo;
				time(&rawtime);
				timeinfo = localtime(&rawtime);//获取系统时间
				int year=timeinfo->tm_year+1900;
				int mon =timeinfo->tm_mon+1;
				if(mon==12)
				{
					printf("\n\t\t请在%4d/%02d/%02d-%02d.%02d.%02d之前还款\n", year+1, mon-11,
						timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
					sprintf(p->time,"%4d/%02d/%02d-%02d.%02d.%02d",year+1, mon-11,
					timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
				}                                                                      //还款日期，加一个月 
				else{
					printf("\n\t\t请在%4d/%02d/%02d-%02d.%02d.%02d之前还款\n", 1900 + timeinfo->tm_year, 1 + timeinfo->tm_mon + 1,
			    		timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
			    	sprintf(p->time,"%4d/%02d/%02d-%02d.%02d.%02d",1900 + timeinfo->tm_year, 1 + timeinfo->tm_mon,
					timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
				}                                                                     //还款日期，加一个月，提醒还款
				getchar();
			}
			
		}
		else if(p1->rmb>0 && p1->rmb+p->money<=0)
		{
			getchar();
			printf("您还需还款%lf元\n",-p->money-p1->rmb);
			char buf[1024]={0};
			fgets(buf,1024,stdin);
			system("clear");
		}
		else if(p1->rmb>0 && p1->rmb+p->money>0)
		{
			getchar();
			printf("您的当前余额为：%lf元\n",p->money+p1->rmb);
			char buf[1024]={0};
			fgets(buf,1024,stdin);
			system("clear");
		}
		if (p1->rmb+p->money >= 0)//违约后还款信用分恢复
		{
			p->point = 0;
			strcpy(p->time, b);
		}
		p->money = p->money + p1->rmb;
	}
	p1->next = L1->next;                                             //将结点p用头插法插入到链表中
	L1->next = p1;
	strcpy(p1->sd, a);
	Save1(L1);                                                     //调用 信息保存函数
	Save(L);
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
	return;
}
void Delete(List L, List1 L1)//客户信息
{
	getchar();
	Position  p = L->next,   m=L ,a;
	Position1  n=L1,b=NULL,p1=L1,n1=L1,n2=L1;
	char num[20];
	printf("\n请输入想注销的账号: ");
	gets(num); //按账号删除
	while (p != NULL&&strcmp(p->num, num) != 0){
		p = p->next;
	}
	if (!p)
	{
		printf("\n不存在该账户哦~\n");
		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear"); return;
	}
	PrintClient(p);      //调用职工信息打印函数
	fflush(stdin);                   //清除键盘缓冲区
	if (p->money > 0)
	{
		printf("\n请先取出账户余额！");
		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
		return;
	}
	if(p->money<0)
	{
		printf("\n请先还款！");
		char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
		return;
	}
	printf("\n是否确认要删除？回复'Y'/'N'\n");
	while(p )
	{
		if(m->next==p)	
		break;
		m=m->next;
	}
	if (getchar() == 'Y')
	{
		fflush(stdin);
		Mimayincan(p->password);
		a = p;
		m->next = a->next;
		free(a);
		while (n2 )  //判断P的Next指针是否为空，且P的下一个结点的客户姓名是否为查找账号
		{
			while(n!=NULL && strcmp(num,n->num) !=0 ) //判断n是否为查找账号 
			n=n->next;
			if(n==NULL)
				break;
			while(n1)                                //查找n的前一位地址 
			{		
				if(n1->next==n)
				break;
				n1=n1->next;				
			}	
				b = n;                              //释放查找的账号 
				n1->next = b->next;
				free(b);
			n=L1;
			n2=n2->next;
		
		}
		printf("\n删除成功!!!\n\n");
		Save(L);                     //调用信息保存函数
		Save1(L1);
	}
	getchar();
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}
//查询函数
void ViewNum(char num[], List L)//账号
{
	Position p = L->next;
	int f = 0;
	while (p)
	{
		if (strcmp(p->num, num)==0)
		{
			PrintClient(p);
			f = 1;
		}
		p = p->next;
	}
	if (f == 0)             //判断是否存在该客户
		printf("\n没有匹配的信息");
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}
void ViewName(char name[], List L)//姓名
{
	int f = 0;
	Position p = L->next;
	while (p)
	{
		if (strcmp(p->name, name)==0)
		{
			PrintClient(p);
			f = 1;
		}
		p = p->next;
	}
	if (f == 0)             //判断是否存在该客户
		printf("\n没有匹配的信息");
	char buf[1024]={0};
	fgets(buf,1024,stdin);
	system("clear");
}
void ViewTel(char tel[], List L)//电话
{
	Position p = L->next;
	int f = 0;
	while (p)
	{
		if (strcmp(p->tel, tel)==0)
		{
			PrintClient(p);
			f = 1;
		}
		p = p->next;
	}
	if (f == 0)             //判断是否存在该客户
		printf("\n没有匹配的信息");
		char buf[1024]={0};
		fgets(buf,1024,stdin);
		system("clear");
}
void ViewID(char ID[], List L)//身份证号
{ 
	Position p = L->next;
	int f = 0;
	while (p)
	{
		if (strcmp(p->ID, ID)==0)
		{
			PrintClient(p);
			f = 1;
		}
		p = p->next;
	}
	if (f == 0)             //判断是否存在该客户
		printf("\n没有匹配的信息");
	
		char buf[1024]={0};
		fgets(buf,1024,stdin);
		system("clear");
}
void ViewCom(List L)//综合查询
{
	Position p = L->next;
	char name[10], tel[12];
	printf("输入姓名: \n");
	gets(name);
	printf("请输入电话: \n");
	gets(tel);
	int f = 0;
	while (p)
	{
		if (strcmp(p->name, name) == 0 && strcmp(p->tel, tel) == 0)
		{
			PrintClient(p);
			f = 1;
		}
		p = p->next;
	}
	if (f == 0)             //判断是否存在该客户
		printf("\n没有匹配的信息");
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}
//收支记录查询
void ViewName1(char name[], List1 L)//按姓名查询
{
	char buf[1024]={0};
	int f = 0;
	Position1 p = L->next;
	while (p)  //判断P的Next指针是否为空，且P的下一个结点的客户账号是否为查找账号
	{
		if (strcmp(p->name, name)==0 )
		{
			PrintRecords(p);
			f = 1;
		}
		p = p->next;
	}
	if (f == 0)              //判断是否存在该客户
		printf("\n没有匹配的信息");	
		fgets(buf,1024,stdin);
		system("clear");
}
void ViewNum1(char num[], List1 L)//按账号查询
{
	int f = 0;
	Position1 p = L->next;
	while (p)  //判断P的Next指针是否为空，且P的下一个结点的客户账号是否为查找账号
	{
		if (strcmp(p->num, num)==0)
		{
			PrintRecords(p);
			f = 1;
		}
		p = p->next;
	}
	if (f == 0)
		printf("\n没有匹配的信息");
	char buf[1024]={0};
	fgets(buf,1024,stdin);
	system("clear");
}
void ViewCom1(List1 L)//综合查询
{
	Position1 p = L->next;
	char num[30], time[18];
	printf("输入账号: \n");
	gets(num);
	printf("请输入操作时间: \n");
	gets(time);
	int f = 0;
	while (p)
	{
		if (strcmp(p->num, num) == 0 && strcmp(p->time, time) == 0)
		{
			PrintRecords(p);
			f = 1;
		}
		p = p->next;
	}
	if (f == 0)             //判断是否存在该客户
		printf("\n没有匹配的信息");
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}
//排序函数(升序
List SortMoney(List L)//余额(客户信息
{
	getchar();
	Position a, b, p = L->next;
	int i, j, num = 0;
	while (p)
	{
		num++;
		p = p->next;
	}
	for (j = 0; j < num - 1; j++)
	{
		a = L->next;
		b = a->next;
		p = L;
		for (i = 0; i < num - 1 - j; i++)
		{ 
			if(a->money>b->money)	
            {
				a->next = b->next;
				p->next = b;
				b->next = a;
			}
			p = p->next;
			a = p->next;
			b = a->next;
		}
	}
	Save(L);
	TravelList(L);
	return L;
}
List SortNum(List L)//账号(客户信息
{
	getchar();
	Position a, b, p = L->next;
	int i, j, num = 0;
	while (p)
	{
		num++;
		p = p->next;
	}
	for (j = 0; j < num - 1; j++)
	{
		p = L;
		a = L->next;
		b = a->next;
		for (i = 0; i < num - 1 - j; i++)
		{
			if (strcmp(a->num, b->num)>0)
			{
				a->next = b->next;
				p->next = b;
				b->next = a;
			}
			p = p->next;
			a = p->next;
			b = a->next;
		}
	}
	Save(L);
	TravelList(L);
	return L;
}
List1 SortNum1(List1 L)//按账号排序显示收支记录
{
	getchar();
	Position1 a, b, p = L->next;
	int i, j, num = 0;
	while (p)
	{
		num++;
		p = p->next;
	}
	for (j = 0; j < num - 1; j++)
	{
		p = L;
		a = L->next;
		b = a->next;
		for (i = 0; i < num - 1 - j; i++)
		{
			if (strcmp(a->num, b->num)>0)
			{
				a->next = b->next;
				p->next = b;
				b->next = a;
			}
			p = p->next;
			a = p->next;
			b = a->next;
		}
	}
	Save1(L);
	TravelList1(L);
	return L;
}
List1 SortTime1(List1 L)//按收支记录时间排序 
{
	getchar();
	Position1 a, b, p = L->next;
	int i, j, num = 0;
	while (p)
	{
		num++;
		p = p->next;
	}
	for (j = 0; j < num - 1; j++)
	{
		a = L->next;
		b = a->next;
		p = L;
		for (i = 0; i < num - 1 - j; i++)
		{
			if (strcmp(a->time, b->time)>0)
			{
				a->next = b->next;
				p->next = b;
				b->next = a;
			}
			p = p->next;
			a = p->next;
			b = a->next;
		}
	}
	Save1(L);
	TravelList1(L);
	return L;
}
//查询修改
void CircleName(char name[], Position p, List L, List1 L1)//姓名
{
	printf("\033c");
	while (p)  //判断P的Next指针是否为空，且P的下一个结点的客户电话是否为查找账号
	{
		if (strcmp(name, p->name) == 0)
		{
			PrintClient(p);
			printf("\n是否是您想修改的账户：回复'Y'/'N'\n");
			if (getchar() == 'Y')
			{
				char a[20];
				strcpy(a, p->password);
				Mimayincan(a);
				ModMeun1(p, L, L1);
			}
			else if (getchar() == 'N')
				CircleName(name, p->next, L, L1);
		}
		p = p->next;
		if (!p)
		{
			printf("\n该账号不存在： ");
			char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
		}
	}
}
void CircleID(char ID[], Position p, List L, List1 L1)//身份证
{
	printf("\033c");
	while (p)  //判断P的Next指针是否为空，且P的下一个结点的客户电话是否为查找账号
	{
		if (strcmp(ID, p->ID) == 0)
		{
			PrintClient(p);
			printf("\n是否是您想修改的账户：回复'Y'/'N'\n");
			if (getchar() == 'Y')
			{
				char a[20];
				strcpy(a, p->password);
				Mimayincan(a);
				ModMeun1(p, L, L1);
			}
			else if (getchar() == 'N')
				CircleID(ID, p->next, L, L1);
		}
		p = p->next;
		if (!p)
		{
			printf("\n该账号不存在： ");
			char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
		}
	}
}
void CircleTel(char tel[], Position p, List L, List1 L1)//电话
{
	printf("\033c");
	while (p)  //判断P的Next指针是否为空，且P的下一个结点的客户电话是否为查找账号
	{
		if (strcmp(tel, p->tel) == 0)
		{
			PrintClient(p);
			printf("\n是否是您想修改的账户：回复'Y'/'N'\n");
			if (getchar() == 'Y')
			{
				char a[20];
				strcpy(a, p->password);
				Mimayincan(a);
				ModMeun1(p, L, L1);
			}
			else if (getchar() == 'N')
				CircleTel(tel, p->next, L, L1);
		}
		p = p->next;
		if (!p)
		{
			printf("\n该账号不存在： ");
			char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
		}
	}
}
//修改函数
void ModName(Position p, List L, List1 L1)//姓名
{
	getchar(); 
	char name[10];
	Position1 p1 = L1->next;
	Position p2 = L->next;
	printf("\n请输入新的姓名: ");
	gets(name);
	while (p2)
	{
		if (strcmp(p->ID, p2->ID) == 0)
		
{
			strcpy(p2->name, name);
			Save(L);
		}
		p2 = p2->next;
	}
	while (p1)
	{
		if (strcmp(p->ID, p1->ID) == 0)
		{
			strcpy(p1->name, name);
			Save1(L1);
		}
		p1 = p1->next;
	}
	char buf[1024]={0};
	fgets(buf,1024,stdin);
	system("clear");
}
void ModTel(Position p, List L)//电话
{
	getchar();
	char tel[20];
	printf("\n请输入新的电话号:  ");
	gets(tel);
	strcpy(p->tel, tel);
	Save(L);         //调用信息保存函数
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}
void ModPassword(Position p, List L)//密码
{
	getchar();
	char a[20];
	printf("\n请输入新的密码: ");
	gets(a);
	strcpy(p->password, a);
	Save(L);
	char buf[1024]={0};
		fgets(buf,1024,stdin);
	system("clear");
}

/********************************功能函数定义******************************************/
Position Logon(List L)//登录函数
{
	getchar();
	char buf[1024]={0};
	char password[20], num[30], a[10] = "Normal", b[10] = "Lock", c[10] = "Loss";//密码，账号
	int f;
	printf("\n\t\t请输入您的账号: ");
	gets(num);
	Position p = L->next;
	while (p != NULL && strcmp(num, p->num) != 0)
		p = p->next;
	if (!p)
	{
		printf("\n\t\t该账号不存在！");
		fgets(buf,1024,stdin);
		system("clear");
		return NULL;
	}
	if (strcmp(p->sd, b) == 0)
	{
		printf("\n\t\t该账号已被锁定，请到柜台解锁！");
		fgets(buf,1024,stdin);
		system("clear");
		return NULL;
	}
	if (strcmp(p->sd, c) == 0)
	{
		printf("\n\t\t该账号以被挂失，请到柜台取消挂失！");
		fgets(buf,1024,stdin);
		system("clear");
		return NULL;
	}
	strcpy(password, p->password);
	if (strcmp(p->sd, a) == 0)
	f = Mimayincan(password);
	if (f == 1)
		return p;
	else
	{
		printf("\n\t\t该账号已被锁定，请到柜台解锁！\n");
		strcpy(p->sd, b); Save(L);
		fgets(buf,1024,stdin);
		system("clear");
		return NULL;
	}
}
int Mimayincan(char a[])//密码隐藏函数//退格不删*
{
	getchar();
	int i, j = 0, flag = 0;
	char b[20];
	int n = strlen(a);
	while (j < 3)
	{
		printf("\n\t\t请输入您的密码(少于20位)：");
		for (i = 0; i < n; i++)
		{
			system("stty -echo");
			scanf("%c",&b[i]);
			system("stty echo");
			if (i>0 && b[i] == '\b')
			{
				i = i - 2;
				printf("\b");
			}
			/*else
				printf("*");*/
		}
		b[i] = '\0';
		j++;
		if (strncmp(a, b, n) == 0)
			return 1;
	else if (j < 3){ 
			printf("\n\t\t密码错误，请重新输入\n\a");
			getchar(); 
			} 
		else if (flag == 0)
		{
			printf("\n\t\t抱歉，该账号暂时已被锁定\n");
			getchar();
			return 0;
		}
	}
	return 1;
}
void PrintClient(Position p)//客户信息打印函数
{
	printf("\n客户信息如下:\n");
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	printf("账号\t\t\t姓名\t\t电话\t\t办卡地址\t\t余额\t\t\t状态\n");
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	printf("%-20s\t%-10s\t%-11s\t%-20s\t%-20.2lf    %-5s\n", p->num, p->name, p->tel, p->loc, p->money, p->sd);
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
}
void PrintRecords(Position1 p)//收支记录打印函数
{
	printf("\n\t\t\t\t收支记录如下:\n");
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - - - - - -\n");
	printf("账号\t\t\t姓名\t\t操作日期\t\t存取款                  \n");
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - - - - - -\n");
	printf("%-20s\t%-10s\t%-18s\t%-.2lf          \n", p->num, p->name, p->time, p->rmb);
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - - - - - -\n");
}
int Testl(int a, int b, int c)//菜单输入检测函数
{
	while (a<b || a>c)
	{
		fflush(stdin);                           //清除键盘缓冲区
		printf("\n\t\t\t输入错误，请重新输入: ");
		scanf("%d", &a);
	}
	return a;
}
void jiesuo(List L, List1 L1)
{
	getchar();
	char buf[1024]={0};
	char ID[20], num[30], a[10] = "Normal", c[10] = "Loss";
	int x;
	Position p = L->next;
	Position1 p1 = L1->next;
	printf("\n\t\t请输入您要选择的操作：1.解锁账号 2.账号挂失 3.取消挂失 0.返回上一层");
	printf("\n\n\t\t请输入您的选择:\n");
	while (1)
	{
		scanf("%d", &x);
		x = Testl(x, 0, 3);
		fflush(stdin); 
		getchar();                     //清除键盘缓冲区
		switch (x)
		{
		case 1:  printf("\n\t\t请输入您需要解锁的账号：");
			gets(num);
			while (p != NULL && strcmp(num, p->num) != 0)
				p = p->next;
			if (!p)
			{
				printf("\n\t\t该账号不存在");
				fgets(buf,1024,stdin);
				system("clear"); return;
			}
			else if (strcmp(p->sd, a) == 0)
			{
				printf("\n\t\t该账号未被锁定");
				fgets(buf,1024,stdin);
				system("clear"); return;
			}
			printf("\n\t\t请输入您的身份证号： ");//确认身份信息
			gets(ID);
			if (strcmp(ID, p->ID) == 0)
			{
				strcpy(p->sd, a); Save(L);
				ModPassword(p, L);
			}
			while (p1)//修改收支记录信息
			{
				if (strcmp(p->num, p1->num) == 0)
				{
					strcpy(p1->sd, a);
					Save1(L1);
				}
				p1 = p1->next;
			}
			MainMeun1(L, L1); break;
		case 2:  printf("\n\t\t请输入您需要挂失的账号：");
			gets(num);
			while (p != NULL && strcmp(num, p->num) != 0)
				p = p->next;
			if (!p)
			{
				printf("\n\t\t该账号不存在");
				fgets(buf,1024,stdin);
				system("clear"); return;
			}
			else if (strcmp(p->sd, c) == 0)
			{
				printf("\n\t\t该账号已挂失");
				fgets(buf,1024,stdin);
				system("clear"); return;
			}
			printf("\n\t\t请输入您的身份证号： ");//确认身份信息
			gets(ID);
			if (strcmp(ID, p->ID) != 0)
			{
				printf("\n\t\t身份证输入有误！");
				fgets(buf,1024,stdin);
				system("clear"); return;
			}
			Mimayincan(p->password);
			strcpy(p->sd, c); Save(L);
			while (p1)//修改收支记录的信息
			{
				if (strcmp(p->num, p1->num) == 0)
				{
					strcpy(p1->sd, c);
					Save1(L1);
				}
				p1 = p1->next;
			}
			printf("\t\t该账号完成挂失\n");
			fgets(buf,1024,stdin);
			system("clear");MainMeun1(L, L1); break;
		case 3:  printf("\n\t\t请输入您需要取消挂失的账号：");
			gets(num);
			while (p != NULL && strcmp(num, p->num) != 0)
				p = p->next;
			if (!p)
			{
				printf("\n\t\t该账号不存在");
				fgets(buf,1024,stdin);
				system("clear"); return;
			}
			else if (strcmp(p->sd, a) == 0)
			{
				printf("\n\t\t该账号未挂失");
				fgets(buf,1024,stdin);
				system("clear"); return;
			}
			printf("\n\t\t请输入您的身份证号： ");//确认身份信息
			gets(ID);
			if (strcmp(ID, p->ID) != 0)
			{
				printf("\n\t\t身份证输入有误！");
				fgets(buf,1024,stdin);
				system("clear"); return;
			}
			Mimayincan(p->password);
			strcpy(p->sd, a); Save(L);
			while (p1)//修改收支记录的信息
			{
				if (strcmp(p->num, p1->num) == 0)
				{
					strcpy(p1->sd, a);
					Save1(L1);
				}
				p1 = p1->next;
			}
			printf("\t\t该账号完成取消挂失\n");
			fgets(buf,1024,stdin);
			system("clear");
			MainMeun1(L, L1); break;
		case 0: MainMeun1(L, L1); break;//返回上一层
		}
	}
}
