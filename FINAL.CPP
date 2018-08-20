// 1RN15IS083 && 1RN15IS091
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream.h>
#include<iomanip.h>
#define studentfile"event.txt"
#define datafile"dat.txt"
#define recsize 80
#define max 100
#include<dir.h>
#include<dos.h>
#include<bios.h>
#include<graphics.h>

fstream file,ifile;
char buffer[85];
class student

{
     public:
	      char eid[15],ename[20],rfee[5],pamt[5],toc[10];
	      void initial();
	      void read();
	      void retrieve(int addr,char k[]);
	      void display();
	      void ddisp();
	      void edelete(int addr,char k[]);
	      void modify(int addr,char k[]);
 };
void student::initial()
{
  int i,j;
  ifile.open(datafile,ios::app);
  if(!ifile)
  {
	cout<<"Unable to open a file"<<endl;
	getch();
	exit(1);
  }
  file.open(studentfile,ios::in);
  if(!file)
  {
     file.open(studentfile,ios::out);
     if(!file)
     {
      cout<<"unable to open the file";
      exit(1);
      }
    for(i=0;i<max;i++)
    {
     file.seekp(i*recsize,ios::beg);
     for(j=0;j<recsize-2;j++)
     file<<"#";
     file<<endl;
   }
 cout<<"empty file created";
 }
 file.close();
 ifile.close();
 return;
 }
void student::read()
{
clrscr();
  int i;
  gotoxy(20,2);
  for(i=0;i<50;i++) cout<<"*";
  gotoxy(35,4);
  cout<<"ADD AN EVENT";
  gotoxy(20,6);
  for(i=0;i<50;i++) cout<<"*";
  gotoxy(20,8);
 cout<<"ENTER EVENT DETAILS:"<<endl;
 cout<<"\tEnter the event id:(ev__)";gets(eid);
 cout<<"\tEnter the event name:";    gets(ename);
 cout<<"\tEnter the time of conduct:";gets(toc);
 cout<<"\tEnter the registeration fee:";gets(rfee);
 cout<<"\tEnter the prize money:";      gets(pamt);
 strcpy(buffer,eid);             strcat(buffer,"|");
 strcat(buffer,ename);             strcat(buffer,"|");
 strcat(buffer,toc);               strcat(buffer,"|");
 strcat(buffer,rfee);             strcat(buffer,"|");
 strcat(buffer,pamt);             strcat(buffer,"|");
 return;
}
int hash(char key[])
{
  int i=0,sum=0;
  while(key[i]!='\0')
  {
    sum=sum+(key[i]);
    i++;
    }
 return sum % max;
 }

void store(int addr)
{
 char dummy[10];
 int flag=0,i;
 ifile.open(datafile,ios::app);
 ifile.fill('*');
 ifile<<setiosflags(ios::left)<<setw(sizeof(student))<<buffer<<endl;
 file.open(studentfile,ios::in|ios::out);
 file.seekp(addr*recsize,ios::beg);
 file.getline(dummy,5,'\n');
 if(strcmp(dummy,"####")==0)
 {
	file.seekp(addr*recsize,ios::beg);
	file<<buffer;
	flag=1;
 }
 else
 {
	for(i=addr+1;i!=addr;i++)
	{
		if(i%max==0)
		i=0;
		file.seekg(i*recsize,ios::beg);
		file.getline(dummy,5,'\n');
		if(strcmp(dummy,"####")==0)
		{
		 //	cout<<"\n collision has occured\n";
		   //	cout<<"home address is:"<<addr<<"actual address is:"<<i<<"\n";
			file.seekp(i*recsize,ios::beg);
			file<<buffer;
			flag=1;
			break;
		 }
		}
	}
 if(i==addr && (!flag))
 cout<<"hash file is full,record cannot be inserted\n";
 file.close();
 ifile.close();
 return;
}
void student::retrieve(int addr,char k[])
{
 int found=0,i;
 char dummy[10];
 i=addr;
 file.open(studentfile,ios::in|ios::out);
 do
 {
	 file.seekg(i*recsize,ios::beg);
	 file.getline(dummy,5,'\n');
	 if(strcmp(dummy,"####")==0)
	 break;
	 file.seekg(i*recsize,ios::beg);
	 file.getline(eid,15,'|');
	 if(strcmp(eid,k)==0)
	 {
		found=1;
		textcolor(RED);
		cout<<"\n";
		gotoxy(20,12);
		cout<<"RECORD FOUND!!\n";
		cout<<endl;
		file.getline(ename,20,'|');
		 file.getline(toc,10,'|');
		file.getline(rfee,5,'|');
		file.getline(pamt,5,'|');
		gotoxy(20,14);
		cout<<"ID:"<<eid<<endl;
		gotoxy(20,15);
		cout<<"NAME:"<<ename;
		gotoxy(20,16);
		cout<<"Time Of Conduct:"<<toc;
		gotoxy(20,17);
		cout<<"Registeration Fee:"<<rfee;
		gotoxy(20,18);
		cout<<"Prize Amount:"<<pamt;
		break;
	 }
	 else
	 {
		i++;
		if(i%max==0)
		i=0;
	 }
 } while(i!=addr);
 if(found==0)
 cout<<"\n\t\t\trecord does not exist in hash file\n";
 getch();
 return;
 }
