extern float view_m[16];
extern float proj_m[16];
extern float model_m[16];
extern float v_port[16];
extern float mod_view[16];
extern float trans[16];
extern  void sglModRotate(float angle, int axisx, int axisy, int axisz);
extern void  sglModTranslate(float tx, float ty,float  tz);
extern void sglModScale(float sx,float sy,float sz);
extern void sglModMatrix(float mat[16]);
extern void sglModLoadIdentity();
extern void sglModPushMatrix();
extern void sglModPopMatrix();
extern void sglViewPort(float a,float b,float c,float d);
extern  void sglViewRotate(float angle, int axisx, int axisy, int axisz);
extern void  sglViewTranslate(float tx, float ty,float  tz);
extern void  sglLookAt(float cx,float cy,float cz,float lx,float ly,float lz,float upx,float upy,float upz);
extern void  sglViewMatrix(float mat[16]);
extern void sglViewLoadIdentity();
extern void sglProjOrtho(float left,float right,float bottom,float top,float near,float far);
extern void sglProjFrustum(float left,float right,float bottiom,float top,float near,float far);
extern void  sglViewport(float llx,float lly,float width,float height);
extern void sglEnd();
extern void sglBegin();
extern void sglColour3f(float r,float g,float b);
extern void sglClear(float r,float g,float b);
extern void sglVertex3f(float x,float y,float z);
extern void sglShow(); 
extern void init(); 







