//
//  prototype.h
//  Ray
//
//  Created by Celestino Simone on 10/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Ray_prototype_h
#define Ray_prototype_h
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "structure.h"

// Funzione Caricamento Scena da File
// -> ritorna il numero di linea in caso di errore di caricamento
// -> ritorna 0 se tutto ok
int loadconfig(char * path, struct scene_t *scene);

// Funzione che legge il Comando da File
// -> Ritorna l'identificativo del comando (nota: è stato usato "enum")
int getOpcode(FILE *file);


color_t getColor(int x,int y,scene_t *scene);

color_t trace(ray_t *ray, scene_t *scene, int depth, double currRefr);

vector_t sum_comp (vector_t *v1, vector_t *v2);
vector_t sub_comp (vector_t *v1, vector_t *v2);
double mul_comp (vector_t *vect1, vector_t *vect2);
vector_t mul_scal (vector_t *v, double t);
void sum_col_scal (color_t *c, double i);
color_t  sum_col (color_t *s, color_t *d);
color_t div_col_scal (color_t *s, int d);
color_t mul_col_scal (color_t *c, double i);
color_t prod_comp_col (color_t *c1, color_t *c2);
vector_t div_scal (vector_t *v, double d);
double length(vector_t *vect);
vector_t norm(vector_t *vect);
vector_t cross(vector_t *v1,vector_t *v2);
void draw(void);
void init(void);
color_t makeCheckImage(int x, int y, scene_t *scene);
int getIntersection(prim_t *p, ray_t *r, double *t);
vector_t getNormal(prim_t *p, point_t *intrPoint);
vector_t correctDir(vector_t *normal, vector_t *dir);

#endif
