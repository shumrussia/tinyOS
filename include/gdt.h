#ifndef __TINYOS__GDT_H
#define __TINYOS__GDT_H

#include <common/types.h>

namespace tinyos
{
    
    class GlobalDescriptorTable
    {
        public:

            class SegmentDescriptor
            {
                private:
                    tinyos::common::uint16_t limit_lo;
                    tinyos::common::uint16_t base_lo;
                    tinyos::common::uint8_t base_hi;
                    tinyos::common::uint8_t type;
                    tinyos::common::uint8_t limit_hi;
                    tinyos::common::uint8_t base_vhi;

                public:
                    SegmentDescriptor(tinyos::common::uint32_t base, tinyos::common::uint32_t limit, tinyos::common::uint8_t type);
                    tinyos::common::uint32_t Base();
                    tinyos::common::uint32_t Limit();
            } __attribute__((packed));

        private:
            SegmentDescriptor nullSegmentSelector;
            SegmentDescriptor unusedSegmentSelector;
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector;

        public:

            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            tinyos::common::uint16_t CodeSegmentSelector();
            tinyos::common::uint16_t DataSegmentSelector();
    };

}
    
#endif