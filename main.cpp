#include <iostream>
#include <GL/glew.h>
#include <string>
#include <sstream>

#include "display.h"
#include "camera.h"
#include "particle.h"

#define WIDTH 800
#define HEIGHT 600

using namespace std;

Particle glass[25];

void generateGlassParts(){
    for(int i=1;i<26;i++){
        string filename = "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/glass_fragments/";
        stringstream convert;
        convert << i;
        filename.append(convert.str());
        filename.append(".obj");
        glass[i].init(filename,
                      "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/basicShader",
                      "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/skin.jpg");
        if (i == 25){
            glass[i].scale(glm::vec3(0.9,0.9,0.9));
        } else {
            glass[i].scale(glm::vec3(-0.1,-0.1,-0.1));
        }
        glass[i].rotate(glm::vec3(0.0,0.7,0.0));
        glass[i].translate(glm::vec3(-0.5,0.0,0.0));
    }
}

int main(){
    Display display(WIDTH,HEIGHT,"Simulation");
    generateGlassParts();
    //Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
    Particle bullet("E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/bullet.obj",
                      "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/basicShader",
                      "E:/Vincent/4thYear/2ND SEM/CMSC_162/FINAL_PROJECT/Simulation/res/bullet_skin.jpg");
    Camera camera(glm::vec3(0,0,-5), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
    float counter = 0.0f;
    bullet.setPosition(glm::vec3(1.5,0.0,0.0));
    bullet.scale(glm::vec3(-0.6,-0.6,-0.6));

    while(!display.isClosed()){
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

        bullet.draw(camera);
//        bullet.translate(glm::vec3(counter,0.0,0.0));

        for(int i=1;i<26;i++){
            glass[i].draw(camera);
        }


        display.update();
        counter -= 0.000001f;
        if(counter < -0.003){
            counter = 0.0f;
            bullet.setPosition(glm::vec3(1.5,0.0,0.0));
        }
    }

    return 0;
}
