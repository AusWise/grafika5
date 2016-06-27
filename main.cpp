/* 
 * File:   main.cpp
 * Author: auswise
 *
 * Created on January 12, 2016, 3:56 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "Scene.h"
#include "exprtk.hpp"

using namespace std;

int width;
int height;

Scene* scene;

void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void mouse(int btn, int state, int x, int y);
void idle();
void display();

/*
 * 
 */

void load(){
    
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Nazwa okna");
    
    scene = new Scene();
   
    glutReshapeFunc(&reshape);
    glutDisplayFunc(&display);
    glutIdleFunc(&idle);
    glutMouseFunc(&mouse);
    glutKeyboardFunc(&keyboard);
    glutMainLoop();

    return 0;
}

void reshape(int w, int h) {
    width = w;
    height = h;
    return;
}

void keyboard(unsigned char key, int x, int y) {
    if(key==GLUT_KEY_LEFT)
        scene->setCameraOnCurve(scene->t-0.1);
        
    if(key==GLUT_KEY_RIGHT)
        scene->setCameraOnCurve(scene->t+0.1);
    
    glutPostRedisplay();
    return;
}

void mouse(int btn, int state, int x, int y) {
    return;
}

void idle() {
    return;
}

void display() {
    scene->setNormals();
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
    glEnable(GL_LIGHT0);
    
    glViewport(0, ((double)width)/height, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(scene->an, 1, 0.1, 1000);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(scene->p0[0], scene->p0[1], scene->p0[2], 
            scene->pt[0], scene->pt[1], scene->pt[2], 
            0, 1, 0);
    
    glLightfv(GL_LIGHT0, GL_POSITION, scene->lightPosition);
    glEnable( GL_RESCALE_NORMAL );
    glEnable(GL_COLOR_MATERIAL);
    
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_MODELVIEW);
    for (int it = 0; it < scene->triangles_length; it++) {
        
        glBegin(GL_TRIANGLES);
        glColor3d(scene->colors[scene->parts[it]][0], 
                scene->colors[scene->parts[it]][1], 
                scene->colors[scene->parts[it]][2]);

        float materialDiffuse[4] = {
            scene->params[scene->parts[it]][0], 
            scene->params[scene->parts[it]][0],
            scene->params[scene->parts[it]][0],
            1};
        
        
        float materialSpecular[4] = {
            scene->params[scene->parts[it]][1], 
            scene->params[scene->parts[it]][1],
            scene->params[scene->parts[it]][1],
            1};
        
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, scene->params[scene->parts[it]][2]);
        
        glNormal3d(
                scene->vertex_normals[scene->triangles[it][0]][0], 
                scene->vertex_normals[scene->triangles[it][0]][1], 
                scene->vertex_normals[scene->triangles[it][0]][2]);
        
        glVertex3d(
                scene->vertices[scene->triangles[it][0]][0], 
                scene->vertices[scene->triangles[it][0]][1], 
                scene->vertices[scene->triangles[it][0]][2]);
        
        glNormal3d(
                scene->vertex_normals[scene->triangles[it][1]][0], 
                scene->vertex_normals[scene->triangles[it][1]][1], 
                scene->vertex_normals[scene->triangles[it][1]][2]);
        
        glVertex3d(
                scene->vertices[scene->triangles[it][1]][0], 
                scene->vertices[scene->triangles[it][1]][1], 
                scene->vertices[scene->triangles[it][1]][2]);
        
        glNormal3d(
                scene->vertex_normals[scene->triangles[it][2]][0], 
                scene->vertex_normals[scene->triangles[it][2]][1], 
                scene->vertex_normals[scene->triangles[it][2]][2]);
        
        glVertex3d(
                scene->vertices[scene->triangles[it][2]][0], 
                scene->vertices[scene->triangles[it][2]][1], 
                scene->vertices[scene->triangles[it][2]][2]);

        glEnd();
    }
    
    glutSwapBuffers();
    
    glFlush();

    return;
}



