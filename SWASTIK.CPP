#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <fstream.h>
#include <graphics.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <dos.h>
char z[20];
char a2[4][20];
int adhd=0;
int lk=0,y=0,c=0;
char f1[][20]={"hello1.txt","hello2.txt","hello3.txt","hello4.txt"};
struct info
{
char n[20];
char g[20];
}b[4];
struct BMP
    {
      char Type[2];           //File type. Set to "BM".
      unsigned long Size;     //Size in BYTES of the file.
      unsigned long Reserved;      //Reserved. Set to zero.
      unsigned long OffSet;   //Offset to the data.
      unsigned long headsize; //Size of rest of header. Set to 40.
      unsigned long Width;     //Width of bitmap in pixels.
      unsigned long Height;     //  Height of bitmap in pixels.
      unsigned int  Planes;    //Number of Planes. Set to 1.
      unsigned int  BitsPerPixel;       //Number of Bits per pixels.
      unsigned long Compression;   //Compression. Usually set to 0.
      unsigned long SizeImage;  //Size in bytes of the bitmap.
      unsigned long XPixelsPreMeter;     //Horizontal pixels per meter.
      unsigned long YPixelsPreMeter;     //Vertical pixels per meter.
      unsigned long ColorsUsed;   //Number of colors used.
      unsigned long ColorsImportant;  //Number of "important" colors.
    };

    int ShowBMP(int x, int y, char* FileName)
    {
	int b,a;
	struct  BMP Obj;

	unsigned char* Datas;
	int in=0;
	unsigned char c=0;
	FILE * fp;

	fp = fopen(FileName,"rb");
	if(!fp){
	printf("Error : Unable to open file ..");
	exit(0);
	}

	fread(&Obj, sizeof(Obj), 1, fp);
	if(Obj.BitsPerPixel!=4)  // This isn't a 16 color bmp we can read;
	{
	 fclose(fp);
	 printf("Error : File format not supported ..");
	 exit(0);
	};
	fseek(fp,Obj.OffSet,SEEK_SET);
	Datas=(unsigned char*) calloc(Obj.Width/2+1, sizeof(unsigned char));
	for(b=Obj.Height;b>=0;b--)
	{
	 fread(Datas, sizeof(unsigned char), Obj.Width/2, fp);
	 c=0;
	 in=0;
	 for(a=0;a<=Obj.Width;a+=2)
	 {
	     c = (Datas[in] | 0x00) >>4;
	     putpixel(a+x,b+y,c);
	     c = (Datas[in] | 0xF0) & 0x0F;
	     putpixel(a+1+x,b+y,c);
	     in++;
	 }
	}
	free (Datas);
	fclose(fp);
	return 1;
    }
    void BMP()
    {
    int color;


     ShowBMP(400,220,"j.bmp");


    }
void iok(char a[])
{
lk=0;
int e=0,pos=0;
char c;
strcpy(a,"");
char a2[20]="";
do
{
cleardevice();
rectangle(getmaxx()/2-100,50,getmaxx()/2+100,250);
arc(getmaxx()/2,260,10,170,100);
circle(getmaxx()/2,110,50);
rectangle(getmaxx()/2-100,300,getmaxx()/2+100,330);
outtextxy(getmaxx()/2-90,310,a2);
c=getch();
switch(c)
{
case 8:
if(pos)
{
pos--;
a[pos]=0;
a2[pos]=0;
}
break;
case 13:
e=1;
break;
case 27:a[0]=0;
a2[0]=0;
e=1;
lk++;
break;
default:
if(pos<20 && c>=' ' && c<='~')
{
a[pos]=c;
a2[pos]='*';
pos++;
a[pos]=0;
a2[pos]=0;
}
}
}
while(!e);

}

