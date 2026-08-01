
# ifndef VEC3_H
# define VEC3_H
 
# include <cmath>
#include <cstdlib>

struct vec3 {

    double v[3];

    vec3() : v{0, 0, 0} {}
    vec3(double a, double b, double c) : v{a, b, c} {}

    vec3 operator-() const{
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

    vec3 operator- (const vec3& v2) const{
        vec3 v3 = vec3(v[0], v[1], v[2]);
        v3.v[0] -= v2.v[0];
        v3.v[1] -= v2.v[1];
        v3.v[2] -= v2.v[2];
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

    vec3 normalized() const{
        return *this / length(); 
    }

    double r() const {return v[0]; }
    double g() const {return v[1]; }
    double b() const {return v[2]; }

    double x() const {return v[0]; }
    double y() const {return v[1]; }
    double z() const {return v[2]; }

    double operator[] (int i) const {return v[i]; }

};

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

inline double dot(const vec3& v1, const vec3& v2){
    return (v1.v[0] * v2.v[0]) + (v1.v[1] * v2.v[1]) + (v1.v[2] * v2.v[2]);
}

inline vec3 operator*(double c, const vec3& v) {
    return v * c; 
}

inline vec3 cross(const vec3& v1, const vec3& v2) {
    return vec3(v1.v[1]*v2.v[2] - v1.v[2]*v2.v[1],
                v1.v[2]*v2.v[0] - v1.v[0]*v2.v[2],
                v1.v[0]*v2.v[1] - v1.v[1]*v2.v[0]);
}

inline vec3 random_unit_vector() {
    while (true) {
        vec3 p = vec3(2 * random_double()-1, 2 * random_double()-1, 2 * random_double()-1);
        double lensq = p.length() * p.length();
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}

inline vec3 random_same_hemisphere(vec3 n) {
    vec3 v = random_unit_vector();
    if (dot(v, n) > 0.0){
        return v;
    }
    else {
        return -v;
    }
}

#endif