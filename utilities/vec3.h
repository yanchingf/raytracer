
# ifndef VEC3_H
# define VEC3_H

// rizz
# include <cmath>

struct vec3 {

    double v[3];

    vec3() : v{0, 0, 0} {}
    vec3(double a, double b, double c) : v{a, b, c} {}

    vec3 operator-(){
        return vec3(-v[0], -v[1], -v[2]);
    }

    vec3& operator+=(const vec3& v2){
        v[0] += v2.v[0];
        v[1] += v2.v[1];
        v[2] += v2.v[2];
        return *this;
    }

    vec3& operator-=(const vec3& v2){
        v[0] -= v2.v[0];
        v[1] -= v2.v[1];
        v[2] -= v2.v[2];
        return *this;
    }

    vec3& operator*=(double c){
        v[0] *= c;
        v[1] *= c;
        v[2] *= c;
        return *this;
    }

    vec3& operator/=(double c){
        v[0] /= c;
        v[1] /= c;
        v[2] /= c;
        return *this;
    }

    vec3 operator+ (const vec3& v2) const{
        vec3 v3 = vec3(v[0], v[1], v[2]);
        v3.v[0] += v2.v[0];
        v3.v[1] += v2.v[1];
        v3.v[2] += v2.v[2];
        return v3;
    }

    vec3 operator* (double c) const{
        vec3 v2 = vec3(v[0], v[1], v[2]); 
        return v2 *= c;
    }

    vec3 operator/ (double c) const{
        vec3 v2 = vec3(v[0], v[1], v[2]); 
        return v2 /= c;
    }

    double length() const{
        return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    }

    vec3 normalized(const vec3& v){
        double l = v.length();
        return v / l; 
    }

    double r() const {return v[0]; }
    double g() const {return v[1]; }
    double b() const {return v[2]; }

    double x() const {return v[0]; }
    double y() const {return v[1]; }
    double z() const {return v[2]; }

    
};

# endif