int user1(char a1[])
{
l:
cleardevice();
char a[20];
rectangle(getmaxx()/2-100,50,getmaxx()/2+100,250);
arc(getmaxx()/2,260,10,170,100);
circle(getmaxx()/2,110,50);

rectangle(getmaxx()/2-100,300,getmaxx()/2+100,330);
setcolor(LIGHTCYAN);
while(!kbhit())
outtextxy(getmaxx()/2-90,310,"Password");

setcolor(WHITE);
iok(a);
if(strcmp(a,"OVERIDE")==0)
return 1;

if(strcmp(a,a1)==0)
return 1;
else if((strcmp(a,a1)!=0)&&(lk==0))
goto l;
else
return 0;

}
void user(int i,int j,char d[],char dd[],int y=0)
{


if(y==1)
setcolor(LIGHTCYAN);
rectangle(20+i,100+j,95+i,175+j);
arc(58+i,175+j,0,180,38);
circle(58+i,120+j,17);
outtextxy(115+i,115+j,"NAME:");
outtextxy(195+i,115+j,d);
outtextxy(115+i,135+j,"PASSWORD:");
outtextxy(195+i,135+j,dd);
outtextxy(115+i,155+j,"STATUS:");
outtextxy(195+i,155+j,((strcmp(d,"")==0)?"INACTIVE":"ACTIVE"));
setcolor(WHITE);

}
void iop(char a[],char a1[])
{

int e=0,pos=0;
char c;
strcpy(a,"");
setcolor(GREEN);
settextstyle(10,HORIZ_DIR,1);
do
{
cleardevice();
outtextxy(10,60,a);
outtextxy(10,10,a1);
c=getch();
switch(c)
{
case 8:
if(pos)
{
pos--;
a[pos]=0;
}
break;
case 13:
e=1;
break;
case 27:a[0]=0;
e=1;
break;
default:
if(pos<20 && c>=' ' && c<='~')
{
a[pos]=c;
pos++;
a[pos]=0;
}
}
}
while(!e);
settextstyle(0,HORIZ_DIR,1);
setcolor(WHITE);
}
void ior(char a[],int i,int j,float k[][2],int c1)
{
char a1[20];
int gh;
if((i==0)&&(j==0))
gh=0;
else if((i!=0)&&(j==0))
gh=1;
else if((i==0)&&(j!=0))
gh=2;
else
gh=3;
strcpy(a1,b[gh].n);
int e=0,pos=0;
char c;
strcpy(a,"");
strcpy(a2[gh],"");
settextstyle(0,HORIZ_DIR,1);
do
{
cleardevice();
/*if(q)
{
a2[gh][q-1]='*';
a2[gh][q]='\0';

}
else
a2[gh][0]=0;
q++;*/
for(int h=0;h<c1;h++)
{

user(k[h][0],k[h][1],b[h].n,((strcmp(a1,"")==0)?"analysing...":a2[h]));
}
rectangle(185+i,110+j+((strcmp(a1,"")==0)?0:20),288+i,130+j+((strcmp(a1,"")==0)?0:20));
if(strcmp(a1,"")==0)
outtextxy(195+i,115+j+((strcmp(a1,"")==0)?0:20),a);
else
outtextxy(195+i,115+j+((strcmp(a1,"")==0)?0:20),a2[gh]);
c=getch();
switch(c)
{
case 8:
if(pos)
{
pos--;
a[pos]=0;
a2[gh][pos]=0;
}
break;
case 13:
e=1;
break;
case 27:a[0]=0;
a2[gh][0]=0;
e=1;
break;
default:
if(pos<20 && c>=' ' && c<='~')
{
a[pos]=c;
a2[gh][pos]='*';
pos++;
a[pos]=0;
a2[gh][pos]=0;
}
}
}
while(!e);
setcolor(WHITE);
}
void u(int oh=0)
{

int j;
int hk[2];
char b[20];
char d[50]="ENTER THE NO. OF USERS(MAXIMUM:4)";
int h=1,s,i;
float a[][2]={{0,0},{350,0},{0,350*9.0/16.0},{350,350*9.0/16.0}};
char k;

if(oh==1)
goto lk;
s:


iop(b,d);
c=atoi(b);

cleardevice();
if((c!=1)&&(c!=2)&&(c!=3)&&(c!=4))
c=1;
for(i=0;i<c;i++)
{
c=(((c<=4)&&(c>0))?c:1);
user(a[i][0],a[i][1],::b[i].n,::a2[i]);
o:
ior(::b[i].n,a[i][0],a[i][1],a,c);
if(strcmp(::b[i].n,"")==0)
goto o;
if(strcmp(::b[i].n,"BATMAN")==0)
{
   cleardevice();
   ShowBMP(getmaxx()/2-100,getmaxy()/2-150,"k.bmp");
   setcolor(BLACK);
   outtextxy(getmaxx()/2-50,getmaxy()/2-62.5,"WELCOME BATMAN");
   setcolor(WHITE);
   settextjustify(CENTER_TEXT,CENTER_TEXT);
   settextstyle(10,HORIZ_DIR,1);
    outtextxy(getmaxx()/2,getmaxy()/2+100,"SUPERUSER ACCESS GRANTED");
   delay(5000);
   settextjustify(LEFT_TEXT,TOP_TEXT);
}
ior(::b[i].g,a[i][0],a[i][1],a,c);
}

for(i=0;i<c;i++)
{
for(j=i+1;j<c;j++)
if(strcmp(::b[i].n,::b[j].n)==0)
{
s=strlen(::b[j].n);
::b[j].n[s]=h+48;
::b[j].n[s+1]='\0';
h++;
}
}
cleardevice();
for(i=0;i<c;i++)
user(a[i][0],a[i][1],::b[i].n,::a2[i]);
outtextxy(10,350*9.0/16.0+30,"Press ENTER to confirm and esc to reset");
k:
k=getch();
switch(k)
{
case 13:break;
case 27:
for(i=0;i<c;i++)
{
strcpy(::b[i].n,"");
strcpy(::b[i].g,"");
}
goto s;
default:
outtextxy(10,350*9.0/16.0+50,"OTHER OPTIONS WONT WORK(EXCEPT WINDOWS KEY)");
goto k;
}
lk:
hk[0]=hk[1]=0;
cleardevice();
hk[0]=0;
hk[1]=0;

for(i=0;i<c;i++)
user(a[i][0],a[i][1],::b[i].n,::a2[i]);
i=0;
user(a[i][0],a[i][1],::b[i].n,::a2[i],1);
jh:
outtextxy(10,350*9.0/16.0+30,"use a-left w-up s-down d-right and ENTER for selecting the account with which ");
outtextxy(10,350*9.0/16.0+40,"you want to log in(ESC-RETURN TO LOGIN PAGE)");


k=getch();
switch(k)
{
case 75:if(c>1)
	hk[0]--;goto l;
case 77:if(c>1);
	 hk[0]++;goto l;
case 80:if(c>2)
	 hk[1]--;goto l;
case 72:if(c>2)
	 hk[1]++;goto l;
case 13:goto sh;
case 27:goto jh;
}
l:
for(i=0;i<2;i++)
{
if(hk[i]<0)
hk[i]+=2;
if(hk[i]>1)
hk[i]-=2;
}

if((hk[0]==0)&&(hk[1]==0))
y=0;
else if((hk[0]==1)&&(hk[1]==0))
y=1;
else if(((hk[0]==0)&&(hk[1]==1))||((hk[0]==1)&&(hk[1]==1)&&(c==3)))
y=2;
else
y=3;
for(i=0;i<c;i++)
{
if(i!=y)
user(a[i][0],a[i][1],::b[i].n,::a2[i]);
else
user(a[i][0],a[i][1],::b[i].n,::a2[i],1);
}
goto jh;
sh:
if(user1(::b[y].g)==1)
cout<<1;
else
goto lk;
cleardevice();
ad:
}
void cal()
{
int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\TC\\BGI");
cleardevice();
char a[31][3],z[4],g,g1;
char c[][12]={"JANUARY","FEBRUARY","MARCH","APRIL","MAY","JUNE","JULY","AUGUST","SEPTEMBER","OCTOBER","NOVEMBER","DECEMBER"};
char d[][4]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
int k=0,j,l=2,b[]={31,28,31,30,31,30,31,31,30,31,30,31,30,31},f;
for(int i=1;i<=31;i++)
{
if(i/10==0)
{
a[i-1][0]=i+48;
a[i-1][1]='\0';
}
else
{
a[i-1][0]=(i/10)+48;
a[i-1][1]=(i%10)+48;
a[i-1][2]='\0';
}
}
float n=0,h=2019;
int sd=h;
gcvt(h,4,z);
for(f=0; ;)
{
sd=h;
if(((sd%4==0)&&(sd%100!=0))||(sd%400==0))
b[1]=29;
else
b[1]=28;
k=0;
if(n>11)
{
h=h+1;
n-=12;
gcvt(h,4,z);
}
if(n<0)
{
h=h-1;
n+=12;
gcvt(h,4,z);
}
cleardevice();
rectangle(25,0,585,400);
for(i=25;i<=585;i+=80)
line(i,50,i,400);
for(i=50;i<=400;i+=50)
line(25,i,585,i);
settextstyle(7,HORIZ_DIR,5);
outtextxy(190,5,c[f]);
outtextxy(485,5,z);
settextstyle(0,HORIZ_DIR,2);
setcolor(RED);
for(i=50;i<=545;i+=80,k++)
outtextxy(i,75,d[k]);
k=0;
setcolor(WHITE);
settextstyle(0,HORIZ_DIR,2);
for(j=125;j<=375;j+=50)
{

for(i=65;i<=545;i+=80,k++)
if(k<b[f])
{
if((j==125)&&((i+l*80)<=545))
{
outtextxy(i+l*80,j,a[k]);
if((i+l*80)==545)
{
k++;
break;
}
}
else
outtextxy(i,j,a[k]);
}
}
g1=getch();
switch(g1)
{
case 0:
g=getch();
switch(g)
{
case 77:
if(f>=12)
f-=12;
if(f<0)
f+=12;
n++;
l=l+(b[f]%7);
if(!(l<7))
l-=7;
f++;
if(f>=12)
f-=12;
if(f<0)
f+=12;
break;

case 75:
n--;
if(f==0)
{
f=12;
goto d;
}
if(f<0)
f+=12;
if(f>=12)
f-=12;
d:
l-=(b[f-1]%7);
while(!(l>0))
l+=7;
f--;
break;
}
break;
case 27:
goto g;


}
}

g:
}
void io(char a[],char a1[])
{
int e=0,pos=0;
char c;
strcpy(a,"");
settextstyle(5,HORIZ_DIR,2);
do
{
cleardevice();
outtextxy(10,30,a1);
outtextxy(250,80,a);
c=getch();
switch(c)
{
case 8:
if(pos)
{
pos--;
a[pos]=0;
}
break;
case 13:
e=1;
break;
case 27:a[0]=0;
e=1;
break;
default:
if(pos<20 && c>=' ' && c<='~')
{
a[pos]=c;
pos++;
a[pos]=0;
}
}
}
while(!e);


}
void alarm(char b[])
{
char a[50]="ENTER THE TIME IN THE FORMAT HH:MM:SS ";
cleardevice();
io(b,a);
}
void ginp(char a[],char a1[])
{
//clrscr();
//int gd=DETECT,gm;
//initgraph(&gd,&gm,"C:\\TC\\BGI");

int e=0,pos=0;
char c;
strcpy(a,"");
settextstyle(5,HORIZ_DIR,2);
do
{
cleardevice();
outtextxy(350,10,a);
outtextxy(10,10,a1);
c=getch();
switch(c)
{
case 8:
if(pos)
{
pos--;
a[pos]=0;
}
break;
case 13:
e=1;
break;
case 27:a[0]=0;
e=1;
break;
default:
if(pos<20 && c>=' ' && c<='~')
{
a[pos]=c;
pos++;
a[pos]=0;
}
}
}
while(!e);
cleardevice();
}