void student::display()
{
clrscr();
 char dummy[85];
 file.open(studentfile,ios::in|ios::out);
 cout<<setiosflags(ios::left);
 cout<<"\t\t\t\tEVENT DETAILS"<<endl;
 cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
 cout<<"\t"<<setw(10)<<"ID"<<setw(20)<<"NAME"<<setw(15)<<"CONDUCT TIME"<<setw(10)<<"FEE"<<setw(10)<<"PRIZE"<<endl;
 cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;

 while(1)
 {
	 file.getline(eid,15,'|');
	 file.getline(ename,20,'|');
	 file.getline(toc,10,'|');
	 file.getline(rfee,5,'|');
	 file.getline(pamt,5,'|');
	 file.getline(dummy,85,'\n');
	 if(file.eof())
		break;
	 if(eid[0]!='#')
	 {
		cout<<"\t"<<setw(10)<<eid<<setw(20)<<ename<<setw(15)<<toc<<setw(10)<<rfee<<setw(10)<<pamt<<"\n";

	 }
 }
 file.close();
 getch();
}
void student::edelete(int addr,char k[])
{
 int found=0,i,j,fn;
 char dummy[10],temp[80];
 i=addr;
 ifile.open(datafile,ios::in|ios::out);
 while(!(ifile.eof()))
 {      fn = ifile.tellg();
	ifile.getline(eid,15,'|');
	ifile.getline(temp,80,'\n');
	if(strcmp(eid,k)==0)
	{
		ifile.seekg(fn,ios::beg);
		ifile.put('$');
	}
 }
 ifile.close();
 file.open(studentfile,ios::in|ios::out);
 do
 {
	 file.seekg(i*recsize,ios::beg);
	 file.getline(dummy,5,'\n');
	 if(strcmp(dummy,"####")==0)
	 break;
	 file.seekg(i*recsize,ios::beg);
	 file.getline(eid,15,'|');
	 if(strcmp(eid,k)==0)
	 {
		found=1;

		cout<<"\n\t\t\t\tRECORD FOUND!!\n";
		cout<<endl;
		file.getline(ename,20,'|');
		cout<<"\t\t\t\tkey="<<eid<<endl<<"\n\t\t\t\tname="<<ename<<"\n";
		file.seekg(i*recsize,ios::beg);
		for(j=0;j<recsize-2;j++)
			file<<"#";
		file<<endl;
		break;
	 }
	 else
	 {
		i++;
		if(i%max==0)
		i=0;
	 }
 } while(i!=addr);
 if(found==0)
 cout<<"\n\t\t\trecord does not exist in hash file\n";
 getch();
 return;
}
void student::ddisp()
{
   clrscr();
 char dummy[80];
 ifile.open(datafile,ios::in);
 cout<<setiosflags(ios::left);
 cout<<"\t\t\t\tEVENT DETAILS"<<endl;
 cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
 cout<<"\t"<<setw(10)<<"ID"<<setw(20)<<"NAME"<<setw(15)<<"CONDUCT TIME"<<setw(10)<<"FEE"<<setw(10)<<"PRIZE"<<endl;
 cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;

 while(1)
 {
	 ifile.getline(eid,15,'|');
	 ifile.getline(ename,20,'|');
	 ifile.getline(toc,10,'|');
	 ifile.getline(rfee,5,'|');
	 ifile.getline(pamt,5,'|');
	 ifile.getline(dummy,80,'\n');
	 if(ifile.eof())
		break;
	 if(eid[0]!='$')
	 {
		cout<<"\t"<<setw(10)<<eid<<setw(20)<<ename<<setw(15)<<toc<<setw(10)<<rfee<<setw(10)<<pamt<<"\n";

	 }
 }
 ifile.close();
 getch();
}

