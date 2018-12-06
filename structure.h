//
//  structure.h
//  Ray
//
//  Created by Celestino Simone on 10/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Ray_structure_h
#define Ray_structure_h
// Strutture Dati 

struct vector_t {
	double x, y, z;
};

typedef struct vector_t point_t;  // Punto individuato da 3 coordinate 
typedef struct vector_t light_t;  // Luce individuata da 3 coordinate
typedef struct vector_t vector_t;

struct ray_t {            // Raggio                               
	point_t src;          // Punto d'origine
	struct vector_t dst;         // Destinazione
};

typedef struct ray_t ray_t;


struct color_t {          // Colore: RED GREEN BLUE
	double r, g, b;
};

typedef struct color_t color_t;


// Primitive
enum PRIMITIVES
{
	POLYGON,
	PLANE,
    SPHERE
};

struct sphere_t {            // SFERA: Centro e Raggio
	point_t center;
	double r;
};

typedef struct sphere_t sphere_t;


/*struct polygon_t {           // Poligono: definito da 3 Punti
 point_t ptA, ptB, ptC;   
 };
 */

struct faces_t{              // Facce del poligono
    int numvertices;         // Num vertici a faccia
    point_t *vertices;       // Vertici della faccia
    point_t normal;          // Normale alla faccia
}; 
typedef struct faces_t faces_t;

struct polygon_t {           // Poligono: definito da facce
    int numfaces;            // Num faccie del poligono
    faces_t *faces;  
};
typedef struct polygon_t polygon_t;

struct plane_t {             // Piano: definito da un punto
	struct vector_t n;
	double d;                                                    //  <<----
};

typedef struct plane_t plane_t;


struct prim_t {              // Primitiva
	int type;                // Tipo di Primitiva
	int mat;                 // Identificativo Materiale
    
	struct sphere_t sphere;
	struct polygon_t polygon;
	struct plane_t plane;
};

typedef struct prim_t prim_t;


struct material_t {          // MAteriale
	int mId;                 // Identificativo
	struct color_t col;             // COlore
	double coefDiffuse;      // Coefficiente Diffusione
	double coefReflect;      // Coefficiente Riflessione
	double coefRefract;      // Coefficiente Rifrazione
	double refrIndex;        // Indice di Rifrazione
};

typedef struct material_t material_t;


struct scene_t {             // Scena
    
	int screenResX;          // Risoluzione Scena Asse X
	int screenResY;          // Risoluzione Scena Asse Y
	double screenSizeX;      // Dimensione Scena Asse X
	double screenSizeY;      // Dimensione Scena Asse Y
    
	int maxAA;               // Antialias
    
	double maxT;             // Max render distance
    
	point_t cam;             // Punto posizione camera
    
	
	// COntenuto della scena
	int primCount,           // Numero Primitive
    lightCount,           // Numero Luci
    matCount;           // NUmero Materiali
    
	struct prim_t *prim;            // Array di Primitive
	light_t *light;          //   ""     Luci
	struct material_t *material;    //   ""     Materiali
    
};

typedef struct scene_t scene_t;
/*
 // MACRO FUNZIONI
 // FUNZIONE RAPPORTO    da trasformare in C e spostare in util.h
 */






// Codici Operazioni
enum OPCODES 
{
	RESO,    // Risoluzione
	SIZE,    // Dimensione
	SPHR,    // Sfera
	POLY,    // Poligono
	LGHT,    // Luce
	MATR,    // Materiale
	PLNE,    // Piano
	AAMX,    // Antialias        <<----
	MAXT,    // Max render T     <<----
	CPOS,    // Posizione CAM
	UNKN     // Comando Sconosciuto
};


#endif
