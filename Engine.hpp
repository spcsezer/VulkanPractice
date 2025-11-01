#pragma once

#include"CreateInstance.hpp"
#include"ValidationLayers.hpp"
#include"CreateSurface.hpp"
#include"PickPhysicalDevice.hpp"
#include"CreateLogicalDevice.hpp"
#include"SwapChain.hpp"
#include"CreateImageViews.hpp"
#include"CreateRenderPass.hpp"
#include"CreateDescriptorSetLayout.hpp"
#include"CreateGraphicsPipeline.hpp"
#include"CreateCommandPool.hpp"
#include"CreateResources.hpp"
#include"CreateFrameBuffers.hpp"
#include"CreateTexture.hpp"
#include"LoadModel.hpp"
#include"CreateBuffer.hpp"
#include"CreateDescriptorSets.hpp"
#include"CreateCommandBuffer.hpp"
#include"CreateSyncObjects.hpp"

extern CreateInstance createInstance;
extern ValidationLayers validationLayers;
extern CreateSurface createSurface;
extern PickPhysicalDevice pickPhysicalDevice;
extern CreateLogicalDevice createLogicalDevice;
extern SwapChain swapChain;
extern CreateImageViews createImageViews;
extern CreateRenderPass createRenderPass;
extern CreateDescriptorSetLayout createDescriptorSetLayout;
extern CreateGraphicsPipeline createGraphicsPipeline;
extern CreateCommandPool createCommandPool;
extern CreateResources createResources;
extern CreateFrameBuffers createFrameBuffers;
extern CreateTexture createTexture;
extern LoadModel loadModel;
extern CreateBuffer createBuffer;
extern CreateDescriptorSets createDescriptorSets;
extern CreateCommandBuffer createCommandBuffer;
extern CreateSyncObjects createSyncObjects;

inline void RunEngine()
{
	createInstance.gCreateInstance();
	validationLayers.gValidationLayers();
	createSurface.gCreateSurface();
	pickPhysicalDevice.gPickPhysicalDevice();
	createLogicalDevice.gCreateLogicalDevice();
	swapChain.gSwapChain();
	createImageViews.gCreateImageViews();
	createRenderPass.gCreateRenderPass();
	createDescriptorSetLayout.gCreateDescriptorSetLayout();
	createGraphicsPipeline.gCreateGraphicsPipeline();
	createCommandPool.gCreateCommandPool();
	createResources.gCreateResources();
	createFrameBuffers.gCreateFrameBuffers();
	createTexture.gCreateTexture();
	loadModel.gLoadModel();
	createBuffer.gCreateBuffer();
	createDescriptorSets.gCreateDescriptorSets();
	createCommandBuffer.gCreateCommandBuffer();
	createSyncObjects.gCreateSyncObjects();
}

inline void CleanEngine()
{
	SwapChain::cleanupSwapChain();
	createSyncObjects.cleanUp();
	createCommandPool.cleanUp();
	createTexture.cleanUp();
	createBuffer.cleanUp();
	createDescriptorSets.cleanUp();
	createDescriptorSetLayout.cleanUp();
	createGraphicsPipeline.cleanUp();
	createRenderPass.cleanUp();
	createLogicalDevice.cleanUp();
	validationLayers.cleanUp();
	createSurface.cleanUp();
	createInstance.cleanUp();
}