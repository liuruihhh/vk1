#include "VulkanLayerAndExtension.h"
#include <vulkan/vulkan_core.h>
#include <iostream>
#include <vector>
#include "VulkanApplication.h"
using namespace std;

VkResult VulkanLayerAndExtension::getInstanceLayerProperties() {
  uint32_t instanceLayerCount;
  std::vector<VkLayerProperties> layerProperties;
  VkResult result;

  do {
    result = vkEnumerateInstanceLayerProperties(&instanceLayerCount, NULL);

    if (result)
      return result;

    if (instanceLayerCount == 0)
      return VK_INCOMPLETE;

    layerProperties.resize(instanceLayerCount);
    result = vkEnumerateInstanceLayerProperties(&instanceLayerCount,
                                                layerProperties.data());
  } while (result == VK_INCOMPLETE);

  std::cout << "\n Instanced Layers" << std::endl;
  std::cout << "===================" << std::endl;

  for (auto gLayerProp : layerProperties) {
    std::cout << "\n"
              << gLayerProp.description << "\n\t|\n\t|---{Layer Name}-->"
              << gLayerProp.layerName << "\n";

    LayerProperties layerProps;
    layerProps.properties = gLayerProp;

    result = getExtensionProperies(layerProps);

    if (result) {
      continue;
    }

    layerPropertyList.push_back(layerProps);

    for (auto ext : layerProps.extensions) {
      std::cout << "\t\t|\n\t\t|---[Layer Extension]-->" << ext.extensionName
                << "\n";
    }
  }

  return result;
}

VkResult VulkanLayerAndExtension::getExtensionProperies(
    LayerProperties& layerProps,
    VkPhysicalDevice* gpu) {
  uint32_t extensionCount;
  VkResult result;
  char* layerName = layerProps.properties.layerName;

  do {
    if (gpu) {
      result = vkEnumerateDeviceExtensionProperties(*gpu, layerName,
                                                    &extensionCount, NULL);
    } else {
      result = vkEnumerateInstanceExtensionProperties(layerName,
                                                      &extensionCount, NULL);
    }

    if (result)
      continue;

    if (extensionCount != 0) {
      layerProps.extensions.resize(extensionCount);

      if (gpu) {
        result = vkEnumerateDeviceExtensionProperties(
            *gpu, layerName, &extensionCount, layerProps.extensions.data());
      } else {
        result = vkEnumerateInstanceExtensionProperties(
            layerName, &extensionCount, layerProps.extensions.data());
      }
    }

  } while (result == VK_INCOMPLETE);

  return result;
}

VkResult VulkanLayerAndExtension::getDeviceExtensionProperties(
    VkPhysicalDevice* gpu) {
  VkResult result;
  std::cout << "\n Device Extensions" << std::endl;
  std::cout << "===================" << std::endl;

  VulkanApplication* appObj = VulkanApplication::GetInstance();
  std::vector<LayerProperties>* instanceLayerProp =
      &appObj->instanceObj->layerExtension.layerPropertyList;

  for (auto globalLayerProp : *instanceLayerProp) {
    LayerProperties layerProps;
    layerProps.properties = globalLayerProp.properties;

    result = getExtensionProperies(layerProps, gpu);

    if (result) {
      continue;
    }

    layerPropertyList.push_back(layerProps);

    for (auto ext : layerProps.extensions) {
      std::cout << "\t\t|\n\t\t|---[Layer Extension]-->" << ext.extensionName
                << "\n";
    }
  }
  return result;
}
