#include<fstream>
#include "sgl.h"
#include<math.h>
#include<stdlib.h>
#include<GL/glut.h>
struct node
{
	float mat[16];
	struct node * next;
};
struct show
{
	float mat[16];
	float p1[3];
	float p2[3];
	float p3[3];
	float proj_m[16];
	float view_m[16];
	float col[3];
	struct show * next;
};
struct show * headd=NULL;
struct node * head=NULL;
float pi=3.14159265;
float view_m[16];
float model_m[16];
float proj_m[16];
float mod_view[16];
float v_port[16];
float lookat_m[16];
void sglBegin();
void sglModMatrix(float mat[16]);
void  sglViewMatrix(float mat[16]);
void  sglViewport(float llx,float lly,float width,float height);
void sglColour3f(float r,float g,float b);
void sglVertex3f(float x,float y,float z);
void init();
void sglClear(float r,float g,float b);
void sglShow();
float curr_m[16];
void multiply(float a1[][4],float b1[][4],float *b);
void sglEnd();
void  sglViewPort(float a,float b,float c,float d);
int flag,cnt=0;
float stac[3][3];
float red,gr,bl;
void init()
{
				headd=(struct show *)malloc(sizeof(struct show));
				headd->next=NULL;
}
void sglColour3f(float r,float g,float b)
{
red=r;
gr=g;
bl=b;
glColor3f(r,g,b);
}
void sglClear(float r,float g,float b)
{
	glClearColor(r,g,b,0);
}
void sglEnd()
{
flag=0;
}

void sglBegin()
{
flag=1;
cnt=0;
}
void sglVertex3f(float a,float b,float c)
{
//int k;
if(flag==1)
{
stac[cnt][0]=a;
stac[cnt][1]=b;
stac[cnt][2]=c;
cnt++;
/*glBegin(GL_TRIANGLES);
 glVertex3f(stac[0][0],stac[0][1],stac[0][2]);
 glVertex3f(stac[1][0],stac[1][1],stac[1][2]);
 glVertex3f(stac[2][0],stac[2][1],stac[2][2]);
 glEnd();*/

if(cnt==3)
		{
			struct show * t;
			if(headd==NULL)
			{

				headd=(struct show *)malloc(sizeof(struct show));
				t=headd;
				headd->next=NULL;
				t->col[0]=red;
				t->col[1]=gr;
				t->col[2]=bl;
				for(int h=0;h<16;h++)
				{
					t->mat[h]=mod_view[h];
					t->proj_m[h]=proj_m[h];
				}
				for(int k=0;k<3;k++)
				{
					t->p1[k]=stac[0][k];
					t->p2[k]=stac[1][k];
					t->p3[k]=stac[2][k];
				}

			}

			else
			{
				t=headd;
				while(t->next!=NULL)
				{
					t=t->next;
				}
				t->next=(struct show *)malloc(sizeof(struct show));
				t->next->col[0]=red;
				t->next->col[1]=gr;
				t->next->col[2]=bl;

				for(int h=0;h<16;h++)
				{
					t->next->mat[h]=mod_view[h];
					t->next->proj_m[h]=proj_m[h];
				}
				for(int k=0;k<3;k++)
				{
					t->next->p1[k]=stac[0][k];
					t->next->p2[k]=stac[1][k];
					t->next->p3[k]=stac[2][k];
				}
				t->next->next=NULL;


			}
			cnt=0;
		}
	}

}
void sglShow()
{
printf("jjjhhhhhhhhhh");
	struct show * t=headd;
	while(t->next!=NULL)
	{
		  glMatrixMode(GL_MODELVIEW);
		  glLoadMatrixf(t->mat);
	//	 glMatrixMode(GL_PROJECTION);
	//	 glLoadMatrixf(t->proj_m);
		  glMatrixMode(GL_MODELVIEW);
		  glLoadMatrixf(t->mat);
		  glColor3f(t->col[0],t->col[1],t->col[2]);
		  glBegin(GL_TRIANGLES);
		  glVertex3f(t->p1[0],t->p1[1],t->p1[2]);
		  glVertex3f(t->p2[0],t->p2[1],t->p2[2]);
		  glVertex3f(t->p3[0],t->p1[1],t->p3[2]);
                  glEnd();
                  t=t->next;
	}
                   




 }



void sglModMatrix(float mat[16])
{
	int i,j,k=0;
        float m1[4][4],m2[4][4];
	for(i=0;i<16;i++)
		model_m[i]=mat[i];
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=view_m[k];
			m2[j][i]=model_m[k];
			k++;
		}
	}
	multiply(m1,m2,mod_view);
