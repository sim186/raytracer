//
//  main.c
//  Ray
//
//  Created by Celestino Simone on 23/04/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include "prototype.h"
#include "structure.h"



//scene_t config(); // loads default "config.cfg" file and returns a scene, implemented by secco92

//#define height 100
//#define width 100
GLubyte image[1600][1200][3];

// image2[160*120];
scene_t scene;

struct pixel{
    GLubyte r;
    GLubyte g;
    GLubyte b;
};

typedef struct pixel pixels;

pixels image2[1600*1200];

void draw(void)
{
    /* display callback, clear frame buffer and z buffer,
     rotate cube and draw, swap buffers */
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    //glRasterPos2i(-1, -1);
    glDisable(GL_DEPTH_TEST);
    glDrawPixels(scene.screenResX , scene.screenResY, GL_RGB, GL_UNSIGNED_BYTE, image2);	
    
    //glDrawPixels(scene.screenResX , scene.screenResY, GL_RGBA, GL_UNSIGNED_BYTE, image);	
    
    glFlush();
}

color_t makeCheckImage(int x,int y,scene_t *scene) {
    
    double i, j;
    vector_t dst;
    color_t cAcc = { 0.0f, 0.0f, 0.0f};
    color_t temp = { 0.0f, 0.0f, 0.0f};
    
    double pixelSizeX = scene->screenSizeX/scene->screenResX;
	double pixelSizeY = scene->screenSizeY/scene->screenResY;
    
	double AAShiftX = pixelSizeX/scene->maxAA;
	double AAShiftY = pixelSizeY/scene->maxAA;
   
    
    for(double i = pixelSizeX * x; i < pixelSizeX * (x + 1); i += AAShiftX)
         for(double j = pixelSizeY * y; j < pixelSizeY * (y + 1); j += AAShiftY)
         {
            
            point_t pixelPos = { i, j, 800.0f};//posizione pixel nello spazio degli oggetti. 
            dst = sub_comp(&pixelPos,&scene->cam);
            
            ray_t ray = { scene->cam, dst};
            norm(&ray.dst);
            //printf("x=%lf,y=%lf,z=%lf\n",dst.x,dst.y,dst.z);

            temp = trace(&ray, scene,0, 1.0f);
            //printf("Rosso=%lf,Verde=%lf,Blu=%lf,Image[%lf][%lf]\n",cAcc.r,cAcc.g,cAcc.b,i,j);

            
            cAcc = sum_col(&temp, &cAcc);
            //printf("RED=%lf,GREEN=%lf,BLUE=%lf\n",cAcc.r, cAcc.g,cAcc.b);
            //cAcc = sum_col(&cAcc, &temp);
            
            
            /*image[i][j][0]=cAcc.r;
            image[i][j][1]=cAcc.g;
            image[i][j][2]=cAcc.b;*/
            //temp.r = 0.0f;
            //temp.g = 0.0f;
            //temp.b = 0.0f;
            //cAcc = {0.0f, 0.0f, 0.0f};
            
        }
    
        int tempMaxA;
        tempMaxA=scene->maxAA*scene->maxAA;
        cAcc = div_col_scal(&cAcc,tempMaxA);
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    return cAcc;
    
}




void init(){
    
    int i,j;
    color_t pixel;
    //glClearColor(0.0, 0.0, 0.0, 0.0);
        
    for (i = 0; i < scene.screenResX ;i++){
        for (j = 0; j < scene.screenResY; j++){ 
    
            
            pixel = makeCheckImage(i,j,&scene);
            
            
            
            
            //color must be in range 0 - 255
			
            pixel.r = pixel.r * 255.0f;
             pixel.g = pixel.g * 255.0f;
             pixel.b = pixel.b * 255.0f;
             
             if(pixel.r > 255) pixel.r = 255.0;
             if(pixel.g > 255) pixel.g = 255.0;
             if(pixel.b > 255) pixel.b = 255.0;
                       
            //printf("RED=%lf,GREEN=%lf,BLUE=%lf\n",pixel.r, pixel.g,pixel.b);
         
            //image[j][i][0]= pixel.r;
            //image[j][i][1]= pixel.g;
            //image[j][i][2]= pixel.b;
            
            image2[j*scene.screenResX+i].r= pixel.r;
            image2[j*scene.screenResX+i].g= pixel.g;
            image2[j*scene.screenResX+i].b= pixel.b;
            
            //image2[j*scene.screenResX+i].r=image[i][j][0];
            //image2[j*scene.screenResX+i].g=image[i][j][1];
            //image2[j*scene.screenResX+i].b=image[i][j][2]; 
            //image2[j*scene.screenResX+i].a=image[i][j][3];
            //|image[i][j][1]|image[i][j][2];
            
        }
    }
    
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
}


