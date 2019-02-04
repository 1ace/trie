#include "lib.h"

#include <stdio.h>
#define MOCK_FUNCTION(f) \
  static void f(void) \
  { \
    printf("%s() called\n", #f); \
  }

MOCK_FUNCTION(eglBindAPI)
MOCK_FUNCTION(eglBindTexImage)
MOCK_FUNCTION(eglBindWaylandDisplayWL)
MOCK_FUNCTION(eglChooseConfig)
MOCK_FUNCTION(eglClientWaitSync)
MOCK_FUNCTION(eglClientWaitSyncKHR)
MOCK_FUNCTION(eglCopyBuffers)
MOCK_FUNCTION(eglCreateContext)
MOCK_FUNCTION(eglCreateDRMImageMESA)
MOCK_FUNCTION(eglCreateImage)
MOCK_FUNCTION(eglCreateImageKHR)
MOCK_FUNCTION(eglCreatePbufferFromClientBuffer)
MOCK_FUNCTION(eglCreatePbufferSurface)
MOCK_FUNCTION(eglCreatePixmapSurface)
MOCK_FUNCTION(eglCreatePlatformPixmapSurface)
MOCK_FUNCTION(eglCreatePlatformPixmapSurfaceEXT)
MOCK_FUNCTION(eglCreatePlatformWindowSurface)
MOCK_FUNCTION(eglCreatePlatformWindowSurfaceEXT)
MOCK_FUNCTION(eglCreateSync)
MOCK_FUNCTION(eglCreateSync64KHR)
MOCK_FUNCTION(eglCreateSyncKHR)
MOCK_FUNCTION(eglCreateWaylandBufferFromImageWL)
MOCK_FUNCTION(eglCreateWindowSurface)
MOCK_FUNCTION(eglDebugMessageControlKHR)
MOCK_FUNCTION(eglDestroyContext)
MOCK_FUNCTION(eglDestroyImage)
MOCK_FUNCTION(eglDestroyImageKHR)
MOCK_FUNCTION(eglDestroySurface)
MOCK_FUNCTION(eglDestroySync)
MOCK_FUNCTION(eglDestroySyncKHR)
MOCK_FUNCTION(eglDupNativeFenceFDANDROID)
MOCK_FUNCTION(eglExportDMABUFImageMESA)
MOCK_FUNCTION(eglExportDMABUFImageQueryMESA)
MOCK_FUNCTION(eglExportDRMImageMESA)
MOCK_FUNCTION(eglGetConfigAttrib)
MOCK_FUNCTION(eglGetConfigs)
MOCK_FUNCTION(eglGetCurrentContext)
MOCK_FUNCTION(eglGetCurrentDisplay)
MOCK_FUNCTION(eglGetCurrentSurface)
MOCK_FUNCTION(eglGetDisplay)
MOCK_FUNCTION(eglGetDisplayDriverConfig)
MOCK_FUNCTION(eglGetDisplayDriverName)
MOCK_FUNCTION(eglGetError)
MOCK_FUNCTION(eglGetPlatformDisplay)
MOCK_FUNCTION(eglGetPlatformDisplayEXT)
MOCK_FUNCTION(eglGetProcAddress)
MOCK_FUNCTION(eglGetSyncAttrib)
MOCK_FUNCTION(eglGetSyncAttribKHR)
MOCK_FUNCTION(eglGetSyncValuesCHROMIUM)
MOCK_FUNCTION(eglInitialize)
MOCK_FUNCTION(eglLabelObjectKHR)
MOCK_FUNCTION(eglMakeCurrent)
MOCK_FUNCTION(eglPostSubBufferNV)
MOCK_FUNCTION(eglQueryAPI)
MOCK_FUNCTION(eglQueryContext)
MOCK_FUNCTION(eglQueryDebugKHR)
MOCK_FUNCTION(eglQueryDeviceAttribEXT)
MOCK_FUNCTION(eglQueryDeviceStringEXT)
MOCK_FUNCTION(eglQueryDevicesEXT)
MOCK_FUNCTION(eglQueryDisplayAttribEXT)
MOCK_FUNCTION(eglQueryDmaBufFormatsEXT)
MOCK_FUNCTION(eglQueryDmaBufModifiersEXT)
MOCK_FUNCTION(eglQueryString)
MOCK_FUNCTION(eglQuerySurface)
MOCK_FUNCTION(eglQueryWaylandBufferWL)
MOCK_FUNCTION(eglReleaseTexImage)
MOCK_FUNCTION(eglReleaseThread)
MOCK_FUNCTION(eglSetBlobCacheFuncsANDROID)
MOCK_FUNCTION(eglSetDamageRegionKHR)
MOCK_FUNCTION(eglSignalSyncKHR)
MOCK_FUNCTION(eglSurfaceAttrib)
MOCK_FUNCTION(eglSwapBuffers)
MOCK_FUNCTION(eglSwapBuffersRegionNOK)
MOCK_FUNCTION(eglSwapBuffersWithDamageEXT)
MOCK_FUNCTION(eglSwapBuffersWithDamageKHR)
MOCK_FUNCTION(eglSwapInterval)
MOCK_FUNCTION(eglTerminate)
MOCK_FUNCTION(eglUnbindWaylandDisplayWL)
MOCK_FUNCTION(eglWaitClient)
MOCK_FUNCTION(eglWaitGL)
MOCK_FUNCTION(eglWaitNative)
MOCK_FUNCTION(eglWaitSync)
MOCK_FUNCTION(eglWaitSyncKHR)

#undef MOCK_FUNCTION



#include "egl_trie.h"

bool
lib_fetch(char const * const name, void const * * const value)
{
  return egl_fetch(name, value);
}