//	for(i=0;i<16;i++)
//		lookat_m[i]=0;
//	multiply(lookat_m,proj_m,view_m);
//	multiply(mod_view,lookat_m,model_m);
}

void sglViewMatrix(float mat[16])
{
	int i,j,k=0;
        float m1[4][4],m2[4][4];
	for(i=0;i<16;i++)
		view_m[i]=mat[i];
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=view_m[k];
			m2[j][i]=model_m[k];
			k++;
		}
	}
	multiply(m1,m2,mod_view);
//	for(i=0;i<16;i++)
//		lookat_m[i]=0;
//	multiply(model_m,proj_m,view_m);
//	multiply(mod_view,lookat_m,model_m);
}
void sglModLoadIdentity()
{
	int i,j,k=0;
	/*	for(int i=0;i<16;i++)
		{
		if(i%5==0)model_m[i]=1;
		else model_m[i]=0;
		}*/
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(i==j)
			{
				model_m[k]=1;
				mod_view[k]=1;
				proj_m[k]=1;
				v_port[k]=1;
				k++;
			}
			else
			{
				model_m[k]=0;
				mod_view[k]=0;
				proj_m[k]=0;
				v_port[k]=0;
				k++;

			}
		}

	}



}
	void multiply(float m1[][4],float m2[][4],float *b)
{
	float sum=0,m3[4][4];
	int k=0;

        for(int c=0;c<4;c++)
	{

		for(int d=0;d<4;d++)
		{
			for(k=0;k<4;k++)
			{
				sum=sum+m1[c][k]*m2[k][d];
			}
			m3[c][d]=sum;
			sum=0;
		}
	}
	k=0;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			b[k]=m3[j][i];
			k++;
		}
	}
}



void sglModRotate(float angle,int axisx,int axisy,int axisz)
{
float m1[4][4],m2[4][4];
	float si,co;
      int k=0,i,j;
	si=sin(angle*pi/180);
	co=cos(angle*pi/180);
	for(i=0;i<16;i++)
		curr_m[i]=0;

	if(axisx==1)
	{
		curr_m[0]=1;
		curr_m[5]=co;
		curr_m[6]=si;
		curr_m[9]=-si;
		curr_m[10]=co;
		curr_m[15]=1;
	}
	else if(axisy==1)
	{
		curr_m[5]=1;
		curr_m[0]=co;
		curr_m[8]=si;
		curr_m[2]=-si;
		curr_m[10]=co;
		curr_m[15]=1;
	}
	else if(axisz==1)
	{
		curr_m[10]=1;
		curr_m[0]=co;
		curr_m[1]=si;
		curr_m[4]=-si;
		curr_m[5]=co;
		curr_m[15]=1;
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=curr_m[k];
			m2[j][i]=model_m[k];
			k++;
		}
	}
	multiply(m1,m2,model_m);
      k=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=view_m[k];
			m2[j][i]=model_m[k];
			k++;
		}
	}
	multiply(m1,m2,mod_view);
	for(i=0;i<16;i++)
	{
		printf("%f ",model_m[i]);
	}
printf("\n");
}

void sglModTranslate(float tx, float ty,float tz)
{
int i,j,k=0;
float m1[4][4],m2[4][4];
	for(i=0;i<16;i++)
		curr_m[i]=0;
	curr_m[0]=1;
	curr_m[5]=1;
	curr_m[10]=1;
	curr_m[12]=tx;
	curr_m[13]=ty;
	curr_m[14]=tz;
	curr_m[15]=1;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=curr_m[k];
			m2[j][i]=model_m[k];
			k++;
		}
	}
	multiply(m1,m2,model_m);
        k=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=view_m[k];
			m2[j][i]=model_m[k];
			k++;
		}
	}
	multiply(m1,m2,mod_view);
}



void sglModScale(float sx,float sy,float sz)
{
int i,j,k=0;
float m1[4][4],m2[4][4];
	for(i=0;i<16;i++)
		curr_m[i]=0;
	curr_m[0]=sx;
	curr_m[5]=sy;
	curr_m[10]=sz;
	curr_m[15]=1;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=curr_m[k];
			m2[j][i]=model_m[k];
			k++;
		}
	}
	multiply(m1,m2,model_m);
        k=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=view_m[k];
			m2[j][i]=model_m[k];
			k++;
		}
	}
	multiply(m1,m2,mod_view);
}

