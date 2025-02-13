#pragma once


//Memory
typedef VkMemoryPropertyFlags memory_flag;
constexpr memory_flag TYP_MEMORY_GPU = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
constexpr memory_flag TYP_MEMORY_SHARED_CPU_GPU = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

//Buffer usage
typedef VkBufferUsageFlags buffer_usage;
constexpr buffer_usage TYP_BUFFER_USAGE_SRC = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
constexpr buffer_usage TYP_BUFFER_USAGE_DST = VK_BUFFER_USAGE_TRANSFER_DST_BIT;
constexpr buffer_usage TYP_BUFFER_USAGE_DST_VERTEX = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
