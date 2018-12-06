//
//  util.c
//  Ray
//
//  Created by Celestino Simone on 10/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include "prototype.h"


//UTIL


vector_t sum_comp( vector_t *v1,  vector_t *v2)
{
	vector_t v = { v1->x + v2->x, v1->y + v2->y, v1->z + v2->z };
	return v;
}

vector_t sub_comp (vector_t *v1, vector_t *v2)
{
	vector_t v = { v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
	return v;
}

double mul_comp (vector_t *vect1, vector_t *vect2)
{
	return (vect1->x * vect2->x + vect1->y * vect2->y + vect1->z * vect2->z);
}

vector_t mul_scal (vector_t *v, double t)
{
	vector_t vt = { v->x * t, v->y * t, v->z * t };
	return vt;
}

void sum_col_scal (color_t *c, double i)
{
	c->b += i;
	c->g += i;
	c->r += i;
    
}

color_t sum_col (color_t *s,  color_t *d)
{
	s->r += d->r;
	s->g += d->g;
	s->b += d->b;
	return *s;
}

color_t div_col_scal (color_t *s, int d)
{
	s->r /= d;
	s->g /= d;
	s->b /= d;
	return *s;
}

color_t mul_col_scal ( color_t *c,  double i)
{
	color_t cl = { c->r * i, c->g * i, c->b * i };
	return cl;
}

color_t prod_comp_col (color_t *c1, color_t *c2)
{
	color_t cl = { c1->r * c2->r, c1->g * c2->g, c1->b * c2->b };
	return cl;
}

vector_t div_scal (vector_t *v, double d)
{
    v->x /= d;
    v->y /= d;
    v->z /= d;
    return *v;
}

double length(vector_t *vect)
{
	return sqrt(mul_comp(vect,vect));
}

vector_t norm(vector_t *vect)
{
	double temp = 1.0f/length(vect); // mul is faster than div
	*vect = mul_scal(vect, temp);
	return *vect;
}

vector_t cross(vector_t *v1,vector_t *v2)
{
	vector_t t;
    
	//t.x=v1.x*v2.x;
	//t.y=v1.y*v2.y;
	//t.z=v1.z*v2.z;
	t.x=v1->y*v2->z - v2->y*v1->z;
	t.y=v1->x*v2->z - v2->x*v1->z;
	t.z=v1->x*v2->y - v2->x*v1->y;
    
	return t;
}
