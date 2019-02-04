#include "lib.h"
#include "stdio.h"

typedef void (func)(void);

int main(void) {
#define EXPECT_SUCCESS(f) \
  func* f; \
  if (lib_fetch(#f, (void*)&f)) { \
    printf("%s found as expected: %p\n", #f, f); \
    f(); \
  } \
  else { \
    printf("%s should exist but doesn't\n", #f); \
    return 1; \
  }

#define EXPECT_FAIL(f) \
  func* f; \
  if (lib_fetch(#f, (void*)&f)) { \
    printf("%s should not exist but does: %p\n", #f, f); \
    return 2; \
  }

  EXPECT_SUCCESS(eglBindAPI);
  EXPECT_SUCCESS(eglBindTexImage);
  EXPECT_SUCCESS(eglBindWaylandDisplayWL);
  EXPECT_SUCCESS(eglChooseConfig);
  EXPECT_SUCCESS(eglClientWaitSync);
  EXPECT_SUCCESS(eglClientWaitSyncKHR);
  EXPECT_SUCCESS(eglCopyBuffers);
  EXPECT_SUCCESS(eglCreateContext);
  EXPECT_SUCCESS(eglCreateDRMImageMESA);
  EXPECT_SUCCESS(eglCreateImage);
  EXPECT_SUCCESS(eglCreateImageKHR);
  EXPECT_SUCCESS(eglCreatePbufferFromClientBuffer);
  EXPECT_SUCCESS(eglCreatePbufferSurface);
  EXPECT_SUCCESS(eglCreatePixmapSurface);
  EXPECT_SUCCESS(eglCreatePlatformPixmapSurface);
  EXPECT_SUCCESS(eglCreatePlatformPixmapSurfaceEXT);
  EXPECT_SUCCESS(eglCreatePlatformWindowSurface);
  EXPECT_SUCCESS(eglCreatePlatformWindowSurfaceEXT);
  EXPECT_SUCCESS(eglCreateSync);
  EXPECT_SUCCESS(eglCreateSync64KHR);
  EXPECT_SUCCESS(eglCreateSyncKHR);
  EXPECT_SUCCESS(eglCreateWaylandBufferFromImageWL);
  EXPECT_SUCCESS(eglCreateWindowSurface);
  EXPECT_SUCCESS(eglDebugMessageControlKHR);
  EXPECT_SUCCESS(eglDestroyContext);
  EXPECT_SUCCESS(eglDestroyImage);
  EXPECT_SUCCESS(eglDestroyImageKHR);
  EXPECT_SUCCESS(eglDestroySurface);
  EXPECT_SUCCESS(eglDestroySync);
  EXPECT_SUCCESS(eglDestroySyncKHR);
  EXPECT_SUCCESS(eglDupNativeFenceFDANDROID);
  EXPECT_SUCCESS(eglExportDMABUFImageMESA);
  EXPECT_SUCCESS(eglExportDMABUFImageQueryMESA);
  EXPECT_SUCCESS(eglExportDRMImageMESA);
  EXPECT_SUCCESS(eglGetConfigAttrib);
  EXPECT_SUCCESS(eglGetConfigs);
  EXPECT_SUCCESS(eglGetCurrentContext);
  EXPECT_SUCCESS(eglGetCurrentDisplay);
  EXPECT_SUCCESS(eglGetCurrentSurface);
  EXPECT_SUCCESS(eglGetDisplay);
  EXPECT_SUCCESS(eglGetDisplayDriverConfig);
  EXPECT_SUCCESS(eglGetDisplayDriverName);
  EXPECT_SUCCESS(eglGetError);
  EXPECT_SUCCESS(eglGetPlatformDisplay);
  EXPECT_SUCCESS(eglGetPlatformDisplayEXT);
  EXPECT_SUCCESS(eglGetProcAddress);
  EXPECT_SUCCESS(eglGetSyncAttrib);
  EXPECT_SUCCESS(eglGetSyncAttribKHR);
  EXPECT_SUCCESS(eglGetSyncValuesCHROMIUM);
  EXPECT_SUCCESS(eglInitialize);
  EXPECT_SUCCESS(eglLabelObjectKHR);
  EXPECT_SUCCESS(eglMakeCurrent);
  EXPECT_SUCCESS(eglPostSubBufferNV);
  EXPECT_SUCCESS(eglQueryAPI);
  EXPECT_SUCCESS(eglQueryContext);
  EXPECT_SUCCESS(eglQueryDebugKHR);
  EXPECT_SUCCESS(eglQueryDeviceAttribEXT);
  EXPECT_SUCCESS(eglQueryDeviceStringEXT);
  EXPECT_SUCCESS(eglQueryDevicesEXT);
  EXPECT_SUCCESS(eglQueryDisplayAttribEXT);
  EXPECT_SUCCESS(eglQueryDmaBufFormatsEXT);
  EXPECT_SUCCESS(eglQueryDmaBufModifiersEXT);
  EXPECT_SUCCESS(eglQueryString);
  EXPECT_SUCCESS(eglQuerySurface);
  EXPECT_SUCCESS(eglQueryWaylandBufferWL);
  EXPECT_SUCCESS(eglReleaseTexImage);
  EXPECT_SUCCESS(eglReleaseThread);
  EXPECT_SUCCESS(eglSetBlobCacheFuncsANDROID);
  EXPECT_SUCCESS(eglSetDamageRegionKHR);
  EXPECT_SUCCESS(eglSignalSyncKHR);
  EXPECT_SUCCESS(eglSurfaceAttrib);
  EXPECT_SUCCESS(eglSwapBuffers);
  EXPECT_SUCCESS(eglSwapBuffersRegionNOK);
  EXPECT_SUCCESS(eglSwapBuffersWithDamageEXT);
  EXPECT_SUCCESS(eglSwapBuffersWithDamageKHR);
  EXPECT_SUCCESS(eglSwapInterval);
  EXPECT_SUCCESS(eglTerminate);
  EXPECT_SUCCESS(eglUnbindWaylandDisplayWL);
  EXPECT_SUCCESS(eglWaitClient);
  EXPECT_SUCCESS(eglWaitGL);
  EXPECT_SUCCESS(eglWaitNative);
  EXPECT_SUCCESS(eglWaitSync);
  EXPECT_SUCCESS(eglWaitSyncKHR);

  EXPECT_FAIL(eglGetErrorSUFFIX);
  EXPECT_FAIL(glGetError);
  EXPECT_FAIL(foo);

  return 0;
}
