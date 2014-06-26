// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Render.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2014/06/24 16:13:17 by Myrkskog          #+#    #+#             //
//   Updated: 2014/06/24 16:13:24 by Myrkskog         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <Render.h>
#include <ctime>
#include <iostream>
#include <gfx.h>
#include <map>
#include <algorithm>

using namespace std;

Camera* Render::m_camera = NULL;
Game* Render::m_game = NULL;
float Render::m_rotX = 10;
float Render::m_rotY = 30;
float Render::m_rotZ = 0;
float Render::m_posX = 0;
float Render::m_posY = 0;
float Render::m_posZ = 0;

char Render::m_up = 0;
char Render::m_down = 0;
char Render::m_left = 0;
char Render::m_right = 0;
char Render::m_moveLeft = 0;
char Render::m_moveRight = 0;
char Render::m_moveUp = 0;
char Render::m_moveDown = 0;
char Render::m_zoomIn = 0;
char Render::m_zoomOut = 0;

char Render::m_activeFps = 1;
int Render::m_time = 0;
int Render::m_timebase = 0;
int Render::m_frame = 0;
string Render::m_fps = "FPS: ";

int Render::mt_time = 0;
int Render::mt_timebase = 0;
int Render::mt_frame = 0;

int Render::m_showInventory = -1;

void Render::newWindow(int ac, char **av, int w, int h, string name, Game *game)
{
    srand(time(0));
    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL);
    glutInitWindowPosition(-1, -1);
    glutInitWindowSize(w, h);
    glutCreateWindow(name.c_str());
    
    glEnable(GL_DEPTH_TEST);
    
    m_camera = new Camera();
    m_game = game;
}

void Render::setOrthographicProjection()
{
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluOrtho2D(0, width, height, 0);
    
	glMatrixMode(GL_MODELVIEW);
}

void Render::restorePerspectiveProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Render::mainLoop()
{
    glutDisplayFunc(Render::renderScene);
    glutIdleFunc(Render::renderScene);
	glutReshapeFunc(changeSize);
    
    glutIgnoreKeyRepeat(1);
    
    glutMouseFunc(Render::mouseButton);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardUpFunc(processUpKeys);
    glutSpecialUpFunc(processUpSpecialKeys);
    
    glutMainLoop();
}

/***********/
/* PRIVATE */
/***********/