void sglModPushMatrix()
{

	if(head==NULL)
	{
		head=(struct node *) malloc (sizeof(struct node));
		for(int i=0;i<16;i++)
		{
			head->mat[i]=model_m[i];
		}
		head->next=NULL;
	}
	else
	{

		struct node * newnode=(struct node *)malloc(sizeof(struct node));
		for(int i=0;i<16;i++)
		{
			newnode->mat[i]=model_m[i];
		}
		newnode->next=head;
		head=newnode;
	}
}
void sglModPopMatrix()
{
int i,j,k=0;
float m1[4][4],m2[4][4];
	struct node * temp=head;
	for(i=0;i<16;i++)
		{
			model_m[i]=head->mat[i];
		}
	head=head->next;
	free(temp);
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=view_m[k];
			m2[j][i]=model_m[k];
			k++;
		}
	}
	multiply(m1,m2,mod_view);
}
void sglViewRotate(float angle, int axisx, int axisy, int axisz)
{
	float si,co;
     int i,j,k=0;
float m1[4][4],m2[4][4];
	si=sin(angle*pi/180);
	co=cos(angle*pi/180);
	for(i=0;i<16;i++)
		curr_m[i]=0;

	if(axisx==1)
	{
		curr_m[0]=1;
		curr_m[5]=co;
		curr_m[6]=si;
		curr_m[9]=-si;
		curr_m[10]=co;
		curr_m[15]=1;
	}
	else if(axisy==1)
	{
		curr_m[5]=1;
		curr_m[0]=co;
		curr_m[8]=si;
		curr_m[2]=-si;
		curr_m[10]=co;
		curr_m[15]=1;
	}
	else if(axisz==1)
	{
		curr_m[10]=1;
		curr_m[0]=co;
		curr_m[1]=si;
		curr_m[4]=-si;
		curr_m[5]=co;
		curr_m[15]=1;
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=curr_m[k];
			m2[j][i]=view_m[k];
			k++;
		}
	}
	multiply(m1,m2,view_m);
      k=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=model_m[k];
			m2[j][i]=view_m[k];
			k++;
		}
	}
	multiply(m2,m1,mod_view);
}



void sglViewTranslate(float tx, float ty,float tz)
{
int i,j,k=0;
float m1[4][4],m2[4][4];
	for(int i=0;i<16;i++)
		curr_m[i]=0;
       curr_m[0]=1;
	curr_m[5]=1;
	curr_m[10]=1;
	curr_m[12]=tx;
	curr_m[13]=ty;
	curr_m[14]=tz;
	curr_m[15]=1;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=curr_m[k];
			m2[j][i]=view_m[k];
			k++;
		}
	}
	multiply(m1,m2,view_m);
      k=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=view_m[k];
			m2[j][i]=model_m[k];
			k++;
		}
	}
	multiply(m1,m2,mod_view);
}
void sglViewPort(float a,float b,float c,float d)
{
glViewport(a,b,c,d);
}
void sglViewLoadIdentity()
{
	int i,j,k=0;
	/*	for(int i=0;i<16;i++)
		{
		if(i%5==0)model_m[i]=1;
		else model_m[i]=0;
		}*/
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(i==j)
			{
				view_m[k]=1;
				mod_view[k]=1;
				v_port[k]=1;
				proj_m[k]=1;
				k++;
			}
			else
			{
				view_m[k]=0;
				mod_view[k]=0;
				v_port[k]=0;
				proj_m[k]=0;
				k++;
			}
		}

/*	for(int i=0;i<16;i++)
	{
		if(i%5==0)view_m[i]=1;
		else view_m[i]=0;
	}*/

}
		

}


void  sglViewport(float llx,float lly,float width,float height)
{
int i,j,k=0;
	float vr,vl,vb,vt,m1[4][4],m2[4][4];
	vl=llx;
	vb=lly;
	vr=vl+width;
	vt=vb+height;
	for(i=0;i<16;i++)
		v_port[i]=0;
	v_port[0]=(vr-vl)/2;
	v_port[5]=(vt-vb)/2;
	v_port[10]=1/2;
	v_port[12]=(vr+vl)/2;
	v_port[13]=(vt+vb)/2;
	v_port[14]=1/2;
	v_port[15]=1;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=view_m[k];
			m2[j][i]=v_port[k];
			k++;
		}
	}
	multiply(m1,m2,view_m);
      k=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=view_m[k];
			m2[j][i]=model_m[k];
			k++;
		}
	}
	multiply(m1,m2,mod_view);
}

