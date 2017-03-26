#include <iostream>
#include <GL/glew.h>

#include "display.h"
#include "camera.h"
#include "particle.h"

#define WIDTH 800
#define HEIGHT 600

int main(){
    Display display(WIDTH,HEIGHT,"Simulation");

    //Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
    Particle bullet("E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/bullet.obj",
                      "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/basicShader",
                      "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/bullet_skin.jpg");
    Particle glass("E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/glass.obj",
                      "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/basicShader",
                      "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/skin.jpg");
    Camera camera(glm::vec3(0,0,-3), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
    float counter = 0.0f;
    bullet.setPosition(glm::vec3(1.5,0.0,0.0));
    bullet.scale(glm::vec3(-0.6,-0.6,-0.6));
    glass.setPosition(glm::vec3(-0.5,0.0,0.0));
    glass.scale(glm::vec3(-0.2,-0.2,-0.2));
    while(!display.isClosed()){
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

        //float cosCounter = cosf(counter);

        bullet.draw(camera);
        glass.draw(camera);
        //p.setScale(glm::vec3(cosCounter, cosCounter, cosCounter));
        bullet.translate(glm::vec3(counter,0.0,0.0));
        //p.setRotation(glm::vec3(0.0,counter*2,0.0));
        display.update();
        counter -= 0.000001f;
        if(counter < -0.003){
            counter = 0.0f;
            bullet.setPosition(glm::vec3(1.5,0.0,0.0));
        }
    }

    return 0;
}
