/* 
 * File:   vectors.h
 * Author: auswise
 *
 * Created on January 21, 2016, 4:02 PM
 */

#ifndef VECTORS_H
#define	VECTORS_H
#include <math.h>

double length(double* x) {
    double length = 0;
    for (int i = 0; i < 3; i++)
        length += x[i] * x[i];

    length = sqrt(length);
    return length;
}

double* add(double* v, double* s) {
    double* t = new double[3];
    for (int i = 0; i < 3; i++)
        t[i] = v[i] + s[i];

    return t;
}

double* addEquals(double* v, double* s){
    for(int i=0;i<3;i++)
        v[i] += s[i];
    
    return v;
}

double* sub(double* v, double* s) {
    double* t = new double[3];
    for (int i = 0; i < 3; i++)
        t[i] = v[i] - s[i];

    return t;
}

double* cross(double* v, double* s) {
    double ax = v[0];
    double ay = v[1];
    double az = v[2];
    double bx = s[0];
    double by = s[1];
    double bz = s[2];

    double* cross = new double[3];
    cross[0] = ay * bz - az*by;
    cross[1] = az * bx - ax*bz;
    cross[2] = ax * by - ay * bx;
    
    return  cross;
}

void normalize(double* v) {
    double _length = length(v);
   
    v[0] = v[0]/_length;
    v[1] = v[1]/_length;
    v[2] = v[2]/_length;
}

#endif	/* VECTORS_H */

