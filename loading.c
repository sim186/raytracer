//
//  loading.c
//  Ray
//
//  Created by Celestino Simone on 10/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "structure.h"
#include "prototype.h"


int getOpcode(FILE *file)
{   char opcode[10];
    
    fscanf(file,"%s",&opcode);
    
    if(strcmp(opcode,"reso")==0) return RESO;
    if(strcmp(opcode,"size")==0) return SIZE;
    if(strcmp(opcode,"sphr")==0) return SPHR;
    if(strcmp(opcode,"poly")==0) return POLY;
    if(strcmp(opcode,"lght")==0) return LGHT;
    if(strcmp(opcode,"matr")==0) return MATR;
    if(strcmp(opcode,"plne")==0) return PLNE;
    if(strcmp(opcode,"aamx")==0) return AAMX;
    if(strcmp(opcode,"maxt")==0) return MAXT;
    if(strcmp(opcode,"cpos")==0) return CPOS;
    return UNKN;
}

int loadconfig(char *path, scene_t *scene)
{   FILE *file;
    struct prim_t tempPrim[10],s,p,pl;
	light_t tempLight[10],l;
	struct material_t tempMat[10],m;
	int countPrim = 0;
    int countLight = 0;
    int countMat = 0;
    int i;
    
    
    file = fopen(path,"rt");
    
    if(!file) printf("Problema apertura file\n");
    
    
    if(file != NULL)
    {   
        int line = 0;
        while(!feof(file))
        {  line++;
            
            switch(getOpcode(file))
            { 
                case RESO:
                    fscanf(file,"%d",&scene->screenResX);
                    fscanf(file,"%d",&scene->screenResY);
                    break;
                case SIZE:
                    fscanf(file,"%lf",&scene->screenSizeX);
                    fscanf(file,"%lf",&scene->screenSizeY);
                    break;
                case SPHR:
                    s.type = SPHERE;
                    fscanf(file,"%lf",&s.sphere.center.x);
                    fscanf(file,"%lf",&s.sphere.center.y);
                    fscanf(file,"%lf",&s.sphere.center.z);
                    fscanf(file,"%lf",&s.sphere.r);
                    fscanf(file,"%d",&s.mat);
                    tempPrim[countPrim]=s;
                    countPrim++;
                    break;
                case POLY:
                    p.type = POLYGON;
                    int k,h;
                    
                    fscanf(file,"%d",&p.polygon.numfaces);
                    
                    p.polygon.faces=(point_t *) malloc(sizeof(point_t) * p.polygon.numfaces);
                    
                    for(k=0; k<p.polygon.numfaces ; k++)
                    {   
                        fscanf(file,"%d",&p.polygon.faces[k].numvertices);
                        p.polygon.faces[k].vertices=(point_t *) malloc(sizeof(point_t) * p.polygon.numfaces);
                        
                        for(h=0; h<p.polygon.numfaces ; h++)
                        {  fscanf(file,"%lf",&p.polygon.faces[k].vertices[h].x);
                            fscanf(file,"%lf",&p.polygon.faces[k].vertices[h].y);
                            fscanf(file,"%lf",&p.polygon.faces[k].vertices[h].z);
                        }
                        fscanf(file,"%lf",&p.polygon.faces[k].normal.x);
                        fscanf(file,"%lf",&p.polygon.faces[k].normal.y);
                        fscanf(file,"%lf",&p.polygon.faces[k].normal.z);
                    }
                    
                    /*fscanf(file,"%lf",&p.polygon.ptA.x);
                     fscanf(file,"%lf",&p.polygon.ptA.y);
                     fscanf(file,"%lf",&p.polygon.ptA.z);
                     fscanf(file,"%lf",&p.polygon.ptB.x);
                     fscanf(file,"%lf",&p.polygon.ptB.y);
                     fscanf(file,"%lf",&p.polygon.ptB.z);
                     fscanf(file,"%lf",&p.polygon.ptC.x);
                     fscanf(file,"%lf",&p.polygon.ptC.y);
                     fscanf(file,"%lf",&p.polygon.ptC.z);*/
                    fscanf(file,"%d",&p.mat);
                    tempPrim[countPrim]=p;
                    countPrim++;
                    break;                
                case LGHT:
                    fscanf(file,"%lf",&l.x);
                    fscanf(file,"%lf",&l.y);
                    fscanf(file,"%lf",&l.z);
                    tempLight[countLight]=l;
                    countLight++;
                    break;
                case MATR:
                    fscanf(file,"%d",&m.mId);
                    fscanf(file,"%lf",&m.col.r);
                    fscanf(file,"%lf",&m.col.g);
                    fscanf(file,"%lf",&m.col.b);
                    fscanf(file,"%lf",&m.coefDiffuse);
                    fscanf(file,"%lf",&m.coefReflect);
                    fscanf(file,"%lf",&m.coefRefract);
                    fscanf(file,"%lf",&m.refrIndex);
                    tempMat[countMat]=m;
                    countMat++;
                    break;
                case PLNE:
                    pl.type = PLANE;
                    fscanf(file,"%lf",&pl.plane.n.x);
                    fscanf(file,"%lf",&pl.plane.n.y);
                    fscanf(file,"%lf",&pl.plane.n.z);
                    norm(&pl.plane.n);
                    fscanf(file,"%lf",&pl.plane.d);
                    fscanf(file,"%d",&pl.mat);
                    tempPrim[countPrim]=pl;
                    break;
                case AAMX:
                    fscanf(file,"%d",&scene->maxAA);
                    break;
                case CPOS:
                    fscanf(file,"%lf",&scene->cam.x);
                    fscanf(file,"%lf",&scene->cam.y);
                    fscanf(file,"%lf",&scene->cam.z);  
                    break;
                case MAXT:
                    fscanf(file,"%lf",&scene->maxT);
                    break;
                case UNKN:
                    return line;
                    break;
            }
        }
        
        // Ora occorre inserire gli elementi nella scena
        scene->primCount = countPrim;
        scene->lightCount = countLight;
        scene->matCount = countMat;
        
        // Allochiamo memoria per la scena
        scene->prim = (prim_t *) malloc(sizeof(prim_t) * scene->primCount);
        scene->light = (light_t *) malloc(sizeof(light_t) * scene->lightCount);
        scene->material = (material_t *) malloc(sizeof(material_t) * scene->matCount);
        
        // Copia da temp
        for(i = 0; i < scene->primCount; i++)
            scene->prim[i] = tempPrim[i];
        
        for(i = 0; i < scene->lightCount; i++)
            scene->light[i] = tempLight[i];
        
        for( i = 0; i < scene->matCount; i++)
            scene->material[i] = tempMat[i];
    }
    fclose(file);
    return 0;
}
