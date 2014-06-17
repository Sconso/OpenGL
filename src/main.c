/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 13:36:47 by Myrkskog          #+#    #+#             */
/*   Updated: 2014/06/17 14:08:24 by Myrkskog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GLUT/glut.h>
#include <stdio.h>

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0,-1.0,0.0);
	glVertex3f(1.0,-1.0,0.0);
	glVertex3f(0.5,0.0,0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(-1.0,-1.0,0.0);
	glVertex3f(0.0,-1.0,0.0);
	glVertex3f(-0.5,0.0,0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5,0.0,0.0);
	glVertex3f(0.5,0.0,0.0);
	glVertex3f(0.0,1.0,0.0);
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(renderScene);

	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;
}
