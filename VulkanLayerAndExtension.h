#pragma once
#include <vulkan/vulkan_core.h>
#include <iostream>
#include <vector>
using namespace std;

struct LayerProperties {
  VkLayerProperties properties;
  vector<VkExtensionProperties> extensions;
};

class VulkanLayerAndExtension {
  std::vector<LayerProperties> layerPropertyList;

  std::vector<const char*> appRequestedLayerNames;

  std::vector<const char*> appRequestedExtenstionNames;

 public:
  VkResult getInstanceLayerProperties();

  VkResult getExtensionProperies(LayerProperties& layerProps,
                                 VkPhysicalDevice* gpu = NULL);
  VkResult getDeviceExtensionProperties(VkPhysicalDevice* gpu);
  VkBool32 areLayersSupported(vector<const char*>& layerNames);
};
