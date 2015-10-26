/*
 *  linux/init/sc_module.c
 *
 *  Copyright (C) 2008  Andic
 *
 */
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/ctype.h>
#include <linux/vmalloc.h>

#include "linux/LzmaDecode.h"
#include "linux/sc_module.h"
#include "MyLzmaDecode.c"

sc_entry_t ap3050_entry;

#ifdef _SC_MODULE_
#define MODULE_START_ADDR (0)
#define MODULE_COMPRESSED_SIZE (4)

#define SC_INFO_START_ADDR (0x1FFFC0)

static unsigned char posandSize[8];
unsigned char *outStream = NULL;
SizeT outProcessed;

static long read_buf_pos = 0;

static int PrintError(const char *message)
{
    printk("%s\n", message); 
    return 1;
}

static void MyReadBuf(char *src, char *dst, long len)
{
    memcpy(dst, src + read_buf_pos, len);
    read_buf_pos += len;
}


static int uncompress_buf(unsigned char *inStream, long len)
{
    /* We use two 32-bit integers to construct 64-bit integer for file size.
     You can remove outSizeHigh, if you don't need >= 4GB supporting,
     or you can use UInt64 outSize, if your compiler supports 64-bit integers*/
    UInt32 outSize = 0;
    UInt32 outSizeHigh = 0;
    SizeT outSizeFull;
    int waitEOS = 1; 
    /* waitEOS = 1, if there is no uncompressed size in headers, 
    so decoder will wait EOS (End of Stream Marker) in compressed stream */
    int res = 0;
    
    SizeT compressedSize;
    CLzmaDecoderState state;  /* it's about 24-80 bytes structure, if int is 32-bit */
    unsigned char properties[LZMA_PROPERTIES_SIZE];
    
    
    if(sizeof(UInt32) < 4)
        return PrintError("LZMA decoder needs correct UInt32");

    {
        long length;
        
        length = len;
        
        if((long)(SizeT)length != length)
            return PrintError("Too big compressed stream");
            
        compressedSize = (SizeT)(length - (LZMA_PROPERTIES_SIZE + 8));
    }

  /* Read LZMA properties for compressed stream */
    MyReadBuf(inStream, properties, sizeof(properties));

  /* Read uncompressed size */
    {
        int i;
        
        for(i = 0; i < 8; i++)
        {
            unsigned char b;
            
            MyReadBuf(inStream, &b, 1);
            
            if(b != 0xFF)
                waitEOS = 0;
                
            if(i < 4)
                outSize += (UInt32)(b) << (i * 8);
            else
                outSizeHigh += (UInt32)(b) << ((i - 4) * 8);
        }
        
        if(waitEOS)
            return PrintError("Stream with EOS marker is not supported");
            
        outSizeFull = (SizeT)outSize;
        
        if(sizeof(SizeT) >= 8)
            outSizeFull |= (((SizeT)outSizeHigh << 16) << 16);
        else if(outSizeHigh != 0 || (UInt32)(SizeT)outSize != outSize)
            return PrintError("Too big uncompressed stream");
    }

  /* Decode LZMA properties and allocate memory */
  
    if(LzmaDecodeProperties(&state.Properties, properties, LZMA_PROPERTIES_SIZE) != LZMA_RESULT_OK)
        return PrintError("Incorrect stream properties");
        
    state.Probs = (CProb *)kmalloc(LzmaGetNumProbs(&state.Properties) * sizeof(CProb), GFP_KERNEL);

    if(outSizeFull == 0)
        outStream = 0;
    else
        outStream = (unsigned char *)vmalloc(outSizeFull);

    if(state.Probs == 0 
        || (outStream == 0 && outSizeFull != 0)
        || (inStream == 0 && compressedSize != 0))
    {
        kfree(state.Probs);
        
        return 1;
    }

  /* Decompress */
    {
        SizeT inProcessed;
        
        res = MyLzmaDecode(&state, inStream + LZMA_PROPERTIES_SIZE + 8, compressedSize, 
                &inProcessed, outStream, outSizeFull, &outProcessed);
        
        if(res != 0)
            PrintError("Decoding error");
    }

    kfree(state.Probs);

    return res;
}

static void init_sercomm_entry(void)
{
    ap3050_entry.sc_os_entry = NULL;
    ap3050_entry.sc_os_rcv = NULL;
}

void insert_sc_module(void)
{
    unsigned long module_pos, module_size;
    int max_module_num = 8;
    int n, addr;
    char *pCompress;
        
    init_sercomm_entry();
    
    addr = SC_INFO_START_ADDR;
    for(n = 0; n < max_module_num; n++){
        FlashRead(posandSize, addr, sizeof(posandSize));
        
        module_pos= *((unsigned long *)(&posandSize[MODULE_START_ADDR]));
        module_size= *((unsigned long *)(&posandSize[MODULE_COMPRESSED_SIZE]));
        
        if(module_pos == 0 || module_pos == 0xFFFFFFFF)
            break;
            
        if(!(pCompress = vmalloc(module_size)))
            return;
            
        FlashRead(pCompress, module_pos, module_size);
        
        read_buf_pos = 0;
        if(!uncompress_buf(pCompress, module_size)){
            sinux_init_module(outStream, (long)outProcessed, "");
            vfree(outStream);
        }
            
        vfree(pCompress);
        addr += sizeof(posandSize);
    }
}

#endif

void insert_sc_os_entry(void (*p)(void))
{
    ap3050_entry.sc_os_entry = p;
}

void insert_sc_os_rcv(int (*p)(struct sk_buff *skb))
{
    ap3050_entry.sc_os_rcv = p;
}

int run_sc_os_rcv(struct sk_buff *skb)
{
    if(ap3050_entry.sc_os_rcv)
        return ap3050_entry.sc_os_rcv(skb);
    else
        return NET_RX_DROP;        
}

void run_sc_os_entry(void)
{
    if(ap3050_entry.sc_os_entry)
        ap3050_entry.sc_os_entry();
}

EXPORT_SYMBOL(insert_sc_os_rcv);
EXPORT_SYMBOL(insert_sc_os_entry);
