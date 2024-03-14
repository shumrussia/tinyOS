
#include <filesystem/msdospart.h>

#include <filesystem/fat.h>

using namespace tinyos;
using namespace tinyos::common;
using namespace tinyos::drivers;
using namespace tinyos::filesystem;


void printf(char*);
void printfHex(uint8_t);

void MSDOSPartitionTable::ReadPartitions(tinyos::drivers::AdvancedTechnologyAttachment *hd)
{
    MasterBootRecord mbr;
    hd->Read28(0, (uint8_t*)&mbr, sizeof(MasterBootRecord));

    // printf("MBR: ");
    // for(int i = 446; i < 446 + 4*16; i++)
    // {
    //     printfHex(((uint8_t*)&mbr)[i]);
    //     printf(" ");
    // }
    // printf("\n");

    if(mbr.magicnumber != 0xAA55)
    {
        printf("illegal MBR");
        return;
    }

    for(int i = 0; i < 4; i++)
    {
        if(mbr.primaryPartition[i].partition_id == 0)
            continue;

        printf(" Partition ");
        printfHex(i & 0xFF);

        if(mbr.primaryPartition[i].bootable == 0x80)
            printf("bootable");
        else
            printf("not bootable");

        printfHex(mbr.primaryPartition[i].partition_id);

        ReadBiosBlock(hd, mbr.primaryPartition[i].start_lba);
    }

};
