#define _CRT_SECURE_NO_WARNINGS
# include "iGraphics.h"
#include <stdlib.h>
#include <string.h>

int winx=800,winy=650;
int mousex,mousey;

int step=1;

int mykeyx[26],mykeyy[26];
int showstrx[20],showstry[20];

int gap=40;

char ansstr[100],showstr[100];
int ansstrlen;
int squarex=30;
int textx=10,texty=10;
int hint=0,hintx=355 ,hinty=510 ;
char hintstr[100]="my name\nthis\nis fun\n";

int newgamex=230,newgamey=570,newgamewidth=300,newgamehight=64;

int catagoryx[15],catagoryy[15],catagorywidth=225,catagoryhight=75,catagorygap=15,catagoryloadedflag=0,catagorynum=0;
char catagoryname[12][25]={"animals","food","transpord","colours","cloting","country","bodyparts","home","random"};
int loadflag=0;
int alertbox=0,alertboxwidth=400 ,alertboxhight=300 ,alertboxx=winx/2-alertboxwidth/2 ,alertboxy=(winy-alertboxhight)/2  ;

time_t start,end;

int lifelineremain=5,lifelineon=0,lifelinex=360,lifeliney=550,lifelinewidth=256,lifelinehight=64;

/*
	function iDraw() is called again and again by the system.

	*/

void load();

int isrange(int x,int y,int widx,int widy,int valuex=mousex,int valuey=mousey)
{
    if (valuex<x || valuex>(x+widx))
    {
        return 0;
    }
    if (valuey<y || valuey >(y+widy))
    {
        return 0;
    }
    else return 1;
}
void showalertbox()
{
    if (alertbox)
    {
        iSetColor(255,128,0);
	    iFilledRectangle(alertboxx,alertboxy,alertboxwidth,alertboxhight);
	    iShowBMP(alertboxx+alertboxwidth-32,alertboxy+alertboxhight-32,"closeimage.bmp");

    }
}

void loadcatagory()
{
    int cox=60,coy=280;
    int i,j,l=0;

    for (i=0;i<3;i++)
    {
        for (j=0;j<3;j++)
        {
            catagoryx[l]=cox;
            catagoryy[l]=coy;
            l++;

            cox+=catagorywidth+catagorygap;



        }
        cox=60;
        coy-=88;

    }

}

int clickcatagory()
{
    int i;
    for (i=0;i<9;i++)
    {
        if (isrange(catagoryx[i],catagoryy[i],catagorywidth,catagoryhight))
        {
            printf ("you have clicked the catagory number: %d\n", i+1);
            step=3;
            load();
            catagorynum=i;
            start=time(NULL);




            return i+1;
        }
    }
}

void uselifeline()
{
    int i;
    for (i=0;i<ansstrlen;i++)
    {
        if (isrange(showstrx[i],showstry[i],gap,gap))
        {
            showstr[i]=ansstr[i];
            lifelineon=0;
            lifelineremain--;
            return ;
        }
    }

}

void myworddraw(char str[])
{
 //   printf ("my word draw\n");
	int len=strlen(str);
    int i;
	int inix=350;
	int iniy=300;
	char strtemp[4];
	int j=0;
	for (i=inix;i<inix+len*gap;i+=gap,j++)
	{
	    int cox=i,coy=iniy;
	    iSetColor(188,84,152);
	    iFilledRectangle(cox,coy,squarex,squarex);
	    iSetColor(0,0,0);
		strtemp[0]=str[j];
		strtemp[1]='\0';
		iText(i+textx,iniy+texty,strtemp,GLUT_BITMAP_HELVETICA_18);

		showstrx[j]=cox;
		showstry[j]=coy;


	}

}

void inttotime(char str[],int n)
{

    int a=n/60;
    int b=n%60;
    itoa(a,str,10);
  //  printf ("%s\n",str);
    strcat(str,":");
 //   printf ("%s\n",str);
    char str2[5];
    itoa(b,str2,10);
    strcat(str,str2);

  //  printf ("%s",str);



}

void screenkeyboard()
{
    int i,j;
    int inix=345,iniy=185;
	char ch='A';
	char strtemp[5];

	int letter=0;

    for (i=0;i<3;i++)
    {
        for (j=0;j<8;j++)
        {
            int cox=inix+gap*j;
            int coy=iniy;
            iSetColor(188,84,152);
            iFilledRectangle(cox,coy,squarex,squarex);
			iSetColor(0,0,0);
			strtemp[0]=ch;
			ch++;
		//	printf ("value of ch %c\n", ch);
			strtemp[1]='\0';
			iText(cox+textx,coy+texty,strtemp,GLUT_BITMAP_HELVETICA_18);

			mykeyx[letter]=cox;
			mykeyy[letter]=coy;
			letter++;


		//	printf ("value of letter %d cox and coy is %d and %d\n",letter, mykeyx[letter],mykeyy[letter]);



        }
        iniy-=gap;
    }
	for (i=0;i<2;i++)
	{
	    int cox=inix+gap*(i+3);
	    int coy=iniy;
	    iSetColor(188,84,152);
        iFilledRectangle(cox,coy,squarex,squarex);
        iSetColor(0,0,0);
        strtemp[0]=ch;
        ch++;

        strtemp[1]='\0';
        iText(cox+textx,coy+texty,strtemp,GLUT_BITMAP_HELVETICA_18);

        mykeyx[letter]=cox;
        mykeyy[letter]=coy;
        letter++;

	}



//    for (i=0;i<26;i++)
//    {
//        printf ("value of x and y %d %d\n", mykeyx[i],mykeyy[i]);
//
//    }




}



