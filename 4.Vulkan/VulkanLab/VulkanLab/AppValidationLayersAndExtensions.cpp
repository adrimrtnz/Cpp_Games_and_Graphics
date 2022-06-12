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

std::vector<const char*> AppValidationLayersAndExtensions::getRequiredExtensions(bool isValdationLayersEnabled)
{
	return std::vector<const char*>();
}

void AppValidationLayersAndExtensions::setupDebugCallback(bool isValidationLayerEnabled, VkInstance vkInstance)
{
}

void AppValidationLayersAndExtensions::destroy(VkInstance instance, bool isValidationLayerEnabled)
{
}
