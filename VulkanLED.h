#pragma once
#include <vulkan/vulkan_core.h>
#include <iostream>
#include <vector>
#include "VulkanApplication.h"
#include "VulkanLED.h"
#include "VulkanLayerAndExtension.h"

PFN_vkCreateDebugReportCallbackEXT dbgCreateDebugReportCallback;
PFN_vkDestroyDebugReportCallbackEXT dbgDestroyDebugReportCallback;