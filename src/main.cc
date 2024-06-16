#include <iostream>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

int main(int argc, char** argv) {
#pragma region WINDOW
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(900, 450, "Vulkan", nullptr, nullptr);
    if (window == nullptr) throw std::runtime_error("Failed to create window.");
    glfwMakeContextCurrent(window);
#pragma endregion WINDOW
#pragma region VKINIT
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
    vk::Instance instance = vk::createInstance(instanceCreateInfo);
#pragma endregion VKINIT
    uint32_t physicalDeviceCount = 0;
    instance.enumeratePhysicalDevices(&physicalDeviceCount, nullptr);
    std::vector<vk::PhysicalDevice> physicalDevices(physicalDeviceCount);
    instance.enumeratePhysicalDevices(&physicalDeviceCount, physicalDevices.data());
    for (const vk::PhysicalDevice& physicalDevice : physicalDevices) {
        const vk::PhysicalDeviceFeatures features = physicalDevice.getFeatures();
    }
    vk::DeviceCreateInfo deviceCreateInfo{};


    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    std::cout << "hello world" << std::endl;
    instance.destroy();
    glfwTerminate();
    return 0;
}