void input(char a[])
{
int e=0,pos=0;
char c;
strcpy(a,"");
settextstyle(1,HORIZ_DIR,1);
do
{
cleardevice();
settextstyle(5,HORIZ_DIR,1);
outtextxy(0,0,"NOTEPAD");
settextstyle(1,HORIZ_DIR,1);
 rectangle(0,0,getmaxx(),getmaxy());
outtextxy(10,30,a);
c=getch();
switch(c)
{
case 8:
if(pos)
{
pos--;
a[pos]=0;
}
break;
case 13:
e=1;
break;
case 27:a[0]=0;
e=1;
break;
default:
if(c>=' ' && c<='~')
{
a[pos]=c;
pos++;
a[pos]=0;
}
}
}
while(!e);
//gets(s);
}
void fileread(char s[])
{
ifstream f;
f.open(f1[y],ios::in);
while(!(f.eof()))
{
f>>s;
cout<<s<<" ";
}
f.close();
}
void note1()
{
ofstream f;
for(int i=0;i<4;i++)
{
 f.open(f1[i],ios::out);
 char s[21]="ENTER YOUR TEXT HERE";
 f<<s;
 f.close();
 }
 }
 void note()
 {

// int gdriver= DETECT,gmode,errorcode;
//initgraph(&gdriver,&gmode,"C:\\TURBOC3\\bgi");
cleardevice();

 char  file[10],s[50];
 setcolor(LIGHTCYAN);

 rectangle(0,0,getmaxx(),getmaxy());
settextstyle(5,HORIZ_DIR,1);
outtextxy(0,0,"NOTEPAD");
settextstyle(1,HORIZ_DIR,1);
 gotoxy(2,3);
 fileread(s);
 getch();
 ofstream f;
 f.open(f1[y],ios::out);

 cleardevice();
  rectangle(0,0,getmaxx(),getmaxy());
  gotoxy(2,2);
 input(s);

 f<<s;
 f.close();




 }
