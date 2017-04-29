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


//string PATH = "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/";
string PATH = "C:/Users/MabelMelgo/Desktop/Vincent/CMSC162/3d-Simulation/";

//Particle glass[25];
float speedValue;
float gravityValue = -9.8f;

glm::vec3 gravity;
glm::vec3 speed;
Bullet bullet;
Plane ground;
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
    bullet.setAngleXY(50.0);
    bullet.setAngleXZ(0.0);
    bullet.setLowerBoundary(lowerBoundary);
    bullet.setSpeed(1.0);
    bullet.setMass(10.0);
    bullet.initBullet();
}

void generateBackground(){
    ground.init(    PATH+"res/obj_files/plane.obj",
                    PATH+"res/shaders/basicShader",
                    PATH+"res/textures/plane_skin.jpg");
    ground.setPosition(glm::vec3(0.0,0.0,0.0));
}

void init(){
    generateBullet();
    generateBackground();
    gravity = glm::vec3(0.0,gravityValue,0.0);
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

        display.update();
    }

    return 0;
}
