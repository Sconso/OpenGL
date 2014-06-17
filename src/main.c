/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        */
 /*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 13:36:47 by Myrkskog          #+#    #+#             */
/*   Updated: 2014/06/17 23:18:51 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GLUT/glut.h>
#include <main.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

t_cam		*cam;

t_cam		*init_cam(void)
{
	t_cam	*cam;

	cam = (t_cam *)malloc(sizeof(t_cam));
	if (!cam)
		exit(0);
	cam->angle = 0.0f;
	cam->pos.x = 0.0f;
	cam->pos.y = 1.0f;
	cam->pos.z = 1.0f;
	cam->point.x = 0.0f;
	cam->point.y = 1.0f;
	cam->point.z = 0.0f;
	cam->tilt.x = 0.0f;
	cam->tilt.y = 1.0f;
	cam->tilt.z = 0.0f;
	return (cam);
}

void	processNormalKeys(unsigned char key, int x, int y)
{
	(void)x;
	(void)y;
	if (key == 27)
		exit(0);
}

void	processSpecialKeys(int key, int x, int y)
{
	(void)x;
	(void)y;
	if (key == GLUT_KEY_LEFT)
	{
		cam->angle -= 0.1f;
		cam->point.x = sin(cam->angle);
		cam->point.z = -cos(cam->angle);
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		cam->angle += 0.1f;
		cam->point.x = sin(cam->angle);
		cam->point.z = -cos(cam->angle);
	}
}

void renderScene(void)
{
	static float	angle = 0.0;
	static float	zoom = 3.0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	cam->pos.z = zoom;
	gluLookAt(cam->pos.x, cam->pos.y, cam->pos.z,
			  cam->pos.x + cam->point.x, cam->point.y, cam->pos.z + cam->point.z,
			  cam->tilt.x, cam->tilt.y, cam->tilt.z);
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

	/*	angle += 5;*/

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
	glutSpecialFunc(processSpecialKeys);

	cam = init_cam();
	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;
}
