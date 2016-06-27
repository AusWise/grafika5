/* 
 * File:   Scene.cpp
 * Author: auswise
 * 
 * Created on January 21, 2016, 3:17 PM
 */

#include "Scene.h"
#include <fstream>
#include "vectors.h"
#include "exprtk.hpp"
#include <iostream>

using namespace std;

Scene::Scene() {
    this->loadScene("/home/auswise/sceny/temple-v1.brp");
    this->loadCamera("/home/auswise/sceny/temple-v1.cam");
    t=0;
}

void Scene::loadScene(const char* path){
    ifstream file;
    file.open(path);

    int n;
    file >> n;

    vertices_length = n;
    vertices = new double* [vertices_length];
    for (int it = 0; it < n; it++) {
        vertices[it] = new double[3];
        file >> vertices[it][0];
        file >> vertices[it][1];
        file >> vertices[it][2];
    }
    
    vertex_normals = new double*[vertices_length];
    for(int i=0;i<vertices_length;i++)
        vertex_normals[i] = new double[3];
    
    file >> n;
    triangles_length = n;
    triangles = new int*[triangles_length];
    for (int it = 0; it < n; it++) {
        triangles[it] = new int[3];
        file >> triangles[it][0];
        file >> triangles[it][1];
        file >> triangles[it][2];
    }
    
    triangle_normals = new double*[triangles_length];
    for(int i=0;i<triangles_length;i++)
        triangle_normals[i] = new double[3];
    
    int p;
    parts = new int[n];
    for (int it = 0; it < n; it++) {
        file >> parts[it];
    }

    file >> n;
    parts_length = n;
    colors = new float* [n];
    params = new float* [n];
    for (int it = 0; it < n; it++) {
        colors[it] = new float[3];
        params[it] = new float[3];
        file >> colors[it][0];
        colors[it][0] = colors[it][0]/255;
        file >> colors[it][1];
        colors[it][1] = colors[it][1]/255;
        file >> colors[it][2];
        colors[it][2] = colors[it][2]/255;
        file >> params[it][0];
        file >> params[it][1];
        file >> params[it][2];
    }

    lightPosition = new float[4];
    file >> lightPosition[0];
    file >> lightPosition[1];
    file >> lightPosition[2];
    lightPosition[3] = 1;

    file.close();
}

void Scene::loadCamera(const char* path){
    ifstream file;
    file.open(path);
    p0 = new double[3];
    pt = new double[3];

    double x,y,z;
    
    file >> x;
    file >> y;
    file >> z;
    
    p0[0]=x;
    p0[1]=y;
    p0[2]=z;
   
    file >> x;
    file >> y;
    file >> z;
    
    pt[0]=x;
    pt[1]=y;
    pt[2]=z;
       
    file >> an;
    
    string expression_string_x, expression_string_y, expression_string_z, s;
    getline(file, s);
    getline(file, expression_string_x);
    getline(file, expression_string_y);
    getline(file, expression_string_z);
    
    exprtk::symbol_table<double> symbol_table;
    symbol_table.add_variable("t", t);
    symbol_table.add_constants();
    
    expression_x.register_symbol_table(symbol_table);
    expression_y.register_symbol_table(symbol_table);
    expression_z.register_symbol_table(symbol_table);
    
    exprtk::parser<double> parser;
    parser.compile(expression_string_x, expression_x);
    parser.compile(expression_string_y, expression_y);
    parser.compile(expression_string_z, expression_z);
    
    return;
}

void Scene::setNormals(){
    double * vector1, * vector2;
    for (int it = 0; it < triangles_length; it++){
        delete [] triangle_normals[it];
        vector1 = sub(vertices[triangles[it][1]], vertices[triangles[it][0]]);
        vector2 = sub(vertices[triangles[it][2]], vertices[triangles[it][1]]);
        triangle_normals[it] = cross(vector1 , vector2);
        normalize(triangle_normals[it]);
        delete [] vector1;
        delete [] vector2;
    }
    
    for(int it=0;it<vertices_length;it++){
        vertex_normals[it][0] = 0;
        vertex_normals[it][1] = 0;
        vertex_normals[it][2] = 0;
    }
    
    for (int it = 0; it < triangles_length; it++){
        vertex_normals[triangles[it][0]] = addEquals(vertex_normals[triangles[it][0]], triangle_normals[it]);
        vertex_normals[triangles[it][1]] = addEquals(vertex_normals[triangles[it][1]], triangle_normals[it]);
        vertex_normals[triangles[it][2]] = addEquals(vertex_normals[triangles[it][2]], triangle_normals[it]);
    }
    
    for(int it=0;it<vertices_length;it++)
        normalize(vertex_normals[it]);

}

void Scene::setCameraOnCurve(double t){
    this->t = t;
    p0[0] = expression_x.value();
    p0[1] = expression_y.value();
    p0[2] = expression_z.value();
}

Scene::~Scene() {
    for(int i=0;i<vertices_length;i++){
        delete [] vertices[i];
        delete [] vertex_normals[i];
    }
        
    delete [] vertices;
    delete [] vertex_normals;
    
    for(int i=0;i<triangles_length;i++){
        delete [] triangles[i];
        delete [] triangle_normals[i];
    }
    
    delete [] triangles;
    delete [] parts;
    delete [] triangle_normals;
    
    for(int i=0;i<parts_length;i++){
        delete [] colors[i];
        delete [] params[i];
    }
    
    delete [] colors;
    delete [] params;
    
    delete [] lightPosition;
    delete [] p0;
    delete [] pt;
}