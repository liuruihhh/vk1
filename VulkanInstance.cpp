#include "VulkanInstance.h"
#include <vulkan/vulkan_core.h>
#include <iostream>
#include <vector>
#include "VulkanLayerAndExtension.h"
using namespace std;

VkResult VulkanInstance::createInstance(vector<const char*>& layers,
                                        vector<const char*>& extensionNames,
                                        char const* const appName) {
  VkApplicationInfo appInfo = {};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pNext = NULL;
  appInfo.pApplicationName = appName;
  appInfo.applicationVersion = 1;
  appInfo.pEngineName = appName;
  appInfo.engineVersion = 1;
  appInfo.apiVersion = VK_API_VERSION_1_2;

  VkInstanceCreateInfo instInfo = {};
  instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instInfo.pNext = NULL;
  instInfo.flags = 0;
  instInfo.pApplicationInfo = &appInfo;

  instInfo.enabledLayerCount = layers.size();
  instInfo.ppEnabledLayerNames = layers.data();

  instInfo.enabledExtensionCount = extensionNames.size();
  instInfo.ppEnabledExtensionNames = extensionNames.data();

  VkResult result = vkCreateInstance(&instInfo, NULL, &instance);

  return result;
}

void VulkanInstance::destoryInstance() {
  vkDestroyInstance(instance, NULL);
}