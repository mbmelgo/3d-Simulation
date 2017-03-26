#include <iostream>
#include <GL/glew.h>

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

#define WIDTH 800
#define HEIGHT 600

int main(){
    Display display(WIDTH,HEIGHT,"Simulation");

    Vertex vertices[] = { Vertex(glm::vec3(-0.5,-0.5,0),glm::vec2(0.0,0.0)),
                          Vertex(glm::vec3(0,0.5,0),glm::vec2(0.5,1.0)),
                          Vertex(glm::vec3(0.5,-0.5,0),glm::vec2(1.0,0.0))
                        };
    unsigned int indices[] = {0, 1, 2};

    //Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
    Mesh mesh("C:/Users/Marko/Desktop/Simulation/res/bullet.obj");
    Shader shader("C:/Users/Marko/Desktop/Simulation/res/basicShader");
    Texture texture("C:/Users/Marko/Desktop/Simulation/res/bricks.jpg");
    Transform transform;
    Camera camera(glm::vec3(0,0,-5), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
    float counter = 0.0f;

    while(!display.isClosed()){
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

//        float cosCounter = cosf(counter);
//
//        transform.getPos().x = sinf(counter);
//        transform.getPos().z = cosCounter;
//        transform.getRot().x = counter * 2;
//        transform.getRot().y = counter * 2;
        transform.getRot().y = counter * 2;
//        transform.setScale(glm::vec3(cosCounter, cosCounter, cosCounter));

        shader.Bind();
        texture.Bind(0);
        shader.Update(transform, camera);
        mesh.Draw();

        display.update();
        counter += 0.0001f;
    }

    return 0;
}
