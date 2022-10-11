#pragma once
#include <vulkan/vulkan.h>
#include <iostream>
// Standard Library logger include
#include <stdio.h>
// TODO: Just so vscode does not complain about memcpy
#include <string.h>

#include "../defines.h"
#if WINDOWS_PLATFORM
#include <windows.h>
#include <windowsx.h> // param input extraction
#include <stdlib.h>
#include <vulkan/vulkan_win32.h>
#endif
#if LINUX_PLATFORM
#include <xcb/xcb.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h> // sudo apt-get install libx11-dev
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h> // sudo apt-get install libxkbcommon-x11-dev
#include <sys/time.h>
#endif

#define VK_CHECK(result)                                           \
    if (result != VK_SUCCESS)                                      \
    {                                                              \
        std::cout << "Vulkan error code: " << result << std::endl; \
        __debugbreak();                                            \
        return false;                                              \
    }
struct Image
{
    VkImage image;
    VkImageView view;
    VkDeviceMemory memory;
};

struct Buffer
{
    VkBuffer buffer;
    VkDeviceMemory memory;
    void *data;
};

struct VkContext
{
    VkDebugUtilsMessengerEXT debugMsg;
    VkExtent2D screenSize;

    VkInstance instance;
    VkSurfaceKHR surface;
    VkSurfaceFormatKHR surfaceFormat;
    VkPhysicalDevice gpu;
    VkDevice device;
    VkQueue graphicsQueue;
    VkSwapchainKHR swapchain;
    VkRenderPass renderPass;
    VkCommandPool commandPool;

    uint32_t scImgCount;
    VkImage scImages[5];
    int graphicsIdx;
    VkSemaphore aquireSemaphore;
    VkSemaphore submitSemaphore;

    VkCommandBuffer cmd;
    // TODO: Will be inside an array
    Image image;
    Buffer stagingBuffer;
    VkDescriptorPool descPool;
    // TODO: We will abstract this later
    VkSampler sampler;
    VkDescriptorSet descSet;
    VkDescriptorSetLayout setLayout;
    VkPipelineLayout pipeLayout;
    VkPipeline pipeline;

    VkSemaphore aquireSemaphore;
    VkSemaphore submitSemaphore;
    VkFence imgAvailableFence;

    // TODO: Suballocation from Main Memory
    VkImage scImages[5];
    VkImageView scImgViews[5];
    VkFramebuffer framebuffers[5];
};

bool vk_init(VkContext *vkcontext, void *window);
bool vk_render(VkContext *vkcontext);