void timer()
{
cleardevice();
int a;
char h[10],m[10],s[10],h1[]="ENTER THE NO. OF HOURS:",m1[]="ENTER THE NO. OF MINUTES:",s1[]="ENTER THE NO. OF SECONDS:";
//int gd=DETECT,gm;
//initgraph(&gd,&gm,"C:\\TC\\BGI");
settextstyle(0,HORIZ_DIR,2);
setcolor(LIGHTGREEN);
ginp(h,h1);
ginp(m,m1);
ginp(s,s1);
a=(atoi(h)*3600)+(atoi(m)*60)+(atoi(s));
char b[2];
settextstyle(3,HORIZ_DIR,10);
for(int i=a;i>=1;)
{
gcvt(i,10,b);
/*b[0]=i+48;

b[1]='\0';  */
if(i!=a)
outtextxy(getmaxx()/2-30,70,b);
i--;
delay(1000);
cleardevice();
}
outtextxy(getmaxx()/5-125,70,"TIMES UP!!!");
d:
for(int j=0;j<4;j++)
{
sound(80);
delay(50);
nosound();
delay(50);
}
if(!kbhit())
{
delay(1000);
goto d;
}
getch();
}
void clo()
{
int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\TC\\BGI");
settextstyle(2,HORIZ_DIR,10);
setcolor(GREEN);
cleardevice();
char k='a',k12;
char f=k;
time_t t;
char a[20],b[10];
struct tm *time_now;
d:

cleardevice();
t=time(NULL);
time_now=localtime(&t);
strftime(a,20,"%I:%M:%S",time_now);
settextstyle(3,HORIZ_DIR,10);
outtextxy(37,100,a);
setfillstyle(SOLID_FILL,GREEN);
bar(150,300,450,400);
setfillstyle(SOLID_FILL,BLACK);
bar(160,310,290,390);
bar(310,310,440,390);
setfillstyle(SOLID_FILL,BLUE);
bar(160+((k=='d')?150:0),310,290+((k=='d')?150:0),390);
settextstyle(0,HORIZ_DIR,2);
outtextxy(180,350,"TIMER");
outtextxy(325,350," ALARM");
delay(1000);
if(strcmp(a,b)==0)
{
outtextxy(10,10,"ALARM FOR:");
outtextxy(170,10,b);
d1:
for(int j=0;j<4;j++)
{
sound(80);
delay(50);
nosound();
delay(50);
}
if(!kbhit())
{
delay(1000);
goto d1;
}
}
if(!kbhit())
goto d;
else
{
k=getch();
switch(k)
{

case 27:
goto l;
case 13:

if(f!='d')
timer();
else
alarm(b);
break ;

case 0:
k12=getch();
switch(k12)
{
case 77:k='d';
break;
case 75:k='a';
break;
}

}
f=k;
goto d;
}
l:
}

