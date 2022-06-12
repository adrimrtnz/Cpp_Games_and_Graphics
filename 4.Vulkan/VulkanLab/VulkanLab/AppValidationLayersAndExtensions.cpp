#include "AppValidationLayersAndExtensions.h"

AppValidationLayersAndExtensions::AppValidationLayersAndExtensions(){}
AppValidationLayersAndExtensions::~AppValidationLayersAndExtensions(){}

bool AppValidationLayersAndExtensions::checkValidationLayerSupport()
{
	uint32_t layerCount;

	// Get count of validation layers available
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);						// gets the number of validation layers available

	// Get the available validation layers names
	std::vector<VkLayerProperties>availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());		// populates it with the names of the layers

	for (const char* layerName : requiredValidationLayers){

		bool layerFound = false;

		for (const auto& layerproperties : availableLayers) {

			// If layer is found set the layer found boolean to true
			if (strcmp(layerName, layerproperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) { return false; }

		return true;

	}
}

/*
* This function will get all the extensions that are supported by GLFW
*/
std::vector<const char*> AppValidationLayersAndExtensions::getRequiredExtensions(bool isValidationLayersEnabled)
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;

	// Get extensions
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*>extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	// debug report extension
	if (isValidationLayersEnabled) {
		extensions.push_back("VK_EXT_debug_report");
	}

	return extensions;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugReportFlagsEXT flags, 
	VkDebugReportObjectTypeEXT objExt, 
	uint64_t obj, 
	size_t location, 
	int32_t code, 
	const char* layerPrefix,
	const char* msg,
	void* userData) {
	
	std::cerr << "Validation layer: " << msg << std::endl << std::endl;

	return false;
}

void AppValidationLayersAndExtensions::setupDebugCallback(bool isValidationLayerEnabled, VkInstance vkInstance)
{
	if (!isValidationLayerEnabled) { return; }

	printf("Setup Call Back \n");

	VkDebugReportCallbackCreateInfoEXT info = {};

	info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	info.pfnCallback = debugCallback;

	if (createDebugReportCallbackEXT(vkInstance, &info, nullptr, &callback) != VK_SUCCESS) {
		throw std::runtime_error("Failed to set debug calback!");
	}
}

void AppValidationLayersAndExtensions::destroy(VkInstance instance, bool isValidationLayerEnabled)
{
	if (isValidationLayerEnabled) {
		vkDestroyDebugReportCallbackEXT(instance, callback, nullptr);
	}
}
