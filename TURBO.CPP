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
REGS i,o;
int f12=0;
int x1=300,x2=x1+140;
int y1=300,y2=y1+90;
int ui,uj;
char cs[][12]={"READABLES","WRITABLES","ACCESSORIES","GAMES"};
//union REGS i,o;  //mouse variables
int color=WHITE;
struct info
{
char n[20];
char g[20];
}b[4];              //user info
void calc(),clo(),cal(),note();
int L (char, char[], char[]);
void I (char[], char[]);

class pic               //object of this class stores
{                       //information of pixels
public:
int col;
int x;
int y;
};

void help()
{
i.x.ax=2;
int86(51,&i,&o);
i.x.ax=4;
i.x.cx=0;
i.x.dx=0;
i.x.bx=0;
int86(51,&i,&o);

int c=-1,x,y,z=2,i;
char ch;
setfillstyle(SOLID_FILL,BLUE);
char a[4][20]={"1. ACCESSORIES","2. GAMES","3. WRITABLES","4. READABLES"};
setcolor(YELLOW);
bar(0,0,getmaxx(),getmaxy());
rectangle(20,10,getmaxx()-25,100);
settextjustify(1,1);
settextstyle(7,HORIZ_DIR,5);
outtextxy(getmaxx()/2,40,"H   E   L   P");
settextjustify(0,2);
h:

::i.x.ax=1;
int86(51,&::i,&o);
::i.x.ax=3;
int86(51,&::i,&o);
x=o.x.cx;
y=o.x.dx;
z=o.x.bx;
for(i=0;i<4;i++)
{
if((x>20)&&(x<(getmaxx()-25))&&(y>(120+i*80+10))&&(y<(200+i*80)))
{
c=i+1;
break;
}
else
c=-1;
}

for(i=0;i<4;i++)
{
setcolor(WHITE);
if(i%2==0)
rectangle(i*2,i*2,getmaxx()-i*2,getmaxy()-i*2);
setcolor(YELLOW);
if(i==(c-1))
setcolor(RED);
rectangle(20,120+i*80+10,getmaxx()-25,200+i*80);
outtextxy(25,150+i*80-10,a[i]);
}
if((c!=1)&&(c!=2)&&(c!=3)&&(c!=4)||(z!=1))
goto h;
bar(0,0,getmaxx(),getmaxy());
for(i=0;i<4;i++)
{
setcolor(WHITE);
if(i%2==0)
rectangle(i*2,i*2,getmaxx()-i*2,getmaxy()-i*2);
setcolor(YELLOW);
}
k:
switch(c)
{
case 1:
settextjustify(1,1);
setcolor(LIGHTRED);
settextstyle(7,HORIZ_DIR,5);
outtextxy(getmaxx()/2,40,"ACCESSORIES");
settextjustify(0,2);
settextstyle(7,HORIZ_DIR,2);
setcolor(YELLOW);
outtextxy(10,100,"CALCULATOR: INSTRUCTIONS ARE GIVEN ALONG WITH ");
outtextxy(150,120,"APP. DONT USE ALPHABET & SPACE");
outtextxy(10,200,"CALENDAR:  IT PROVIDES YOU WITH CURRENT DATE");
outtextxy(150,220,"USE ARROW KEYS (LEFT AND RIGHT)");
outtextxy(10,300,"CLOCK:     IT PROVIDES YOU WITH CURRENT TIME");
outtextxy(140,320,"ALARM AND TIMER");
outtextxy(140,340,"USE ARROW KEYS (LEFT AND RIGHT)");
break;
case 2: settextjustify(1,1);
setcolor(LIGHTRED);
settextstyle(7,HORIZ_DIR,5);
outtextxy(getmaxx()/2,40,"GAMES");
settextjustify(0,2);
settextstyle(7,HORIZ_DIR,2);
setcolor(YELLOW);
outtextxy(10,100,"ROBOX: INSTRUCTIONS ARE GIVEN ALONG WITH ");
outtextxy(150,120,"APP. DONT USE ALPHABET & SPACE");
outtextxy(10,200,"HANGMAN: A TRADITIONAL GAME OF HANGMAN");
outtextxy(150,220,"BY GUESSING NAMES OF CAR BRANDS");
outtextxy(150,240,"USE ONE KEY AT A TIME");
break;
case 3: settextjustify(1,1);
setcolor(LIGHTRED);
settextstyle(7,HORIZ_DIR,5);
outtextxy(getmaxx()/2,40,"WRITABLES");
settextjustify(0,2);
settextstyle(7,HORIZ_DIR,2);
setcolor(YELLOW);
outtextxy(10,100,"PAINT: AN ARTISTIC FINISH TO THIS OS");
outtextxy(150,120,"USE MOUSE(LEFT-CLICK ONLY)");
outtextxy(10,200,"NOTEPAD: STORE A FEW PARAGRAPHS");
outtextxy(150,220,"BUT SAVED ONLY TILL NEXT ");
outtextxy(150,240,"TIME VISITED ");
break;

case 4: settextjustify(1,1);
setcolor(LIGHTRED);
settextstyle(7,HORIZ_DIR,5);
outtextxy(getmaxx()/2,40,"READABLES");
settextjustify(0,2);
settextstyle(7,HORIZ_DIR,2);
setcolor(YELLOW);
outtextxy(10,100,"COMICS: HAVE A FUN TIME READING");
outtextxy(150,120,"USE ARROW KEYS");
outtextxy(10,200,"HELP: SOMETHING THAT CAN HELP");
outtextxy(150,220,"YOU GET AROUND");
outtextxy(150,240,"");
break;

}

ch=getch();
if(ch!=27)
goto k;
}

int get_user()
{
info inf;
int i=0;
ifstream fin("user_info.dat",ios::in|ios::binary);
while(fin.read((char*)&inf,sizeof(inf)))
{
b[i]=inf;
i++;
}
fin.close();
return(i);
}
void save_user(int c)
{
ofstream fout("user_info.dat",ios::out|ios::binary);
for(int i=0;i<c;i++)
fout.write((char*)&b[i],sizeof(b[i]));
fout.close();
ofstream fout1("u.txt",ios::out);
fout1<<'y';
fout1.close();
}
void dat(int x,int y, char ch[30])   //function to read pixels from file
{                                    //and display with starting coordinates
pic obj1;                            //(x,y) file name:ch
ifstream fin(ch ,ios::in|ios::binary);
while(fin.read((char*)&obj1,sizeof(obj1)))
putpixel(x+obj1.x,y+obj1.y,obj1.col);
fin.close();
}