void inpu(char a[20])
{
int e=0,pos=0;
char c;
strcpy(a,"");
settextstyle(3,HORIZ_DIR,2);
do
{
cleardevice();
rectangle(0,0,getmaxx(),getmaxy());
rectangle(10,60,getmaxx()-10,130);
outtextxy(10,150,"PLEASE PROVIDE THE TASK ONE OPERATION A TIME");
outtextxy(10,210,"FOR EXAMPLE:");
outtextxy(10,180,"START WITH + [ YOUR_NUMBER ]");
outtextxy(10,240,"0 + 32 AND THEN HIT ENTER");
outtextxy(10,270,"TO END OPERATION TYPE '='");
outtextxy(10,300,"AND THEN HIT ENTER");
outtextxy(10,10,"CALCULATOR");
outtextxy(30,80,z);
outtextxy(210,80,a);
c=getch();
switch(c)
{
case 8:
if(pos)
{
pos--;
a[pos]=0;
}
break;
case 13:
e=1;
break;
case 27:a[0]=0;
e=1;
break;
default:
if(pos<20 && c>=' ' && c<='~')
{
a[pos]=c;
pos++;
a[pos]=0;
}
}
}
while(!e);
}
 void calc()
{
//int gd=DETECT,gm;
//initgraph(&gd,&gm,"C:\\TC\\BGI");
cleardevice();
char a[20];
int i,j;
float c,sum=0;
char b;

d:
cleardevice();

settextstyle(2,HORIZ_DIR,15);
gcvt(sum,9,z);

setcolor(LIGHTCYAN);
outtextxy(20,30,z);
gotoxy(30,30);
inpu(a);
b=a[0];
for(j=0;j<strlen(a);j++)
a[j]=a[j+1];
//puts(a);
char da[3][5]={"+INF","-INF","-NAN"};
for(int hs=0;hs<3;hs++)
if(strcmp(z,da[hs])==0)
goto k;

c=atof(a);
switch(b)
{
case '+':sum+=c;goto d;
case '-':sum-=c;goto d;
case '*':sum*=c;goto d;
case '/':sum/=c;goto d;
case '=':sum*=0;goto d;
default :goto k;
}
k:

}

