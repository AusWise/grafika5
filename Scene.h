/* 
 * File:   Scene.h
 * Author: auswise
 *
 * Created on January 21, 2016, 3:17 PM
 */

#ifndef SCENE_H
#define	SCENE_H
#include "exprtk.hpp"

class Scene {
public:
    int vertices_length;
    double ** vertices;
    double** vertex_normals;

    int triangles_length;
    int** triangles;
    int * parts;
    double** triangle_normals;
    
    int parts_length;
    float ** colors;
    float ** params;
    
    float* lightPosition;

    double * p0;
    double * pt;
    double an;

    double t;
    
    exprtk::expression<double> expression_x;
    exprtk::expression<double> expression_y;
    exprtk::expression<double> expression_z;
    
    
    Scene();
    void setNormals();
    void setCameraOnCurve(double t);
    ~Scene();
private:
    void loadScene(const char* path);
    void loadCamera(const char* path);
    

};

#endif	/* SCENE_H */