void hangman(char p[])             //p is the username
{
struct hang
{
char p[20];
}ob;
char s[20];                 //string that is being guessed
int maxt=7;                 //maximum tries
cleardevice();              //clrscr in graphics mode
char l;
int wrong_guess=0;
char wd[20];              //stores car name
strcpy(ob.p,p);           //ob.p saves the username
cleardevice();
char w[][20]=           //array of strings
{
 "rollsroyce",
 "tata",
 "jaguar",
 "volkswagen",
 "landrover",
 "hyundai",
 "maruti",
 "chevorlet",
 "mahindra",
 "honda",
 "renault",
 "toyota",
 "mercedesbenz",
 "lamborghini",
 "bugatti",
 "volvo",
 "porsche",
 "audi",
 "nissan",
 "ferrari",
};
randomize();
int n=random(20);
strcpy(wd,w[n]);
I(wd, s);            //כ coded word

cout<<"\n\t\t\t WELCOME TO HANGMAN ";
cout<<"\n\n";
cout<<"\n                          ®®® About the game ¯¯¯";
cout<< "\n\n x  The Topic is given below." ;
cout<< "\n\n x  Each letter of the word is represented by a כ symbol.";
cout<< "\n\n x  You have to type only one letter in one attempt.";
cout<< "\n\n x  If a letter repeats it will be automatically displayed.";
cout<< "\n\n x  You have " << maxt << " tries guess the word.";
cout<< "\n\n x  No capital letters,numbers,special characters are allowed.";
cout<<"\n\nננננננננננננננננננננננננננננננננננננננננננננננננננננננננננננננננננננננננננננננננ";
cout<<"\nTopic :--- CAR BRAND";

while (wrong_guess<maxt)
{
cout<< "\n" <<s;
cout<<"\nCome on Guess a letter:-\n";
s:
l=getch();      //accept only one letter
if(!isalpha(l)) //avoiding anyting apart from alphabet
goto s;
cout<<l;        //print character
int k=L(l,wd,s);
if (k==0)   // 0 for wrong letter
{
cout<<endl<< "OOPS! That letter isn't correct" << endl;
wrong_guess++;
}
else if(k==-1)  //-1 if letter is already entered
{
cout<<endl<<"YOU HAVE ALREADY ENTERED THAT LETTER";
}
else           //1 if letter is correct
{
cout << endl << "DAMM GOOD You got that correct" << endl;
}

cout << "Now You have " << maxt-wrong_guess;
cout << " try left\n";

if (strcmp(wd, s) == 0)  //when all letters are guessed
{
cout << wd << endl;
cout << " \n            ךךך DAMM COOL  You got that correct ךךך \n";
cout<<"                        You ARE SAFE            \n";
cout<<"\n\t\t"<<ob.p<<" "<<"Won! Congratulations! ";
cout<<"\n\n"<<"Press Enter to EXIT";
break;
}
}
if(wrong_guess == maxt)   //if no. of tries is exhausted
{
cout << "\n\t\tÞÞÞ So Sad! you have been hanged ÞÞÞ\n" << endl;
cout << "\t\t  The correct word was  \n " << "\t\t\t"<<"®®®"<<wd<<"¯¯¯" << endl;
cout<<"\n\t\t"<<ob.p<<" "<<"Lost! Better Luck Next Time";
cout<<"\n\n"<<"Press Enter to EXIT";
}
getch();

}

int L (char guess, char correctword[], char guessedword[])
{
//function to check if LETTER is correct incorrect or already entered
int i;
int m=0;
for (i = 0; guessedword[i]!='\0'; i++)  //to check if letter is already entered
if (guess == guessedword[i])            //the guessed word contains כ and the respective letter
return -1;                              //that is correctly guessed
for (i = 0; correctword[i]!='\0'; i++)
{

if (guess == correctword[i])      // if a letter matches
{
guessedword[i] = guess;
m++;
}
}
return m;
}

void I (char wd[], char s[])   //function to convert each letter to כ
{
int i;
int len = strlen(wd);
for (i = 0; i < len; i++)
s[i]='כ';
s[i]='\0';

}

int ret_user()
{
	int a[][2]={{0,0},{350,0},{0,196},{350,196}};
	for(int i=0;i<4;i++)
	{
		if((a[i][0]==ui)&&(a[i][1]==uj))
		return i;
	}

	return 1;
}
void execute(char c,int g)      //to run programs in individual folders
{
switch(c)
{
case 'r':                        //WRITABLES
switch(g)
{
case 0: settextjustify(LEFT_TEXT,TOP_TEXT);       note();break;
case 1:
case 2:
case 3:        break;
}  break;
case 'b':
switch(g)
{
case 0:                           //calculator
settextjustify(LEFT_TEXT,TOP_TEXT);
calc();
 break;
case 1:                       //calendar
settextjustify(LEFT_TEXT,TOP_TEXT);
cal();
   break;
case 2:                         //clock
settextjustify(LEFT_TEXT,TOP_TEXT);
clo();
 break;
}           break;
case 'g':                     //READABLES
switch(g)
{
case 0: break;
case 1: help();break;
case 2:
case 3:      break;
}              break;
case 'y':                    //GAMES
switch(g)
{
case 0:   //robox1();break;
case 1: hangman(b[ret_user()].n);   //HANGMAN
break;

}  break;
}
}
class mouse
{
public:

int c,x,y;
double dist(int x1,int y1,int x2,int y2)   //2-point distance function
{
float x=pow((x1-x2),2);
float y=pow((y1-y2),2);
double s=sqrt(x+y);
return s;
}
void mou(char &s);
mouse()  //default constuctor
{
c=x=y=0;
}
mouse(char &s)   //parameterized constructor
{
c=x=y=0;
s=' ';
mou(s);
setfillstyle(SOLID_FILL,WHITE); //normal fill style
}
};
//end of class

void assign1(float b[4][1][2],float x,float y)

//function to assign coordinates of a bar with length 45 and width 5
//with its centre  at (x,y)

{
b[0][0][0]=x-5;         //bottom left coordinate
b[0][0][1]=y-45;

b[1][0][0]=x+5;        //bottom right coordinate
b[1][0][1]=y-45;

b[2][0][0]=x-5;        //top left coordinate
b[2][0][1]=y+45;

b[3][0][0]=x+5;        //top right coordinate
b[3][0][1]=y+45;

}


void bar1(float a[4][1][2]);
void rotate(float cx,float cy,float angle,float a[1][2]);
int menu_tray(int color,int n,char *a1="",char *a2="",char *a3="",char *a4="",int space=200)
{
double s[4];
char **a;
a[0]=a1;           //saves all the strings in string array
a[1]=a2;
a[2]=a3;
a[3]=a4;

setfillstyle(SOLID_FILL,color);
setcolor(color);
for(int i=0;i<=space;i++)                //expansion of chosen menu
{
fillellipse(295-i,200,50,50);         //filled circle
fillellipse(295+i,200,50,50);
delay(2);
}
setfillstyle(SOLID_FILL,color-8);
setcolor(color-8);   //color-8 gives darker colour of color
for(i=0;i<n;i++)
fillellipse(295-space+i*(space*2)/(n-1),200,40,40);
setcolor(color);
for(i=0;i<n;i++)
{
settextjustify(1,1);
outtextxy(295-space+i*(space*2)/(n-1),200,a[i]);
}
l:
::i.x.ax=1;
int86(51,&::i,&o);
::i.x.ax=3;
int86(51,&::i,&o);
int x1=o.x.cx;
int y1=o.x.dx;
int z1=o.x.bx;
mouse m;
for(i=0;i<4;i++)
s[i]=m.dist(295-space+i*(space*2)/(n-1),200,x1,y1);
for(i=0;i<4;i++)
{
if(s[i]<40)
{
if(z1==1)
{
::i.x.ax=1;
int86(51,&::i,&o);
::i.x.ax=2;
int86(51,&::i,&o);

return i;
}
}
}

goto l;
}

