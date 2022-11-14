#pragma once
#include <vulkan/vulkan_core.h>
#include <iostream>
#include <vector>
#include "VulkanInstance.h"
#include "VulkanLayerAndExtension.h"

using namespace std;

class VulkanApplication {
 private:
  VulkanApplication();

 public:
  ~VulkanApplication();

 public:
  VkResult createVulkanInstance(vector<const char*>& layers,
                                vector<const char*>& extensions,
                                const char* application);
  VulkanInstance* instanceObj;

  static VulkanApplication* GetInstance();

  VkResult enumeratePhysicalDevices(std::vector<VkPhysicalDevice>& gpuList);

  void initialize();

  VkResult handShakeWithDevice(VkPhysicalDevice* gpu,
                               std::vector<const char*>& layers,
                               std::vector<const char*>& extensions);
};
