//#pragma once
//// vulkan
//#define GLFW_INCLUDE_VULKAN
//#include <vulkan\vulkan.h>
//#include <GLFW/glfw3.h>
//
//#include <stb_image.h>
//
//#include "Message.h"
//#include "File.h"
//#include <stdexcept>
//#include <algorithm>
//#include <iostream>
//#include <cstring>
//#include <vector>
//#include <set>
//#include <map>
//
//
////////////////////////////////////////////////////////////////////////////////////
////IMAGE / DEPTH BUFFER BEGIN
////////////////////////////////////////////////////////////////////////////////////
//#define GLM_FORCE_RADIANS
//#define GLM_FORCE_DEPTH_ZERO_TO_ONE
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <unordered_map>
////////////////////////////////////////////////////////////////////////////////////
////IMAGE / DEPTH BUFFER object END
////////////////////////////////////////////////////////////////////////////////////
//const std::string MODEL_PATH = "Models/chalet.obj";
//const std::string TEXTURE_PATH = "Textures/chalet.jpg";
//#include <tiny_obj_loader.h>
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/hash.hpp>
////////////////////////////////////////////////////////////////////////////////////
////VERTEX SHADER BEGIN
////////////////////////////////////////////////////////////////////////////////////
//#include <glm\glm.hpp>
//#include <array>
//
//struct Vertex {
//    glm::vec3 pos;
//    glm::vec3 color;
//    glm::vec2 texCoord;
//
//    static VkVertexInputBindingDescription getBindingDescription () {
//        VkVertexInputBindingDescription bindingDescription = {};
//        bindingDescription.binding = 0;
//        bindingDescription.stride = sizeof (Vertex);
//        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
//
//        return bindingDescription;
//    }
//    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions () {
//        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};
//
//        attributeDescriptions[0].binding = 0;
//        attributeDescriptions[0].location = 0;
//        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
//        attributeDescriptions[0].offset = offsetof (Vertex, pos);
//
//        attributeDescriptions[1].binding = 0;
//        attributeDescriptions[1].location = 1;
//        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
//        attributeDescriptions[1].offset = offsetof (Vertex, color);
//
//        attributeDescriptions[2].binding = 0;
//        attributeDescriptions[2].location = 2;
//        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
//        attributeDescriptions[2].offset = offsetof (Vertex, texCoord);
//
//        return attributeDescriptions;
//    }
//    bool operator==(const Vertex& other) const {
//        return pos == other.pos && color == other.color && texCoord == other.texCoord;
//    }
//};
//namespace std {
//    template<> struct hash<Vertex> {
//        size_t operator()(Vertex const& vertex) const {
//            return ((hash<glm::vec3> ()(vertex.pos) ^ (hash<glm::vec3> ()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2> ()(vertex.texCoord) << 1);
//        }
//    };
//}
////const std::vector<Vertex> vertices = {
////    //x      y        z      Red   Green Blue
////    {{0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
////    {{ 1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
////    {{ 1.0f,  0.8f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
////    {{0.0f,  0.8f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
////
////    {{-1.0f, -0.8f, -0.2f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
////    {{0.0f, -0.8f, -0.2f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
////    {{0.0f,  0.0f,-0.2f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
////    {{-1.0f,  0.0f, -0.2f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
////};
////const std::vector<uint16_t> indices = {
////    0, 1, 2, 2, 3, 0,
////    4, 5, 6, 6, 7, 4
////};
////////////////////////////////////////////////////////////////////////////////////
////VERTEX SHADER  END
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////DESCRIPTOR BEGIN
////////////////////////////////////////////////////////////////////////////////////
//#define GLM_FORCE_RADIANS
//#include <glm/gtc/matrix_transform.hpp>
//#include <chrono>
//
//struct UniformBufferObject {
//    glm::mat4 model;
//    glm::mat4 view;
//    glm::mat4 proj;
//};
////////////////////////////////////////////////////////////////////////////////////
////DESCRIPTOR  END
////////////////////////////////////////////////////////////////////////////////////
//
//
//struct QueueFamilyIndices {
//    int graphicsFamily = -1;
//     int presentFamily = -1;
//
//    bool isComplete () {
//        return graphicsFamily >= 0 && presentFamily >= 0;
//    }
//};
//
//struct SwapChainSupportDetails {
//    VkSurfaceCapabilitiesKHR capabilities;
//    std::vector<VkSurfaceFormatKHR> formats;
//    std::vector<VkPresentModeKHR> presentModes;
//};
//
//class render {
//public: // functions
//    render ();
//    ~render ();
//    void init (GLFWwindow* window);
//    void deinit ();
//    //GETTERS
//    void get_recreateSwapChain () { reCreateSwapChain (); };
//    void get_drawFrame () { drawFrame (); };
//    void get_updateUniformBuffer () { updateUniformBuffer (); };
//private: // functions
//    void createInstance ();
//    std::vector<const char*> GetRequiredExtensions (); // fele kell fele debugg
//    void createSurface ();
//    void getPhysicalDevice (); //get GPU
//    int ratePhisicalDevice (VkPhysicalDevice device); // check device supports and rate
//    bool checkDeviceExtensionSupport (VkPhysicalDevice device); // rate device - extension support
//    QueueFamilyIndices findQueueFamilies (VkPhysicalDevice device); // rate device - queue support
//    void createLogicalDevice ();
//    void createSwapChain ();
//    void reCreateSwapChain ();
//    void cleanSwapChain ();
//    SwapChainSupportDetails querySwapChainSupport (VkPhysicalDevice device);
//    VkSurfaceFormatKHR chooseSwapSurfaceFormat (const std::vector<VkSurfaceFormatKHR>& availableFormats);
//    VkPresentModeKHR chooseSwapPresentMode (const std::vector<VkPresentModeKHR> availablePresentModes);
//    VkExtent2D chooseSwapExtent (const VkSurfaceCapabilitiesKHR& capabilities);
//    void createImageViews ();
//    VkImageView createImageView (VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
//    void createRenderPass (); //kell a pipeline hoz
//    void createDescriptorSetLayout ();
//    void createGraphicsPipeline ();
//    VkShaderModule createShaderModule (const std::vector<char>& code); //shader modul TODO kivenni a render classból talán ????????
//    void createFramebuffers ();
//    void createCommandPool ();
//    void  createDepthResources ();
//    VkFormat findSupportedFormat (const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
//    VkFormat findDepthFormat ();
//    bool hasStencilComponent (VkFormat format);
//    void createTextureImage (); //TODO áttenni másik fileba ! image setup
//    void createTextureImageView ();
//    void createTextureSampler ();
//    void transitionImageLayout (VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
//    VkCommandBuffer beginSingleTimeCommands ();
//    void endSingleTimeCommands (VkCommandBuffer commandBuffer);
//    void createImage (uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage & image, VkDeviceMemory & imageMemory);
//    void createVertexBuffer (); //TODO kivenni külön class ba
//    void createIndexBuffer ();
//    void createUniformBuffer ();
//    void updateUniformBuffer (); // main loop ba kell !!!!!!!!!!!!!!!!!!!!!!!!!!!!! TODO
//    void createDescriptorPool ();
//    void createDescriptorSet ();
//    uint32_t findMemoryType (uint32_t typeFilter, VkMemoryPropertyFlags properties); //vertex buffer  modul
//    void createBuffer (VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
//    void copyBuffer (VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
//    void copyBufferToImage (VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
//    void createCommandBuffers ();
//    void drawFrame ();
//    void createSemaphores ();
//
//    void loadModel ();
//
//private: // Handle
//    GLFWwindow* glfw_window;
//    //Snstance//
//    VkInstance instance;
//    //Surface//
//    VkSurfaceKHR surface;
//    //Select physical device//
//    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE; //GPU
//    //Create logical device//
//    VkDevice device;
//    VkQueue graphicsQueue;
//    VkQueue presentQueue;
//    //VkQueue presentQueue; //?? valamit kell vele csinálni
//    //Swap chain//
//    VkSwapchainKHR swapChain;
//    std::vector<VkImage> swapChainImages;
//    VkFormat swapChainImageFormat;
//    VkExtent2D swapChainExtent;
//    std::vector<VkImageView> swapChainImageViews;
//    //Descriptor//
//    VkDescriptorSetLayout descriptorSetLayout;
//    VkDescriptorPool descriptorPool;
//    VkDescriptorSet descriptorSet;
//    //Image//
//    VkImage textureImage;                   // IMAGE
//    VkDeviceMemory textureImageMemory;      // IMAGE
//    VkImageView textureImageView;           // IMAGE
//    VkSampler textureSampler;               // IMAGE
//    VkImage depthImage;                     // DEPTH
//    VkDeviceMemory depthImageMemory;        // DEPTH
//    VkImageView depthImageView;             // DEPTH
//    std::vector<Vertex> vertices;           // OBJECT
//    std::vector<uint32_t> indices;          // OBJECT
//    //Pipeline//
//    VkRenderPass renderPass;
//    VkPipelineLayout pipelineLayout;
//    VkPipeline graphicsPipeline;
//    //Frame buffer//
//    std::vector<VkFramebuffer> swapChainFramebuffers;
//    //Command pool//
//    VkCommandPool commandPool;
//    //Vertex Buffer//
//    VkBuffer vertexBuffer;
//    VkDeviceMemory vertexBufferMemory;
//    VkBuffer indexBuffer;
//    VkDeviceMemory indexBufferMemory;
//    VkBuffer uniformBuffer;                 //UNIFORM BUFFER
//    VkDeviceMemory uniformBufferMemory;     //UNIFORM BUFFER
//    //Command buffer//
//    std::vector<VkCommandBuffer> commandBuffers;
//    //Draw frames//
//    VkSemaphore availableSemaphore;
//    VkSemaphore renderFinishSemaphore;
//
//
//    /////////////////////////////////////////////////////////////////////////////////////
//    // DEBUG KELLÉKEK TODO
//    VkDebugLogCallbackEXT callback;
//
//#ifdef DEBUG
//    const bool enableValidationLayers = true;
//#else
//    const bool enableValidationLayers = false;
//#endif
//
//    const std::vector<const char*> validationLayers = {"VK_LAYER_LUNARG_standard_validation"};
//    const std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
//
//    // Functions
//    bool checkValidationLayerSupport (); //TODO ez nem debugg csak?
//    void setupDebugCallback ();
//    // Hiba esetén a hibás layer nevének kiírása
//    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback (VkDebugLogFlagsEXT flags,
//                                                         VkDebugLogObjectTypeEXT objType,
//                                                         uint64_t obj,
//                                                         size_t location, int32_t code,
//                                                         const char* layerPrefix,
//                                                         const char* msg,
//                                                         void* userData);
//    VkResult CreateDebugLogCallbackEXT (VkInstance instance,
//                                           const VkDebugLogCallbackCreateInfoEXT* pCreateInfo,
//                                           const VkAllocationCallbacks* pAllocator,
//                                           VkDebugLogCallbackEXT* pCallback);
//    void DestroyDebugLogCallbackEXT (VkInstance instance,
//                                        VkDebugLogCallbackEXT callback,
//                                        const VkAllocationCallbacks* pAllocator);
//
//};
