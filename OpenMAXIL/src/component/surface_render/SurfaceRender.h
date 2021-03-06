/**
 *  Copyright (c) 2011-2013, Freescale Semiconductor Inc.,
 *  All Rights Reserved.
 *
 *  The following programs are the sole property of Freescale Semiconductor Inc.,
 *  and contain its proprietary and confidential information.
 *
 */

#ifndef SurfaceRender_h
#define SurfaceRender_h

//#include <surfaceflinger/ISurface.h>
#include <cutils/log.h>

#include "gralloc_priv.h"

#include "VideoRender.h"

#if (ANDROID_VERSION <= ICS)
#include "ui/android_native_buffer.h"
#include <surfaceflinger/ISurface.h>
#include <android_natives.h>
#include "Surface.h"
#elif (ANDROID_VERSION == JELLY_BEAN_42)
#include <gui/ISurface.h>
#include <gui/Surface.h>
#elif (ANDROID_VERSION >= JELLY_BEAN_43)
#include <gui/Surface.h>
#endif

#define MAX_SURFACE_BUFFER 25

using android::sp;
#if (ANDROID_VERSION <= JELLY_BEAN_42)
using android::ISurface;
#endif
using android::Surface;

enum OWNER_TYPE{
    OWNER_VPU,
    OWNER_RENDER,
    OWNER_SURFACE,
};

/* display framebuffer type */
typedef struct {
    OMX_U32 nLength;
    OMX_PTR pVirtualAddr;
    OMX_PTR pPhyiscAddr;
    android_native_buffer_t* pNativeBufferT;
    OMX_BUFFERHEADERTYPE * pOMXBufferHdr;
    OWNER_TYPE owner;
    OMX_BOOL bReturned;
}FB_DATA;

class SurfaceRender : public VideoRender {
    public:
        SurfaceRender();
    private:
        OMX_BOOL bFrameBufferInit;
        OMX_U32 nFrameBuffer;
        OMX_U32 nAllocating;
        FB_DATA fb_data[MAX_SURFACE_BUFFER];
        fsl_osal_mutex lock;
        OMX_CONFIG_CAPTUREFRAME sCapture;
        OMX_S32 EnqueueBufferIdx;
        OMX_CONFIG_OUTPUTMODE sOutputMode;
        OMX_BOOL bCaptureFrameDone;
        sp<Surface>     mSurface;
        sp<ANativeWindow> nativeWindow;
        OMX_U32 nEnqueuedBuffers;
        int nMinUndequeuedBuffers;
        OMX_BOOL bSuspend;
        OMX_U32 mBufferUsage;
        OMX_S32 mScalingMode;
        OMX_BOOL bFirstRender;
        OMX_U32 nFrameNumber;


        OMX_ERRORTYPE InitRenderComponent();
        OMX_ERRORTYPE DeInitRenderComponent();
        OMX_ERRORTYPE RenderGetConfig(OMX_INDEXTYPE nParamIndex, OMX_PTR pStructure);
        OMX_ERRORTYPE RenderSetConfig(OMX_INDEXTYPE nParamIndex, OMX_PTR pStructure);
        OMX_ERRORTYPE PortFormatChanged(OMX_U32 nPortIndex);
        OMX_ERRORTYPE DoAllocateBuffer(OMX_PTR *buffer, OMX_U32 nSize,OMX_U32 nPortIndex);
        OMX_ERRORTYPE DoFreeBuffer(OMX_PTR buffer,OMX_U32 nPortIndex);
        OMX_ERRORTYPE OpenDevice();
        OMX_ERRORTYPE CloseDevice();
        OMX_ERRORTYPE WriteDevice(OMX_BUFFERHEADERTYPE *pBufferHdr);
        OMX_ERRORTYPE CaptureFrame(OMX_U32 nIndex);
        OMX_ERRORTYPE SetOutputMode();
        OMX_ERRORTYPE SetDeviceInputCrop();
        OMX_ERRORTYPE SetScalingMode();
        OMX_ERRORTYPE SetDeviceRotation();
        OMX_ERRORTYPE BufferInit();
        OMX_ERRORTYPE BufferDeInit();
        OMX_ERRORTYPE SearchBuffer(OMX_BUFFERHEADERTYPE *pBufferHdr, OMX_U32 *pIndex);
        OMX_ERRORTYPE SearchBuffer(android_native_buffer_t *pNativeBufferT, OMX_U32 *pIndex);
        OMX_ERRORTYPE FlushComponent( OMX_U32 nPortIndex);
        OMX_U8 GetDequeuedBufferNumber();
        OMX_U32 GetDeviceDropFames();
        OMX_ERRORTYPE CleanBufferContent(OMX_U32 index);
        void CleanCropContent(OMX_U32 index);
};
#endif
/* File EOF */