int main (int argc, char** argv)
{
    int status;
    
    
    
    //carichiamo la scena su cui effettura il ray tracing
	//scene_t scene;
    
    status = loadconfig("/home/sim1/Scrivania/ray/config.cfg", &scene);
    
    //printf("La risoluzione x e':%d", scene.material->mId);
    
    glutInit(&argc,argv);
	
	// The image is not animated so single buffering is OK. 
	glutInitDisplayMode(GLUT_RGB);
	
	// Window position (from top corner), and size (width and hieght)
	glutInitWindowPosition( 250, 150 );
	glutInitWindowSize( 1600, 1200 );
	glutCreateWindow( "RayTracer" );
	
	// Initialize OpenGL as we like it..
	//initRendering();
	
	// Set up callback functions for key presses
	//glutKeyboardFunc( keyboard );			// Handles "normal" ascii symbols
	// glutSpecialFunc( mySpecialKeyFunc );		// Handles "special" keyboard keys
	
	// Set up the callback function for resizing windows
	//glutReshapeFunc( redraw );
	
	// Call this for background processing
	// glutIdleFunc( myIdleFunction );
	
    
    init();
    
	// call this whenever window needs redrawing
	glutDisplayFunc( draw );
	
	//fprintf(stdout, "Press space bar to toggle images; escape button to quit.\n");
	
    
	// Start the main loop.  glutMainLoop never returns.
	glutMainLoop(  );
    
	
	return(0);	// This line is never reached.    
}

