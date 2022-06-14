#include "VulkanInstance.h"

VulkanInstance::VulkanInstance() {}
VulkanInstance::~VulkanInstance() {}

void createAppAndVkInstance(bool enableValidationLayers, AppValidationLayersAndExtensions *valLayerAndExtendions)
{
	// Links the APP to the Vulkan Library
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Vulkan!!!";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "AM Vulkan Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo vkInstanceInfo = {};
	vkInstanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	vkInstanceInfo.pApplicationInfo = &appInfo;

	// specify extensions and validation layers
	auto extensions = valLayerAndExtendions->getRequiredExtensions(enableValidationLayers);
	vkInstanceInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	vkInstanceInfo.ppEnabledExtensionNames = extensions.data();

	if (enableValidationLayers) {
		vkInstanceInfo.enabledLayerCount = static_cast<uint32_t>(valLayerAndExtendions->requiredValidationLayers.size());
		vkInstanceInfo.ppEnabledExtensionNames = valLayerAndExtendions->requiredValidationLayers.data();
	}
	else {
		vkInstanceInfo.enabledLayerCount = 0;
	}

	if (vkCreateInstance(&vkInstanceInfo, nullptr, &vkInstance)) {
		throw std::runtime_error("Failed to create vkInstance. ");
	}
}