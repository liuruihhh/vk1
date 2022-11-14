#include "VulkanLED.h"
#include <vulkan/vulkan_core.h>
#include <iostream>
#include <vector>
#include "VulkanApplication.h"
#include "VulkanLayerAndExtension.h"
using namespace std;

VkBool32 VulkanLayerAndExtension::areLayersSupported(
    vector<const char*>& layerNames) {
  uint32_t checkCount = layerNames.size();
  uint32_t layerCount = layerPropertyList.size();
  std::vector<const char*> unsupportLayerNames;
  for (uint32_t i = 0; i < checkCount; i++) {
    VkBool32 isSupported = 0;
    for (uint32_t j = 0; j < layerCount; j++) {
      if (!strcmp(layerNames[i], layerPropertyList[j].properties.layerName)) {
        isSupported = 1;
      }
    }
    if (!isSupported) {
      std::cout << "No Layer support fount, removed from layer£º"
                << layerNames[i] << endl;
      unsupportLayerNames.push_back(layerNames[i]);
    } else {
      cout << "Layer supported: " << layerNames[i] << endl;
    }
  }
  for (auto i : unsupportLayerNames) {
    auto it = std::find(layerNames.begin(), layerNames.end(), i);
    if (it != layerNames.end())
      layerNames.erase(it);
  }
  return true;
}

VkResult VulkanLayerAndExtension::createDebugReportCallback() {}