//nel momento in cui la funzione trace viene chiamata per la prima volta, non sappiamo ancora se il nostro occhio
//(quindi il raggio partente da esso) incontrerà un oggetto della scena o solo un punto nella 
color_t trace(ray_t *ray, scene_t *scene, int depth, double currRefr)
{
    int i;
	color_t background = { 0.0f, 0.0f, 0.0f}; //colore di sfondo
	color_t c = { 0.0f, 0.0f, 0.0f };
	prim_t *p = NULL; //array degli oggetti primitivi all'interno della scena
	material_t *m = NULL; //array dei materiali
	double t = scene->maxT; //imposta la massima distanza di rendering
	//double temp;
    vector_t vect1,vect2;
    color_t col;
    color_t col2;
        
	if(depth > 3) return c; //se abbiamo raggiunto il massimo grado di profondità
    
	//raccoglie l'intersezione più vicina
	for(i = 0; i < scene->primCount; i++){
		//printf("tipo=%d",scene->prim[i].type);
        if(getIntersection(&scene->prim[i], ray, &t)) //se è stata trovata una intersezione con un oggetto
			p = &scene->prim[i]; //salva il puntatore all'oggetto intersecante
    }
    printf("tipo:%d",scene->prim[i].type);

    if(!p) return background; // altrimenti,non sono state trovate intersezioni
    

    //valuta il materiale dell'oggetto intersecato
	for(i = 0; i < scene->matCount; i++)
		if(scene->material[i].mId == p->mat)
			m = &scene->material[i]; //i valori del materiale vengono memorizzati in m
    if(!m) return background; // altrimenti, non esiste un materiale specificato nella scena
    
    
    
	//calcola ombre e luci
    
    vect1 = mul_scal(&ray->dst, t);
    
	vector_t intrPoint = sum_comp(&ray->src, &vect1); //calcola il punto di intersezione tra il raggio e l'oggetto
	ray_t lightRay;
	int inShadow;
    
	lightRay.src = intrPoint;
    vector_t normal;
    normal = getNormal(p, &intrPoint); // calcolo la normale (normalizzata) al punto di intersezione
    
    normal = correctDir(&normal, &ray->dst); //calcola la direzione della normale del raggio che interseca l'oggetto
	
	
	int j;
    double temp;
	inShadow = 0;
    
    //ciclava sulle luci, ma nel nostro caso la luce è unica
	lightRay.dst = sub_comp(&scene->light[0], &intrPoint); //calcola il segmento del raggio del punto intersecato 
    //(intrpoint) verso la sorgente di luce
    
	if(mul_comp(&normal, &lightRay.dst) <= 0.0f) inShadow=1; // il punto è nella direzione opposta, quindi non viene illuminato
	temp = sqrt(mul_comp(&lightRay.dst, &lightRay.dst));
    
	norm(&lightRay.dst);
    
	for( j = 0; j < scene->primCount; j++)
		if(getIntersection(&scene->prim[j], &lightRay, &temp)) //controlliamo che non ci siano 
            //oggetti che si frappongono tra la luce e l'oggetto intersecato
        {
            inShadow = 1;
            break;
        }
    
    if(inShadow==0) //se non ci sono oggetti lungo il percorso del raggio
    {
        //lambert
        double lambert = mul_comp(&lightRay.dst, &normal);
        //c.r += m->col.r * m->coefDiffuse;// * lambert;
        //c.g += m->col.g * m->coefDiffuse;// * lambert;
        //c.b += m->col.b * m->coefDiffuse;// * lambert;
        color_t temp=mul_col_scal(&m->col, m->coefDiffuse);
        color_t temp2=mul_col_scal(&temp,lambert);
        c= sum_col(&c, &temp2);
        
        //blinn
        vector_t blinnDst = sub_comp(&lightRay.dst, &ray->dst);
        norm(&blinnDst);
        
        double blinn = mul_comp(&blinnDst, &normal);
        blinn = m->coefReflect * pow(blinn, (double)100.0f);
        
        temp=mul_col_scal(&m->col, blinn);
        
        c = sum_col(&c, &temp);
    }//if !InShadow
    
		//calcola il raggio di riflessione del raggio di luce che colpisce l'oggetto
	ray_t reflRay;
        
		double cos1 = - (mul_comp(&ray->dst,&normal));
    //printf("coef=%lf\n",m->coefReflect);
    //printf("depth=%d\n",depth);

		if(m->coefReflect >= 0.01f)
		{
			double refl = cos1 * 2.0f;
            
			reflRay.src = intrPoint;
            
            vect1= mul_scal(&normal, refl);
            
			reflRay.dst = sum_comp(&ray->dst, &vect1);
			//norm(reflRay.dst); no need
            
            col = trace(&reflRay, scene, depth + 1, currRefr);
            col2 = mul_col_scal(&col, m->coefRefract);
            c = sum_col(&c, &col2);
            
		}
        
		//calcola il raggio di rifrazione del raggio di luce che colpisce l'oggetto
		ray_t refrRay;
        
		double n;// = 1.0f/1.33f; //"insert a comment here"
        
		//rifrazione nel vetro
		if(currRefr == 1.0f)
		{
			currRefr = m->refrIndex;
			n = 1.0f/currRefr;
		}
		else
		{
			currRefr = m->refrIndex;
			n = currRefr/1.0f;
		}
        
		if(m->coefRefract >= 0.01f)
		{
			double cos2 = sqrt(1.0f - n*n * (1.0f - cos1*cos1));
			refrRay.src = intrPoint;
			double refr;
			if(cos1 >= 0.0f)
				refr = n * cos1 - cos2;
			else
				refr = -n * cos1 + cos2;
            
        	vect1 = mul_scal(&ray->dst, n);
        	vect2 = mul_scal(&normal, refr);
            
            refrRay.dst = sum_comp(&vect1,&vect2);
            
            
            
        	col = trace(&refrRay, scene, depth + 1, currRefr);
        	col2 = mul_col_scal(&col, m->coefRefract);
        	c = sum_col(&c, &col2);
		}
     return c;
}