/*	for(int i=0;i<16;i++)mid[i]=0;
	matmul(mid,proj,view);
	matmul(res,mid,model);*/

void  sglLookAt(float cx,float cy,float cz,float lx,float ly,float lz,float upx,float upy,float upz)
{
   int i,j,k=0;
   float mod;
	float n[]={lx-cx,ly-cy,lz-cz};
            mod = sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
              n[0]=lx-cx/mod;
              n[1]=ly-cy/mod;
              n[2]=lz-cz/mod;

float m1[4][4],m2[4][4];
        float u[3],v[3],up[3];
        u[0]=(upy*n[2]-upz*n[1]);
	u[1]=-(upx*n[2]-upz*n[0]);
        u[2]=(upx*n[1]-upy*n[0]);
            mod = sqrt(u[0]*u[0] + u[1]*u[1] + u[2]*u[2]);
              u[0]=u[0]/mod;
              u[1]=u[1]/mod;
              u[2]=u[2]/mod;
	v[0]=n[1]*u[2]-n[2]*u[1];
	v[1]=-(n[0]*u[2]-n[2]*u[0]);
	v[2]=n[0]*u[1]-n[1]*u[0];
            mod = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
              v[0]=v[0]/mod;
              v[1]=v[1]/mod;
              v[2]=v[2]/mod;
          mod=sqrt(upx*upx+upy*upy+upz*upz);
       up[0]=upx/mod;
       up[1]=upy/mod;
       up[2]=upz/mod;
        for(int i=0;i<12;i=i+4)
	{
		curr_m[i]=u[i];
		curr_m[i+1]=v[i];
		curr_m[i+2]=-n[i];
		curr_m[i+3]=0;
	}
         curr_m[12]=0;
	curr_m[13]=0;
	curr_m[14]=0;
	curr_m[15]=1;
	for(int i=0;i<16;i++)
	{
		lookat_m[i]=0;
	}
	lookat_m[12]=-cx;
	lookat_m[13]=-cy;
	lookat_m[14]=-cz;
	lookat_m[15]=1;
	lookat_m[0]=1;
	lookat_m[5]=1;
	lookat_m[10]=1;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=curr_m[k];
			m2[j][i]=lookat_m[k];
			k++;
		}
	}
	multiply(m1,m2,lookat_m);
     k=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=curr_m[k];
			m2[j][i]=view_m[k];
			k++;
		}
	}
	multiply(m1,m2,view_m);
      k=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=view_m[k];
			m2[j][i]=model_m[k];
			k++;
		}
	}
	multiply(m1,m2,mod_view);
}

void sglProjOrtho(float left,float right,float bottom,float top,float near,float far)
{
int i,j,k=0;
float m1[4][4],m2[4][4];
	float tmx,tmy,tmz;
	tmx=-(right+left)/(right-left);
	tmy=-(top+bottom)/(top-bottom);
	tmz=-(far+near)/(far-near);
	for(i=0;i<16;i++)
		curr_m[i]=0;
	curr_m[0]=2/(right-left);
	curr_m[5]=2/(top-bottom);
	curr_m[10]=2/(far-near);
	curr_m[12]=tmx;
	curr_m[13]=tmy;
	curr_m[14]=tmz;
	curr_m[15]=1;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=curr_m[k];
			m2[j][i]=proj_m[k];
			k++;
		}
	}
	multiply(m1,m2,proj_m);
      k=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=view_m[k];
			m2[j][i]=model_m[k];
			k++;
		}
	}
	multiply(m1,m2,mod_view);
}


void sglProjFrustum(float left,float right,float bottom,float top,float near,float far)
{
int i,j,k=0;
float m1[4][4],m2[4][4];
	float a=(right+left)/(right-left);
	float b=(top+bottom)/(top-bottom);
	float c=-(far+near)/(far-near);
        float d=-(2*far*near)/(far-near);
	for(i=0;i<16;i++)
		curr_m[i]=0;
	curr_m[0]=2*near/(right-left);
	curr_m[5]=2*near/(top-bottom);
	curr_m[8]=a;
	curr_m[9]=b;
	curr_m[10]=c;
	curr_m[11]=-1;
	curr_m[14]=d;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=curr_m[k];
			m2[j][i]=proj_m[k];
			k++;
		}
	}
	multiply(m1,m2,proj_m);
      k=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			m1[j][i]=view_m[k];
			m2[j][i]=model_m[k];
			k++;
		}
	}
	multiply(m1,m2,mod_view);
		

}