int clickkeyboard()
{
    int i;
    for (i=0;i<26;i++)
    {

	//	printf ("value of mx and my %d %d and mx and my %d %d\n",mousex,mousey,mykeyx[i],mykeyy[i]);
        if (isrange(mykeyx[i],mykeyy[i],squarex,squarex,mousex,mousey))

        {

     //       printf ("ooooe of keyx and keyy %d %d\n", mykeyx[i],mykeyy[i]);
            return i+1;
        }

     //   printf ("value of keyx and keyy %d %d\n", mykeyx[i],mykeyy[i]);
    }

    return 0;

}

void playerinformation()
{
    end=time(NULL);
    char playername[]="MD ABDULLAH AL ALAMIN";
    char playerscore[30]="SCORE: ";
    char temp[10];
    itoa(1040,temp,10);
    strcat(playerscore,temp);

    char playtime[20]="TIME PASSED: ";
    inttotime(temp,end-start);
    strcat(playtime,temp);

    int inix=350  ,iniy=450  ;
    iSetColor(127,127,127);

    iText (inix,iniy,playername,GLUT_BITMAP_TIMES_ROMAN_24);
     iSetColor(127,127,127);
     iniy-=35;
    iText (inix,iniy,playerscore,GLUT_BITMAP_TIMES_ROMAN_24);
    iniy-=35;
     iSetColor(127,127,127);
    iText (inix,iniy,playtime,GLUT_BITMAP_TIMES_ROMAN_24);

}


void load()

{

    if (step==2){

        if (catagoryloadedflag==0)

        {
            loadcatagory();
            catagoryloadedflag=1;
        }

    }

    else if (step==3)
    {

        FILE *fp;
        char filename[30];
        strcpy(filename,catagoryname[catagorynum]);
        printf ("value of catagorynum: %d\n",catagorynum);
        strcat(filename,".txt");

//        printf ("catagory num: %d\n",catagorynum);
//
//       strcat(filename,catagoryname[catagorynum]);
//       printf ("filename: %s\n",filename);
//       strcat(filename,".txt");
//
//       printf ("filename: %s\n",filename);

  //     strcpy(filename,"animals.txt");



        if ((fp=fopen(filename,"r"))==NULL)
        {
           printf ("error in reading file %s\n",filename);

       //    exit(1);
        }

        printf ("file has been opended\n");

        char temp[20]="asdlkjf";

        fscanf (fp,"%s",temp);
        printf ("the temp is %s\n",temp);


        strcpy(ansstr,temp);


        ansstrlen=strlen(ansstr);
        int i;
        for (i=0;i<ansstrlen;i++)
        {
            showstr[i]='*';
        }
        showstr[i]='\0';

        printf ("showstr %s\n",showstr);



        fclose(fp);







    }

    else{
        strcpy(ansstr,"alamin");

        ansstrlen=strlen(ansstr);
        int i;
        for (i=0;i<ansstrlen;i++)
        {
            showstr[i]='*';
        }
        showstr[i]='\0';

        printf ("showstr %s\n",showstr);


    }



}

void newshowstr (int n)
{
    char ch='a'+n-1;
    int i;
    for (i=0;i<ansstrlen;i++)
    {
        if (ansstr[i]==ch)
        {
            showstr[i]=ch;
        }
    }

}

void hangmanimage()
{
    char imagename[]="hangmanpic.bmp";
    iShowBMP(125,110,"alaminpic.bmp");
}

void showhint()
{
    if (hint==0)
    {
        iSetColor(127,127,127);
        iText (hintx,hinty,"CLICK HERE FOR HINTS",GLUT_BITMAP_TIMES_ROMAN_24);

    }

    else{
        iSetColor(127,127,127);
        iText (355,510,hintstr,GLUT_BITMAP_TIMES_ROMAN_24);


    }
}


void iDraw() {
	iSetColor(129,85,172);
    iFilledRectangle(0,0,winx,winy);

    if (step==1)
    {
        iShowBMP(0,0,"cover.bmp");
        iShowBMP(newgamex,newgamey,"newgame.bmp");
        iShowBMP (newgamex,newgamey-newgamehight,"resumegame.bmp");

    }

    else if (step==2)
    {

        iShowBMP(0,0,"choosecatagory.bmp");
        load();






    }

    else{
        myworddraw(showstr);
        screenkeyboard();
        playerinformation();
        iShowBMP (2,100,"hangmanpic.bmp");
        iShowBMP  (lifelinex,lifeliney,"lifelinepic.bmp");
        showhint();
        showalertbox();


    }




}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {

}


void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mousex=mx;
		mousey=my;
		printf ("%d %d\n", mx,my);

		if (step==1)
        {
            if (isrange(newgamex,newgamey,newgamewidth,newgamehight))
            {
                step=2;
                return;
            }
        }

        else if (step==2)
        {
           clickcatagory();
           return;
        }

		else if ((isrange(lifelinex,lifeliney,lifelinewidth,lifelinehight) || lifelineon) && lifelineremain)
        {
            lifelineon=1;
            uselifeline();
        }


		else if (clickkeyboard())
        {
            int n=clickkeyboard();
            newshowstr(n);
        }
        else if (isrange(hintx,hinty,273,20,mx,my))
        {
            hint=1;
        }
        else if (isrange(alertboxx+alertboxwidth-32,alertboxy+alertboxhight-32,32,32))
        {
            alertbox=0;
        }



	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {


	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
	if (key == 'q') {
		exit(0);
	}
	//place your codes for other keys here
}


void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_END) {
		exit(0);
	}
	//place your codes for other keys here
}


int main() {

//	load();
//	start=time(NULL);
//	iSetColor(129,85,172);
  //  iFilledRectangle(0,0,7000,50000);
	//place your own initialization codes here.
	iInitialize(winx,winy, "alamin & hasan");
	return 0;
}