void catchball(int x,int y,float angle,int ad=0,int ch=0)
{
float a[4][1][2];
assign1(a,x,y);
bar1(a);
assign1(a,x+7,y-50);
for(int i=0;i<4;i++)
rotate(x+7,y-50,M_PI/2,a[i]);
bar1(a);
assign1(a,x-7,y-50);
for(i=0;i<4;i++)
rotate(x-7,y-50,M_PI/2,a[i]);
bar1(a);
assign1(a,x+ad-7-45/1.414-40,y-50-45/1.414);
for(i=0;i<4;i++)
rotate(x+ad-7-45/1.414-40,y-50-45/1.414,-(angle),a[i]);
bar1(a);
assign1(a,x-ad+7+45/1.414+40,y-50-45/1.414);
for(i=0;i<4;i++)
rotate(x-ad+7+45/1.414+40,y-50-45/1.414,(angle),a[i]);
bar1(a);
if(ch==1)
{
for(int i=0;i<20;i++)
{

setcolor(color);
catchball(x,y,angle,i);
delay(5);
setcolor(BLACK);
catchball(x,y,angle,i);
}
setcolor(color);
catchball(x,y,angle,i);

}
if(ch==2)
{
setcolor(BLACK);
catchball(x,y-1,angle,20+1);

for(int i=20;i>=0;i--)
{

setcolor(color);
catchball(x,y,angle,i);
delay(5);
setcolor(BLACK);
catchball(x,y,angle,i);
}
setcolor(color);
catchball(x,y,angle,i);

}

}
void caughtball_move(char op)
{
int x,y;
void *p;
int size;
switch(op)
{
case 'r':
setcolor(BLACK);
line(300,0,493.150757,51.892006);
size=imagesize(541-50-15,169-155-5,541+60+5,169+40+5);
p=malloc(size);
getimage(541-50-15,169-155-5,541+60+5,169+40+5,p);
for(x=541,y=169;x>300,y<456; )
{
{setcolor(LIGHTCYAN);
line(300,0,399.95401,173.231628);
circle(424.942505,216.539536,50);
settextjustify(1,1);
outtextxy(424,216.539536,cs[2]);
settextjustify(0,2);

}
putimage(x-50-15,y-155-5,p,COPY_PUT);
if(x>300)
x-=2;
if(y<456)
y+=2;
}
free(p);
break;
case 'b':
setcolor(BLACK);
line(300,0,399.95401,173.231628);

size=imagesize(424-50-15,321-155-5,424+60+5,321+40+5);
p=malloc(size);
getimage(424-50-15,321-155-5,424+60+5,321+40+5,p);

for(x=424,y=321;x>300,y<456; )
{
putimage(x-50-15,y-155-5,p,COPY_PUT);

if(x>300)
x--;
if(y<456)
y++;
}
free(p);
break;
case 'y':setcolor(BLACK);
line(300,0,200.04599,173.231628);

size=imagesize(175-50-15,321-155-5,175+60+5,321+40+5);
p=malloc(size);
getimage(175-50-15,321-155-5,175+60+5,321+40+5,p);

for(x=175,y=321;x<300,y<456; )
{
putimage(x-50-15,y-155-5,p,COPY_PUT);

if(x<300)
x++;
if(y<456)
y++;
}
free(p);
break;
case 'g':setcolor(BLACK);
line(300,0,106.849228,51.892006);
line(0,0,0,getmaxy());
size=imagesize(0,0,58+60+5+7,169+40+5);
p=malloc(size);
getimage(0,0,50+60+5+7,169+40+5,p);


for(x=58,y=169;x<300,y<456; )
{
{  setcolor(YELLOW);
line(300,0,200.04599,173.231628);
circle(175.05748,216.539536,50);
settextjustify(1,1);
outtextxy(175,216.539536,cs[3]);
settextjustify(0,2);
}

putimage(x-58,y-169,p,COPY_PUT);
setcolor(color);
rectangle(x-50-15+2,y-130+3,x-50-15+10+2,y-155-12+130);
setcolor(BLACK);
rectangle(x-2-50-15+2,y-2-130+3,x-2-50-15+10+2,y-2-155-12+130);
rectangle(x-1-50-15+2,y-1-130+3,x-1-50-15+10+2,y-1-155-12+130);
if(x<300)
x+=2;
if(y<456)
y+=2;
}
free(p);
break;

}
}
void catchball_move(char op)
{
int x,y;
float x1;
switch(op)
{
case 'r':
color=RED;
for(x=300,y=456;x<541,y>169; )
{
{setcolor(LIGHTCYAN);
line(300,0,399.95401,173.231628);
circle(424.942505,216.539536,50);
settextjustify(1,1);
outtextxy(424,216.539536,cs[2]);
settextjustify(0,2);

}
setcolor(color);
catchball(x,y,M_PI/6);
delay(5);
setcolor(BLACK);
catchball(x,y,M_PI/6);
if(x<541)
x++;
if(y>169)
y--;
}
setcolor(color);
catchball(x,y,M_PI/6);
for(x1=M_PI/6;x1>=0;x1-=0.01)
{
setcolor(color);
catchball(x,y,x1);
delay(5);
setcolor(BLACK);
catchball(x,y,x1);
}
setcolor(color);
catchball(x,y,x1+0.01,0,1);
break;
case 'b':
color=CYAN;
for(x=300,y=456;x<424,y>321; )
{
{setcolor(LIGHTCYAN);
line(300,0,399.95401,173.231628);
circle(424.942505,216.539536,50);
settextjustify(1,1);
outtextxy(424,216.539536,cs[2]);
settextjustify(0,2);

}

setcolor(color);
catchball(x,y,M_PI/6);
delay(5);
setcolor(BLACK);
catchball(x,y,M_PI/6);
if(x<424)
x++;
if(y>321)
y--;
}
setcolor(color);
catchball(x,y,M_PI/6);
for(x1=M_PI/6;x1>=0;x1-=0.01)
{
setcolor(color);
catchball(x,y,x1);
delay(5);
setcolor(BLACK);
catchball(x,y,x1);
}
setcolor(color);
catchball(x,y,x1+0.01,0,1);
break;
case 'y':
color=YELLOW;
for(x=300,y=456;x>175,y>321; )
{
{setcolor(LIGHTCYAN);
line(300,0,399.95401,173.231628);
circle(424.942505,216.539536,50);
settextjustify(1,1);
outtextxy(424,216.539536,cs[2]);
settextjustify(0,2);

}
//if(i>=3.14/6)
{  setcolor(YELLOW);
line(300,0,200.04599,173.231628);
circle(175.05748,216.539536,50);
settextjustify(1,1);
outtextxy(175,216.539536,cs[3]);
settextjustify(0,2);
}
setcolor(color);
catchball(x,y,M_PI/6);
delay(5);
setcolor(BLACK);
catchball(x,y,M_PI/6);
if(x>175)
x--;
if(y>321)
y--;
}
setcolor(color);
catchball(x,y,M_PI/6);
for(x1=M_PI/6;x1>=0;x1-=0.01)
{
setcolor(color);
catchball(x,y,x1);
delay(5);
setcolor(BLACK);
catchball(x,y,x1);
}
setcolor(color);
catchball(x,y,x1+0.01,0,1);
break;
case 'g':
color=GREEN;
for(x=300,y=456;x>58,y>169; )
{
{setcolor(LIGHTCYAN);
line(300,0,399.95401,173.231628);
circle(424.942505,216.539536,50);
settextjustify(1,1);
outtextxy(424,216.539536,cs[2]);
settextjustify(0,2);

}
//if(i>=3.14/6)
{  setcolor(YELLOW);
line(300,0,200.04599,173.231628);
circle(175.05748,216.539536,50);
settextjustify(1,1);
outtextxy(175,216.539536,cs[3]);
settextjustify(0,2);
}
setcolor(color);
catchball(x,y,M_PI/6);
delay(5);
setcolor(BLACK);
catchball(x,y,M_PI/6);
if(x>58)
x--;
if(y>169)
y--;
}
setcolor(color);
catchball(x,y,M_PI/6);
for(x1=M_PI/6;x1>=0;x1-=0.01)
{
setcolor(color);
catchball(x,y,x1);
delay(5);
setcolor(BLACK);
catchball(x,y,x1);
}
setcolor(color);
catchball(x,y,x1+0.01,0,1);
break;
}
}
void men(char c)
{
::i.x.ax=2;
int86(0x33,&::i,&o);

void *p;int size;
cleardevice();
{
setcolor(LIGHTRED);
line(300,0,493.150757,51.892006);
circle(541.438477,64.865005,50);
settextjustify(1,1);
outtextxy(541,64.865005,cs[1]);
settextjustify(0,2);
}
//if(i>=-3.14/6)
{setcolor(LIGHTCYAN);
line(300,0,399.95401,173.231628);
circle(424.942505,216.539536,50);
settextjustify(1,1);
outtextxy(424,216.539536,cs[2]);
settextjustify(0,2);

}
//if(i>=3.14/6)
{  setcolor(YELLOW);
line(300,0,200.04599,173.231628);
circle(175.05748,216.539536,50);
settextjustify(1,1);
outtextxy(175,216.539536,cs[3]);
settextjustify(0,2);
}
//if(i>=5*3.14/12)
{ setcolor(LIGHTGREEN);
line(300,0,106.849228,51.892006);
circle(58.561539,64.865005,50);
settextjustify(1,1);
outtextxy(58,64.865005,cs[0]);
settextjustify(0,2);

}

cleardevice();
{
setcolor(LIGHTRED);
line(300,0,493.150757,51.892006);
circle(541.438477,64.865005,50);
settextjustify(1,1);
outtextxy(541,64.865005,cs[1]);
settextjustify(0,2);
}
//if(i>=-3.14/6)
{setcolor(LIGHTCYAN);
line(300,0,399.95401,173.231628);
circle(424.942505,216.539536,50);
settextjustify(1,1);
outtextxy(424,216.539536,cs[2]);
settextjustify(0,2);

}
//if(i>=3.14/6)
{  setcolor(YELLOW);
line(300,0,200.04599,173.231628);
circle(175.05748,216.539536,50);
settextjustify(1,1);
outtextxy(175,216.539536,cs[3]);
settextjustify(0,2);
}
//if(i>=5*3.14/12)
{ setcolor(LIGHTGREEN);
line(300,0,106.849228,51.892006);
circle(58.561539,64.865005,50);
settextjustify(1,1);
outtextxy(58,64.865005,cs[0]);
settextjustify(0,2);

}

catchball_move(c);
caughtball_move(c);
for(int i=0;i<getmaxx();i++)
for(int j=0;j<300;j++)
{
putpixel(i,j,BLACK);
}
catchball(300,456,0,20,2);
size=imagesize(245,300,355,450);
p=malloc(size);
int g=-1;
getimage(245,300,355,450,p);
for(int y=0;y<150;y++)
putimage(245,300-y,p,COPY_PUT);
switch(c)
{
case 'r': g=menu_tray(LIGHTRED,2,"NOTEPAD","","","",75);break;
case 'g': g=menu_tray(LIGHTGREEN,2,"COMICS","","","",75);break;
case 'b': g=menu_tray(LIGHTCYAN,3,"CALCULATOR","CALENDAR","CLOCK");break;
case 'y': g=menu_tray(YELLOW,2,"ROBOX","HANGMAN","","",75);break;
}
execute(c,g);
::i.x.ax=1;
int86(51,&::i,&o);
free(p);

}
void mouse::mou(char &s)
{                         //snapshot of interface

{
setcolor(LIGHTRED);
line(300,0,493.150757,51.892006);
circle(541.438477,64.865005,50);
settextjustify(1,1);
outtextxy(541,64.865005,cs[1]);
settextjustify(0,2);
}
//if(i>=-3.14/6)
{setcolor(LIGHTCYAN);
line(300,0,399.95401,173.231628);
circle(424.942505,216.539536,50);
settextjustify(1,1);
outtextxy(424,216.539536,cs[2]);
settextjustify(0,2);

}
//if(i>=3.14/6)
{  setcolor(YELLOW);
line(300,0,200.04599,173.231628);
circle(175.05748,216.539536,50);
settextjustify(1,1);
outtextxy(175,216.539536,cs[3]);
settextjustify(0,2);
}
//if(i>=5*3.14/12)
{ setcolor(LIGHTGREEN);
line(300,0,106.849228,51.892006);
circle(58.561539,64.865005,50);
settextjustify(1,1);
outtextxy(58,64.865005,cs[0]);
settextjustify(0,2);

}
{
setcolor(WHITE);
rectangle(x1,y1,x2,y2);
line(x1,((y1+y2)/2),x2,((y1+y2)/2));
line(x1+40,y1,x1+40,y2);
line(x1+20,y1+22,x1+20,y1+8);
arc(x1+20,y1+22,120,420,10);
outtextxy(x1+55,y1+20,"SHUTDOWN");
outtextxy(x1+55,y1+65,"LOGOUT");
setfillstyle(SOLID_FILL,YELLOW);
fillellipse(x1+20,y1+77,7,7);
bar(x1+22,y1+70,x1+20,y1+50);
bar(x1+20,y1+50,x1+13,y1+55);
bar(x1+20,y1+59,x1+13,y1+64);

}
//circle(200,100,20);
int a[][2]={{541,64},{424,216},{175,216},{58,64}}; //centers of circles
char b[]="rbyg";      //colours
i.x.ax=1;                      //mouse mode to show mouse
int86(0x33,&i,&o);                                       //changing i and o
if(f12==0)  //so that its executed only once
{
i.x.ax=4;                                   //to set the position of mouse
i.x.cx=getmaxx()/2;
i.x.dx=getmaxy()/2;
int86(0x33,&i,&o);
f12++;                         //changing f12 so that f12!=0
}
h:
c=0;

do
{
			 //mouse mode to input dynamic mouse variables
i.x.ax=3;
int86(0x33,&i,&o);       //changing values of i and o
c=o.x.bx;                //click state
x=o.x.cx;                //x coordinate
y=o.x.dx;                //y coordinate
if((x>x1)&&(y>((y1+y2)/2))&&(x<x2)&&(y<y2)&&(c==0))      //if mouse hovers over logout
{
setfillstyle(SOLID_FILL,WHITE);
fillellipse(x1+20,y1+77,7,7);
bar(x1+22,y1+70,x1+20,y1+50);
bar(x1+13,y1+50,x1+22,y1+55);
bar(x1+13,y1+59,x1+22,y1+64);

}
else                                                                    //if mouse does not hover
{
setfillstyle(SOLID_FILL,YELLOW);
fillellipse(x1+20,y1+77,7,7);
bar(x1+22,y1+70,x1+20,y1+50);
bar(x1+13,y1+50,x1+22,y1+55);
bar(x1+13,y1+59,x1+22,y1+64);
}
for(int j=0;j<4;j++)                 //loop to check all circles
{
if((x>x1)&&(y>y1)&&(x<x2)&&(y<((y1+y2)/2))&&(c==0))    //if mouse hovers over shutdown
{
for(int j=0;j<2;j++)
{
setcolor(WHITE);
if(j==0)
line(x1+21+j,y1+22,x1+21+j,y1+8); //line should be drawn only once
arc(x1+20,y1+22,120,420,11+j);
}
}
else
{
for(int j=0;j<5;j++)
{
setcolor(BLACK);
line(x1+21+j,y1+22,x1+21+j,y1+8); //it doesnt matter as colour is black
arc(x1+20,y1+22,120,420,11+j);
}
}
if((c==0)&&((dist(x,y,a[j][0],a[j][1]))<50))           //if mouse hovers over any circle
{                                                      //only one value of j satisfies one circle
switch(b[j])                                           //returns character for colour
{
case 'r':setcolor(RED);break;                          //calender
case 'g':setcolor(GREEN);break;                        //calculator
case 'b':setcolor(CYAN);break;                         //clock
case 'y':setcolor(YELLOW);break;                       //notepad
}
for(int t=0;t<5;t++)
{
circle(a[j][0],a[j][1],51+t);                          //highlight circle
}
}
else
{
for(int t=0;t<5;t++)                                   //lowlight circle
{
setcolor(BLACK);
circle(a[j][0],a[j][1],51+t);
}
}
}
i.x.ax=1;
int86(0x33,&i,&o);                                  //changing mouse mode repeatedly
}while((c!=1)&&(!kbhit()));                  //when click state is left click
for(int j=0;j<4;j++)
{
if((dist(x,y,a[j][0],a[j][1]))<50)                  //if clicked on any circle
s=b[j];
}
if((x>x1)&&(y>y1)&&(x<x2)&&(y<((y1+y2)/2)))
s=27;                                               //if clicked on shutdown
if((x>x1)&&(y>((y1+y2)/2))&&(x<x2)&&(y<y2))
s='l';
					//if clicked on logout


if(s==' ')
{
if(c!=1)
getch();
goto h;
}
}
char z[20];
char a2[4][20];
float b1[4][1][2];
int lk=0,y=0;
void rotate(float,float,float,float[1][2]);
char f1[][20]={"hello1.txt","hello2.txt","hello3.txt","hello4.txt"};



