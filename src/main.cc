#include <iostream>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

GLFWwindow* setupWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(900, 450, "Vulkan", nullptr, nullptr);
    if (window == nullptr) throw std::runtime_error("Failed to create window.");
    glfwMakeContextCurrent(window);
    return window;
}

vk::Instance setupInstance() {
    vk::ApplicationInfo applicationInfo{
        "spicy-pierogi", VK_MAKE_VERSION(1, 0, 0), "No Engine",
        VK_MAKE_VERSION(1, 0, 0), VK_API_VERSION_1_3};
    vk::InstanceCreateInfo instanceCreateInfo{};
    instanceCreateInfo.setPApplicationInfo(&applicationInfo);
    uint32_t glfwExtensionsCount;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionsCount);
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    instanceCreateInfo.setPEnabledExtensionNames(extensions);
    std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
    instanceCreateInfo.setPEnabledLayerNames(validationLayers);
    return vk::createInstance(instanceCreateInfo);
}

int main(int argc, char** argv) {
    GLFWwindow* window = setupWindow();
    vk::Instance instance = setupInstance();
#pragma region VKDEVICE
    uint32_t physicalDeviceCount = 0;
    vk::Result result = instance.enumeratePhysicalDevices(&physicalDeviceCount, nullptr);
    std::vector<vk::PhysicalDevice> physicalDevices(physicalDeviceCount);
    result = instance.enumeratePhysicalDevices(&physicalDeviceCount, physicalDevices.data());
    vk::PhysicalDevice selectedPhysicalDevice;
    for (const vk::PhysicalDevice& physicalDevice : physicalDevices) {
        const vk::PhysicalDeviceProperties properties = physicalDevice.getProperties();
        if (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu) {
            selectedPhysicalDevice = physicalDevice;
            break;
        }
        else if (properties.deviceType == vk::PhysicalDeviceType::eIntegratedGpu) {
            selectedPhysicalDevice = physicalDevice;
            continue;
        }
    }
    vk::DeviceCreateInfo deviceCreateInfo{};
#pragma endregion VKDEVICE

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    instance.destroy();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}