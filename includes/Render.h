/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 16:13:41 by Myrkskog          #+#    #+#             */
/*   Updated: 2014/06/24 16:13:41 by Myrkskog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include <GLUT/glut.h>
#include <string>
#include <Game.h>

class Camera;

class Render
{
    public:
    /****************************/
    /*          CORE            */
    /****************************/
    static void newWindow(int ac, char **av, int w, int h, std::string name, Game *game);
    static void setOrthographicProjection();
    static void restorePerspectiveProjection();
    static void mainLoop();

    /****************************/
    /*          DRAWING         */
    /****************************/
    static void teamColor(std::string team, int nb);
    static void drawPlayer(std::string team, int nb);
    static void drawInventory(void);
    static void drawPoints(void);
    static void drawBroadcast(std::string msg);
    static void DrawEllipse(float radiusX, float radiusY);
    
    /****************************/
    /*        PROCESSING        */
    /****************************/
    static void changeSize(int w, int h);
    static void mouseButton(int button, int state, int x, int y);
    static void processKeyboardEvents(void);
    static void processNormalKeys(unsigned char key, int x, int y);
    static void processSpecialKeys(int key, int x, int y);
    static void processUpKeys(unsigned char key, int x, int y);
    static void processUpSpecialKeys(int key, int x, int y);
    
    /****************************/
    /*         OPTIONS          */
    /****************************/
    static void enableAA(void);
    
    /****************************/
    /*          RENDERS         */
    /****************************/
    static void renderScene(void);
    static void renderBitmapString(float x, float y, void *font, std::string str);
    static void renderStrokeFontString(float x, float y, float z, float scale, float width, void *font, std::string str);
    static GLuint createDl(void);

    /****************************/
    /*       CALCULATIONS       */
    /****************************/
    static void computeFps(void);
    static void computeTime(void);
    
    private:
    /* POSITIONS */
    static float m_rotX;
    static float m_rotY;
    static float m_rotZ;
    static float m_posX;
    static float m_posY;
    static float m_posZ;
    
    /* KEYS */
    static char m_up;
    static char m_down;
    static char m_left;
    static char m_right;
    static char m_moveLeft;
    static char m_moveRight;
    static char m_moveUp;
    static char m_moveDown;
    static char m_zoomIn;
    static char m_zoomOut;
    
    /* ATTRIBUTES */
    static Camera *m_camera;
    static Game *m_game;
    static GLuint m_dlId;
    
    /* FPS */
    static char m_activeFps;
    static int m_time;
    static int m_timebase;
    static int m_frame;
    static std::string m_fps;
    
    /* TME */
    static int mt_time;
    static int mt_timebase;
    static int mt_frame;
    
    /* FLAGS */
    static int m_showInventory;
    static char m_showLines;
};

class Camera
{
    friend class Render;
    
    public:
    Camera();
    
    private:
    float angle;
    float posX;
    float posY;
    float posZ;
    float pointX;
    float pointY;
    float pointZ;
    float tiltX;
    float tiltY;
    float tiltZ;
};

class Cube
{
    public:
    static void drawCube(int x, int y, float xMax, float yMax);
    static void drawOutline();
    
    private:
};

#endif