void Render::changeSize(int w, int h)
{
	float ratio;
    
	if (h == 0)
		h = 1;
	ratio = 1.0 * w / h;
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void Render::renderScene(void)
{
    int width = m_game->getWidth();
    int height = m_game->getHeight();
    int resTab[7];
    static int resX = rand() % 200;
    static int resZ = rand() % 200;
    
    computeFps();
    computeTime();
    processKeyboardEvents();
    glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
	gluLookAt(m_camera->posX, m_camera->posY, m_camera->posZ,
			  m_camera->pointX, m_camera->pointY, m_camera->pointZ,
			  m_camera->tiltX, m_camera->tiltY, m_camera->tiltZ);
    
    glRotatef(m_rotX, 1, 0, 0);
    glRotatef(m_rotY, 0, 1, 0);
    glRotatef(m_rotZ, 0, 0, 1);
    
    glTranslatef(m_posX, 0, m_posZ);
    glTranslatef(0, 0, (height / 2 - height) * 2 + 1);
    for (int y = 0; y < height; ++y)
    {
        glPushMatrix();
        glTranslatef((width / 2 - width) * 2 + 1, 0, 0);
        for (int x = 0; x < width; ++x)
        {
            Cube::drawCube(x, y, m_game->getWidth() * 1.0, m_game->getHeight() * 1.0);
            Cube::drawOutline();
            
            m_game->getSquare(x, y, resTab);

            glPushMatrix();
            glTranslatef(0, 1, 0);
            for (int i = 0; i < 7; ++i)
            {
                if (resTab[i] > 0)
                {
                    float posX;
                    float posZ;
                
                    posX = ((resX * i) % 200 - 100) % 100 * 1.0 / 100;
                    posZ = ((resZ * i) % 200 - 100) % 100 * 1.0 / 100;

                    glPushMatrix();
                    
                    glTranslatef(posX, 0, posZ);
                    glColor3ub(255 % (i + 1), i * 100 % 255, i * i * 10 % 255);
                
                    GLUquadric* params = gluNewQuadric();
                    gluQuadricDrawStyle(params,GLU_FILL);
                    gluSphere(params,0.2, i + 3, i + 2);
                    gluDeleteQuadric(params);
                    
                    glPopMatrix();
                }
            }
            glPopMatrix();
            
            // PLAYERS
            map<int, Player *> players = m_game->getPlayers(x, y);
            map<int, Player *>::iterator it;
            
            for (it = players.begin(); it != players.end(); ++it)
            {
                glStencilFunc(GL_ALWAYS, (*it).second->getNb() + 1, -1);
                drawPlayer((*it).second->getTeam(), (*it).second->getNb());
            }
            glStencilFunc(GL_ALWAYS, 0, -1);

            glTranslatef(2, 0, 0);
        }
        glPopMatrix();
        glTranslatef(0, 0, 2);
    }

    glPushMatrix();
    glLoadIdentity();
    setOrthographicProjection();
    if (m_activeFps)
    {
        glColor3f(0.0f,1.0f,1.0f);
        renderBitmapString(5, 15, GLUT_BITMAP_HELVETICA_12, m_fps);
    }
    if (m_showInventory >= 0)
        drawInventory();
    drawPoints();
    
    restorePerspectiveProjection();
    glPopMatrix();
    
    glFlush();
	glutSwapBuffers();
}

void Render::teamColor(string team, int nb)
{
    int color = 0;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    
    for (unsigned long i = 0; i < team.size(); ++i)
        color = team[i] + ((color << 5) - color);
    
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
    if (nb >= 0 && m_showInventory >= 0 && nb == m_showInventory)
    {
        r = (r >= 155 ? 255 : r + 100);
        g = (g >= 155 ? 255 : g + 100);
        b = (b >= 155 ? 255 : b + 100);
    }
    glColor3ub(r, g, b);
}

void Render::drawPlayer(string team, int nb)
{
    glPushMatrix();
    
    glTranslatef(0, 1, 0);
    glRotatef(-90, 1, 0, 0);

    teamColor(team, nb);
    GLUquadric* params = gluNewQuadric();
    gluQuadricDrawStyle(params,GLU_FILL);
    gluCylinder(params, 0.2, 0.05, 1.5, 20, 1);
    
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, 1.3, 0);
    glColor3ub(235, 180, 152);
    
    gluSphere(params, 0.3, 20, 20);
    
    glColor3ub(255, 255, 255);
    
    glPushMatrix();
    glTranslatef(0.15, 0, 0.24);
    gluSphere(params, 0.05, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.05, 0, 0.27);
    gluSphere(params, 0.05, 20, 20);
    glPopMatrix();
    
    gluDeleteQuadric(params);
    
    glPopMatrix();
}

void Render::drawInventory(void)
{
    int tab[7];
    int textY = (m_activeFps ? 30 : 15);
    string str;
    
    m_game->getInventory(m_showInventory, tab);
    glColor3ub(255, 255, 255);
    
    str = "Player: ";
    str += to_string(m_showInventory);
    renderBitmapString(5, textY, GLUT_BITMAP_HELVETICA_12, str);
    textY += 15;
    
    str = "Team: ";
    str += m_game->getTeam(m_showInventory);
    renderBitmapString(5, textY, GLUT_BITMAP_HELVETICA_12, str);
    textY += 15;
    
    str = "Level: ";
    str += to_string(m_game->getLevel(m_showInventory));
    renderBitmapString(5, textY, GLUT_BITMAP_HELVETICA_12, str);
    textY += 15;
    
    str = "Nourriture: ";
    str += to_string(tab[0]);
    renderBitmapString(5, textY, GLUT_BITMAP_HELVETICA_12, str);
    textY += 15;
    
    str = "Linemate: ";
    str += to_string(tab[1]);
    renderBitmapString(5, textY, GLUT_BITMAP_HELVETICA_12, str);
    textY += 15;
    
    str = "Deraumere: ";
    str += to_string(tab[2]);
    renderBitmapString(5, textY, GLUT_BITMAP_HELVETICA_12, str);
    textY += 15;
    
    str = "Sibur: ";
    str += to_string(tab[3]);
    renderBitmapString(5, textY, GLUT_BITMAP_HELVETICA_12, str);
    textY += 15;
    
    str = "Mendiane: ";
    str += to_string(tab[4]);
    renderBitmapString(5, textY, GLUT_BITMAP_HELVETICA_12, str);
    textY += 15;
    
    str = "Phiras: ";
    str += to_string(tab[5]);
    renderBitmapString(5, textY, GLUT_BITMAP_HELVETICA_12, str);
    textY += 15;
    
    str = "Thystame: ";
    str += to_string(tab[6]);
    renderBitmapString(5, textY, GLUT_BITMAP_HELVETICA_12, str);
}

