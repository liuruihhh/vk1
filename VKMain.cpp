#include "VKMain.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <iostream>
#include <vector>
#include "VulkanApplication.h"
using namespace std;

int main() {
  VkResult result;
  VulkanApplication* appObj = VulkanApplication::GetInstance();
  appObj->initialize();
}