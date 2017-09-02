Assignment 3


The sgl functions implemented are:
   sglModRotate(float angle, int axisx, int axisy, int axisz);
   sglModTranslate(float tx, float ty,float  tz);
   sglModScale(float sx,float sy,float sz);
   sglModMatrix(float mat[16]);
   sglModLoadIdentity();
   sglModPushMatrix();
   sglModPopMatrix();
   sglViewRotate(float angle, int axisx, int axisy, int axisz);
   sglViewTranslate(float tx, float ty,float  tz);
   sglLookAt(float cx,float cy,float cz,float lx,float ly,float lz,float upx,float upy,float upz);
   sglViewMatrix(float mat[16]);
   sglViewLoadIdentity();
   sglProjOrtho(float left,float right,float bottom,float top,float near,float far);
   sglProjFrustum(float left,float right,float bottiom,float top,float near,float far);
   sglViewport(float llx,float lly,float width,float height);
   sglEnd();
   sglBegin();
   sglColour3f(float r,float g,float b);
   sglClear(float r,float g,float b);
   sglVertex3f(float x,float y,float z);
   sglShow();
   init();
Keys to be used:
Up,Down,Right,Left arrows -- ModTranslate
Mouse click               -- ModRotate
t                         -- ViewTranslate
r                         -- ViewRotate
l                         -- Lookat