void Render::drawPoints(void)
{
    map<string, Team *> teamsMap;
    map<string, Team *>::iterator it;
    vector<Team *> teams;
    vector<Team *>::iterator it2;
    string str;
    string name;
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int points;
    int textY = 15;
    
    teamsMap = m_game->getTeams();
    
    for (it = teamsMap.begin(); it != teamsMap.end(); ++it)
        teams.push_back((*it).second);
    
    sort(teams.begin(), teams.end(), [](Team *a, Team *b){return a->getPoints() > b->getPoints();});
    
    for (it2 = teams.begin(); it2 != teams.end(); ++it2)
    {
        points = (*it2)->getPoints();
        name = (*it2)->getName();
        
        teamColor(name, -1);
        glLineWidth(18);
        glRasterPos3f(width - 200, textY - 6, 0);
        glBegin(GL_LINES);
        glVertex3f(width - 100, textY - 6, -0.1);
        glVertex3f(width - 100 + points, textY - 6, -0.1);
        glEnd();
        glLineWidth(1);
        
        str = name;
        str += " = " + to_string(points) + " point" + (points > 1 ? "s" : "");
        renderBitmapString(width - 180 - (name.size() * 7), textY, GLUT_BITMAP_HELVETICA_12, str);
        textY += 15;
    }
    
}

