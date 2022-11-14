#include "VulkanDevice.h"
#include <vulkan/vulkan_core.h>
#include <cassert>
#include <iostream>
#include <vector>
#include "VulkanLayerAndExtension.h"

VulkanDevice::VulkanDevice(VkPhysicalDevice* gpu) {}

VulkanDevice::~VulkanDevice() {}

VkResult VulkanDevice::createDevice(vector<const char*>& layers,
                                    vector<const char*>& extensions) {
  VkResult result;
  float queuePriorities[1] = {0.0};

  VkDeviceQueueCreateInfo queueInfo = {};
  queueInfo.queueFamilyIndex = graphicsQueueFamilyIndex;
  queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queueInfo.pNext = NULL;
  queueInfo.queueCount = 1;
  queueInfo.pQueuePriorities = queuePriorities;

  VkDeviceCreateInfo deviceInfo = {};
  deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  deviceInfo.pNext = NULL;
  deviceInfo.queueCreateInfoCount = 1;
  deviceInfo.pQueueCreateInfos = &queueInfo;
  deviceInfo.enabledLayerCount = 0;
  deviceInfo.ppEnabledLayerNames = NULL;
  deviceInfo.enabledExtensionCount = extensions.size();
  deviceInfo.ppEnabledExtensionNames = extensions.data();
  deviceInfo.pEnabledFeatures = NULL;

  result = vkCreateDevice(*gpu, &deviceInfo, NULL, &device);

  assert(result == VK_SUCCESS);

  return result;
}

void VulkanDevice::getPhysicalDeviceQueuesAndProperties() {
  vkGetPhysicalDeviceQueueFamilyProperties(*gpu, &queueFamilyCount, NULL);
  queueFamilyProps.resize(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(*gpu, &queueFamilyCount,
                                           queueFamilyProps.data());
}

uint32_t VulkanDevice::getGraphicsQueueHandle() {
  bool found = false;

  for (unsigned int i = 0; i < queueFamilyCount; i++) {
    if (queueFamilyProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      found = true;
      graphicsQueueFamilyIndex = i;
      break;
    }
  }
  return 0;
}

void VulkanDevice::getDeviceQueue() {
  vkGetDeviceQueue(device, graphicsQueueFamilyIndex, 0, &queue);
}