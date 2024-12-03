#pragma once
#include<glad/glad.h>
#include<glfw/glfw3.h>

#include<ShaderH.h>
#include<iostream>
#include<cmath>

void InitCubeVerts(float x,float y,float length);
void RenderCube(Shader shader, float color1[4], float color2[4], float mul, glm::vec2 resolution);
void DeleteCubeData();