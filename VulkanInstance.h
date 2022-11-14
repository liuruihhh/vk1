#pragma once
#include <vulkan/vulkan_core.h>
#include <iostream>
#include <vector>
#include "VulkanLayerAndExtension.h"
using namespace std;

class VulkanInstance {
 public:
  VkInstance instance;

 public:
  VulkanLayerAndExtension layerExtension;

  VkResult createInstance(vector<const char*>& layers,
                          vector<const char*>& extension,
                          const char* applicationName);

  void destoryInstance();
};