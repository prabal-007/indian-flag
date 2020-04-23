#include<graphics.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include<alloc.h>
 void startgraph();
 void initmouse();
 void showmouse();
 void hidemouse();
 void getmouse();
 void graph();
 void setmouse(int &px, int &py);
 union REGS in,out;
 int px=0,py=0;
 int click ; //mouse button. 0 1 2 3
void main()
 {
     startgraph();
     setbkcolor(CYAN); //changes background color
     initmouse();
   //  graph();
      //Step 1: making flag 3 bands..
    setfillstyle(1,LIGHTRED);
    bar(100,360,280,390);
    setfillstyle(1,WHITE);
    bar(100,390,280,420);
    setcolor(BLUE);
      for(int i=0;i<=360;i=i+15)
       {
	 pieslice(190,405,i,i+15,15); //24 spokes...
       } //end for..
       circle(190,405,14); //outer circle...
       fillellipse(190,405,4,4);//tiny circle..
    setfillstyle(1,GREEN);
    bar(100,420,280,450);
    //calculate size..
    int imgsize=imagesize(100,360,280,450);
    void *flagbuf = (void*)malloc(imgsize);
    getimage(100,360,280,450,flagbuf);

    //Next make stick of flag..
    setfillstyle(3,DARKGRAY);
    bar3d(90,20,99,460,0,0);
    //Next making base of flag..
    setfillstyle(2,BLUE);
    bar3d(20,460,170,470,0,0);

    showmouse();
     while(1)
      {
       getmouse();    //px,py,click update...
       if(px>=100&&px<=280&&py>=360&&py<=450 && click==1)
	{
	 hidemouse();
	 //off the earlier image:
	 putimage(100,360,flagbuf,1); //image off.
	 for(int y=360;y>=20;y=y-5)
	   {
	     putimage(100,y,flagbuf,1); //image on...
	     delay(80);
	     putimage(100,y,flagbuf,1); //image off...
	      if(y==20) //flag is at top...
	      {
		  putimage(100,y,flagbuf,1);//set image on...
		  showmouse();  goto end;
	      }//end if..
	   } //end for...


	} //end if...





      } //end while...

     end:
     getch();
     cleardevice(); //clear    to avoid distortion at end of program.
     restorecrtmode();
     closegraph(); //shuts down graphics system.

 } //end main...
    void graph()
     {
      int x; //x axis
      int y; // y axis
      int i; //loop
      char xsg[10]; //x coordinate message.
      char ysg[10]; // y .....
      setbkcolor(DARKGRAY);
      settextstyle(2,0,2);
       for(x=0,y=0;x<=639;x=x+20,y=y+20)
	{
	  //for x axis..
	  setcolor(WHITE);
	  line(x,0,x,479);
	  sprintf(xsg,"%d",x);
	  outtextxy(x+2,0,xsg);
	  //for y axis...
	  setcolor(WHITE);
	  line(0,y,639,y);
	  sprintf(ysg,"%d",y);
	  outtextxy(0+2,y+1,ysg);
	  //red color for x and y axis...
	  setcolor(RED);
	  line(x+10,0+10,x+10,479);  //x axis..
	  line(0+10,y+10,639,y+10); //y axis..
	} //end for...



     } //end graph()...

    void initmouse()
      {
       in.x.ax =0;
       int86(51, &in, &out);
      } //end of initmouse()..
    void showmouse()
      {
	 in.x.ax =1;
	 int86(51,&in,&out);

      } //end showmouse()..
   void hidemouse()
     {
	 in.x.ax =2;
	 int86(51,&in,&out);

     } //end hidemouse..
   void getmouse()
    {
      in.x.ax =3;
      int86(51,&in,&out);
      click = out.x.bx;
      px=out.x.cx;   //x
      py = out.x.dx; //y

    }  //end of getmouse();
   void setmouse(int &px,int &py)
     {

       in.x.ax = 4;
       in.x.cx = px;
       in.x.dx = py;
       int86(0x33,&in,&out);
     } //end of setmouse()...
 void startgraph()
   {
   //request for autodetection...
   int gd = DETECT, gm, errcode;
    //intialize graphics system.
    initgraph(&gd, &gm, "c:\\tc\\bgi");  delay(50);
    //read result of initialization.
    errcode = graphresult();
     if(errcode != grOk) //some error...
       {
	 cout<<"Graphics err msg: "<<grapherrormsg(errcode)<<endl;
	 getch();
	  exit(1); //terminate code...
       } //end if...



   } //end startgraph()...