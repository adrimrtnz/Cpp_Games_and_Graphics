#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class AppValidationLayersAndExtensions
{
public:
	AppValidationLayersAndExtensions();
	~AppValidationLayersAndExtensions();

	const std::vector<const char*> requiredValidationLayers = { "VK_LAYER_LUNARG_standard_validation" };
	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions(bool isValidationLayersEnabled);

	// Debug Callback
	VkDebugReportCallbackEXT callback;

	void setupDebugCallback(bool isValidationLayerEnabled, VkInstance vkInstance);
	void destroy(VkInstance instance, bool isValidationLayerEnabled);

	// Callback
	VkResult createDebugReportCallbackEXT(
		VkInstance instance,
		const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugReportCallbackEXT* pCallback) {
	
		auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");

		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pCallback);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}
};

