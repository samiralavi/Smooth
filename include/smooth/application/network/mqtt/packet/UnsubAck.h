//
// Created by permal on 7/22/17.
//

#include <smooth/application/network/mqtt/packet/MQTTPacket.h>

namespace smooth
{
    namespace application
    {
        namespace network
        {
            namespace mqtt
            {
                namespace packet
                {
                    class UnsubAck
                            : public MQTTPacket
                    {
                        public:
                            UnsubAck() = default;

                            UnsubAck(const MQTTPacket& packet) : MQTTPacket(packet)
                            {
                            }

                            void visit(IPacketReceiver& receiver) override;
                    };
                }
            }
        }
    }
}