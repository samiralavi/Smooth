#pragma once

#include "responses/IRequestResponeOperation.h"
#include "IResponseQueue.h"
#include <memory>

namespace smooth
{
    namespace application
    {
        namespace network
        {
            namespace http
            {
                template<int MaxHeaderSize, int ContentChuckSize>
                using ResponseSignature = std::function<void(
                        IResponseQueue& response,
                        const std::string& url,
                        bool first_part,
                        bool last_part,
                        const std::unordered_map<std::string, std::string>& headers,
                        const std::unordered_map<std::string, std::string>& request_parameters,
                        const std::vector<uint8_t>& content
                        )>;

            }
        }
    }
}