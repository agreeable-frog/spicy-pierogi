#include <iostream>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

int main(int argc, char** argv) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(900, 450, "Vulkan", nullptr, nullptr);
    if (window == nullptr) throw std::runtime_error("Failed to create window.");
    glfwMakeContextCurrent(window);
    vk::ApplicationInfo applicationInfo{
        "spicy-pierogi", VK_MAKE_VERSION(1, 0, 0), "No Engine",
        VK_MAKE_VERSION(1, 0, 0), VK_API_VERSION_1_3};
    vk::InstanceCreateInfo instanceCreateInfo{};
    instanceCreateInfo.setPApplicationInfo(&applicationInfo);
    uint32_t glfwExtensionsCount;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionsCount);
    std::cout << "glfw extensions : ";
    for (auto extension : extensions) {
        std::cout << extension << ", ";
    }
    std::cout << '\n';
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    extensions.push_back(VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME);
    instanceCreateInfo.setPEnabledExtensionNames(extensions);
    std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
    instanceCreateInfo.setPEnabledLayerNames(validationLayers);
    vk::Instance instance = vk::createInstance(instanceCreateInfo);

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    std::cout << "hello world" << std::endl;
    instance.destroy();
    glfwTerminate();
    return 0;
}