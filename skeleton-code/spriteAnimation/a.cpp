
#include <stdio.h>
#include <iostream>

#include <stdlib.h>

#include <zglut.h>
#include "pixMap.h"
#include "Mario.h"


void myInit(void)
{
  glClearColor(1.0f,1.0f,1.0f,1.0f);
  
 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  gluOrtho2D(0,640,0,480);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  
}


void display(void)
{
  
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

	 glFlush();
  
}

void myKB_Handler(unsigned char key, int mx, int my)
{
    switch(key)
	{
	  case 'r':
	           	 
			
		  
		  
		  break;
	  
	 
	}
glutPostRedisplay();
}
void pressKeySpecial(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT :
		
		break;
    
	case GLUT_KEY_RIGHT :
		
		break;
    
	case GLUT_KEY_UP :
			 	
		break;
    
	case GLUT_KEY_DOWN :
		
	
		break;
    }
	glutPostRedisplay();

}


void releaseKeySpecial(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT :
	
	
	break;
    
	case GLUT_KEY_RIGHT :
	
	
	break;
    
	case GLUT_KEY_UP :
		
	break;
    
	case GLUT_KEY_DOWN :
	
	
	break;
    }
glutPostRedisplay();

}
void main(int argc, char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("MY Mario");
  
  
  glutDisplayFunc(display);
  glutSpecialFunc(pressKeySpecial);
  glutSpecialUpFunc(releaseKeySpecial);
  glutKeyboardFunc(myKB_Handler);
  

  myInit();
  //glutIdleFunc(display);
  //glutTimerFunc(500,myTimer,1);
  glutMainLoop();
}

