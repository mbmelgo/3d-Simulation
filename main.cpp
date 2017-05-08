#include <iostream>
#include <GL/glew.h>
#include <string>
#include <sstream>

#include "display.h"
#include "camera.h"
#include "bullet.h"
#include "plane.h"
#include "menu.h"
#include "glass.h"

#define WIDTH 800
#define HEIGHT 600

using namespace std;


string PATH = "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/";
//string PATH = "C:/Users/MabelMelgo/Desktop/Vincent/CMSC162/3d-Simulation/";

Display display(WIDTH,HEIGHT,"Simulation", PATH);

Glass glass;
Bullet bullet;
Plane ground;
Plane leftWall;
Plane rightWall;
int totalMenuSize = 11;
Menu menu[11];
Camera camera(glm::vec3(0,0,5), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
float lowerBoundary = 0.0;
bool start = true;
bool hasTarget = false;

void generateGlass(){
    glass.init(PATH+"res/shaders/basicShader",
               PATH+"res/textures/glass_skin.jpg");
    glass.setTarget(glm::vec3(0.0,0.0,0.0));
}

void generateBullet(){
    bullet.init(    PATH+"res/obj_files/bullet.obj",
                    PATH+"res/shaders/basicShader",
                    PATH+"res/textures/bullet_skin.jpg");
    bullet.setAngleXY(display.getAngleXYValue());
    bullet.setAngleXZ(display.getAngleXZValue());
    bullet.setLowerBoundary(lowerBoundary);
    bullet.setSpeed(display.getSpeedValue());
    bullet.setMass(display.getMassValue());
    bullet.initBullet();
}

void generateBackground(){
    ground.init(    PATH+"res/obj_files/plane.obj",
                    PATH+"res/shaders/basicShader",
                    PATH+"res/textures/plane_skin.jpg");
    ground.setPosition(glm::vec3(0.0,0.0,0.0));
    ground.setScale(glm::vec3(5.0,0.0,5.0));
    ground.setDrawCoordinates(true);
    leftWall.init(  PATH+"res/obj_files/plane_2.obj",
                    PATH+"res/shaders/basicShader",
                    PATH+"res/textures/plane_skin_2.jpeg");
    leftWall.setPosition(glm::vec3(20.0,5.0,-15.0));
    leftWall.setScale(glm::vec3(0.5,0.5,0.5));
    leftWall.setDrawCoordinates(false);
    rightWall.init( PATH+"res/obj_files/plane_2.obj",
                    PATH+"res/shaders/basicShader",
                    PATH+"res/textures/plane_skin_2.jpeg");
    rightWall.setPosition(glm::vec3(20.0,5.0,15.0));
    rightWall.setScale(glm::vec3(0.5,0.5,0.5));
    rightWall.setDrawCoordinates(false);
}

void generateMenu(){
    menu[0].init( PATH+"res/obj_files/menu.obj",
                PATH+"res/shaders/basicShader",
                PATH+"res/textures/menu/speed.png");
    menu[0].setPosition(glm::vec3(-0.6,5.20,18.0));
    menu[0].setScale(glm::vec3(0.6,0.3,0.0));
    menu[1].init( PATH+"res/obj_files/menu.obj",
                PATH+"res/shaders/basicShader",
                PATH+"res/textures/menu/mass.png");
    menu[1].setPosition(glm::vec3(-0.62,5.00,18.0));
    menu[1].setScale(glm::vec3(0.6,0.3,0.0));
    menu[2].init( PATH+"res/obj_files/menu.obj",
                PATH+"res/shaders/basicShader",
                PATH+"res/textures/menu/angleVertical.png");
    menu[2].setPosition(glm::vec3(-0.63,4.80,18.0));
    menu[2].setScale(glm::vec3(0.6,0.3,0.0));
    menu[3].init( PATH+"res/obj_files/menu.obj",
                PATH+"res/shaders/basicShader",
                PATH+"res/textures/menu/start.png");
    menu[3].setPosition(glm::vec3(0.0,4.30,18.0));
    menu[3].setScale(glm::vec3(0.8,0.3,0.0));
    menu[4].init( PATH+"res/obj_files/info.obj",
                PATH+"res/shaders/basicShader",
                PATH+"res/textures/menu/speed_info.png");
    menu[4].setPosition(glm::vec3(0.35,5.19,18.0));
    menu[4].setScale(glm::vec3(0.5,0.3,0.0));
    menu[5].init( PATH+"res/obj_files/info.obj",
                PATH+"res/shaders/basicShader",
                PATH+"res/textures/menu/mass_info.png");
    menu[5].setPosition(glm::vec3(0.35,4.99,18.0));
    menu[5].setScale(glm::vec3(0.5,0.3,0.0));
    menu[6].init( PATH+"res/obj_files/info.obj",
                PATH+"res/shaders/basicShader",
                PATH+"res/textures/menu/angle_info.png");
    menu[6].setPosition(glm::vec3(0.355,4.79,18.0));
    menu[6].setScale(glm::vec3(0.5,0.3,0.0));
    menu[7].init( PATH+"res/obj_files/info.obj",
                PATH+"res/shaders/basicShader",
                PATH+"res/textures/menu/1x.png");
    menu[7].setPosition(glm::vec3(0.9,5.19,18.0));
    menu[7].setScale(glm::vec3(0.5,0.3,0.0));
    menu[8].init( PATH+"res/obj_files/info.obj",
                PATH+"res/shaders/basicShader",
                PATH+"res/textures/menu/1x.png");
    menu[8].setPosition(glm::vec3(0.9,4.99,18.0));
    menu[8].setScale(glm::vec3(0.5,0.3,0.0));
    menu[9].init( PATH+"res/obj_files/info.obj",
                PATH+"res/shaders/basicShader",
                PATH+"res/textures/menu/0d.png");
    menu[9].setPosition(glm::vec3(0.9,4.79,18.0));
    menu[9].setScale(glm::vec3(0.5,0.3,0.0));
    menu[10].init( PATH+"res/obj_files/menu.obj",
                PATH+"res/shaders/basicShader",
                PATH+"res/textures/menu/title.png");
    menu[10].setPosition(glm::vec3(0.0,5.6,18.0));
    menu[10].setScale(glm::vec3(0.8,0.8,1.0));

}

void init(){
    generateBackground();
    generateMenu();
    generateBullet();
}

void startActions(){
    bullet.draw(camera);

    if (!hasTarget && bullet.hasTarget()){
        glass.setVelocityIncoming(bullet.getTargetVelocity());
        glass.setTarget(bullet.getTarget());
        hasTarget = true;
        if(glass.canBreak()){
            display.playGlassBreak();
        }
    }
    glass.draw(camera);


//      WALLS
    ground.draw(camera);
    leftWall.draw(camera);
    rightWall.draw(camera);
}

void getSpeedTimes(){
    if(display.getSpeedTimes()==1.0){
        menu[7].changeTexture(PATH+"res/textures/menu/1x.png");
    } else if(display.getSpeedTimes()==1.25){
        menu[7].changeTexture(PATH+"res/textures/menu/2x.png");
    } else if(display.getSpeedTimes()==1.50){
        menu[7].changeTexture(PATH+"res/textures/menu/3x.png");
    } else if(display.getSpeedTimes()==1.75){
        menu[7].changeTexture(PATH+"res/textures/menu/4x.png");
    }
}

void getAngleTimes(){
    if(display.getAngleTimes()==0){
        menu[9].changeTexture(PATH+"res/textures/menu/0d.png");
    } else if (display.getAngleTimes()==1){
        menu[9].changeTexture(PATH+"res/textures/menu/10d.png");
    } else if (display.getAngleTimes()==2){
        menu[9].changeTexture(PATH+"res/textures/menu/20d.png");
    } else if (display.getAngleTimes()==3){
        menu[9].changeTexture(PATH+"res/textures/menu/30d.png");
    } else if (display.getAngleTimes()==4){
        menu[9].changeTexture(PATH+"res/textures/menu/40d.png");
    } else if (display.getAngleTimes()==5){
        menu[9].changeTexture(PATH+"res/textures/menu/50d.png");
    } else if (display.getAngleTimes()==6){
        menu[9].changeTexture(PATH+"res/textures/menu/60d.png");
    } else if (display.getAngleTimes()==7){
        menu[9].changeTexture(PATH+"res/textures/menu/70d.png");
    } else if (display.getAngleTimes()==8){
        menu[9].changeTexture(PATH+"res/textures/menu/80d.png");
    } else if (display.getAngleTimes()==9){
        menu[9].changeTexture(PATH+"res/textures/menu/90d.png");
    }
}

void getMassTimes(){
    if(display.getMassTimes()==1.0){
        menu[8].changeTexture(PATH+"res/textures/menu/1x.png");
    } else if(display.getMassTimes()==1.25){
        menu[8].changeTexture(PATH+"res/textures/menu/2x.png");
    } else if(display.getMassTimes()==1.5){
        menu[8].changeTexture(PATH+"res/textures/menu/3x.png");
    } else if(display.getMassTimes()==1.75){
        menu[8].changeTexture(PATH+"res/textures/menu/4x.png");
    }
}

void menuActions(){
    getSpeedTimes();
    getAngleTimes();
    getMassTimes();
    for(int i=0;i<totalMenuSize;i++){
        menu[i].draw(camera);
    }
    bullet.setAngleXY(display.getAngleXYValue());
    bullet.setSpeed(display.getSpeedValue());
    bullet.setMass(display.getMassValue());
}

int main(){
    init();

    while(!display.isClosed()){
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
        camera.setCamera(display.getCameraPosition(),display.getCameraFront());

        if (display.isStart()){
            if(start){
                printf("START\n");
                generateGlass();
                bullet.initBullet();
                display.setCamerPosition(glm::vec3(0.0f, 5.0f, 50.0f));
                start = false;
            }
            startActions();
        } else {
            menuActions();
        }

        display.update();
    }

    return 0;
}