void bar1(float a[4][1][2])   //function to draw rectangle using coordinates
{

line(a[0][0][0],a[0][0][1],a[1][0][0],a[1][0][1]);
line(a[0][0][0],a[0][0][1],a[2][0][0],a[2][0][1]);
line(a[3][0][0],a[3][0][1],a[1][0][0],a[1][0][1]);
line(a[3][0][0],a[3][0][1],a[2][0][0],a[2][0][1]);
}
void assign(float b[4][1][2],float x,float y)

//function to assign coordinates of a bar with length 45 and width 5
//with its centre  at (x,y)

{
b[0][0][0]=x-5;         //bottom left coordinate
b[0][0][1]=y-45;

b[1][0][0]=x+5;        //bottom right coordinate
b[1][0][1]=y-45;

b[2][0][0]=x-5;        //top left coordinate
b[2][0][1]=y+45;

b[3][0][0]=x+5;        //top right coordinate
b[3][0][1]=y+45;

}
void icon(float b[4][1][2],float x,float y)
{
assign(b,x,y);
 bar1(b);
for(float k=0;k<=0.5;k+=0.1)
{
for(int i=0;i<4;i++)
rotate(x,y,k,b[i]);        //to rotate whole icon by 0.1 radians
for(int j=0;j<8;j++)       //  to
{                          //  draw
for(int i=0;i<4;i++)       //  the
rotate(x,y,M_PI/4,b[i]);   //  whole
bar1(b);                   //  wheel
}                          //  icon
setfillstyle(1,BLACK);
fillellipse(x,y,20,20);    //smaller filled black circle


delay(20);
fillellipse(x,y,49,49);    //filled circle to clear the circle of radius 50
}
setfillstyle(1,WHITE);      //default fillstyle
setcolor(WHITE);            //default color
}
void icon()
{
//function to draw default icon at base

float b[4][1][2]={{295,345},{305,345},{295,435},{305,435}};
bar1(b);
for(int j=0;j<8;j++)   //rotating 8 times to form icon
{
for(int i=0;i<4;i++)
rotate(300,390,M_PI/4,b[i]);
bar1(b);
}

setfillstyle(1,BLACK);
fillellipse(300,390,20,20);
setfillstyle(1,WHITE);


}
void icon(float b[4][1][2])
{
//function to rotate slowly


bar1(b);
for(float k=0;k<=0.5;k+=0.1)
{
for(int i=0;i<4;i++)
rotate(300,390,k,b[i]); //to rotate whole icon by 0.1 radians
for(int j=0;j<8;j++)          //to
{                             //draw
for(int i=0;i<4;i++)          //the
rotate(300,390,M_PI/4,b[i]);  //whole
bar1(b);                      //icon
}
setfillstyle(1,BLACK);



fillellipse(300,390,20,20);
delay(200);
fillellipse(300,390,49,49);

delay(50);
}

setfillstyle(1,WHITE);
}
void iok(char a[])   //input function when user enters password to login
{

lk=0;
int e=0,pos=0;
char c;
strcpy(a,"");          //by default blank strings
char a2[20]="";
do
{
cleardevice();                                                 //drawing entire image repeatedly
rectangle(getmaxx()/2-100,50,getmaxx()/2+100,250);
arc(getmaxx()/2,260,10,170,100);
circle(getmaxx()/2,110,50);
rectangle(getmaxx()/2-100,300,getmaxx()/2+100,330);
outtextxy(getmaxx()/2-90,310,a2);
c=getch();         //accepting character
switch(c)
{
case 8:               //if character is backspace key
if(pos)               //if its not the first character
{
pos--;
a[pos]=0;
a2[pos]=0;
}
break;
case 13:                  //if character is enter key
e=1;                      //flag function
break;
case 27:a[0]=0;           //string with first character \0 is null string
a2[0]=0;
e=1;
lk++;
break;
default:
if(pos<20 && c>=' ' && c<='~')
{             //in whole keyboard
		//' ' has lowest ascii
		//'~'has highest ascii

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

int user1(char a1[]) //function to check if password of given user is correct
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
if(strcmp(a,"OVERIDE")==0)  //master key
return 1;

if(strcmp(a,a1)==0)
return 1;
else if((strcmp(a,a1)!=0)&&(lk==0))
goto l;
else
return 0;

}
void user(int i,int j,char d[],char dd[],int y=0)  //function to print user option screen(ONLY ONE USER IMAGE)
{

//i and j are coordinates of each user image
//d is name
//dd is password
if(y==1)
{
setcolor(MAGENTA);             //highlight
::ui=i;
::uj=j;
}
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
void iop(char a[],char a1[])  //function to accept no. of users initially
{

			//a for accepting number
		       //a1="ENTER NO OF USERS"
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
h:
c=getch();
if((!isdigit(c))&&(c!=8)&&(c!=13)&&(c!=27))
goto h;
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
void ior(char a[],int i,int j,float k[][2],int c1)//function to accept user details
{
// a is the buffer string with a changed value given by function
//i and j are coordinates of user icon
// k is the array of coordinates of all user icons
//c1 is the number of users
char a1[20];
int gh;
if((i==0)&&(j==0))           //top left user icon
gh=0;
else if((i!=0)&&(j==0))      //top right user icon
gh=1;
else if((i==0)&&(j!=0))     //bottom left user icon
gh=2;
else                        //bottom right user icon
gh=3;
strcpy(a1,b[gh].n);  //copying username to a1 (VALUE OF A1 REMAINS CONTANT AFTER INITIALISATION)
//while typing username the value of orignal username string b[gh].n
//changes dynamically, so after one entry its not a blank string
//therefore another string a1 is used so that it will take initial value
//of b[gh].n | if a1 is blank then username has not been entered so it
//has to be entered using this function the value of a1 is responsible
//for many values such as rectangle enclosing and password display

int e=0,pos=0;           //e is to check if user is done entering or not
			 //
char c;
strcpy(a,"");
strcpy(a2[gh],"");  //a2 is used for password coding
settextstyle(0,HORIZ_DIR,1);
do
{
cleardevice();
for(int h=0;h<c1;h++)
user(k[h][0],k[h][1],b[h].n,((strcmp(a1,"")==0)?"analysing...":a2[h]));
//printing details of every user (while typing username password is
//"analysing...")
rectangle(185+i,110+j+((strcmp(a1,"")==0)?0:20),288+i,130+j+((strcmp(a1,"")==0)?0:20));
//rectangle enclosing
if(strcmp(a1,"")==0)
outtextxy(195+i,115+j,a);
//displaying what is typed if username has not being entered
else
outtextxy(195+i,115+j+20,a2[gh]);
//displaying password coded password
c=getch();
switch(c)
{             //pos acts as pointer for character being entered
case 8:       //backspace
if(pos)       //if first only backspace is pressed it should not
{             //do anything
pos--;
a[pos]=0;    //for a to be legible string last character should be '\0'
a2[gh][pos]=0; //for a2[gh] to be legible string last character should be '\0'
}
break;
case 13:     //enter
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
void u(int oh=0)         //function for entering and accessing users
{                       //oh=0 when user is not entered
			//oh=1 when user information present

int j;
int hk[2];
char b[20];
char d[50]="ENTER THE NO. OF USERS (MAXIMUM:4) ";
int h=1,s,i,c=oh;
float a[][2]={{0,0},{350,0},{0,350*9.0/16.0},{350,350*9.0/16.0}};
//starting coordinates of each icon
char k;

if(oh!=0)
goto lk;
s:


iop(b,d);                   //to accept no. of user in form of string(b)
c=atoi(b);

cleardevice();
if((c!=1)&&(c!=2)&&(c!=3)&&(c!=4))
c=1;
for(i=0;i<c;i++)
{
user(a[i][0],a[i][1],::b[i].n,::a2[i]);
o:
ior(::b[i].n,a[i][0],a[i][1],a,c);
if(strcmp(::b[i].n,"")==0)                       //user name cannot be blank
goto o;
if(strcmpi(::b[i].n,"BATMAN")==0)                //special user
{
   cleardevice();
   dat(getmaxx()/2-100,getmaxy()/2-150,"k.dat");
   setcolor(BLACK);
   outtextxy(getmaxx()/2-50,getmaxy()/2-62.5,"WELCOME BATMAN");
   setcolor(WHITE);
   settextjustify(CENTER_TEXT,CENTER_TEXT);
   settextstyle(10,HORIZ_DIR,1);
    outtextxy(getmaxx()/2,getmaxy()/2+100,"SUPERUSER ACCESS GRANTED");
   delay(2000);
   settextjustify(LEFT_TEXT,TOP_TEXT);
}
pass:
ior(::b[i].g,a[i][0],a[i][1],a,c);
if(strcmp(::b[i].g,"")==0)            //password cannot be blank
goto pass;
}

for(i=0;i<c;i++)
{
h=1;
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
setcolor(RED);
outtextxy(10,350*9.0/16.0+50,"OTHER OPTIONS WONT WORK(EXCEPT WINDOWS KEY)");
setcolor(WHITE);
goto k;
}
save_user(c);
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

int temp=0;                   //initiate two keys to move a month and back
cleardevice();
setcolor(WHITE);
setfillstyle(SOLID_FILL,WHITE);
i.x.ax=4;                                   //to set the position of mouse
i.x.cx=getmaxx()-2;
i.x.dx=getmaxy();
int86(0x33,&i,&o);
i.x.ax=2;                     //hiding mouse
int86(0x33,&i,&o);

char a[31][3],z[20],g,g1;
//g1 is the first key pressed
//g is the second key pressed
//z is a buffer string(dummy)
//a stores the date in string form
//b stores the last date of every month in order
char c[][12]={"JANUARY","FEBRUARY","MARCH","APRIL","MAY","JUNE","JULY","AUGUST","SEPTEMBER","OCTOBER","NOVEMBER","DECEMBER"};
char d[][4]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
int k=0,j,l,b[]={31,28,31,30,31,30,31,31,30,31,30,31,30,31},f;
for(int i=1;i<=31;i++)
{
if(i/10==0)      //1 digit date
{
a[i-1][0]=i+48;  //i+48 for int value of int character
a[i-1][1]='\0';  //end with \0
}
else             //2 digit date
{
a[i-1][0]=(i/10)+48;   //first digit of number
a[i-1][1]=(i%10)+48;   //second digit of number
a[i-1][2]='\0';
}
}
struct tm *time_now;           //time stucture
time_t secs_now;
int h,n1,n,day,day1;
tzset();
time(&secs_now);
time_now = localtime(&secs_now); //sets system time
strftime(z, 20,"%d",time_now);   //date in z
day=atoi(z);                     //int form of z ::day
strftime(z, 20,"%w",time_now);   //week in z
l=atoi(z)-((day-1)%7);

strftime(z, 20,"%m",time_now);   //month in z
n=atoi(z);                       //int form of z ::month
n1=n;                            //n1 in n
strftime(z, 20,"%Y",time_now);   //year in z
h=atoi(z);                       //int form of z ::year
int sd=h;                        //sd in h
for(f=n-1; ;)
{
sd=h;
if(((sd%4==0)&&(sd%100!=0))||(sd%400==0)) //check for leap year
b[1]=29;
else
b[1]=28;
k=0;
if(n>12)
{
h=h+1;
n-=12;
gcvt(h,4,z);
}
if(n<1)
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
settextjustify(CENTER_TEXT,CENTER_TEXT);
if((j==125)&&((i+l*80)<=545))
{

day1=atoi(a[k]);
if((day1==day)&&(n1==n))
{
setfillstyle(SOLID_FILL,LIGHTRED);
bar((i+l*80)-40,j-25,(i+l*80)+40,j+25);
setfillstyle(SOLID_FILL,BLACK);
bar((i+l*80)-35,j-20,(i+l*80)+35,j+20);
}
outtextxy(i+l*80,j,a[k]);
if((i+l*80)==545)
{
k++;
break;
}
}
else
{
day1=atoi(a[k]);
if((day1==day)&&(n1==n))
{
setfillstyle(SOLID_FILL,LIGHTRED);
bar((i)-40,j-25,(i)+40,j+25);
setfillstyle(SOLID_FILL,BLACK);
bar((i)-35,j-20,(i)+35,j+20);
}
//rectangle((i)-35,j-20,(i)+35,j+20);
outtextxy(i,j,a[k]);
}
settextjustify(LEFT_TEXT,TOP_TEXT);
}
}
if(temp==0)
g1=0;
else if(temp==1)
g1=0;
else
g1=getch();
switch(g1)
{
case 0:
if(temp==0)
{
g=75;
temp++;
}
else if(temp==1)
{
g=77;
temp++;
}
else
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
::i.x.ax=1;
int86(0x33,&::i,&o);
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
 ;
int86(0x33,&i,&o);
char a[50]="ENTER THE TIME IN THE FORMAT HH:MM:SS ";
cleardevice();
io(b,a);
}
void ginp(char a[],char a1[])
{
 ;
int86(0x33,&i,&o);
//clrscr();
//int gd=DETECT,gm;
//initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

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
 ;
int86(0x33,&i,&o);
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

void note1(int a)
{
a++;
ofstream f;
ofstream f2;
for(int i=0;i<4;i++)
{
  f2.open(f1[i]);
 f.open(f1[i],ios::out);
 char s[21]="ENTER YOUR TEXT HERE";
 f<<s;
 f.close();
 }
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
 ;
int86(0x33,&i,&o);
cleardevice();
int a;
char h[10],m[10],s[10],h1[]="ENTER THE NO. OF HOURS:",m1[]="ENTER THE NO. OF MINUTES:",s1[]="ENTER THE NO. OF SECONDS:";
//int gd=DETECT,gm;
//initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
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
 ;
int86(0x33,&i,&o);
settextstyle(2,HORIZ_DIR,10);
setcolor(GREEN);
cleardevice();
char k='a',k12;
char f=k;
time_t t;
char a[20],b[10];
struct tm *time_now;
int ik=0;
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
if(ik==0)
delay(1000);
ik=0;
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
ik=1;
f=k;
goto d;
}
l:
setfillstyle(1,WHITE);
}

void inpu(char a[20])
{
 ;
int86(0x33,&i,&o);
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
h:
c=getch();
if(isalpha(c))
goto h;
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
 ;
int86(0x33,&i,&o);
//int gd=DETECT,gm;
//initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
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
 ;
int86(0x33,&i,&o);
//float a[1][2]={{300,200}},b[1][2]={{300,250}},c[1][2]={{298,210}},d[1][2]={{302,250}};

for(float i=-3.14/2;i<=4.14/2;i+=0.1)
{
float a1[][1][2]={{300,300},{300,340},{300,390},{300,200},{300,250},{298,210},{302,250}};
//float b[4][1][2]={{295,345},{305,345},{295,435},{305,435}};
cleardevice();
delay(10);
if(i>=5*-3.14/12 )
{
setcolor(LIGHTRED);
line(300,0,493.150757,51.892006);
circle(541.438477,64.865005,50);
settextjustify(1,1);
outtextxy(541,64.865005,cs[1]);
settextjustify(0,2);
}
if(i>=-3.14/6)
{setcolor(LIGHTCYAN);
line(300,0,399.95401,173.231628);
circle(424.942505,216.539536,50);
settextjustify(1,1);
outtextxy(424,216.539536,cs[2]);
settextjustify(0,2);

}
if(i>=3.14/6)
{  setcolor(YELLOW);
line(300,0,200.04599,173.231628);
circle(175.05748,216.539536,50);
settextjustify(1,1);
outtextxy(175,216.539536,cs[3]);
settextjustify(0,2);
}
if(i>=5*3.14/12)
{ setcolor(LIGHTGREEN);
line(300,0,106.849228,51.892006);
circle(58.561539,64.865005,50);
settextjustify(1,1);
outtextxy(58,64.865005,cs[0]);
settextjustify(0,2);

}

for(int ik=0;ik<7;ik++)
{
rotate(300,0,i,a1[ik]);
}
if(((a1[2][0][0]+50)>getmaxx())||((a1[2][0][0]-50)<0))
{
for(int ki=0;ki<3;ki++)
rotate(a1[4][0][0],a1[4][0][1],-i,a1[ki]);
}
for(int j=0;j<3;j++)
{
line(300+j,0+j,a1[3][0][0]+j,a1[3][0][1]+j);
circle(a1[4][0][0],a1[4][0][1],50+j);
line(a1[0][0][0]+j,a1[0][0][1]+j,a1[1][0][0]+j,a1[1][0][1]+j);
circle(a1[2][0][0],a1[2][0][1],50+j);
}
for(int k=0;k<7;k++)
arc(a1[4][0][0],a1[4][0][1],120-(i*180/3.14),420-(i*180/3.14),35-k);
line(a1[5][0][0],a1[5][0][1],a1[6][0][0],a1[6][0][1]);
icon(b1,a1[2][0][0],a1[2][0][1]);
//delay(100);
}
}
void start1()
{
 ;
int86(0x33,&i,&o);
settextjustify(LEFT_TEXT,TOP_TEXT);
settextstyle(0,HORIZ_DIR,1);
//float a[1][2]={{300,200}},b[1][2]={{300,250}},c[1][2]={{298,210}},d[1][2]={{302,250}};

for(float i=4.14/2;i>=-3.14/2;i-=0.1)
{
float a1[][1][2]={{300,300},{300,340},{300,390},{300,200},{300,250},{298,210},{302,250}};
cleardevice();
delay(10);
if(i>=5*-3.14/12 )
{
setcolor(LIGHTRED);
line(300,0,493.150757,51.892006);
circle(541.438477,64.865005,50);
settextjustify(1,1);
outtextxy(541,64,cs[1]);
settextjustify(0,2);

}
if(i>=-3.14/6)
{setcolor(LIGHTCYAN);
line(300,0,399.95401,173.231628);
circle(424.942505,216.539536,50);
settextjustify(1,1);
outtextxy(424,216.539536,cs[2]);
settextjustify(0,2);

}
if(i>=3.14/6)
{  setcolor(YELLOW);
line(300,0,200.04599,173.231628);
circle(175.05748,216.539536,50);
settextjustify(1,1);
outtextxy(175,216.539536,cs[3]);
settextjustify(0,2);

}
if(i>=5*3.14/12)
{ setcolor(LIGHTGREEN);
line(300,0,106.849228,51.892006);
circle(58.561539,64.865005,50);
settextjustify(1,1);
outtextxy(58,64,cs[0]);
settextjustify(0,2);

}

for(int ik=0;ik<7;ik++)
rotate(300,0,i,a1[ik]);
if(((a1[2][0][0]+50)>getmaxx())||((a1[2][0][0]-50)<0))
{
for(int ki=0;ki<3;ki++)
rotate(a1[4][0][0],a1[4][0][1],-i,a1[ki]);
}
for(int j=0;j<3;j++)
{
line(300+j,0+j,a1[3][0][0]+j,a1[3][0][1]+j);
circle(a1[4][0][0],a1[4][0][1],50+j);
line(a1[0][0][0]+j,a1[0][0][1]+j,a1[1][0][0]+j,a1[1][0][1]+j);
circle(a1[2][0][0],a1[2][0][1],50+j);
}
for(int k=0;k<7;k++)
arc(a1[4][0][0],a1[4][0][1],120-(i*180/3.14),420-(i*180/3.14),35-k);


line(a1[5][0][0],a1[5][0][1],a1[6][0][0],a1[6][0][1]);
icon(b1,a1[2][0][0],a1[2][0][1]);
//delay(100);
}
}
void ini()
{

 ;
int86(0x33,&i,&o);
for(float i=0;i>=-3.14/2;i-=0.1)
{
cleardevice();

float a1[][1][2]={{300,300},{300,340},{300,390},{300,200},{300,250},{298,210},{302,250}};

rotate(300,0,i,a1[3]);
rotate(300,0,i,a1[4]);

for(int ik=0;ik<3;ik++)
rotate(300,0,i,a1[ik]);
if((a1[2][0][0]+50)>getmaxx())
{
for(int ki=0;ki<3;ki++)
rotate(a1[4][0][0],a1[4][0][1],-i,a1[ki]);
}
for(int j=0;j<3;j++)
{
line(300+j,0+j,a1[3][0][0]+j,a1[3][0][1]+j);
circle(a1[4][0][0],a1[4][0][1],50+j);
line(a1[0][0][0]+j,a1[0][0][1]+j,a1[1][0][0]+j,a1[1][0][1]+j);
circle(a1[2][0][0],a1[2][0][1],50+j);
}
for(int k=0;k<7;k++)
arc(a1[4][0][0],a1[4][0][1],120-(i*180/3.14),420-(i*180/3.14),35-k);
rotate(298,0,i,a1[5]);
rotate(302,0,i,a1[6]);
line(a1[5][0][0],a1[5][0][1],a1[6][0][0],a1[6][0][1]);
icon(b1,a1[2][0][0],a1[2][0][1]);
setfillstyle(1,WHITE);
//delay(100);
}
}
void ini1()
{
 ;
int86(0x33,&i,&o);
//float a[1][2]={{300,200}},b[1][2]={{300,250}},c[1][2]={{298,210}},d[1][2]={{302,250}};
for(float i=-3.14/2;i<=0;i+=0.1)
{
float a1[][1][2]={{300,300},{300,340},{300,390},{300,200},{300,250},{298,210},{302,250}};
cleardevice();
for(int ik=0;ik<7;ik++)
rotate(300,0,i,a1[ik]);
if((a1[2][0][0]+50)>getmaxx())
{
for(int ki=0;ki<3;ki++)
rotate(a1[4][0][0],a1[4][0][1],-i,a1[ki]);
}
for(int j=0;j<3;j++)
{
line(300+j,0+j,a1[3][0][0]+j,a1[3][0][1]+j);
circle(a1[4][0][0],a1[4][0][1],50+j);
line(a1[0][0][0]+j,a1[0][0][1]+j,a1[1][0][0]+j,a1[1][0][1]+j);
circle(a1[2][0][0],a1[2][0][1],50+j);
}
for(int k=0;k<7;k++)
arc(a1[4][0][0],a1[4][0][1],120-(i*180/3.14),420-(i*180/3.14),35-k);

line(a1[5][0][0],a1[5][0][1],a1[5][0][0],a1[5][0][1]);
icon(b1,a1[2][0][0],a1[2][0][1]);
//delay(100);
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
char ch;
//note1(3);
char doll[50];
char dol[50][50];
char hk[]="TURBO OS ";
char hkh[9][9];
int kh;
int i;
int g;
for(i=0;i<strlen(hk);i++)
{
for(kh=0;kh<=i;kh++)
hkh[i][kh]=hk[kh];
hkh[i][kh]='\0';
}
int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
ifstream fin("u.txt",ios::in);
while(!fin.eof())
{
fin.get(ch);
if(ch=='y')
break;
}
fin.close();
if(ch!='y')
u();
else
{
g=get_user();
u(g);
}


kl:
for(i=0;i<=200;i++)                  //dynamic drawing of initial line
{
delay(3);
circle(300,0+i,2) ;
}
for(float j=0;j<=6.28;j+=0.01)     //dynamic drawing of circle
{
delay(3);
circle(300+50*cos(j+(1.52*3.14)),250+50*sin(j+(1.52*3.14)),1);
}
for(j=0;j<=6.28-(0.35*3.14);j+=0.01)    //dynamic drawing of arc
{
delay(3);
circle(300+30*cos(j+(1.65*3.14)),250+30*sin(j+(1.65*3.14)),2);
}
for(i=0;i<41;i++)
{
delay(10);
circle(300,210+i,0.5);                     //dynamic drawing of power button line
circle(300,300+i,0.5);                     //dynamic drawing of stalk of icon
}
for(j=0;j<=6.28;j+=0.01)                   //dynamic drawing of icon circle
{
delay(3);
circle(300+50*cos(j+(1.52*3.14)),390+50*sin(j+(1.52*3.14)),1);
}
float b[4][1][2]={{295,345},{305,345},{295,435},{305,435}};
icon();                                    //function call to draw icon
setcolor(GREEN);
char kc[50]="RECALIBRATING RESOLUTION FOR THIS COMP." ;
char ck[50],ckc[50]="INITIALIZING ALL DRIVES...",kck[]="CHECKING SYSTEM STATUS....";
for(i=0;i<strlen(kc);i++)     //printing RECALIBRATING RESOLUTION letter by letter
{
ck[i]=kc[i];
ck[i+1]='\0';
outtextxy(getmaxx()/2,20,ck);
delay(20);
}
delay(3000);                   //3 second pause
setcolor(WHITE);
cleardevice();                //drawing static image using graphical function
bar(298,0,300,200);           //drawing initial line
bar(298,300,302,340);         //drawing stalk line
for(i=0;i<3;i++)              //drawing both the circles
{
circle(300,250,50+i);
circle(300,390,50+i);
}
for(i=0;i<7;i++)
arc(300,250,120,420,35-i);     //drawing arc of power button
line(300,210,300,250);         //drawing power button line
outtextxy(100,100,"HOLD DOWN THE 'H' KEY");
outtextxy(350,30,kck);         //printing TURBO OS
dat(400,220,"j.dat");			 //FINGERPRINT DISPLAY
icon();                        //function call to draw static icon
setcolor(LIGHTRED);
outtextxy(1,0,ckc);            //printing initializing all drives

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
outtextxy(100,325,hkh[j/20]);
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

//float b[4][1][2]={{295,345},{305,345},{295,435},{305,435}};
int r[4]={12,11,14,10};
for(int ki=0;ki<4;ki++)
{
setcolor(r[ki]);
cleardevice();
bar(298,0,300,200);
bar(298,300,302,340);
for(i=0;i<3;i++)
{
circle(300,250,50+i);
circle(300,390,50+i);    //NEW CIRCLE
}
for(i=0;i<7;i++)
arc(300,250,120,420,35-i);
line(300,210,300,250) ;
icon(b);
}
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
settextjustify(1,1);
outtextxy(541,64.865005,cs[1]);
settextjustify(0,2);
}
//if(i>=-3.14/6)
{setcolor(LIGHTCYAN);
line(300,0,399.95401,173.231628);
circle(424.942505,216.539536,50);

settextjustify(1,1);
outtextxy(424,216.539536,cs[2]);
settextjustify(0,2);

}
//if(i>=3.14/6)
{  setcolor(YELLOW);
line(300,0,200.04599,173.231628);
circle(175.05748,216.539536,50);
settextjustify(1,1);
outtextxy(175,216.539536,cs[3]);
settextjustify(0,2);
}
//if(i>=5*3.14/12)
{ setcolor(LIGHTGREEN);
line(300,0,106.849228,51.892006);
circle(58.561539,64.865005,50);
settextjustify(1,1);
outtextxy(58,64.865005,cs[0]);
settextjustify(0,2);
}
//ins();
char s;
::i.x.ax=1;
int86(0x33,&::i,&o);
mouse ob(s);
if((s=='g')||(s=='G'))
{
men('g');
goto l;
}
else if((s=='y')||(s=='Y'))
{
men('y');
goto l;
}
else if((s=='B')||(s=='b'))
{
men('b');
goto l;
}
else if((s=='R')||(s=='r'))
{
men('r');
goto l;
}

else if(s==27)
{
::i.x.ax=2;
int86(51,&::i,&o);
//float a1[][1][2]={{300,300},{300,340},{300,390},{300,200},{300,250},{298,210},{302,250}};
cleardevice();
settextjustify(CENTER_TEXT,CENTER_TEXT);
settextstyle(1,HORIZ_DIR,2);
setcolor(LIGHTGREEN);
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
int r[]={12,11,14,10,15};
for(int ki=0;ki<5;ki++)
{
setcolor(r[ki]);
cleardevice();
bar(298,0,300,200);
bar(298,300,302,340);
for(i=0;i<3;i++)
{
circle(300,250,50+i);
circle(300,390,50+i);    //NEW CIRCLE
}
for(i=0;i<7;i++)
arc(300,250,120,420,35-i);
line(300,210,300,250) ;
icon(b);
}
exit(0);
}
else if((s=='l')||(s=='L'))
goto sh;
else
goto l;
sh:
cleardevice();
setcolor(WHITE);
if(user1(::b[y].g)==1)
{}
else
{
y=0;
::i.x.ax=4;
int86(51,&::i,&o);
o.x.cx=getmaxx()/2;
o.x.dx=getmaxx()/2;
::i.x.ax=2;
int86(51,&::i,&o);

u(g);
}
cleardevice();
goto kl;
}