int getIntersection(prim_t *p, ray_t *r, double *t)
{
    point_t PoPc;
    double B, D, x1, x2;
    int rval;
    vector_t u={0,1,0};
    double t0,normb;
    double pN, pD, pT;
    

	//algoritm depends on primitive type
	switch(p->type)
	{
        case SPHERE: //sfera
            
            
            rval = 0;
            
            PoPc = sub_comp(&r->src, &p->sphere.center);
            B = mul_comp(&r->dst, &PoPc); 
            D = B*B - mul_comp(&PoPc, &PoPc) + p->sphere.r*p->sphere.r; 
            
            
            /*vector_t temp=sub_comp(&p->sphere.center, &r->src);
            vector_t temp2,P0,b;
            
            t0=mul_comp(&u, &temp);
            temp2=mul_scal(&u, t0);
            P0=sum_comp(&r->src, &temp2);
            b=sub_comp(&P0, &p->sphere.center);
            normb=(b.x*b.x) + (b.y*b.y) + (b.z*b.z);
            normb=sqrt(normb);
            
            D=(p->sphere.r*p->sphere.r) - (normb*normb);
            */
            if(D < 0.0f) return 0;
            
            x1 = -B - sqrt(D);
            x2 = -B + sqrt(D);
            
            if(x1 > 0.1f && x1 < *t)
            {
                *t = x1;
                rval = 1;
            }
            if(x2 > 0.1f && x2 < *t)
            {
                *t = x2;
                rval = 1;
            }
            return rval;
            
            break;
        case PLANE:
            // d + N * Po
            pN = mul_comp(&p->plane.n, &r->src);
            pN = pN + p->plane.d;
            pN = pN * -1.0f;
            
            
            // vD * N
            pD = mul_comp(&r->dst,&p->plane.n);
            
            
            if(!pD) return 0; // ray and norm parallel
            
            pT = pN / pD;
            
            if(pT <= 0.0f || pT > *t) return 0; // if behind or there's another intersection before
            
            *t = pT - 0.0001f; // fix for precision problems
            return 0;
            
            break;
            
            /* case POLYGON: //poligono
             
             vector_t u, v, n;//, w0, w;
             prim_t pl;
             double plT;//, tS, tT, tD;
             point_t intrPoint;
             
             //triangle vectors
             u = p->polygon.ptB-p->polygon.ptA;
             v = p.polygon.ptC-p.polygon.ptA;
             
             //plane normal
             n=cross(u,v);
             if(!length(n)) return false;
             norm(n); // normalize normal
             n = correctDir(n, r.dst); // normal pointing in right directions
             
             //plane intersection - using getIntersection()
             plT = 6000.0f;
             pl.type = PLANE;
             pl.plane.n = n;
             pl.plane.d = n * p.polygon.ptA * -1.0f;
             if(!getIntersection(pl, r, plT)) return false;
             if(plT >= t) return false;
             
             /* old intersection
             w0 = r.src - p.polygon.ptA;
             norm(w0);
             if(n * r.dst == 0.0f) return false; // ray parallel to plane
             plT = (n * w0 * -1.0f)/(n * r.dst); // distance to intersection
             if(plT < 0.0 || plT > t) return false;
             */
            
            // intrPoint = r.src + r.dst * plT; // intersection point
            
            /* old intersection
             w = intrPoint - p.polygon.ptA;
             //norm(w); incorrect
             tD = (u*v)*(u*v)-(u*u)*(v*v);
             
             tS=((u*v)*(w*v)-(v*v)*(w*u))/tD;
             if(tS < 0.0f || tS > 1.0f) return false;
             tT=((u*v)*(w*u)-(u*u)*(w*v))/tD;
             if(tT < 0.0f || (tS+tT) > 1.0f) return false;
             
             t = plT; // new closest intersection
             return true;
             */
            
            
            //new method, credits to stanford
            // double u0, u1, u2, v0, v1, v2, aA, aB;
            
            /*
             //stampellen monstruosen in corsen
             //we need to play a bit with indexes
             int i0, i1, i2;
             if(n.x >= n.y && n.x >= n.z)
             i0 = 0;
             if(n.y >= n.x && n.y >= n.z)
             i0 = 1;
             if(n.z >= n.x && n.z >= n.y)
             i0 = 2;
             
             if(i0 == 0) {
             i1 = 1; i2 = 2;
             }
             if(i0 == 1) {
             i1 = 0; i2 = 2;
             }
             if(i0 == 2) {
             i1 = 0; i2 = 1;
             }
             
             
             double poly[3][3];
             poly[0][0] = p.polygon.ptA.x;
             poly[0][1] = p.polygon.ptA.y;
             poly[0][2] = p.polygon.ptA.z;
             
             poly[1][0] = p.polygon.ptB.x;
             poly[1][1] = p.polygon.ptB.y;
             poly[1][2] = p.polygon.ptB.z;
             
             poly[2][0] = p.polygon.ptC.x;
             poly[2][1] = p.polygon.ptC.y;
             poly[2][2] = p.polygon.ptC.z;
             
             double pt[3];
             pt[0] = intrPoint.x;
             pt[1] = intrPoint.y;
             pt[2] = intrPoint.z;
             
             u0 = pt[i1] - poly[0][i1];		//
             v0 = pt[i2] - poly[0][i2];		//
             u1 = poly[1][i1] - poly[0][i1];	//
             u2 = poly[2][i1] - poly[0][i1];	//
             v1 = poly[1][i2] - poly[0][i2];	//
             v2 = poly[2][i2] - poly[0][i2];	//
             
             */
            //end of stampellen
            
            
            //probably works, DO NOT TOUCH
            /*   if(fabs(n.x) >= fabs(n.y) && fabs(n.x) >= fabs(n.z)) // projecting to yz plane
             {
             u0 = intrPoint.y - p.polygon.ptA.y;//pt[i1] - poly[0][i1];		//
             v0 = intrPoint.z - p.polygon.ptA.z;//pt[i2] - poly[0][i2];		//
             u1 = p.polygon.ptB.y - p.polygon.ptA.y;//poly[1][i1] - poly[0][i1];	//
             u2 = p.polygon.ptC.y - p.polygon.ptA.y;//poly[2][i1] - poly[0][i1];	//
             v1 = p.polygon.ptB.z - p.polygon.ptA.z;//poly[1][i2] - poly[0][i2];	//
             v2 = p.polygon.ptC.z - p.polygon.ptA.z;//poly[2][i2] - poly[0][i2];	//
             }
             else if(fabs(n.y) >= fabs(n.x) && fabs(n.y) >= fabs(n.z)) // projecting to xz plane
             {
             u0 = intrPoint.x - p.polygon.ptA.x;
             v0 = intrPoint.z - p.polygon.ptA.z;
             u1 = p.polygon.ptB.x - p.polygon.ptA.x;
             u2 = p.polygon.ptC.x - p.polygon.ptA.x;
             v1 = p.polygon.ptB.z - p.polygon.ptA.z;
             v2 = p.polygon.ptC.z - p.polygon.ptA.z;
             }
             else // xy plane
             {
             u0 = intrPoint.x - p.polygon.ptA.x;
             v0 = intrPoint.y - p.polygon.ptA.y;
             u1 = p.polygon.ptB.x - p.polygon.ptA.x;
             u2 = p.polygon.ptC.x - p.polygon.ptA.x;
             v1 = p.polygon.ptB.y - p.polygon.ptA.y;
             v2 = p.polygon.ptC.y - p.polygon.ptA.y;
             }
             
             if(!u1)
             {
             aB = u0/u1;
             if(aB >= 0 && aB <= 1)
             aA = (v0 - aB*v2)/v1;
             }
             else
             {
             aB = (v0*u1 - u0*v1)/(v2*u1 - u2*v1);
             if(aB >= 0 && aB <= 1)
             aA = (u0 - aB*u2)/u1;
             }
             
             if(aA >= 0 && aB >= 0 && (aA+aB) <= 1)
             {
             t = plT;
             return true;
             }
             return false;
             
             break;
             */
    }
    
    
    return 0; // se arriva qui è un male!
}



vector_t getNormal(prim_t *p, point_t *intrPoint)
{
	vector_t normal, u, v;
	switch(p->type)
	{
        case SPHERE:
            normal = sub_comp(intrPoint,&p->sphere.center);
            norm(&normal);
            break;
        case PLANE:
            normal = p->plane.n; // already normalized
            // particularity of our implementation
            //normal.x = - normal.x; 
            //normal.y = - normal.y;
            //normal.z = - normal.z;

            /*case POLYGON:
             //triangle vectors
             u=p.polygon.ptB-p.polygon.ptA;
             v=p.polygon.ptC-p.polygon.ptA;
             
             //plane normal
             normal=cross(u,v);
             norm(normal); // normalize normal
             break;
             case PLANE:
             normal = p.plane.n; // already normalized
             // particularity of our implementation
             //normal.x = - normal.x; 
             //normal.y = - normal.y;
             //normal.z = - normal.z;
             break;
             case CONSTRUCTOR:
             break;*/
	}
	return normal;
}

vector_t correctDir(vector_t *normal, vector_t *dir)
{
	double temp = -1.0f;
	if(mul_comp(normal, dir) > 0.0f)
		*normal = mul_scal(normal,temp);
    
	return *normal;
}

