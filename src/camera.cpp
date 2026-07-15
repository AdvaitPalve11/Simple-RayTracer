#include "camera.h"

Camera::Camera(double fov , double AR): position(0,0,0),forward(0,0,-1),up(0,1,0),right(1,0,0), fov(fov) , aspectRatio(AR){}
Ray Camera::getRay(double u , double v) const{

}