void rotate(float cx,float cy,float angle,float a[1][2])
{
float s=sin(angle);
float c=cos(angle);
a[0][0]-=cx;
a[0][1]-=cy;
float xnew=a[0][0]*c-a[0][1]*s;
float ynew=a[0][0]*s+a[0][1]*c;
a[0][0]=xnew+cx;
a[0][1]=ynew+cy;
}
void start()
{

float a[1][2]={{300,200}},b[1][2]={{300,250}},c[1][2]={{298,210}},d[1][2]={{302,250}};

for(float i=-3.14/2;i<=4.14/2;i+=0.1)
{
cleardevice();
delay(10);
if(i>=5*-3.14/12 )
{
setcolor(LIGHTRED);
line(300,0,493.150757,51.892006);
circle(541.438477,64.865005,50);
outtextxy(510,62.865005,"CALENDAR");
}
if(i>=-3.14/6)
{setcolor(LIGHTCYAN);
line(300,0,399.95401,173.231628);
circle(424.942505,216.539536,50);
outtextxy(403,216.539536,"CLOCK");
}
if(i>=3.14/6)
{  setcolor(YELLOW);
line(300,0,200.04599,173.231628);
circle(175.05748,216.539536,50);
outtextxy(145,216.539536,"NOTEPAD");
}
if(i>=5*3.14/12)
{ setcolor(LIGHTGREEN);
line(300,0,106.849228,51.892006);
circle(58.561539,64.865005,50);
outtextxy(18,60.865005,"CALCULATOR");
}

a[0][0]=300;a[0][1]=200;
b[0][0]=300;b[0][1]=250;
c[0][0]=298,c[0][1]=210;
d[0][0]=302,d[0][1]=250;
rotate(300,0,i,a);
rotate(300,0,i,b);
for(int j=0;j<3;j++)
{
line(300+j,0+j,a[0][0]+j,a[0][1]+j);
circle(b[0][0],b[0][1],50+j);

}
for(int k=0;k<7;k++)
arc(b[0][0],b[0][1],120-(i*180/3.14),420-(i*180/3.14),35-k);
rotate(298,0,i,c);
rotate(302,0,i,d);
line(c[0][0],c[0][1],d[0][0],d[0][1]);
delay(100);
}
}
void start1()
{
settextjustify(LEFT_TEXT,TOP_TEXT);
settextstyle(0,HORIZ_DIR,1);
float a[1][2]={{300,200}},b[1][2]={{300,250}},c[1][2]={{298,210}},d[1][2]={{302,250}};

for(float i=4.14/2;i>=-3.14/2;i-=0.1)
{
cleardevice();
delay(10);
if(i>=5*-3.14/12 )
{
setcolor(LIGHTRED);
line(300,0,493.150757,51.892006);
circle(541.438477,64.865005,50);
outtextxy(510,62.865005,"CALENDAR");
}
if(i>=-3.14/6)
{setcolor(LIGHTCYAN);
line(300,0,399.95401,173.231628);
circle(424.942505,216.539536,50);
outtextxy(403,216.539536,"CLOCK");
}
if(i>=3.14/6)
{  setcolor(YELLOW);
line(300,0,200.04599,173.231628);
circle(175.05748,216.539536,50);
outtextxy(145,216.539536,"NOTEPAD");
}
if(i>=5*3.14/12)
{ setcolor(LIGHTGREEN);
line(300,0,106.849228,51.892006);
circle(58.561539,64.865005,50);
outtextxy(18,60.865005,"CALCULATOR");
}

a[0][0]=300;a[0][1]=200;
b[0][0]=300;b[0][1]=250;
c[0][0]=298,c[0][1]=210;
d[0][0]=302,d[0][1]=250;
rotate(300,0,i,a);
rotate(300,0,i,b);
for(int j=0;j<3;j++)
{
line(300+j,0+j,a[0][0]+j,a[0][1]+j);
circle(b[0][0],b[0][1],50+j);

}
for(int k=0;k<7;k++)
arc(b[0][0],b[0][1],120-(i*180/3.14),420-(i*180/3.14),35-k);
rotate(298,0,i,c);
rotate(302,0,i,d);
line(c[0][0],c[0][1],d[0][0],d[0][1]);
delay(100);
}
}
void ini()
{
float a[1][2]={{300,200}},b[1][2]={{300,250}},c[1][2]={{298,210}},d[1][2]={{302,250}};
for(float i=0;i>=-3.14/2;i-=0.1)
{
cleardevice();
a[0][0]=300;a[0][1]=200;
b[0][0]=300;b[0][1]=250;
c[0][0]=298,c[0][1]=210;
d[0][0]=302,d[0][1]=250;
rotate(300,0,i,a);
rotate(300,0,i,b);
for(int j=0;j<3;j++)
{
line(300+j,0+j,a[0][0]+j,a[0][1]+j);
circle(b[0][0],b[0][1],50+j);

}
for(int k=0;k<7;k++)
arc(b[0][0],b[0][1],120-(i*180/3.14),420-(i*180/3.14),35-k);
rotate(298,0,i,c);
rotate(302,0,i,d);
line(c[0][0],c[0][1],d[0][0],d[0][1]);
delay(100);
}
}
void ini1()
{
float a[1][2]={{300,200}},b[1][2]={{300,250}},c[1][2]={{298,210}},d[1][2]={{302,250}};
for(float i=-3.14/2;i<=0;i+=0.1)
{
cleardevice();
a[0][0]=300;a[0][1]=200;
b[0][0]=300;b[0][1]=250;
c[0][0]=298,c[0][1]=210;
d[0][0]=302,d[0][1]=250;
rotate(300,0,i,a);
rotate(300,0,i,b);
for(int j=0;j<3;j++)
{
line(300+j,0+j,a[0][0]+j,a[0][1]+j);
circle(b[0][0],b[0][1],50+j);

}
for(int k=0;k<7;k++)
arc(b[0][0],b[0][1],120-(i*180/3.14),420-(i*180/3.14),35-k);
rotate(298,0,i,c);
rotate(302,0,i,d);
line(c[0][0],c[0][1],d[0][0],d[0][1]);
delay(100);
}
}
void ins()
{

outtextxy(getmaxx()/2-100,400,"CHOOSE THE FIRST LETTER OF THE COLOUR");
outtextxy(getmaxx()/2-100,420,"R-red,B-blue,G-green,Y-Yellow");
outtextxy(getmaxx()/2-100,440,"use ARROW keys for LEFT/RIGHT,l-log out");
outtextxy(getmaxx()/2-100,460,"esc-exit from application/SHUTDOWN");
}
void main()
{


char doll[50];
char dol[50][50];
char hk[]="TURBO OS ";
char hkh[9][9];
int kh;
int i;
for(i=0;i<strlen(hk);i++)
{
for(kh=0;kh<=i;kh++)
hkh[i][kh]=hk[kh];
hkh[i][kh]='\0';
}
int gd=DETECT,gm,jklm=0;
initgraph(&gd,&gm,"C:\\TC\\BGI");
jklm=adhd;
klm:
if(adhd==1)
{
adhd=0;

cleardevice();
ShowBMP(getmaxx()/2-100,getmaxy()/2-150,"k.bmp");
delay(3000);
for(i=0;i<c;i++)
{
strcpy(::b[i].n,"");
strcpy(::b[i].g,"");
}
}
u();
if(adhd==1)
goto klm;
kl:
for(i=0;i<=200;i++)
{
delay(3);
circle(300,0+i,2) ;
}
for(float j=0;j<=6.28;j+=0.01)
{
delay(3);
circle(300+50*cos(j+(1.52*3.14)),250+50*sin(j+(1.52*3.14)),1);
}
for(j=0;j<=6.28-(0.35*3.14);j+=0.01)
{
delay(3);
circle(300+30*cos(j+(1.65*3.14)),250+30*sin(j+(1.65*3.14)),2);
}
for(i=0;i<41;i++)
{
delay(10);
circle(300,210+i,0.5);
}
/*for(i=0;i<3;i++)
{
circle(400,200,30+i);
delay(20);
}
		 */
setcolor(GREEN);
char kc[50]="RECALIBRATING RESOLUTION FOR THIS COMPUTER....." ;
char ck[50],ckc[50]="INITIALIZING ALL DRIVES...",kck[]="CHECKING SYSTEM STATUS....";
for(i=0;i<strlen(kc);i++)
{
ck[i]=kc[i];
ck[i+1]='\0';
outtextxy(10,400,ck);
delay(20);
}
delay(3000);
setcolor(WHITE);
cleardevice();
bar(298,0,300,200);
for(i=0;i<3;i++)
{
circle(300,250,50+i);
}
for(i=0;i<7;i++)
arc(300,250,120,420,35-i);
line(300,210,300,250);
outtextxy(100,100,"HOLD DOWN THE 'H' KEY");
outtextxy(350,30,kck);
BMP();
setcolor(LIGHTRED);
outtextxy(1,0,ckc);

for(j=0;j<=300;j+=3)
{

k:
setcolor(LIGHTRED);
for(i=0;i<7;i++)
arc(300,250,420-j,420,35-i);
setcolor(WHITE);
if((int)(j-19)%20==0)
{
setcolor(LIGHTCYAN);
settextstyle(10,HORIZ_DIR,1);
if(j/20<9)
outtextxy(220,350,hkh[j/20]);
settextstyle(0,HORIZ_DIR,1);
setcolor(WHITE);
}
if(j!=0)
{

setfillstyle(SOLID_FILL,LIGHTGREEN);
bar(350,50,350+j,70);
setfillstyle(SOLID_FILL,WHITE);
pieslice(40,50,j,j+60,30);
rectangle(350,50,getmaxx()-1,70);
}

setcolor(RED);
if(j>50)
{
for(int i=0;i<3;i++)
     {
     if(j>50)
     {
     circle(480,290,5-i);
     line(470,280-i,480,290-i);
     line(410,280-i,470,280-i);
     outtextxy(407,270,"analysing");
     }
     if(j>100)
     {
     circle(520,320,5-i);
     line(530,330-i,520,320-i);
     line(530,330-i,getmaxx()-55,330-i);
      outtextxy(530,320,"analysing");
      }
      if(j>150)
      {
     circle(520-20,320+40,5-i);
     line(530-20,330-i+40,520-20,320-i+40);
     line(530-20,330-i+40,getmaxx()-55-20,330-i+40);
      outtextxy(530-20,320+40,"analysing");
      }
      if(j>200)
      {
     circle(480,290+50,5-i);
     line(470,280-i+50,480,290-i+50);
     line(430,280-i+50,470,280-i+50);
      outtextxy(390,270+50,"analysing");
      }
      if(j>220)
      {
      setcolor(GREEN);
     for(int j=0;j<=20;j++)
     circle(500,320,20-j);
     setcolor(RED);
      circle(500,320,20);
     circle(480+40,290-10,5-i);
     line(500+40,270-i-10,480+40,290-i-10);
     line(getmaxx()-55-20,270-i-10,500+40,270-i-10);
      outtextxy(getmaxx()-55-40,270-20,"analysing");
      }
     }
}
if((getch()!='h')&&(getch()!='H'))
goto k;
}

setcolor(LIGHTRED);
cleardevice();
bar(298,0,300,200);
for(i=0;i<3;i++)
{
circle(300,250,50+i);
}
for(i=0;i<7;i++)
arc(300,250,120,420,35-i);
line(300,210,300,250);
delay(1000);
setcolor(LIGHTCYAN);
cleardevice();
bar(298,0,300,200);
for(i=0;i<3;i++)
{
circle(300,250,50+i);
}
for(i=0;i<7;i++)
arc(300,250,120,420,35-i);
line(300,210,300,250);
delay(1000);
setcolor(YELLOW);
cleardevice();
bar(298,0,300,200);
for(i=0;i<3;i++)
{
circle(300,250,50+i);
}
for(i=0;i<7;i++)
arc(300,250,120,420,35-i);
line(300,210,300,250);
delay(1000);
setcolor(LIGHTGREEN);
cleardevice();
bar(298,0,300,200);
for(i=0;i<3;i++)
circle(300,250,50+i);
for(i=0;i<7;i++)
arc(300,250,120,420,35-i);
line(300,210,300,250);
delay(1000);

setcolor(WHITE);
ini();
start();
l:
settextstyle(0,HORIZ_DIR,1);
cleardevice();
{
setcolor(LIGHTRED);
line(300,0,493.150757,51.892006);
circle(541.438477,64.865005,50);
outtextxy(510,62.865005,"CALENDAR");
}
//if(i>=-3.14/6)
{setcolor(LIGHTCYAN);
line(300,0,399.95401,173.231628);
circle(424.942505,216.539536,50);
outtextxy(403,216.539536,"CLOCK");
}
//if(i>=3.14/6)
{  setcolor(YELLOW);
line(300,0,200.04599,173.231628);
circle(175.05748,216.539536,50);
outtextxy(145,216.539536,"NOTEPAD");
}
//if(i>=5*3.14/12)
{ setcolor(LIGHTGREEN);
line(300,0,106.849228,51.892006);
circle(58.561539,64.865005,50);
outtextxy(18,60.865005,"CALCULATOR");
}
ins();
char s=getch();
if((s=='g')||(s=='G'))
{
calc();
goto l;
}
else if((s=='y')||(s=='Y'))
{
note();
goto l;
}
else if((s=='B')||(s=='b'))
{
clo();
goto l;
}
else if((s=='R')||(s=='r'))
{
cal();
goto l;
}

else if(s==27)
{
cleardevice();
settextjustify(CENTER_TEXT,CENTER_TEXT);
settextstyle(1,HORIZ_DIR,2);
strcpy(doll,"INITIATING SHUTDOWN SEQUENCE....");
for(i=0;i<strlen(doll);i++)
{
for(j=0;j<=i;j++)
dol[i][j]=doll[j];
dol[i][j]='\0';
}
for(i=0;i<strlen(doll);i++)
{
cleardevice();
outtextxy(getmaxx()/2,100,dol[i]);
delay(100);
}
delay(2000);
start1();
setcolor(WHITE);
ini1();
setcolor(LIGHTRED);
cleardevice();
bar(298,0,300,200);
for(i=0;i<3;i++)
{
circle(300,250,50+i);
}
for(i=0;i<7;i++)
arc(300,250,120,420,35-i);
line(300,210,300,250);
delay(1000);
setcolor(LIGHTCYAN);
cleardevice();
bar(298,0,300,200);
for(i=0;i<3;i++)
{
circle(300,250,50+i);
}
for(i=0;i<7;i++)
arc(300,250,120,420,35-i);
line(300,210,300,250);
delay(1000);
setcolor(YELLOW);
cleardevice();
bar(298,0,300,200);
for(i=0;i<3;i++)
{
circle(300,250,50+i);
}
for(i=0;i<7;i++)
arc(300,250,120,420,35-i);
line(300,210,300,250);
delay(1000);
setcolor(LIGHTGREEN);
cleardevice();
bar(298,0,300,200);
for(i=0;i<3;i++)
{
circle(300,250,50+i);
}
for(i=0;i<7;i++)
arc(300,250,120,420,35-i);
line(300,210,300,250);
note1();
delay(1000);
exit(0);
}
else if((s=='l')||(s=='L'))
goto sh;
else
goto l;
sh:
cleardevice();
if(user1(::b[y].g)==1)
cout<<1;
else
{
y=0;
u(1);
}
cleardevice();
goto kl;
}