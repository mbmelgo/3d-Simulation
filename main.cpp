#include <iostream>
#include <GL/glew.h>
#include <string>
#include <sstream>

#include "display.h"
#include "camera.h"
#include "bullet.h"
#include "plane.h"
#include "menu.h"

#define WIDTH 800
#define HEIGHT 600

using namespace std;


string PATH = "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/";
//string PATH = "C:/Users/MabelMelgo/Desktop/Vincent/CMSC162/3d-Simulation/";

//Particle glass[25];

float gravityValue = -9.8f;
Display display(WIDTH,HEIGHT,"Simulation");

glm::vec3 gravity;
Bullet bullet;
Plane ground;
int totalMenuSize = 11;
Menu menu[11];
Camera camera(glm::vec3(0,0,5), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
float lowerBoundary = 0.0;

//void generateGlassParts(){
//    for(int i=1;i<26;i++){
//        string filename = "Simulation/res/glass_fragments/";
//        stringstream convert;
//        convert << i;
//        filename.append(convert.str());
//        filename.append(".obj");
//        glass[i].init(filename,
//                      "Simulation/res/basicShader",
//                      "Simulation/res/skin.jpg");
//        if (i == 25){
//            glass[i].scale(glm::vec3(0.9,0.9,0.9));
//        } else {
//            glass[i].scale(glm::vec3(-0.1,-0.1,-0.1));
//        }
////        glass[i].rotate(glm::vec3(0.0,0.7,0.0));
//        glass[i].setLocation(glm::vec3(-0.5,0.0,0.0));
//    }
//}

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
    gravity = glm::vec3(0.0,gravityValue,0.0);
}

void startActions(){
    bullet.applyForce(gravity);
    bullet.draw(camera);


//      WALLS
    ground.draw(camera);
}

void getSpeedTimes(){
    if(display.getSpeedTimes()==1){
        menu[7].changeTexture(PATH+"res/textures/menu/1x.png");
    } else if(display.getSpeedTimes()==2){
        menu[7].changeTexture(PATH+"res/textures/menu/2x.png");
    } else if(display.getSpeedTimes()==3){
        menu[7].changeTexture(PATH+"res/textures/menu/3x.png");
    } else if(display.getSpeedTimes()==4){
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
    } else if (display.getAngleTimes()==-1){
        menu[9].changeTexture(PATH+"res/textures/menu/10dn.png");
    } else if (display.getAngleTimes()==-2){
        menu[9].changeTexture(PATH+"res/textures/menu/20dn.png");
    } else if (display.getAngleTimes()==-3){
        menu[9].changeTexture(PATH+"res/textures/menu/30dn.png");
    } else if (display.getAngleTimes()==-4){
        menu[9].changeTexture(PATH+"res/textures/menu/40dn.png");
    } else if (display.getAngleTimes()==-5){
        menu[9].changeTexture(PATH+"res/textures/menu/50dn.png");
    } else if (display.getAngleTimes()==-6){
        menu[9].changeTexture(PATH+"res/textures/menu/60dn.png");
    } else if (display.getAngleTimes()==-7){
        menu[9].changeTexture(PATH+"res/textures/menu/70dn.png");
    } else if (display.getAngleTimes()==-8){
        menu[9].changeTexture(PATH+"res/textures/menu/80dn.png");
    } else if (display.getAngleTimes()==-9){
        menu[9].changeTexture(PATH+"res/textures/menu/90dn.png");
    }
}

void getMassTimes(){
    if(display.getMassTimes()==1){
        menu[8].changeTexture(PATH+"res/textures/menu/1x.png");
    } else if(display.getMassTimes()==2){
        menu[8].changeTexture(PATH+"res/textures/menu/2x.png");
    } else if(display.getMassTimes()==3){
        menu[8].changeTexture(PATH+"res/textures/menu/3x.png");
    } else if(display.getMassTimes()==4){
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
    bullet.initBullet();
}

int main(){
    init();

    while(!display.isClosed()){
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
        camera.setCamera(display.getCameraPosition(),display.getCameraFront());

        if (display.isStart()){
                startActions();
        } else {
            menuActions();
        }

        display.update();
    }

    return 0;
}
