/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        */
 /*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 13:36:47 by Myrkskog          #+#    #+#             */
/*   Updated: 2014/06/17 22:37:46 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>

void processNormalKeys(unsigned char key, int x, int y)
{
	(void)x;
	(void)y;
	if (key == 27)
		exit(0);
}

void renderScene(void)
{
	static float	angle = 0.0;
	static float	zoom = 3.0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0, 0.0, zoom,
			  0.0, 0.0,  0.0,
			  0.0, 1.0,  0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0,-1.0, -1.0);
	glVertex3f(1.0,-1.0, -1.0);
	glVertex3f(0.5,0.0, -1.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(0.0, -1.0, -1.0);
	glVertex3f(-0.5, 0.0, -1.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5, 0.0, -1.0);
	glVertex3f(0.5, 0.0, -1.0);
	glVertex3f(0.0, 1.0, -1.0);
	glEnd();

	angle += 5;

	glutSwapBuffers();
}

void 		changeSize(int w, int h)
{
	float	ratio;

	if (h == 0)
		h = 1;
	ratio = 1.0 * w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(90, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(2560, 1440);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);


	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;
}
