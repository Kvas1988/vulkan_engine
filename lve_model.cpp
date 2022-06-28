#include "lve_model.h"

#include <cassert>

namespace lve {
    LveModel::LveModel(LveDevice& device, const std::vector<Vertex>& verticies) : lveDevice{device} {
        createVertexBuffers(verticies);
    }

    LveModel::~LveModel() {
        vkDestroyBuffer(lveDevice.device(), vertexBuffer, nullptr);
        vkFreeMemory(lveDevice.device(), vertexBufferMemory, nullptr);
    }

    void LveModel::createVertexBuffers(const std::vector<Vertex>& verticies) {
        vertexCount = static_cast<uint32_t>(verticies.size());
        assert(vertexCount >= 3 && "Vertex count must be at least 3"); 
        VkDeviceSize bufferSize = sizeof(verticies[0]) * vertexCount;
        lveDevice.createBuffer(bufferSize, 
            VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            vertexBuffer,
            vertexBufferMemory);
        
        void *data;
        vkMapMemory(lveDevice.device(), vertexBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, verticies.data(), static_cast<uint32_t>(bufferSize));
        vkUnmapMemory(lveDevice.device(), vertexBufferMemory); 
    }

    void LveModel::bind(VkCommandBuffer commandBuffer) {
        VkBuffer buffers[] = {vertexBuffer};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
    }

    void LveModel::draw(VkCommandBuffer commandBuffer) {
        vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
    }

    std::vector<VkVertexInputBindingDescription> LveModel::Vertex::getBindingDescriptions() {
        std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
        bindingDescriptions[0].binding = 0;
        bindingDescriptions[0].stride = sizeof(Vertex);
        bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescriptions;
    }

    std::vector<VkVertexInputAttributeDescription> LveModel::Vertex::getAttributeDescriptions() {
        std::vector<VkVertexInputAttributeDescription> attributeteDescriptions(1);
        attributeteDescriptions[0].binding = 0;
        attributeteDescriptions[0].location = 0;
        attributeteDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeteDescriptions[0].offset = 0;
        return attributeteDescriptions;
    }

}