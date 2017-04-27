#include <iostream>
#include <GL/glew.h>
#include <string>
#include <sstream>

#include "display.h"
#include "camera.h"
#include "bullet.h"

#define WIDTH 800
#define HEIGHT 600

using namespace std;

glm::vec3 gravity;

//Particle glass[25];
Bullet bullet;

glm::vec3 getPixelValue(glm::vec3 f){
    return glm::vec3(f.x/1000000.00,f.y/1000000.00,f.z/1000000.00);
}

//void generateGlassParts(){
//    for(int i=1;i<26;i++){
//        string filename = "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/glass_fragments/";
//        stringstream convert;
//        convert << i;
//        filename.append(convert.str());
//        filename.append(".obj");
//        glass[i].init(filename,
//                      "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/basicShader",
//                      "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/skin.jpg");
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
    bullet.init("E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/bullet.obj",
                      "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/basicShader",
                      "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/bullet_skin.jpg");

    bullet.setLocation(glm::vec3(1.5,0.0,0.0));
    bullet.scale(glm::vec3(-0.6,-0.6,-0.6));
    bullet.setAcceleration(getPixelValue(glm::vec3(-0.2,0.0,0.0)));
    bullet.setVelocity(glm::vec3(0.0,0.0,0.0));
    bullet.setMass(4.2);
}

void init(){
    gravity = getPixelValue(glm::vec3(0.0,-0.8,0.0));
    generateBullet();
}

int main(){
    Display display(WIDTH,HEIGHT,"Simulation");
    init();
    //generateGlassParts();

    Camera camera(glm::vec3(0,0,-5), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);

    bullet.applyForce(gravity);
    while(!display.isClosed()){
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
        camera.setCamera(display.getCameraPosition(),display.getCameraFront());

        bullet.draw(camera);

        display.update();
    }

    return 0;
}
