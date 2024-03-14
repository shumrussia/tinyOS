
#ifndef __TINYOS__DRIVERS__MOUSE_H
#define __TINYOS__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <hardwarecommunication/interrupts.h>

namespace tinyos
{
    namespace drivers
    {
    
        class MouseEventHandler
        {
        public:
            MouseEventHandler();

            virtual void OnActivate();
            virtual void OnMouseDown(tinyos::common::uint8_t button);
            virtual void OnMouseUp(tinyos::common::uint8_t button);
            virtual void OnMouseMove(int x, int y);
        };
        
        
        class MouseDriver : public tinyos::hardwarecommunication::InterruptHandler, public Driver
        {
            tinyos::hardwarecommunication::Port8Bit dataport;
            tinyos::hardwarecommunication::Port8Bit commandport;
            tinyos::common::uint8_t buffer[3];
            tinyos::common::uint8_t offset;
            tinyos::common::uint8_t buttons;

            MouseEventHandler* handler;
        public:
            MouseDriver(tinyos::hardwarecommunication::InterruptManager* manager, MouseEventHandler* handler);
            ~MouseDriver();
            virtual tinyos::common::uint32_t HandleInterrupt(tinyos::common::uint32_t esp);
            virtual void Activate();
        };

    }
}
    
#endif