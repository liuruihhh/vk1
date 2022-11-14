#pragma once
#include <vulkan/vulkan_core.h>
#include <iostream>
#include <vector>
#include "VulkanLayerAndExtension.h"
class VulkanDevice {
 public:
  VulkanDevice(VkPhysicalDevice* gpu);
  ~VulkanDevice();

  VkDevice device;
  VkPhysicalDevice* gpu;
  VkPhysicalDeviceProperties gpuProps;
  VkPhysicalDeviceMemoryProperties memoryProperties;

  VkQueue queue;
  vector<VkQueueFamilyProperties> queueFamilyProps;

  uint32_t graphicsQueueFamilyIndex;
  uint32_t queueFamilyCount;

  VulkanLayerAndExtension layerExtension;

  VkResult createDevice(vector<const char*>& layers,
                        vector<const char*>& exxtensions);
  void getPhysicalDeviceQueuesAndProperties();

  uint32_t getGraphicsQueueHandle();
  void getDeviceQueue();
};
