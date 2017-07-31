//
// Created by permal on 7/5/17.
//

#pragma once

#include "PacketReceiveBuffer.h"

namespace smooth
{
    namespace core
    {
        namespace network
        {
            template<typename T>
            class DataAvailableEvent
            {
                public:
                    DataAvailableEvent() = default;

                    DataAvailableEvent(IPacketReceiveBuffer <T>* rx) : rx(rx)
                    {
                    }

                    bool get(T& target) const
                    {
                        bool res = false;
                        if (rx)
                        {
                            res = rx->get(target);
                        }
                        return res;
                    }

                private:
                    IPacketReceiveBuffer <T>* rx = nullptr;
            };
        }
    }
}