void Render::mouseButton(int button, int state, int x, int y)
{
//    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    GLuint index;
    
    if (state != GLUT_DOWN)
        return ;
    
    if (button == 0)
    {
        glReadPixels(x, height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
        m_showInventory = (index == 0 ? -1 : index - 1);
    }
    else if (button == 2)
        m_camera->posZ++;
    
    else if (button == 3)
        m_camera->posZ -= (m_camera->posZ - 1 <= 4 ? 0 : 1);
    else if (button == 4)
        m_camera->posZ++;
}

void Render::processKeyboardEvents(void)
{
    if (m_moveLeft)
        m_posX--;
    if (m_moveRight)
        m_posX++;
    if (m_moveUp)
        m_posZ--;
    if (m_moveDown)
        m_posZ++;
	if (m_left)
        m_rotY = (m_rotY - 1 < 0 ? 359 : m_rotY - 1);
    if (m_right)
        m_rotY = (m_rotY + 1 > 360 ? 1 : m_rotY + 1);
	if (m_up)
        m_rotX = (m_rotX - 1 < 0 ? 359 : m_rotX - 1);
    if (m_down)
        m_rotX = (m_rotX + 1 > 360 ? 1 : m_rotX + 1);
    if (m_zoomIn)
        m_camera->posZ -= (m_camera->posZ - 1 <= 4 ? 0 : 1);
    if (m_zoomOut)
        m_camera->posZ++;
}

void Render::processNormalKeys(unsigned char key, int x, int y)
{
    (void)x;
    (void)y;
    
    if (key == 27)
        ft_exit("Attempting to exit...");
    else if (key == '`')
        m_activeFps = (m_activeFps ? 0 : 1);
    else if (key == '+')
        m_zoomIn = 1;
    else if (key == '-')
        m_zoomOut = 1;
    else if (key == 'w')
        m_moveUp = 1;
    else if (key == 's')
        m_moveDown = 1;
    else if (key == 'a')
        m_moveLeft = 1;
    else if (key == 'd')
        m_moveRight = 1;
}

void Render::processSpecialKeys(int key, int x, int y)
{
    (void)x;
	(void)y;

	if (key == GLUT_KEY_LEFT)
        m_left = 1;
    else if (key == GLUT_KEY_RIGHT)
        m_right = 1;
	else if (key == GLUT_KEY_UP)
        m_up = 1;
    else if (key == GLUT_KEY_DOWN)
        m_down = 1;
}

void Render::processUpKeys(unsigned char key, int x, int y)
{
    (void)x;
	(void)y;

    if (key == '+')
        m_zoomIn = 0;
    if (key == '-')
        m_zoomOut = 0;
    if (key == 'w')
        m_moveUp = 0;
    if (key == 's')
        m_moveDown = 0;
    if (key == 'a')
        m_moveLeft = 0;
    if (key == 'd')
        m_moveRight = 0;
}

void Render::processUpSpecialKeys(int key, int x, int y)
{
    (void)x;
	(void)y;
    
	if (key == GLUT_KEY_LEFT)
        m_left = 0;
    else if (key == GLUT_KEY_RIGHT)
        m_right = 0;
	else if (key == GLUT_KEY_UP)
        m_up = 0;
    else if (key == GLUT_KEY_DOWN)
        m_down = 0;
}


void Render::enableAA(void)
{
    glEnable(GL_LINE_SMOOTH);
}

void Render::renderBitmapString(float x, float y, void *font, string str)
{
    glRasterPos3f(x, y, 0);
	for (char *c = &str[0]; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}

void Render::computeFps(void)
{
    ++m_frame;
    m_time = glutGet(GLUT_ELAPSED_TIME);
    if (m_time - m_timebase > 1000)
    {
        m_frame = (m_frame * 1000.0) / (m_time - m_timebase) + 1;
        m_fps = "FPS: ";
        m_fps += to_string(m_frame);
		m_timebase = m_time;
		m_frame = 0;
	}
}

void Render::computeTime(void)
{
    static int foodTime = 0;
    
    ++mt_frame;
    mt_time = glutGet(GLUT_ELAPSED_TIME);
    if (mt_time - mt_timebase > 1000 / m_game->getTime())
    {
        vector<string> move;
        
        ++foodTime;
        if (foodTime == 126)
        {
            move.push_back("lol");
            move.push_back("#42");
            move.push_back(to_string(rand() % 20));
            move.push_back(to_string(rand() % 20));
            move.push_back("1");
            m_game->movePlayer(move);
        

            foodTime = 0;
            m_game->starvePlayers();
        }
        
		mt_timebase = mt_time;
		mt_frame = 0;
	}
}

/*************************************************/
/*********         CUBE          *****************/
/*************************************************/

void Cube::drawCube(int x, int y, float xMax, float yMax)
{
    glPushMatrix();
    
    glBegin(GL_QUADS);
    if (x * y < xMax / 2)
        glColor3ub(70, 171, 67);
    else if (x * y > xMax / 1.5 && x * y < yMax)
        glColor3ub(7, 171, 30);
    else if (x + y > xMax / 3 && x + y < xMax / 2)
        glColor3ub(100, 82, 0);
    else if (x * y > (xMax * 20) + (yMax * 10))
        glColor3ub(91, 71, 0);
    else if (x * y > (xMax * 3) + (yMax * 6))
        glColor3ub(7, 171, 30);
    else if (x * y > xMax + yMax + xMax)
        glColor3ub(65, 242, 76);
    else
        glColor3ub(27, 196, 57);
    glVertex3d(1,1,1);
    glVertex3d(1,1,-1);
    glVertex3d(-1,1,-1);
    glVertex3d(-1,1,1);

    glColor3ub(111, 83, 69);
    glVertex3d(1,-1,1);
    glVertex3d(1,-1,-1);
    glVertex3d(1,1,-1);
    glVertex3d(1,1,1);
    
    glVertex3d(-1,-1,1);
    glVertex3d(-1,-1,-1);
    glVertex3d(1,-1,-1);
    glVertex3d(1,-1,1);
    
    glVertex3d(-1,1,1);
    glVertex3d(-1,1,-1);
    glVertex3d(-1,-1,-1);
    glVertex3d(-1,-1,1);
    
    glVertex3d(1,1,-1);
    glVertex3d(1,-1,-1);
    glVertex3d(-1,-1,-1);
    glVertex3d(-1,1,-1);
    
    glVertex3d(1,-1,1);
    glVertex3d(1,1,1);
    glVertex3d(-1,1,1);
    glVertex3d(-1,-1,1);
    glEnd();
    
    glPopMatrix();
}

void Cube::drawOutline()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glPushMatrix();
    
    glBegin(GL_QUADS);
    glColor3f(.3, .3, .3);
    
    glVertex3d(1,1,1);
    glVertex3d(1,1,-1);
    glVertex3d(-1,1,-1);
    glVertex3d(-1,1,1);
    
    glVertex3d(1,-1,1);
    glVertex3d(1,-1,-1);
    glVertex3d(1,1,-1);
    glVertex3d(1,1,1);
    
    glVertex3d(-1,-1,1);
    glVertex3d(-1,-1,-1);
    glVertex3d(1,-1,-1);
    glVertex3d(1,-1,1);
    
    glVertex3d(-1,1,1);
    glVertex3d(-1,1,-1);
    glVertex3d(-1,-1,-1);
    glVertex3d(-1,-1,1);
    
    glVertex3d(1,1,-1);
    glVertex3d(1,-1,-1);
    glVertex3d(-1,-1,-1);
    glVertex3d(-1,1,-1);
    
    glVertex3d(1,-1,1);
    glVertex3d(1,1,1);
    glVertex3d(-1,1,1);
    glVertex3d(-1,-1,1);
    glEnd();
    
    glPopMatrix();
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