void student::modify(int addr,char k[])
{
 int found=0,i,count,fn;
 char dummy[10],temp[80];
 i=addr;
 ifile.open(datafile,ios::in|ios::out);
 while(!(ifile.eof()))
 {      fn = ifile.tellg();
	ifile.getline(eid,15,'|');
	ifile.getline(temp,80,'\n');
	if(strcmp(eid,k)==0)
	{
		ifile.seekg(fn,ios::beg);
		ifile.put('$');
	}
 }
 ifile.close();
 file.open(studentfile,ios::in|ios::out);
 do
 {
	 file.seekg(i*recsize,ios::beg);
	 file.getline(dummy,5,'\n');
	 if(strcmp(dummy,"####")==0)
	 break;
	 file.seekg(i*recsize,ios::beg);
	 file.getline(eid,15,'|');
	 if(strcmp(eid,k)==0)
	 {
		found=1;
		textcolor(RED);
		cout<<"\n";
		gotoxy(20,12);
		cout<<"RECORD FOUND!!\n";
		cout<<endl;
		file.getline(ename,20,'|');
		gotoxy(20,13);
		cout<<"ID:"<<eid<<endl;
		gotoxy(20,14);
		cout<<"NAME:"<<ename<<"\n";
		file.getline(ename,20,'|');
		gotoxy(20,16);
		cout<<"Enter the event name:";
		gets(ename);
		gotoxy(20,17);
		cout<<"Enter the time of conduct:";
		gets(toc);
		gotoxy(20,18);
		cout<<"Enter the registration fee:";
		gets(rfee);
		gotoxy(20,19);
		cout<<"Enter the prize amount:";
		gets(pamt);
		strcpy(buffer,eid);             strcat(buffer,"|");
		strcat(buffer,ename);             strcat(buffer,"|");
		strcat(buffer,toc);               strcat(buffer,"|");
		strcat(buffer,rfee);             strcat(buffer,"|");
		strcat(buffer,pamt);             strcat(buffer,"|");
		file.seekp(addr*recsize,ios::beg);
		file<<buffer;
		break;
	 }
	 else
	 {
		i++;
		if(i%max==0)
		i=0;
	 }
 } while(i!=addr);
if(found==0)
 cout<<"\n\t\t\trecord does not exist in hash file\n";
 getch();
  ifile.open(datafile,ios::app);
 ifile.fill('*');
 ifile<<setiosflags(ios::left)<<setw(sizeof(student))<<buffer<<endl;
 ifile.close();
 return;
 }

void screen()
{
	int i;
	textcolor(YELLOW);
	clrscr();
	gotoxy(20,2);
	for(i=0;i<50;i++) cout<<"*";
	gotoxy(20,4);
	cout<<"*";
	gotoxy(36,4);
	cout<<"MAIN MENU";
	gotoxy(70,4);
	cout<<"*";
	gotoxy(20,6);
	for(i=0;i<50;i++) cout<<"*";
	gotoxy(30,8);
	cout<<"* "<<"1. Add an event"<<endl;
	gotoxy(30,10);
	cout<<"* "<<"2. Display events in Datafile"<<endl;
	gotoxy(30,12);
	cout<<"* "<<"3. Search event details"<<endl;
	gotoxy(30,14);
	cout<<"* "<<"4. Display all event"<<endl;
	gotoxy(30,16);
	cout<<"* "<<"5. Delete an event "<<endl;
	gotoxy(30,18);
	cout<<"* "<<"6. Modify an event"<<endl;
	gotoxy(30,20);
	cout<<"* "<<"7. Quit Program\n";
	gotoxy(20,22);
	for(i=0;i<50;i++) cout<<"*";
}

void main()
{
 int ch,addr,i,j;
 char skey[15],dkey[15],mkey[15];
 student s;
 clrscr();
 s.initial();
 for(;;)
 {
	screen();
	gotoxy(20,24);
	cout<<"ENTER YOUR CHOICE:";
	cin>>ch;
	switch(ch)
	{
		case 1:
			s.read();
			addr=hash(s.eid);
			store(addr);
			break;
		case 2:s.ddisp();
			break;
		case 3: clrscr();
			gotoxy(20,2);
			for(i=0;i<50;i++) cout<<"*";
			gotoxy(30,4);
			cout<<"SEARCH FOR EVENT DETAILS";
			gotoxy(20,6);
			for(i=0;i<50;i++) cout<<"*";
			gotoxy(20,8);
			cout<<"ENTER EVENT ID:";
			cin>>skey;
			gotoxy(20,10);
			cout<<"++++++++++++++++++++++++++++++++"<<endl;
			addr=hash(skey);
			s.retrieve(addr,skey);
			break;
		case 4:
			s.display();
			break;
		case 5: clrscr();
			gotoxy(20,2);
			for(i=0;i<50;i++) cout<<"*";
			gotoxy(30,4);
			cout<<"DELETE AN EVENT";
			gotoxy(20,6);
			for(i=0;i<50;i++) cout<<"*";
			gotoxy(20,8);
			cout<<"Enter the ID to delete:";
			cin>>dkey;
			gotoxy(20,10);
			cout<<"+++++++++++++++++++++++++++++++++++++++++++"<<endl;
			addr=hash(dkey);
			s.edelete(addr,dkey);
			break;
		case 6:clrscr();
			gotoxy(20,2);
			for(i=0;i<50;i++) cout<<"*";
			gotoxy(30,4);
			cout<<"MODIFY AN EVENT";
			gotoxy(20,6);
			for(i=0;i<50;i++) cout<<"*";
			gotoxy(20,8);
			cout<<"ENTER EVENT ID:";
			cin>>mkey;
			gotoxy(20,10);
			cout<<"++++++++++++++++++++++++++++++++"<<endl;
			addr=hash(mkey);
			s.modify(addr,mkey);
			break;
		default:exit(0);
			break;

 }
 file.close();
}
}
