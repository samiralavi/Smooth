//
// Created by permal on 8/25/17.
//

#pragma once

#include <utility>
#include <smooth/core/io/i2c/I2CMasterDevice.h>
#include <smooth/core/util/FixedBuffer.h>

namespace smooth
{
    namespace application
    {
        namespace io
        {
            // http://ww1.microchip.com/downloads/en/DeviceDoc/20001952C.pdf
            /// MCP23017 I2C I/O extender.
            /// @note This class assumes IOCON.BANK = 0 and IOCON.SEQOP = 0
            class MCP23017
                    : public core::io::i2c::I2CMasterDevice
            {
                private:
                    /// Register addresses used when IOCON.BANK = 0
                    enum Register_BANK0
                            : uint8_t
                    {
                        B0_IODIRA = 0x00,
                        B0_IODIRB = 0x01,
                        B0_IPOLA = 0x02,
                        B0_IPOLB = 0x03,
                        B0_GPINTENA = 0x04,
                        B0_GPINTENB = 0x05,
                        B0_DEFVALA = 0x06,
                        B0_DEFVALB = 0x07,
                        B0_INTCONA = 0x08,
                        B0_INTCONB = 0x09,
                        B0_IOCON = 0x0A,
                        //B0_IOCON = 0x0B, // Second location
                                B0_GPPUA = 0x0C,
                        B0_GPPUB = 0x0D,
                        B0_INTFA = 0x0E,
                        B0_INTFB = 0x0F,
                        B0_INTCAPA = 0x10,
                        B0_INTCAPB = 0x11,
                        B0_GPIOA = 0x12,
                        B0_GPIOB = 0x13,
                        B0_OLATA = 0x14,
                        B0_OLATB = 0x15
                    };

                    /// Register addresses used when IOCON.BANK = 1
                    enum Register_BANK1
                            : uint8_t
                    {
                        B1_IODIRA = 0x00,
                        B1_IPOLA = 0x01,
                        B1_GPINTENA = 0x02,
                        B1_DEFVALA = 0x03,
                        B1_INTCONA = 0x04,
                        B1_IOCON = 0x05,
                        B1_GPPUA = 0x06,
                        B1_INTFA = 0x07,
                        B1_INTCAPA = 0x08,
                        B1_GPIOA = 0x09,
                        B1_OLATA = 0x0A,
                        B1_IODIRB = 0x10,
                        B1_IPOLB = 0x11,
                        B1_GPINTENB = 0x12,
                        B1_DEFVALB = 0x13,
                        B1_INTCONB = 0x14,
                        //B1_IOCON = 0x15, // Second location
                                B1_GPPUB = 0x16,
                        B1_INTFB = 0x17,
                        B1_INTCAPB = 0x18,
                        B1_GPIOB = 0x19,
                        B1_OLATB = 0x1A,
                    };

                public:
                    enum Port
                    {
                        A,
                        B
                    };

                    MCP23017(i2c_port_t port, uint8_t address, core::ipc::Mutex& guard);

                    /// Puts the device into a known state where IOCON.BANK = 0
                    /// @note Unless you have specifically set IOCON.BANK=1, there is no need to call this method
                    /// as the device defaults to IOCON.BANK = 0 on POR.
                    /// \param enable_portb_int7 Set true if PORTB.INT7 should be enabled afterwards
                    /// \return true on success, false on failure
                    bool put_device_into_known_state(bool enable_portb_int7);

                    /// Configures the I/O ports.
                    /// \param port_a_direction A bit mask where 0 is output, 1 is input, for port A.
                    /// \param input_a_pullup For I/O configured as input, enable internal pull-up if the corresponding bit is set.
                    /// \param input_a_polarity For I/O configured as input, report the inverted read state if the corresponding bit is set. For port A.
                    /// \param port_b_direction A bit mask where 0 is output, 1 is input, for port B.
                    /// \param input_b_pullup For I/O that is configured as input, enable internal pull-up if the corresponding bit is set.
                    /// \param input_b_polarity For I/O configured as input, report the inverted read state if the corresponding bit is set. For port B.
                    /// \return true on success, false on failure
                    bool configure_ports(uint8_t port_a_direction,
                                            uint8_t input_a_pull_up,
                                            uint8_t input_a_polarity,
                                            uint8_t port_b_direction,
                                            uint8_t input_b_pull_up,
                                            uint8_t input_b_polarity);

                    /// Sets the output state
                    /// \param port The port
                    /// \param state The state, where 1 is
                    /// \return tru on success, false on failure.
                    bool set_output(Port port, uint8_t state);

                private:

            };
        }
    }
}