#include "filebackground.h"
#include "public.h"

int numPoint = 0, numTriangle = 0;

point* pointList;
triangle* triangleList;

float sc = 0.065, alpha = 0.0, beta = 0.0;
float centerX, centerY, centerZ;

void drawFlower(double theX, double theY, double theZ)
{
	int i, r, s, t;
	point P;
	triangle T;

	/*GLfloat material_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0f };
	GLfloat material_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat material_shininess = 120.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);*/

	//glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT, GL_DIFFUSE);
	//glColor3f(0.2, 0.5, 0.8);
	//glColorMaterial(GL_FRONT, GL_SPECULAR);
	//glColor3f(0.9, 0.0, 0.2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(theX, theY, theZ);
	glTranslatef(centerX, centerY, centerZ);
	glRotatef(alpha, 0.0, 1.0, 0.0);
	glRotatef(beta, 0.0, 0.0, 1.0);
	glScalef(sc, sc, sc);
	glTranslatef(-centerX, -centerY, -centerZ);
	glBegin(GL_TRIANGLES);
	for (i = 1; i <= numTriangle; i++)
	{
		T = triangleList[i];
		r = T.i; s = T.j; t = T.k;
		P = pointList[r];
		glNormal3f(P.nx, P.ny, P.nz); glVertex3f(P.x, P.y, P.z);
		P = pointList[s];
		glNormal3f(P.nx, P.ny, P.nz); glVertex3f(P.x, P.y, P.z);
		P = pointList[t];
		glNormal3f(P.nx, P.ny, P.nz); glVertex3f(P.x, P.y, P.z);
	}
	glEnd();
	glPopMatrix();

	//glDisable(GL_COLOR_MATERIAL);

	beta++;
	alpha++;

	if (beta > 360.0) beta = beta - 360;
	if (alpha > 360.0) alpha = alpha - 360;
}

void Inputobjfile(char* filename)
{
	FILE* fin;
	int ith, s, r, t,err;
	double x, y, z, nx, ny, nz, xmin, xmax, ymin, ymax, zmin, zmax;
	char str[100];

	err =fopen_s(&fin, filename, "r");
	if (err)
	{
		cout << "Error:obj file can't be open!\n";
		exit(1);
	}

	fscanf_s(fin, "%d %d", &numPoint, &numTriangle);

	pointList = new point[numPoint + 1];
	triangleList = new triangle[numTriangle + 1];

	fscanf(fin, "%s %lf %lf %lf\n", str, &nx, &ny, &nz);
	fscanf(fin, "%s %lf %lf %lf\n", str, &x, &y, &z);
	pointList[1].x = x;
	pointList[1].y = y;
	pointList[1].z = z;
	pointList[1].nx = nx;
	pointList[1].ny = ny;
	pointList[1].nz = nz;

	xmin = x;  xmax = x;
	ymin = y;  ymax = y;
	zmin = z;  zmax = z;

	for (ith = 2; ith <= numPoint; ith++)
	{
		fscanf(fin, "%s %lf %lf %lf\n", str, &nx, &ny, &nz);
		fscanf(fin, "%s %lf %lf %lf\n", str, &x, &y, &z);
		pointList[ith].x = x;
		pointList[ith].y = y;
		pointList[ith].z = z;
		pointList[ith].nx = nx;
		pointList[ith].ny = ny;
		pointList[ith].nz = nz;

		if (pointList[ith].x < xmin)
			xmin = pointList[ith].x;
		if (pointList[ith].x > xmax)
			xmax = pointList[ith].x;
		if (pointList[ith].y < ymin)
			ymin = pointList[ith].y;
		if (pointList[ith].y > ymax)
			ymax = pointList[ith].y;
		if (pointList[ith].z < zmin)
			zmin = pointList[ith].z;
		if (pointList[ith].z > zmax)
			zmax = pointList[ith].z;
	}

	centerX = (xmin + xmax) / 2.0;
	centerY = (ymin + ymax) / 2.0;
	centerZ = (zmin + zmax) / 2.0;

	for (ith = 1; ith <= numTriangle; ith++)
	{
		fscanf(fin, "%s %d//%d %d//%d %d//%d\n", str, &r, &r, &s, &s, &t, &t);
		triangleList[ith].i = r;
		triangleList[ith].j = s;
		triangleList[ith].k = t;
	}

	fclose(fin);
}
