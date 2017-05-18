#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// INTERFACE FOR MOVING THE OBJECTS IN 3D: SCALRE, ROTATE, TRANSFORM
class Transform
{
    public:
        Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
        :   m_pos(pos),
            m_rot(rot),
            m_scale(scale){};

        // CONVERT THE ROTATION AND SCALE INTO A 4X4 MATRIX: THE MODEL MATRIX
        inline glm::mat4 getModel() const {
            glm::mat4 posMatrix = glm::translate(m_pos); // GENERATE A 4X4 MATRIX FOR THE TRANSLATION
            glm::mat4 rotXMatrix = glm::rotate(m_rot.x, glm::vec3(1,0,0)); // GENERATE A 4X4 MATRIX FOR THE X ROTATION
            glm::mat4 rotYMatrix = glm::rotate(m_rot.y, glm::vec3(0,1,0)); // GENERATE A 4X4 MATRIX FOR THE Y ROTATION
            glm::mat4 rotZMatrix = glm::rotate(m_rot.z, glm::vec3(0,0,1)); // GENERATE A 4X4 MATRIX FOR THE Z ROTATION
            glm::mat4 scaleMatrix = glm::scale(m_scale); // GENERATE A 4X4 MATRIX FOR THE SCALING

            glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix; // COMBINE THE ROTATION MATRICES

            return posMatrix * rotMatrix * scaleMatrix; // RETURN THE MODEL MATRIX BY COMBINING THE SCALE MATRIX, ROTATION MATRIX AND POSITION MATRIX
        }

        inline glm::vec3& getPos(){return m_pos;};
        inline glm::vec3& getRot(){return m_rot;};
        inline glm::vec3& getScale(){return m_scale;};

        inline void setPos(const glm::vec3& pos){ m_pos = pos;};
        inline void setRot(const glm::vec3& rot){ m_rot = rot;};
        inline void setScale(const glm::vec3& scale){ m_scale = scale;};
    protected:

    private:
        glm::vec3 m_pos;
        glm::vec3 m_rot;
        glm::vec3 m_scale;
};

#endif // TRANSFORM_H
