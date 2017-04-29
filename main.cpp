#include <iostream>
#include <GL/glew.h>
#include <string>
#include <sstream>

#include "display.h"
#include "camera.h"
#include "bullet.h"
#include "plane.h"

#define WIDTH 800
#define HEIGHT 600


// MINIMUM SPEED = 10000, MAXIMUM = 1000000

using namespace std;


string PATH = "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/";

//Particle glass[25];
glm::vec3 gravity;
glm::vec3 speed;
Bullet bullet;
Plane ground;
Plane top;
Plane leftSide;
Plane rightSide;
Plane backSide;
Plane frontSide;
glm::vec3 target(0.0,10.0,20.0);
Camera camera(glm::vec3(0,0,5), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
float m_lowerBoundary = -10.0;

glm::vec3 getPixelValue(glm::vec3 f){
    return glm::vec3(f.x/1000000.00,f.y/1000000.00,f.z/1000000.00);
}

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
    bullet.init(    PATH+"Simulation/res/obj_files/bullet.obj",
                    PATH+"Simulation/res/shaders/basicShader",
                    PATH+"Simulation/res/textures/bullet_skin.jpg");
    bullet.setTarget(target);
    speed = getPixelValue(glm::vec3(-9000.0,9000.0,0.0));
    bullet.applyForce(speed);
}

void generateBackground(){
    top.init(   PATH+"Simulation/res/obj_files/plane.obj",
                PATH+"Simulation/res/shaders/basicShader",
                PATH+"Simulation/res/textures/plane_skin_3.jpg");
    top.setPosition(glm::vec3(0.0,20.0,0.0));
    ground.init(    PATH+"Simulation/res/obj_files/plane.obj",
                    PATH+"Simulation/res/shaders/basicShader",
                    PATH+"Simulation/res/textures/plane_skin.jpg");
    ground.setPosition(glm::vec3(0.0,-10.0,0.0));
    leftSide.init(  PATH+"Simulation/res/obj_files/plane_3.obj",
                    PATH+"Simulation/res/shaders/basicShader",
                    PATH+"Simulation/res/textures/plane_skin_2.jpeg");
    leftSide.setPosition(glm::vec3(0.0,10.0,20.0));
    rightSide.init( PATH+"Simulation/res/obj_files/plane_3.obj",
                    PATH+"Simulation/res/shaders/basicShader",
                    PATH+"Simulation/res/textures/plane_skin_2.jpeg");
    rightSide.setPosition(glm::vec3(0.0,10.0,-20.0));
    backSide.init( PATH+"Simulation/res/obj_files/plane_2.obj",
                    PATH+"Simulation/res/shaders/basicShader",
                    PATH+"Simulation/res/textures/plane_skin_2.jpeg");
    backSide.setPosition(glm::vec3(20.0,10.0,0.0));

    // CHANGE TO GLASS
    frontSide.init(  PATH+"Simulation/res/obj_files/plane_2.obj",
                    PATH+"Simulation/res/shaders/basicShader",
                    PATH+"Simulation/res/textures/glass_skin.jpg");
    frontSide.setPosition(glm::vec3(20.0,10.0,0.0));
    frontSide.setPosition(glm::vec3(-20.0,10.0,0.0));
}

void init(){
    generateBullet();
    generateBackground();
    gravity = getPixelValue(glm::vec3(0.0,-0.98,0.0));
}

int main(){
    Display display(WIDTH,HEIGHT,"Simulation");
    init();
    //generateGlassParts();

    while(!display.isClosed()){
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
        camera.setCamera(display.getCameraPosition(),display.getCameraFront());

        bullet.applyForce(gravity);
        bullet.draw(camera);




//      WALLS
        ground.draw(camera);
        top.draw(camera);
        leftSide.draw(camera);
        rightSide.draw(camera);
        backSide.draw(camera);
        frontSide.draw(camera);

        display.update();
    }

    return 0;
}
