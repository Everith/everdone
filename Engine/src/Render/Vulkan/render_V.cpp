//#define STB_IMAGE_IMPLEMENTATION
//#define TINYOBJLOADER_IMPLEMENTATION
//
//#include "Render_v.h"
//
//render::render () {
//}
//
//render::~render () {
//}
//
//void render::init (GLFWwindow* window) {
//    glfw_window = window;
//    createInstance ();
//#ifdef DEBUG
//    setupDebugCallback ();
//#endif
//    createSurface ();
//    getPhysicalDevice ();
//    createLogicalDevice ();
//    createSwapChain ();
//    createImageViews ();
//    createRenderPass ();
//    createDescriptorSetLayout ();
//    createGraphicsPipeline ();
//    createCommandPool ();
//    createDepthResources ();
//    createFramebuffers ();
//    createTextureImage ();
//    createTextureImageView ();
//    createTextureSampler ();
//    loadModel ();
//    createVertexBuffer ();
//    createIndexBuffer ();
//    createUniformBuffer ();
//    createDescriptorPool ();
//    createDescriptorSet ();
//    createCommandBuffers ();
//    createSemaphores ();
//
//    //pickPhysicalDevice ();
//}
//
//void render::deinit () {
//    vkDeviceWaitIdle (device);
//    vkDestroySemaphore (device, renderFinishSemaphore, nullptr);
//    vkDestroySemaphore (device, availableSemaphore, nullptr);
//    //for (size_t i = 0; i < swapChainFramebuffers.size (); i++) {
//    //    vkDestroyFramebuffer (device, swapChainFramebuffers[i], nullptr);
//    //}
//    //vkDestroyPipelineLayout (device, pipelineLayout, nullptr);
//    //vkDestroyPipeline (device, graphicsPipeline, nullptr);
//    //vkDestroyRenderPass (device, renderPass, nullptr);
//    //for (size_t i = 0; i < swapChainImageViews.size (); i++) {
//    //    vkDestroyImageView (device, swapChainImageViews[i], nullptr);
//    //}
//    cleanSwapChain ();
//    vkDestroyDescriptorPool (device, descriptorPool, nullptr);
//    vkDestroyDescriptorSetLayout (device, descriptorSetLayout, nullptr);
//    vkDestroyBuffer (device, uniformBuffer, nullptr);
//    vkFreeMemory (device, uniformBufferMemory, nullptr);
//    vkDestroyBuffer (device, indexBuffer, nullptr);
//    vkFreeMemory (device, indexBufferMemory, nullptr);
//    vkDestroyBuffer (device, vertexBuffer, nullptr); // vertex buffer
//    vkFreeMemory (device, vertexBufferMemory, nullptr); // buffer memory
//    vkDestroySampler (device, textureSampler, nullptr); // texture image sampler
//    vkDestroyImageView (device, textureImageView, nullptr); //texture image view
//    vkDestroyImage (device, textureImage, nullptr);  //image
//    vkFreeMemory (device, textureImageMemory, nullptr);  //image memory
//    vkDestroyCommandPool (device, commandPool, nullptr);
//    vkDestroyDevice (device, nullptr);
//    vkDestroySurfaceKHR (instance, surface, nullptr);
//#ifdef DEBUG
//    DestroyDebugLogCallbackEXT (instance, callback, nullptr);
//#endif
//    vkDestroyInstance (instance, nullptr);
//}
//
//
//void render::createInstance () {
//    if (enableValidationLayers && !checkValidationLayerSupport ()) {
//        throw std::runtime_error ("validation layers requested, but not available!");
//    }
//
//    VkApplicationInfo appInfo = {};
//    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
//    appInfo.pApplicationName = "Everith";
//    appInfo.applicationVersion = VK_MAKE_VERSION (1, 0, 0);
//    appInfo.pEngineName = "No Engine";
//    appInfo.engineVersion = VK_MAKE_VERSION (1, 0, 0);
//    appInfo.apiVersion = VK_API_VERSION_1_0;
//
//    VkInstanceCreateInfo createInfo = {};
//    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
//    createInfo.pNext = nullptr;
//    createInfo.flags = 0;
//    createInfo.pApplicationInfo = &appInfo;
//    if (enableValidationLayers) {
//        createInfo.enabledLayerCount = validationLayers.size ();
//        createInfo.ppEnabledLayerNames = validationLayers.data ();
//    } else {
//        createInfo.enabledLayerCount = 0;
//        createInfo.ppEnabledLayerNames = nullptr;
//    }
//    auto extensions = GetRequiredExtensions ();
//    createInfo.enabledExtensionCount = extensions.size ();
//    createInfo.ppEnabledExtensionNames = extensions.data ();
//
//    if (vkCreateInstance (&createInfo, nullptr, &instance) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to create instance!");
//    } else {
//        message::pConsol ("1. Instance created.");
//    }
//}
//
//std::vector<const char*> render::GetRequiredExtensions () {
//    std::vector<const char*> extensions;
//    unsigned int glfwExtensionCount = 0;
//    const char** glfwExtensions;
//    glfwExtensions = glfwGetRequiredInstanceExtensions (&glfwExtensionCount);
//    for (unsigned int i = 0; i < glfwExtensionCount; i++) {
//        extensions.push_back (glfwExtensions[i]);
//    }
//    if (enableValidationLayers) {
//        extensions.push_back (VK_EXT_DEBUG_Log_EXTENSION_NAME);
//    }
//    return extensions;
//}
//
//void render::createSurface () {
//    if (glfwCreateWindowSurface (instance, glfw_window, nullptr, &surface) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to create window surface!");
//    } else {
//        message::pConsol ("2. Surface crated.");
//    }
//}
//
//void render::getPhysicalDevice () {
//    uint32_t deviceCount = 0;
//    vkEnumeratePhysicalDevices (instance, &deviceCount, nullptr);
//    if (deviceCount == 0) {
//        throw std::runtime_error ("GPU nem támogatja a Vulkan-t!");
//    }
//
//    std::vector<VkPhysicalDevice> foundDevices (deviceCount);
//    vkEnumeratePhysicalDevices (instance, &deviceCount, foundDevices.data ());
//
//    std::multimap<int, VkPhysicalDevice> rankedDevices;
//    for (const auto &device : foundDevices) {
//        int score = ratePhisicalDevice (device);
//        rankedDevices.insert (std::make_pair (score, device));
//    }
//    if (rankedDevices.rbegin ()->first > 0) {
//        physicalDevice = rankedDevices.rbegin ()->second;
//    }
//    if (physicalDevice == VK_NULL_HANDLE) {
//        throw std::runtime_error ("GPU nem felel meg a követelményeknek!");
//    } else {
//        message::pConsol ("3. Physical Device(GPU) megfelel a követelményeknek.");
//    }
//}
//// @pick best device
//int render::ratePhisicalDevice (VkPhysicalDevice device) {
//    int score = 0;
//
//    QueueFamilyIndices indicates = findQueueFamilies (device);
//    bool extensionSupported = checkDeviceExtensionSupport (device);
//    if (!indicates.isComplete () && extensionSupported) {
//        return 0;
//    }
//
//    bool swapChainAdequate = false;
//    SwapChainSupportDetails swapChainSupport = querySwapChainSupport (device);
//    swapChainAdequate = !swapChainSupport.formats.empty () && !swapChainSupport.presentModes.empty ();
//    if (!swapChainAdequate) {
//        return 0;
//    }
//
//    VkPhysicalDeviceProperties deviceProperties;
//    VkPhysicalDeviceFeatures deviceFeatures;
//    vkGetPhysicalDeviceProperties (device, &deviceProperties);
//    vkGetPhysicalDeviceFeatures (device, &deviceFeatures);
//    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
//        score += 1000;
//    }
//    if (deviceFeatures.samplerAnisotropy) {
//        score += 500;
//    } else {
//        return 0;
//    }
//    score += deviceProperties.limits.maxImageDimension2D;
//
//    if (!deviceFeatures.geometryShader) {
//        return 0;
//    }
//    return score;
//}
//// @rate device
//QueueFamilyIndices render::findQueueFamilies (VkPhysicalDevice device) {
//    QueueFamilyIndices indices;
//    uint32_t queueFamilyCount = 0;
//    vkGetPhysicalDeviceQueueFamilyProperties (device, &queueFamilyCount, nullptr);
//    std::vector<VkQueueFamilyProperties> queueFamilies (queueFamilyCount);
//    vkGetPhysicalDeviceQueueFamilyProperties (device, &queueFamilyCount, queueFamilies.data ());
//    int i = 0;
//    for (const auto& queueFamily : queueFamilies) {
//        if (queueFamily.queueCount > 0 && queueFamily.queueFlags && VK_QUEUE_GRAPHICS_BIT) {
//            indices.graphicsFamily = i;
//        }
//        VkBool32 presentSupport = false;
//        vkGetPhysicalDeviceSurfaceSupportKHR (device, i, surface, &presentSupport); //swap chain surface support ellenörzése ??
//
//        if (queueFamily.queueCount > 0 && presentSupport) {
//            indices.presentFamily = i;
//        }
//        if (indices.isComplete ()) {
//            break;
//        }
//        i++;
//    }
//    return indices;
//}
//// @rate device
//bool render::checkDeviceExtensionSupport (VkPhysicalDevice device) {
//    uint32_t extensionCount;
//    vkEnumerateDeviceExtensionProperties (device, nullptr, &extensionCount, nullptr);
//    std::vector<VkExtensionProperties> availableExtensions (extensionCount);
//    vkEnumerateDeviceExtensionProperties (device, nullptr, &extensionCount, availableExtensions.data ());
//
//    std::set<std::string> requiredExtensions (deviceExtensions.begin (), deviceExtensions.end ());
//    for (const auto& extension : availableExtensions) {
//        requiredExtensions.erase (extension.extensionName);
//    }
//    return requiredExtensions.empty ();
//}
//
//void render::createLogicalDevice () {
//    QueueFamilyIndices indices = findQueueFamilies (physicalDevice);
//
//    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
//    std::set<int> uniqueQueueFamilies = {indices.graphicsFamily, indices.presentFamily};
//
//    float queuePriority = 1.0f;
//    for (int queueFamily : uniqueQueueFamilies) {
//        VkDeviceQueueCreateInfo queueCreateInfo = {};
//        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//        queueCreateInfo.pNext = nullptr;
//        queueCreateInfo.flags = 0;
//        queueCreateInfo.queueFamilyIndex = indices.graphicsFamily;
//        queueCreateInfo.queueCount = 1;
//        queueCreateInfo.pQueuePriorities = &queuePriority;
//        queueCreateInfos.push_back (queueCreateInfo);
//    }
//
//    VkPhysicalDeviceFeatures deviceFeatures = {};
//    deviceFeatures.samplerAnisotropy = VK_TRUE;
//
//    VkDeviceCreateInfo createInfo = {};
//    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
//    createInfo.pNext = nullptr;
//    createInfo.flags = 0;
//    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size ());
//    createInfo.pQueueCreateInfos = queueCreateInfos.data ();
//    createInfo.pEnabledFeatures = &deviceFeatures;
//    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size ());
//    createInfo.ppEnabledExtensionNames = deviceExtensions.data ();
//    if (enableValidationLayers) {
//        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size ());
//        createInfo.ppEnabledLayerNames = validationLayers.data ();
//    } else {
//        createInfo.enabledLayerCount = 0;
//    }
//
//    if (vkCreateDevice (physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to create logical device!");
//    } else {
//        message::pConsol ("4. Logical Device created.");
//    }
//
//    vkGetDeviceQueue (device, indices.graphicsFamily, 0, &graphicsQueue);
//    vkGetDeviceQueue (device, indices.presentFamily, 0, &presentQueue);
//
//}
//
//void render::createSwapChain () {
//    SwapChainSupportDetails swapChainSupport = querySwapChainSupport (physicalDevice);     //swap chain támogatási tullajdonságok adatok
//    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat (swapChainSupport.formats); //swap chain optimális beálitásai
//    VkPresentModeKHR presentMode = chooseSwapPresentMode (swapChainSupport.presentModes);  //swap chain optimális beálitásai
//    VkExtent2D extent = chooseSwapExtent (swapChainSupport.capabilities);                  //swap chain optimális beálitásai
//
//    //createInfo minImageCount data
//    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
//    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
//        imageCount = swapChainSupport.capabilities.maxImageCount;
//    }
//    VkSwapchainCreateInfoKHR createInfo = {};
//    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
//    createInfo.surface = surface;
//    createInfo.minImageCount = imageCount;
//    createInfo.imageFormat = surfaceFormat.format;
//    createInfo.imageColorSpace = surfaceFormat.colorSpace;
//    createInfo.imageExtent = extent;
//    createInfo.imageArrayLayers = 1; //TODO kell a 3D-hez jelenleg csak 2D
//    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
//    QueueFamilyIndices indices = findQueueFamilies (physicalDevice);
//    uint32_t queueFamilyIndices[] = {(uint32_t) indices.graphicsFamily, (uint32_t) indices.presentFamily};
//    if (indices.graphicsFamily != indices.presentFamily) {
//        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
//        createInfo.queueFamilyIndexCount = 2;
//        createInfo.pQueueFamilyIndices = queueFamilyIndices;
//    } else {
//        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
//    }
//    createInfo.preTransform = swapChainSupport.capabilities.currentTransform; //transfort the images
//    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
//    createInfo.presentMode = presentMode;
//    createInfo.clipped = VK_TRUE;
//    createInfo.oldSwapchain = VK_NULL_HANDLE; //ha több swap chaint akarunk használni
//
//    if (vkCreateSwapchainKHR (device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to create swap chain!");
//    } else {
//        message::pConsol ("5. Swap chain created.");
//    }
//
//    vkGetSwapchainImagesKHR (device, swapChain, &imageCount, nullptr);
//    swapChainImages.resize (imageCount);
//    vkGetSwapchainImagesKHR (device, swapChain, &imageCount, swapChainImages.data ());
//
//    swapChainImageFormat = surfaceFormat.format;
//    swapChainExtent = extent;
//}
//
//void render::reCreateSwapChain () {
//    vkDeviceWaitIdle (device);
//    cleanSwapChain ();
//    // az ablak méretére alapoznak vagy a swap chainnel -re
//    createSwapChain ();
//    createImageViews ();
//    createRenderPass ();
//    createGraphicsPipeline ();
//    createDepthResources ();
//    createFramebuffers ();
//    createCommandBuffers ();
//}
//
//void render::cleanSwapChain () {
//    vkDestroyImageView (device, depthImageView, nullptr);       //DEPTH
//    vkDestroyImage (device, depthImage, nullptr);               //DEPTH
//    vkFreeMemory (device, depthImageMemory, nullptr);           //DEPTH
//    for (size_t i = 0; i < swapChainFramebuffers.size (); i++) {
//        vkDestroyFramebuffer (device, swapChainFramebuffers[i], nullptr);
//    }
//    vkFreeCommandBuffers (device, commandPool, static_cast<uint32_t>(commandBuffers.size ()), commandBuffers.data ());
//    vkDestroyPipeline (device, graphicsPipeline, nullptr);
//    vkDestroyPipelineLayout (device, pipelineLayout, nullptr);
//    vkDestroyRenderPass (device, renderPass, nullptr);
//    for (size_t i = 0; i < swapChainImageViews.size (); i++) {
//        vkDestroyImageView (device, swapChainImageViews[i], nullptr);
//    }
//    vkDestroySwapchainKHR (device, swapChain, nullptr);
//}
//
//SwapChainSupportDetails render::querySwapChainSupport (VkPhysicalDevice device) {
//    SwapChainSupportDetails details;
//
//    vkGetPhysicalDeviceSurfaceCapabilitiesKHR (device, surface, &details.capabilities);
//
//    uint32_t formatCount;
//    vkGetPhysicalDeviceSurfaceFormatsKHR (device, surface, &formatCount, nullptr);
//    if (formatCount != 0) {
//        details.formats.resize (formatCount);
//        vkGetPhysicalDeviceSurfaceFormatsKHR (device, surface, &formatCount, details.formats.data ());
//    }
//
//    uint32_t presentModeCount;
//    vkGetPhysicalDeviceSurfacePresentModesKHR (device, surface, &presentModeCount, nullptr);
//    if (presentModeCount != 0) {
//        details.presentModes.resize (presentModeCount);
//        vkGetPhysicalDeviceSurfacePresentModesKHR (device, surface, &presentModeCount, details.presentModes.data ());
//    }
//    return details;
//}
//
//VkSurfaceFormatKHR render::chooseSwapSurfaceFormat (const std::vector<VkSurfaceFormatKHR>& availableFormats) {
//    if (availableFormats.size () == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
//        return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
//    }
//    for (const auto& currentFormat : availableFormats) {
//        if (currentFormat.format == VK_FORMAT_B8G8R8A8_UNORM && currentFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
//            return currentFormat;
//        }
//    }
//    return availableFormats[0];
//}
//
//VkPresentModeKHR render::chooseSwapPresentMode (const std::vector<VkPresentModeKHR> availablePresentModes) {
//    for (const auto& currentPresentMode : availablePresentModes) {
//        if (currentPresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
//            return currentPresentMode;
//        } else if (currentPresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
//            return currentPresentMode;
//        }
//    }
//    return VK_PRESENT_MODE_FIFO_KHR;
//}
//
//VkExtent2D render::chooseSwapExtent (const VkSurfaceCapabilitiesKHR & capabilities) {
//    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max ()) {
//        return capabilities.currentExtent;
//    } else {
//        int width, height;
//        glfwGetWindowSize (glfw_window, &width, &height);
//        VkExtent2D actualExtent = {width, height};
//        actualExtent.width = std::max (capabilities.minImageExtent.width, std::min (capabilities.maxImageExtent.width, actualExtent.width));
//        actualExtent.height = std::max (capabilities.minImageExtent.height, std::min (capabilities.maxImageExtent.height, actualExtent.height));
//        return actualExtent;
//    }
//}
//
//void render::createImageViews () {
//    swapChainImageViews.resize (swapChainImages.size ());
//    for (size_t i = 0; i < swapChainImages.size (); i++) {
//        swapChainImageViews[i] = createImageView (swapChainImages[i], swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
//    }
//    message::pConsol ("\t- Image View created");
//}
//
//VkImageView render::createImageView (VkImage image, VkFormat format, VkImageAspectFlags aspectFlags) {
//    VkImageViewCreateInfo viewInfo = {};
//    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
//    viewInfo.image = image;
//    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
//    viewInfo.format = format;
//    viewInfo.subresourceRange.aspectMask = aspectFlags;
//    viewInfo.subresourceRange.baseMipLevel = 0;
//    viewInfo.subresourceRange.levelCount = 1;
//    viewInfo.subresourceRange.baseArrayLayer = 0;
//    viewInfo.subresourceRange.layerCount = 1;
//
//    VkImageView imageView;
//    if (vkCreateImageView (device, &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
//        throw std::runtime_error ("failed to create texture image view!");
//    }
//
//    return imageView;
//}
//
//void render::createRenderPass () {
//    VkAttachmentDescription colorAttachment = {};
//    colorAttachment.format = swapChainImageFormat;
//    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
//    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
//    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
//    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
//
//    VkAttachmentDescription depthAttachment = {};
//    depthAttachment.format = findDepthFormat ();
//    depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
//    depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
//    depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//    depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//    depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//    depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//    depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
//
//    VkAttachmentReference colorAttachmentRef = {};
//    colorAttachmentRef.attachment = 0;
//    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
//
//    VkAttachmentReference depthAttachmentRef = {};
//    depthAttachmentRef.attachment = 1;
//    depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
//
//    VkSubpassDescription subpass = {};
//    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
//    subpass.colorAttachmentCount = 1;
//    subpass.pColorAttachments = &colorAttachmentRef;
//    subpass.pDepthStencilAttachment = &depthAttachmentRef;
//
//    VkSubpassDependency dependancy = {};
//    dependancy.srcSubpass = VK_SUBPASS_EXTERNAL;
//    dependancy.dstSubpass = 0;
//    dependancy.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
//    dependancy.srcAccessMask = 0;
//    dependancy.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
//    dependancy.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
//
//    std::array<VkAttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};
//    VkRenderPassCreateInfo renderPassInfo = {};
//    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
//    renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size ());
//    renderPassInfo.pAttachments = attachments.data ();
//    renderPassInfo.subpassCount = 1;
//    renderPassInfo.pSubpasses = &subpass;
//    renderPassInfo.dependencyCount = 1;
//    renderPassInfo.pDependencies = &dependancy;
//
//    if (vkCreateRenderPass (device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
//        throw std::runtime_error ("failed to create render pass!");
//    } else {
//        message::pConsol ("6. Render pass created");
//    }
//}
//
//void render::createDescriptorSetLayout () {
//    VkDescriptorSetLayoutBinding uboLayoutBinding = {};
//    uboLayoutBinding.binding = 0;
//    uboLayoutBinding.descriptorCount = 1;
//    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//    uboLayoutBinding.pImmutableSamplers = nullptr;
//    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
//
//    VkDescriptorSetLayoutBinding samplerLayoutBinding = {};
//    samplerLayoutBinding.binding = 1;
//    samplerLayoutBinding.descriptorCount = 1;
//    samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//    samplerLayoutBinding.pImmutableSamplers = nullptr;
//    samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
//
//    std::array<VkDescriptorSetLayoutBinding, 2> bindings = {uboLayoutBinding, samplerLayoutBinding};
//    VkDescriptorSetLayoutCreateInfo layoutInfo = {};
//    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
//    layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size ());
//    layoutInfo.pBindings = bindings.data ();
//
//
//    if (vkCreateDescriptorSetLayout (device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to create descriptor set layout!");
//    } else {
//        message::pConsol ("?. Descriptor created.");
//    }
//}
//
//void render::createGraphicsPipeline () {
//    auto vertShaderCode = file::readFile ("shaders/vert.spv");
//    auto fragShaderCode = file::readFile ("shaders/frag.spv");
//
//    VkShaderModule vertShaderModule = createShaderModule (vertShaderCode);
//    VkShaderModule fragShaderModule = createShaderModule (fragShaderCode);
//
//    VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
//    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
//    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
//    vertShaderStageInfo.module = vertShaderModule;
//    vertShaderStageInfo.pName = "main";
//
//    VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
//    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
//    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
//    fragShaderStageInfo.module = fragShaderModule;
//    fragShaderStageInfo.pName = "main";
//
//    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};
//
//    VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
//    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
//    auto bindingDescription = Vertex::getBindingDescription ();
//    auto attributeDescriptions = Vertex::getAttributeDescriptions ();
//    vertexInputInfo.vertexBindingDescriptionCount = 1;
//    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size ());
//    vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
//    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data ();
//
//    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
//    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
//    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
//    inputAssembly.primitiveRestartEnable = VK_FALSE;
//
//    VkViewport viewport = {};
//    viewport.x = 0.0f;
//    viewport.y = 0.0f;
//    viewport.width = (float) swapChainExtent.width;
//    viewport.height = (float) swapChainExtent.height;
//    viewport.minDepth = 0.0f;
//    viewport.maxDepth = 1.0f;
//
//    VkRect2D scissor = {};
//    scissor.offset = {0, 0};
//    scissor.extent = swapChainExtent;
//
//    VkPipelineViewportStateCreateInfo viewportState = {};
//    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
//    viewportState.viewportCount = 1;
//    viewportState.pViewports = &viewport;
//    viewportState.scissorCount = 1;
//    viewportState.pScissors = &scissor;
//
//    VkPipelineRasterizationStateCreateInfo rasterizer = {};
//    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
//    rasterizer.depthClampEnable = VK_FALSE;
//    rasterizer.rasterizerDiscardEnable = VK_FALSE;
//    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
//    rasterizer.lineWidth = 1.0f;
//    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
//    rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE; //TODO Fontos a polygonok oldalát határozza meg hogy meik oldal néz a kamera felé
//    rasterizer.depthBiasEnable = VK_FALSE;
//
//    VkPipelineMultisampleStateCreateInfo multisampling = {}; //TODO anti aliasing
//    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
//    multisampling.sampleShadingEnable = VK_FALSE;
//    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
//
//    VkPipelineDepthStencilStateCreateInfo depthStencil = {};            //DEPTH
//    depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
//    depthStencil.depthTestEnable = VK_TRUE;
//    depthStencil.depthWriteEnable = VK_TRUE;
//    depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
//    depthStencil.depthBoundsTestEnable = VK_FALSE;
//    //depthStencil.minDepthBounds = 0.0f; // Optional csak akkor csinál valamit ha depthBoundsTestEnable engedélyezve van
//    //depthStencil.maxDepthBounds = 1.0f; // Optional csak akkor csinál valamit ha depthBoundsTestEnable engedélyezve van
//    depthStencil.stencilTestEnable = VK_FALSE;
//    //depthStencil.front = {}; // Optional
//    //depthStencil.back = {}; // Optional
//
//
//    VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
//    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
//    colorBlendAttachment.blendEnable = VK_FALSE;
//
//    VkPipelineColorBlendStateCreateInfo colorBlending = {};
//    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
//    colorBlending.logicOpEnable = VK_FALSE;
//    colorBlending.logicOp = VK_LOGIC_OP_COPY;
//    colorBlending.attachmentCount = 1;
//    colorBlending.pAttachments = &colorBlendAttachment;
//    colorBlending.blendConstants[0] = 0.0f;
//    colorBlending.blendConstants[1] = 0.0f;
//    colorBlending.blendConstants[2] = 0.0f;
//    colorBlending.blendConstants[3] = 0.0f;
//
//    VkDynamicState dynamicStates[] = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_LINE_WIDTH};
//    VkPipelineDynamicStateCreateInfo dynamicState = {};
//    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
//    dynamicState.dynamicStateCount = 2;
//    dynamicState.pDynamicStates = dynamicStates;
//
//    VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
//    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
//    pipelineLayoutInfo.setLayoutCount = 1;
//    pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;
//    pipelineLayoutInfo.pushConstantRangeCount = 0;
//
//    if (vkCreatePipelineLayout (device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to create pipeline layout!");
//    }
//
//    VkGraphicsPipelineCreateInfo pipelineInfo = {};
//    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
//    pipelineInfo.stageCount = 2;
//    pipelineInfo.pStages = shaderStages;
//    pipelineInfo.pVertexInputState = &vertexInputInfo;
//    pipelineInfo.pInputAssemblyState = &inputAssembly;
//    pipelineInfo.pViewportState = &viewportState;
//    pipelineInfo.pRasterizationState = &rasterizer;
//    pipelineInfo.pMultisampleState = &multisampling;
//    pipelineInfo.pDepthStencilState = &depthStencil;
//    pipelineInfo.pColorBlendState = &colorBlending;
//    pipelineInfo.layout = pipelineLayout;
//    pipelineInfo.renderPass = renderPass;
//    pipelineInfo.subpass = 0;
//    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
//
//    if (vkCreateGraphicsPipelines (device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to create graphics pipeline!");
//    } else {
//        message::pConsol ("7. Graphics pipeline created.");
//    }
//
//    vkDestroyShaderModule (device, fragShaderModule, nullptr);
//    vkDestroyShaderModule (device, vertShaderModule, nullptr);
//}
//
//VkShaderModule render::createShaderModule (const std::vector<char>& code) {
//    VkShaderModuleCreateInfo createInfo = {};
//    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
//    createInfo.codeSize = code.size ();
//    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data ());
//    VkShaderModule shaderModule;
//    if (vkCreateShaderModule (device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to create shader module!");
//    } else {
//        message::pConsol ("\t- Shader modul created");
//    }
//    return shaderModule;
//}
//
//void render::createFramebuffers () {
//    swapChainFramebuffers.resize (swapChainImageViews.size ());
//
//    for (size_t i = 0; i < swapChainImageViews.size (); i++) {
//        std::array<VkImageView, 2> attachments = {
//            swapChainImageViews[i],
//            depthImageView
//        };
//
//        VkFramebufferCreateInfo framebufferInfo = {};
//        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
//        framebufferInfo.renderPass = renderPass;
//        framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size ());
//        framebufferInfo.pAttachments = attachments.data();
//        framebufferInfo.width = swapChainExtent.width;
//        framebufferInfo.height = swapChainExtent.height;
//        framebufferInfo.layers = 1;
//
//        if (vkCreateFramebuffer (device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
//            throw std::runtime_error ("Failed to create framebuffer!");
//        }
//    }
//    message::pConsol ("8. Frame buffers created.");
//}
//
//void render::createCommandPool () {
//    QueueFamilyIndices queueFamilyIndices = findQueueFamilies (physicalDevice);
//
//    VkCommandPoolCreateInfo poolInfo = {};
//    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
//    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily;
//
//    if (vkCreateCommandPool (device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to create command pool!");
//    } else {
//        message::pConsol ("9. Command pool created.");
//    }
//}
//
//void render::createDepthResources () {
//    VkFormat depthFormat = findDepthFormat ();
//
//    createImage (swapChainExtent.width, swapChainExtent.height, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, depthImage, depthImageMemory);
//    depthImageView = createImageView (depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
//
//    transitionImageLayout (depthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
//}
//
//VkFormat render::findSupportedFormat (const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
//    for (VkFormat format : candidates) {
//        VkFormatProperties props;
//        vkGetPhysicalDeviceFormatProperties (physicalDevice, format, &props);
//
//        if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
//            return format;
//        } else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
//            return format;
//        }
//    }
//    throw std::runtime_error ("Failed to find supported format!");
//}
//
//VkFormat render::findDepthFormat () {
//    return findSupportedFormat ({VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT}, VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
//}
//
//bool render::hasStencilComponent (VkFormat format) {
//    return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
//}
//
//void render::createTextureImage () {
//    int texWidth, texHeight, texChannels;
//    stbi_uc* pixels = stbi_load (TEXTURE_PATH.c_str (), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
//    //stbi_uc* pixels = stbi_load ("Textures/00.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
//    VkDeviceSize imageSize = texWidth * texHeight * 4;
//
//    if (!pixels) {
//        throw std::runtime_error ("Failed to load texture image!");
//    }
//
//    VkBuffer stagingBuffer;
//    VkDeviceMemory stagingBufferMemory;
//    createBuffer (imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
//
//    void* data;
//    vkMapMemory (device, stagingBufferMemory, 0, imageSize, 0, &data);
//    memcpy (data, pixels, static_cast<size_t>(imageSize));
//    vkUnmapMemory (device, stagingBufferMemory);
//
//    stbi_image_free (pixels);
//
//    createImage (texWidth, texHeight, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, textureImage, textureImageMemory);
//
//    transitionImageLayout (textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
//    copyBufferToImage (stagingBuffer, textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
//    transitionImageLayout (textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
//
//    vkDestroyBuffer (device, stagingBuffer, nullptr);
//    vkFreeMemory (device, stagingBufferMemory, nullptr);
//}
//
//void render::createTextureImageView () {
//    textureImageView = createImageView (textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT);
//}
//
//void render::createTextureSampler () {
//    VkSamplerCreateInfo samplerInfo = {};
//    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
//    samplerInfo.magFilter = VK_FILTER_LINEAR;
//    samplerInfo.minFilter = VK_FILTER_LINEAR;
//    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
//    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
//    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
//    samplerInfo.anisotropyEnable = VK_TRUE;
//    samplerInfo.maxAnisotropy = 16;
//    samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
//    samplerInfo.unnormalizedCoordinates = VK_FALSE;
//    samplerInfo.compareEnable = VK_FALSE;
//    samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
//    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
//
//    if (vkCreateSampler (device, &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS) {
//        throw std::runtime_error ("failed to create texture sampler!");
//    }
//}
//
//void render::createImage (uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory) {
//    VkImageCreateInfo imageInfo = {};
//    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
//    imageInfo.imageType = VK_IMAGE_TYPE_2D;
//    imageInfo.extent.width = width;
//    imageInfo.extent.height = height;
//    imageInfo.extent.depth = 1;
//    imageInfo.mipLevels = 1;
//    imageInfo.arrayLayers = 1;
//    imageInfo.format = format;
//    imageInfo.tiling = tiling;
//    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//    imageInfo.usage = usage;
//    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
//    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
//
//    if (vkCreateImage (device, &imageInfo, nullptr, &image) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to create image!");
//    }
//
//    VkMemoryRequirements memRequirements;
//    vkGetImageMemoryRequirements (device, image, &memRequirements);
//
//    VkMemoryAllocateInfo allocInfo = {};
//    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
//    allocInfo.allocationSize = memRequirements.size;
//    allocInfo.memoryTypeIndex = findMemoryType (memRequirements.memoryTypeBits, properties);
//
//    if (vkAllocateMemory (device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to allocate image memory!");
//    }
//
//    vkBindImageMemory (device, image, imageMemory, 0);
//}
//
//void render::transitionImageLayout (VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout) {
//    VkCommandBuffer commandBuffer = beginSingleTimeCommands ();
//
//    VkImageMemoryBarrier barrier = {};
//    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
//    barrier.oldLayout = oldLayout;
//    barrier.newLayout = newLayout;
//    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
//    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
//    barrier.image = image;
//    if (newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
//        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
//        if (hasStencilComponent (format)) {
//            barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;}
//        } else {
//            barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;}
//    barrier.subresourceRange.baseMipLevel = 0;
//    barrier.subresourceRange.levelCount = 1;
//    barrier.subresourceRange.baseArrayLayer = 0;
//    barrier.subresourceRange.layerCount = 1;
//
//    VkPipelineStageFlags sourceStage;
//    VkPipelineStageFlags destinationStage;
//
//    if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
//        barrier.srcAccessMask = 0;
//        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
//
//        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
//        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
//    } else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
//        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
//        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
//
//        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
//        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
//    } else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
//        barrier.srcAccessMask = 0;
//        barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
//
//        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
//        destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
//    } else {
//        throw std::invalid_argument ("unsupported layout transition!");
//    }
//
//    vkCmdPipelineBarrier (
//        commandBuffer,
//        sourceStage, destinationStage,
//        0,
//        0, nullptr,
//        0, nullptr,
//        1, &barrier
//    );
//
//    endSingleTimeCommands (commandBuffer);
//}
//
//VkCommandBuffer render::beginSingleTimeCommands () {
//    VkCommandBufferAllocateInfo allocInfo = {};
//    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
//    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
//    allocInfo.commandPool = commandPool;
//    allocInfo.commandBufferCount = 1;
//
//    VkCommandBuffer commandBuffer;
//    vkAllocateCommandBuffers (device, &allocInfo, &commandBuffer);
//
//    VkCommandBufferBeginInfo beginInfo = {};
//    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
//    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
//
//    vkBeginCommandBuffer (commandBuffer, &beginInfo);
//
//    return commandBuffer;
//}
//void render::endSingleTimeCommands (VkCommandBuffer commandBuffer) {
//    vkEndCommandBuffer (commandBuffer);
//
//    VkSubmitInfo submitInfo = {};
//    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
//    submitInfo.commandBufferCount = 1;
//    submitInfo.pCommandBuffers = &commandBuffer;
//
//    vkQueueSubmit (graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
//    vkQueueWaitIdle (graphicsQueue);
//
//    vkFreeCommandBuffers (device, commandPool, 1, &commandBuffer);
//}
//
//void render::createVertexBuffer () {
//    VkDeviceSize bufferSize = sizeof (vertices[0]) * vertices.size ();
//
//    VkBuffer stagingBuffer;
//    VkDeviceMemory stagingBufferMemory;
//    createBuffer (bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
//
//    void* data;
//    vkMapMemory (device, stagingBufferMemory, 0, bufferSize, 0, &data);
//    memcpy (data, vertices.data (), (size_t) bufferSize);
//    vkUnmapMemory (device, stagingBufferMemory);
//
//    createBuffer (bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);
//
//    copyBuffer (stagingBuffer, vertexBuffer, bufferSize);
//
//    vkDestroyBuffer (device, stagingBuffer, nullptr);
//    vkFreeMemory (device, stagingBufferMemory, nullptr);
//}
//
//void render::createIndexBuffer () {
//    VkDeviceSize bufferSize = sizeof (indices[0]) * indices.size ();
//
//    VkBuffer stagingBuffer;
//    VkDeviceMemory stagingBufferMemory;
//    createBuffer (bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
//
//    void* data;
//    vkMapMemory (device, stagingBufferMemory, 0, bufferSize, 0, &data);
//    memcpy (data, indices.data (), (size_t) bufferSize);
//    vkUnmapMemory (device, stagingBufferMemory);
//
//    createBuffer (bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);
//
//    copyBuffer (stagingBuffer, indexBuffer, bufferSize);
//
//    vkDestroyBuffer (device, stagingBuffer, nullptr);
//    vkFreeMemory (device, stagingBufferMemory, nullptr);
//}
//
//void render::createUniformBuffer () {
//    VkDeviceSize bufferSize = sizeof (UniformBufferObject);
//    createBuffer (bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffer, uniformBufferMemory);
//}
//
//void render::updateUniformBuffer () {
//    static auto startTime = std::chrono::high_resolution_clock::now ();
//
//    auto currentTime = std::chrono::high_resolution_clock::now ();
//    float time = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count () / 1000.0f;
//
//    UniformBufferObject ubo = {};
//    ubo.model = glm::rotate (glm::mat4 (1.0f), 0 * glm::radians (20.0f), glm::vec3 (0.0f, 0.0f, 1.0f));
//    ubo.view = glm::lookAt (glm::vec3 (-2.0f, 0.0f, 0.4f), glm::vec3 (0.0f, 0.0f, 0.4f), glm::vec3 (0.0f, 0.0f, 1.0f));
//    ubo.proj = glm::perspective (glm::radians (45.0f), swapChainExtent.width / (float) swapChainExtent.height, 1.0f, 10.0f);
//    ubo.proj[1][1] *= -1;
//
//    void* data;
//    vkMapMemory (device, uniformBufferMemory, 0, sizeof (ubo), 0, &data);
//    memcpy (data, &ubo, sizeof (ubo));
//    vkUnmapMemory (device, uniformBufferMemory);
//}
//
//void render::createDescriptorPool () {
//    std::array<VkDescriptorPoolSize, 2> poolSizes = {};
//    poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//    poolSizes[0].descriptorCount = 1;
//    poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//    poolSizes[1].descriptorCount = 1;
//
//    VkDescriptorPoolCreateInfo poolInfo = {};
//    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
//    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size ());
//    poolInfo.pPoolSizes = poolSizes.data ();
//    poolInfo.maxSets = 1;
//
//    //RÉGI
//    //VkDescriptorPoolSize poolSize = {};
//    //poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//    //poolSize.descriptorCount = 1;
//
//    //VkDescriptorPoolCreateInfo poolInfo = {};
//    //poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
//    //poolInfo.poolSizeCount = 1;
//    //poolInfo.pPoolSizes = &poolSize;
//    //poolInfo.maxSets = 1;
//
//    if (vkCreateDescriptorPool (device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to create descriptor pool!");
//    } else {
//        message::pConsol ("?. Desctriptor pool created.");
//    }
//}
//
//void render::createDescriptorSet () {
//    VkDescriptorSetLayout layouts[] = {descriptorSetLayout};
//    VkDescriptorSetAllocateInfo allocInfo = {};
//    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
//    allocInfo.descriptorPool = descriptorPool;
//    allocInfo.descriptorSetCount = 1;
//    allocInfo.pSetLayouts = layouts;
//
//
//    if (vkAllocateDescriptorSets (device, &allocInfo, &descriptorSet) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to allocate descriptor set!");
//    } else {
//        message::pConsol ("?. Desctriptor set created.");
//    }
//
//    VkDescriptorBufferInfo bufferInfo = {};
//    bufferInfo.buffer = uniformBuffer;
//    bufferInfo.offset = 0;
//    bufferInfo.range = sizeof (UniformBufferObject);
//
//    VkDescriptorImageInfo imageInfo = {};
//    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//    imageInfo.imageView = textureImageView;
//    imageInfo.sampler = textureSampler;
//
//    std::array<VkWriteDescriptorSet, 2> descriptorWrites = {};
//
//    descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//    descriptorWrites[0].dstSet = descriptorSet;
//    descriptorWrites[0].dstBinding = 0;
//    descriptorWrites[0].dstArrayElement = 0;
//    descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//    descriptorWrites[0].descriptorCount = 1;
//    descriptorWrites[0].pBufferInfo = &bufferInfo;
//
//    descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//    descriptorWrites[1].dstSet = descriptorSet;
//    descriptorWrites[1].dstBinding = 1;
//    descriptorWrites[1].dstArrayElement = 0;
//    descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//    descriptorWrites[1].descriptorCount = 1;
//    descriptorWrites[1].pImageInfo = &imageInfo;
//
//    vkUpdateDescriptorSets (device, static_cast<uint32_t>(descriptorWrites.size ()), descriptorWrites.data (), 0, nullptr);
//
//    //LECSERÉLVE FENTEBB
//    //VkWriteDescriptorSet descriptorWrite = {};
//    //descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//    //descriptorWrite.dstSet = descriptorSet;
//    //descriptorWrite.dstBinding = 0;
//    //descriptorWrite.dstArrayElement = 0;
//    //descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//    //descriptorWrite.descriptorCount = 1;
//    //descriptorWrite.pBufferInfo = &bufferInfo;
//    //vkUpdateDescriptorSets (device, 1, &descriptorWrite, 0, nullptr);
//}
//
//uint32_t render::findMemoryType (uint32_t typeFilter, VkMemoryPropertyFlags properties) {
//    VkPhysicalDeviceMemoryProperties memProperties;
//    vkGetPhysicalDeviceMemoryProperties (physicalDevice, &memProperties);
//    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
//        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
//            return i;
//        }
//    }
//    throw std::runtime_error ("Failed to find suitable memory type!");
//
//
//}
//
//void render::createBuffer (VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
//    VkBufferCreateInfo bufferInfo = {};
//    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
//    bufferInfo.size = size;
//    bufferInfo.usage = usage;
//    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
//
//    if (vkCreateBuffer (device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
//        throw std::runtime_error ("failed to create buffer!");
//    }
//
//    VkMemoryRequirements memRequirements;
//    vkGetBufferMemoryRequirements (device, buffer, &memRequirements);
//
//    VkMemoryAllocateInfo allocInfo = {};
//    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
//    allocInfo.allocationSize = memRequirements.size;
//    allocInfo.memoryTypeIndex = findMemoryType (memRequirements.memoryTypeBits, properties);
//
//    if (vkAllocateMemory (device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to allocate buffer memory!");
//    }
//
//    vkBindBufferMemory (device, buffer, bufferMemory, 0);
//}
//
//void render::copyBuffer (VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
//    VkCommandBuffer commandBuffer = beginSingleTimeCommands ();
//
//    VkBufferCopy copyRegion = {};
//    copyRegion.size = size;
//    vkCmdCopyBuffer (commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
//
//    endSingleTimeCommands (commandBuffer);
//
//    //lecserélve a fenti dologra
//
//    //VkCommandBufferAllocateInfo allocInfo = {};
//    //allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
//    //allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
//    //allocInfo.commandPool = commandPool;
//    //allocInfo.commandBufferCount = 1;
//    //VkCommandBuffer commandBuffer;
//    //vkAllocateCommandBuffers (device, &allocInfo, &commandBuffer);
//
//    //VkCommandBufferBeginInfo beginInfo = {};
//    //beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
//    //beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
//    //vkBeginCommandBuffer (commandBuffer, &beginInfo);
//
//    //VkBufferCopy copyRegion = {};
//    //copyRegion.srcOffset = 0; // Optional
//    //copyRegion.dstOffset = 0; // Optional
//    //copyRegion.size = size;
//    //vkCmdCopyBuffer (commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
//
//    //vkEndCommandBuffer (commandBuffer);
//
//    //VkSubmitInfo submitInfo = {};
//    //submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
//    //submitInfo.commandBufferCount = 1;
//    //submitInfo.pCommandBuffers = &commandBuffer;
//
//    //vkQueueSubmit (graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
//    //vkQueueWaitIdle (graphicsQueue);
//
//    //vkFreeCommandBuffers (device, commandPool, 1, &commandBuffer);
//}
//
//void render::copyBufferToImage (VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) {
//    VkCommandBuffer commandBuffer = beginSingleTimeCommands ();
//
//    VkBufferImageCopy region = {};
//    region.bufferOffset = 0;
//    region.bufferRowLength = 0;
//    region.bufferImageHeight = 0;
//    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
//    region.imageSubresource.mipLevel = 0;
//    region.imageSubresource.baseArrayLayer = 0;
//    region.imageSubresource.layerCount = 1;
//    region.imageOffset = {0, 0, 0};
//    region.imageExtent = {
//        width,
//        height,
//        1
//    };
//
//    vkCmdCopyBufferToImage (commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
//
//    endSingleTimeCommands (commandBuffer);
//}
//
//
//void render::createCommandBuffers () {
//    commandBuffers.resize (swapChainFramebuffers.size ());
//
//    VkCommandBufferAllocateInfo allocInfo = {};
//    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
//    allocInfo.commandPool = commandPool;
//    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
//    allocInfo.commandBufferCount = (uint32_t) commandBuffers.size ();
//
//    if (vkAllocateCommandBuffers (device, &allocInfo, commandBuffers.data ()) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to allocate command buffers!");
//    } else {
//        message::pConsol ("\t-Command buffers created.");
//    }
//
//    for (size_t i = 0; i < commandBuffers.size (); i++) {
//        VkCommandBufferBeginInfo beginInfo = {};
//        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
//        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
//
//        vkBeginCommandBuffer (commandBuffers[i], &beginInfo);
//
//        VkRenderPassBeginInfo renderPassInfo = {};
//        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
//        renderPassInfo.renderPass = renderPass;
//        renderPassInfo.framebuffer = swapChainFramebuffers[i];
//        renderPassInfo.renderArea.offset = {0, 0};
//        renderPassInfo.renderArea.extent = swapChainExtent;
//        std::array<VkClearValue, 2> clearValues = {};
//        clearValues[0].color = {0.0f, 0.0f, 0.0f, 1.0f};
//        clearValues[1].depthStencil = {1.0f, 0};
//        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size ());
//        renderPassInfo.pClearValues = clearValues.data();
//
//        vkCmdBeginRenderPass (commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
//        vkCmdBindPipeline (commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
//        VkBuffer vertexBuffers[] = {vertexBuffer};
//        VkDeviceSize offsets[] = {0};
//        vkCmdBindVertexBuffers (commandBuffers[i], 0, 1, vertexBuffers, offsets);
//        vkCmdBindIndexBuffer (commandBuffers[i], indexBuffer, 0, VK_INDEX_TYPE_UINT32);
//        vkCmdBindDescriptorSets (commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);
//        //vkCmdDraw (commandBuffers[i], static_cast<uint32_t>(vertices.size ()), 1, 0, 0);  //lecserélve a vkCmdDrawIndexed-el
//        vkCmdDrawIndexed (commandBuffers[i], static_cast<uint32_t>(indices.size ()), 1, 0, 0, 0);
//        vkCmdEndRenderPass (commandBuffers[i]);
//
//        if (vkEndCommandBuffer (commandBuffers[i]) != VK_SUCCESS) {
//            throw std::runtime_error ("Failed to record command buffer!");
//        }
//    }
//    message::pConsol ("10. Command budffer created.");
//}
//
//void render::drawFrame () {
//    uint32_t imageindex;
//    VkResult result = vkAcquireNextImageKHR (device, swapChain, std::numeric_limits<uint64_t>::max (), availableSemaphore, VK_NULL_HANDLE, &imageindex);
//
//    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
//        reCreateSwapChain ();
//        return;
//    } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
//        throw std::runtime_error ("Failed to acquire swap chain image!");
//    }
//
//    VkSubmitInfo submitInfo = {};
//    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
//    VkSemaphore waitSemaphores[] = {availableSemaphore};
//    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
//    submitInfo.waitSemaphoreCount = 1;
//    submitInfo.pWaitSemaphores = waitSemaphores;
//    submitInfo.pWaitDstStageMask = waitStages;
//    VkSemaphore signalSemaphores[] = {renderFinishSemaphore};
//    submitInfo.signalSemaphoreCount = 1;
//    submitInfo.pSignalSemaphores = signalSemaphores;
//    submitInfo.commandBufferCount = 1;
//    submitInfo.pCommandBuffers = &commandBuffers[imageindex];
//
//    if (vkQueueSubmit (graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to submit draw command buffer!");
//    }
//
//    VkPresentInfoKHR presentInfo = {};
//    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
//    presentInfo.waitSemaphoreCount = 1;
//    presentInfo.pWaitSemaphores = signalSemaphores;
//    VkSwapchainKHR swapChains[] = {swapChain};
//    presentInfo.swapchainCount = 1;
//    presentInfo.pSwapchains = swapChains;
//    presentInfo.pImageIndices = &imageindex;
//    VkResult queueResult = vkQueuePresentKHR (graphicsQueue, &presentInfo);
//
//    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
//        reCreateSwapChain ();
//    } else if (result != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to present swap chain image!");
//    }
//
//    vkQueueWaitIdle (graphicsQueue);
//
//}
//
//void render::createSemaphores () {
//    VkSemaphoreCreateInfo semaphoreInfo {};
//    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
//
//    if (vkCreateSemaphore (device, &semaphoreInfo, nullptr, &availableSemaphore) != VK_SUCCESS || vkCreateSemaphore (device, &semaphoreInfo, nullptr, &renderFinishSemaphore) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to create semaphore!");
//    } else {
//        message::pConsol ("11. Semaphore created.");
//    }
//}
//
//void render::loadModel () {
//    tinyobj::attrib_t attrib;
//    std::vector<tinyobj::shape_t> shapes;
//    std::vector<tinyobj::material_t> materials;
//    std::string err;
//
//    if (!tinyobj::LoadObj (&attrib, &shapes, &materials, &err, MODEL_PATH.c_str ())) {
//        throw std::runtime_error (err);
//    }
//
//    std::unordered_map<Vertex, uint32_t> uniqueVertices = {};
//
//    for (const auto& shape : shapes) {
//        for (const auto& index : shape.mesh.indices) {
//            Vertex vertex = {};
//            vertex.pos = {
//                attrib.vertices[3 * index.vertex_index + 0],
//                attrib.vertices[3 * index.vertex_index + 1],
//                attrib.vertices[3 * index.vertex_index + 2]
//            };
//            vertex.texCoord = {
//                attrib.texcoords[2 * index.texcoord_index + 0],
//                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
//            };
//            vertex.color = {1.0f, 1.0f, 1.0f};
//
//
//            if (uniqueVertices.count (vertex) == 0) {
//                uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size ());
//                vertices.push_back (vertex);
//            }
//            indices.push_back (uniqueVertices[vertex]);
//        }
//    }
//}
//
//
//
//
//// DEBUG TOOLS
//bool render::checkValidationLayerSupport () {
//    uint32_t layerCount;
//    vkEnumerateInstanceLayerProperties (&layerCount, nullptr);
//
//    std::vector<VkLayerProperties> availableLayers (layerCount);
//    vkEnumerateInstanceLayerProperties (&layerCount, availableLayers.data ());
//
//    for (const char* layerName : validationLayers) {
//        bool layerFound = false;
//        for (const auto& layerProperties : availableLayers) {
//            if (strcmp (layerName, layerProperties.layerName) == 0) {
//                layerFound = true;
//                break;
//            }
//        }
//        if (!layerFound) {
//            return false;
//        }
//    }
//    return true;
//}
//
//void render::setupDebugCallback () {
//    if (!enableValidationLayers) { return; }
//    VkDebugLogCallbackCreateInfoEXT createInfo = {};
//    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_Log_CALLBACK_CREATE_INFO_EXT;
//    createInfo.flags = VK_DEBUG_Log_ERROR_BIT_EXT | VK_DEBUG_Log_WARNING_BIT_EXT;
//    createInfo.pfnCallback = debugCallback;
//    if (CreateDebugLogCallbackEXT (instance, &createInfo, nullptr, &callback) != VK_SUCCESS) {
//        throw std::runtime_error ("Failed to setup debug callback!");
//    } else {
//        message::pConsol ("-. Debug callback created.");
//    }
//}
//VKAPI_ATTR VkBool32 VKAPI_CALL render::debugCallback (VkDebugLogFlagsEXT flags,
//                                                      VkDebugLogObjectTypeEXT objType,
//                                                      uint64_t obj,
//                                                      size_t location,
//                                                      int32_t code,
//                                                      const char * layerPrefix,
//                                                      const char * msg,
//                                                      void * userData) {
//    std::cout << "validation layer: " << msg << std::endl;
//    return VK_FALSE;
//}
//VkResult render::CreateDebugLogCallbackEXT (VkInstance instance,
//                                               const VkDebugLogCallbackCreateInfoEXT * pCreateInfo,
//                                               const VkAllocationCallbacks * pAllocator,
//                                               VkDebugLogCallbackEXT * pCallback) {
//    auto func = (PFN_vkCreateDebugLogCallbackEXT) vkGetInstanceProcAddr (instance, "vkCreateDebugLogCallbackEXT");
//    if (func != nullptr) {
//        return func (instance, pCreateInfo, pAllocator, pCallback);
//    } else {
//        return VK_ERROR_EXTENSION_NOT_PRESENT;
//    }
//}
//void render::DestroyDebugLogCallbackEXT (VkInstance instance,
//                                            VkDebugLogCallbackEXT callback,
//                                            const VkAllocationCallbacks * pAllocator) {
//    auto func = (PFN_vkDestroyDebugLogCallbackEXT) vkGetInstanceProcAddr (instance, "vkDestroyDebugLogCallbackEXT");
//    if (func != nullptr) {
//        func (instance, callback, pAllocator);
//    }
//}