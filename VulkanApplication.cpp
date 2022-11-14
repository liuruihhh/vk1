#pragma once
#include "VulkanApplication.h"
#include <vulkan/vulkan_core.h>
#include <cassert>
#include <iostream>
#include <vector>
#include "VulkanDevice.h"
#include "VulkanInstance.h"
#include "VulkanLayerAndExtension.h"
using namespace std;

// std::vector<const char*> instanceExtensionNames = {
//    VK_KHR_SURFACE_EXTENSION_NAME, "VK_KHR_WIN32_SURFACE_EXTENSION_NAME"};

std::vector<const char*> instanceExtensionNames = {
    VK_EXT_DEBUG_REPORT_EXTENSION_NAME};

std::vector<const char*> deviceExtensionNames = {};

std::vector<const char*> layerNames = {
    ""
    "VK_LAYER_LUNARG_api_dump"};

VulkanApplication::VulkanApplication() {
  instanceObj = new VulkanInstance();
  instanceObj->layerExtension.getInstanceLayerProperties();
}

VulkanApplication::~VulkanApplication() {}

VkResult VulkanApplication::createVulkanInstance(
    vector<const char*>& layers,
    vector<const char*>& extensions,
    const char* appName) {
  instanceObj->createInstance(layers, extensions, appName);
  return VK_SUCCESS;
}

VulkanApplication* appObj;

VulkanApplication* VulkanApplication::GetInstance() {
  if (appObj == NULL) {
    VulkanApplication app = VulkanApplication();
    appObj = &app;
  }
  return appObj;
}

VkResult VulkanApplication::enumeratePhysicalDevices(
    std::vector<VkPhysicalDevice>& gpuList) {
  uint32_t gpuDeviceCount;

  VkResult result =
      vkEnumeratePhysicalDevices(instanceObj->instance, &gpuDeviceCount, NULL);

  assert(result == VK_SUCCESS);

  gpuList.resize(gpuDeviceCount);

  assert(gpuDeviceCount);

  return vkEnumeratePhysicalDevices(instanceObj->instance, &gpuDeviceCount,
                                    gpuList.data());
}

void VulkanApplication::initialize() {
  char title[] = "Hello World!!!";

  createVulkanInstance(layerNames, instanceExtensionNames, title);

  vector<VkPhysicalDevice> gpuList;

  enumeratePhysicalDevices(gpuList);

  if (gpuList.size() > 0) {
    appObj->handShakeWithDevice(&gpuList[0], layerNames, deviceExtensionNames);
  }
}

VkResult VulkanApplication::handShakeWithDevice(
    VkPhysicalDevice* gpu,
    std::vector<const char*>& layers,
    std::vector<const char*>& extensions) {
  VulkanDevice* deviceObj = new VulkanDevice(gpu);

  if (!deviceObj) {
    return VK_ERROR_OUT_OF_HOST_MEMORY;
  }

  deviceObj->layerExtension.getDeviceExtensionProperties(gpu);

  vkGetPhysicalDeviceProperties(*gpu, &deviceObj->gpuProps);

  vkGetPhysicalDeviceMemoryProperties(*gpu, &deviceObj->memoryProperties);

  deviceObj->getPhysicalDeviceQueuesAndProperties();

  deviceObj->getGraphicsQueueHandle();

  deviceObj->createDevice(layers, extensions);

  return VK_SUCCESS;
}
