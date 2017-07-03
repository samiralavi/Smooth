//
// Created by permal on 6/25/17.
//
#pragma once

#include <freertos/queue.h>
#include <esp_log.h>
#include <chrono>
#include <string>

namespace smooth
{
    namespace ipc
    {
        template<typename T>
        class Queue
        {
            public:
                Queue(const std::string& name, int size)
                        : name(name)
                {
                    ESP_LOGV("Queue", "Creating queue '%s', with %d items of size %d.", name.c_str(), size, sizeof(T));
                    handle = xQueueCreate(size, sizeof(T));
                    if (handle == nullptr)
                    {
                        ESP_LOGE("Queue", "Failed to create Queue '%s'", name.c_str());
                        abort();
                    }
                }

                virtual ~Queue()
                {
                    if (handle != nullptr)
                    {
                        vQueueDelete(handle);
                    }
                }

                virtual bool push(const T& item)
                {
                    return xQueueSend(handle, &item, 0 ) == pdTRUE;
                }

                virtual bool push(const T& item, std::chrono::milliseconds wait_time )
                {
                    return xQueueSend(handle, &item, to_ticks(wait_time)) == pdTRUE;
                }

                bool push_from_isr(const T& item)
                {
                    return xQueueSendFromISR(handle, &item, nullptr) == pdTRUE;
                }

                bool pop(T& target)
                {
                    return xQueueReceive(handle, &target, 0);
                }

                bool pop(T& target, std::chrono::milliseconds wait_time)
                {
                    return xQueueReceive(handle, &target, to_ticks(wait_time)) == pdTRUE;
                }

                bool pop_from_isr(T& target)
                {
                    return xQueueReceiveFromISR(handle, &target, nullptr) == pdTRUE;
                }

                bool empty()
                {
                    return uxQueueMessagesWaiting(handle) == 0;
                }

                bool empty_from_isr()
                {
                    return uxQueueMessagesWaitingFromISR(handle) == 0;
                }

            private:
                QueueHandle_t handle = nullptr;
                std::string name;

                TickType_t to_ticks(std::chrono::milliseconds ms)
                {
                    return pdMS_TO_TICKS( ms.count() );
                }
        };
    }
}