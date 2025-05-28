#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ifcg/shader/vao.hpp"
#include "ifcg/shader/vbo.hpp"
#include "ifcg/shader/ebo.hpp"
#include "ifcg/shader/shader.hpp"

namespace ifcg
{
    class Mesh
    {
    public:
        virtual ~Mesh() = default;

        virtual void draw() = 0;
    };
}