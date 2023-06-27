#include "camera.h"
#include "public.h"

Camera::Camera() { }

Camera::Camera(double x, double y, double z) :
	cx(x), cy(y), cz(z) { }

double Camera::getCx() { return cx; }

double Camera::getCy() { return cy; }

double Camera::getCz() { return cz; }

void Camera::follow1(double bx, double by, double bz) { cx = bx + 2, cy = by, cz = bz; }

void Camera::follow3(double bx, double by, double bz) { cx = bx, cy = by + 8, cz = bz + 16; }