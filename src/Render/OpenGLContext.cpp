#include <Render/OpenGLContext.h>
#include <iostream>


namespace vrv
{

// Defines from the WGL_ARB_pixel_format specification document
//https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt
#define WGL_DRAW_TO_WINDOW_ARB                  0x2001
#define WGL_SUPPORT_OPENGL_ARB                  0x2010
#define WGL_DOUBLE_BUFFER_ARB                   0x2011
#define WGL_PIXEL_TYPE_ARB                      0x2013
#define WGL_TYPE_RGBA_ARB                       0x202B
#define WGL_COLOR_BITS_ARB                      0x2014
#define WGL_DEPTH_BITS_ARB                      0x2022
#define WGL_STENCIL_BITS_ARB                    0x2023
#define WGL_CONTEXT_MAJOR_VERSION_ARB  0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB  0x2092


   //
   // Entry points used from the WGL extensions
   //
   //    BOOL wglChoosePixelFormatARB(HDC hdc,
   //                                 const int *piAttribIList,
   //                                 const FLOAT *pfAttribFList,
   //                                 UINT nMaxFormats,
   //                                 int *piFormats,
   //                                 UINT *nNumFormats);
   //
   typedef bool (WINAPI * WGLChoosePixelFormatARB) (HDC, const int *, const float *, unsigned int, int *, unsigned int *);

   //HGLRC wglCreateContextAttribsARB(HDC hDC, HGLRC hshareContext, const int *attribList);
   typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);

   OpenGLContext* OpenGLContext::myInstance = 0;

   OpenGLContext& OpenGLContext::instance()
   {
      return *myInstance;
   }

   OpenGLContext::OpenGLContext(HWND hWnd)
      : myWindowHandle(hWnd)
      , myContextHandle(0)
      , myMajorVersion(3)
      , myMinorVersion(3)
   {
      myInstance = this;
   }

   void OpenGLContext::initialize()
   {
      myDeviceContext = GetDC(myWindowHandle);
      if (myDeviceContext == 0)
      {
         std::cout << "Failed to get dc from window handle" << std::endl;
      }
      createContext();
   }

   bool OpenGLContext::makeCurrent()
   {
      if (wglMakeCurrent(myDeviceContext, myContextHandle))
      {
         return true;
      }

      return false;
   }

   bool OpenGLContext::createContext()
   {
      if (!setPixelFormat())
      {
         std::cout << "Failed to set pixel format" << std::endl;
         destroy();
         return false;
      }

      PFNWGLCREATECONTEXTATTRIBSARBPROC  wglCreateContextAttribsARB =
         (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
      if (wglCreateContextAttribsARB == 0)
      {
         std::cout << "Failed to find wglCreateContextAttribsARB proc address" << std::endl;
         return false;
      }

      const int attribList[] =
      {
          WGL_CONTEXT_MAJOR_VERSION_ARB, myMajorVersion,
          WGL_CONTEXT_MINOR_VERSION_ARB, myMinorVersion,
          0, // End
      };

      myContextHandle = wglCreateContextAttribsARB(myDeviceContext, 0, attribList);
      if (myContextHandle == 0)
      {
         std::cout << "Failed to create context" << std::endl;
         return false;
      }

      destorySampleContext();

      makeCurrent();

      retrieveOpenGLFunctions();

      std::cout << "Opengl version :" << glGetString(GL_VERSION) << std::endl;

      return true;
   }

   bool OpenGLContext::setPixelFormat()
   {
      if (makeSampleContextCurrent())
      {
         WGLChoosePixelFormatARB wglChoosePixelFormatARB = (WGLChoosePixelFormatARB)wglGetProcAddress("wglChoosePixelFormatARB");
         if (wglChoosePixelFormatARB == 0)
         {
            std::cout << "wglChoosePixelFormatARB proc not found" << std::endl;
            return false;
         }

         const int attribList[] =
         {
             WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
             WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
             WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
             WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
             WGL_COLOR_BITS_ARB, 32,
             WGL_DEPTH_BITS_ARB, 24,
             WGL_STENCIL_BITS_ARB, 8,
             0, // End
         };

         int pixelFormat;
         UINT numFormats;
         if (!wglChoosePixelFormatARB(mySampleDeviceHandle, attribList, NULL, 1, &pixelFormat, &numFormats))
         {
            return false;
         }

         if (numFormats == 0)
         {
            return false;
         }

         PIXELFORMATDESCRIPTOR pfd;
         ::memset(&pfd, 0, sizeof(pfd));
         pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
         pfd.nVersion = 1;

         if (!SetPixelFormat(myDeviceContext, pixelFormat, &pfd))
         {
            std::cout << "Failed to set pixel format" << std::endl;
            return false;
         }

         return true;
      }
   }

   bool OpenGLContext::makeSampleContextCurrent()
   {
      WNDCLASSEX wc;
      std::string className = "sample window";

      HINSTANCE hinst = GetModuleHandle(NULL);

      wc.cbSize = sizeof(wc);
      wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
      wc.lpfnWndProc = DefWindowProc;
      wc.cbClsExtra = 0;
      wc.cbWndExtra = 0;
      wc.hInstance = hinst;
      wc.hIcon = 0;
      wc.hCursor = 0;
      wc.hbrBackground = NULL;
      wc.lpszMenuName = 0;
      wc.lpszClassName = className.c_str();
      wc.hIconSm = NULL;

      if (::RegisterClassEx(&wc) == 0)
      {
         return false;
      }

      mySampleWindowHandle = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
         className.c_str(),
         NULL,
         WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_DISABLED,
         0,
         0,
         1,
         1,
         NULL,
         NULL,
         ::GetModuleHandle(NULL),
         NULL);

      if (mySampleWindowHandle == 0)
      {
         return false;
      }

      mySampleDeviceHandle = GetDC(mySampleWindowHandle);
      if (mySampleDeviceHandle == 0)
      {
         DestroyWindow(mySampleWindowHandle);
         return false;
      }

      PIXELFORMATDESCRIPTOR pixelFormat =
      {
          sizeof(PIXELFORMATDESCRIPTOR),
          1,
          PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
          PFD_TYPE_RGBA,
          24,
          0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0,
          24,
          0,
          0,
          PFD_MAIN_PLANE,
          0,
          0, 0, 0
      };

      int pixelFormatIndex = ChoosePixelFormat(mySampleDeviceHandle, &pixelFormat);
      if (pixelFormatIndex == 0)
      {
         ReleaseDC(mySampleWindowHandle, mySampleDeviceHandle);
         DestroyWindow(mySampleWindowHandle);
         return false;
      }

      if (!SetPixelFormat(mySampleDeviceHandle, pixelFormatIndex, &pixelFormat))
      {
         ReleaseDC(mySampleWindowHandle, mySampleDeviceHandle);
         DestroyWindow(mySampleWindowHandle);
         return false;
      }

      mySampleContextHandle = wglCreateContext(mySampleDeviceHandle);
      if (mySampleContextHandle == 0)
      {
         ReleaseDC(mySampleWindowHandle, mySampleDeviceHandle);
         DestroyWindow(mySampleWindowHandle);
         return false;
      }

      if (!wglMakeCurrent(mySampleDeviceHandle, mySampleContextHandle))
      {
         wglMakeCurrent(mySampleDeviceHandle, NULL);
         wglDeleteContext(mySampleContextHandle);
         ReleaseDC(mySampleWindowHandle, mySampleDeviceHandle);
         DestroyWindow(mySampleWindowHandle);
         return false;
      }

      return true;
   }

   void OpenGLContext::destorySampleContext()
   {
      if (mySampleContextHandle && mySampleDeviceHandle)
      {
         wglMakeCurrent(mySampleDeviceHandle, NULL);
         wglDeleteContext(mySampleContextHandle);
         mySampleContextHandle = 0;
      }

      if (mySampleDeviceHandle && mySampleWindowHandle)
      {
         ReleaseDC(mySampleWindowHandle, mySampleDeviceHandle);
      }

      if (mySampleWindowHandle)
      {
         DestroyWindow(mySampleWindowHandle);
         mySampleWindowHandle = 0;
      }
   }

   void OpenGLContext::destroy()
   {
      if (myContextHandle && myDeviceContext)
      {
         wglMakeCurrent(myDeviceContext, NULL);
         wglDeleteContext(myContextHandle);
         myContextHandle = 0;
      }

      if (myDeviceContext && myWindowHandle)
      {
         ReleaseDC(myWindowHandle, myDeviceContext);
      }

      if (myWindowHandle)
      {
         DestroyWindow(myWindowHandle);
         myWindowHandle = 0;
      }
   }

   template<typename T, typename R>
   bool convertPointer(T& dest, R src)
   {
      memcpy(&dest, &src, sizeof(src));
      return src != 0;
   }

   void OpenGLContext::retrieveOpenGLFunctions()
   {
      if (!convertPointer(glGenBuffers, (void*)wglGetProcAddress("glGenBuffers")))
      {
         std::cout << "Failed to get pointer for glGenBuffers " << std::endl;
      }
      if (!convertPointer(glBindBuffer, (void*)wglGetProcAddress("glBindBuffer")))
      {
         std::cout << "Failed to get pointer for glBindBuffer " << std::endl;
      }
      if (!convertPointer(glBufferData, (void*)wglGetProcAddress("glBufferData")))
      {
         std::cout << "Failed to get pointer for glBufferData " << std::endl;
      }
      if (!convertPointer(glDeleteBuffers, (void*)wglGetProcAddress("glDeleteBuffers")))
      {
         std::cout << "Failed to get pointer for glDeleteBuffers " << std::endl;
      }
      if (!convertPointer(glBufferSubData, (void*)wglGetProcAddress("glBufferSubData")))
      {
         std::cout << "Failed to get pointer for glBufferSubData " << std::endl;
      }
      if (!convertPointer(glDrawArraysInstanced, (void*)wglGetProcAddress("glDrawArraysInstanced")))
      {
         std::cout << "Failed to get pointer for glDrawArraysInstanced " << std::endl;
      }
      if (!convertPointer(glDrawElementsInstanced, (void*)wglGetProcAddress("glDrawElementsInstanced")))
      {
         std::cout << "Failed to get pointer for glDrawElementsInstanced " << std::endl;
      }
      if (!convertPointer(glFramebufferTexture2D, (void*)wglGetProcAddress("glFramebufferTexture2D")))
      {
         std::cout << "Failed to get pointer for glFramebufferTexture2D " << std::endl;
      }
      if (!convertPointer(glFramebufferRenderbuffer, (void*)wglGetProcAddress("glFramebufferRenderbuffer")))
      {
         std::cout << "Failed to get pointer for glFramebufferRenderbuffer " << std::endl;
      }
      if (!convertPointer(glBindRenderbuffer, (void*)wglGetProcAddress("glBindRenderbuffer")))
      {
         std::cout << "Failed to get pointer for glBindRenderbuffer " << std::endl;
      }
      if (!convertPointer(glGenRenderbuffers, (void*)wglGetProcAddress("glGenRenderbuffers")))
      {
         std::cout << "Failed to get pointer for glGenRenderbuffers " << std::endl;
      }
      if (!convertPointer(glRenderbufferStorage, (void*)wglGetProcAddress("glRenderbufferStorage")))
      {
         std::cout << "Failed to get pointer for glRenderbufferStorage " << std::endl;
      }
      if (!convertPointer(glGenFramebuffers, (void*)wglGetProcAddress("glGenFramebuffers")))
      {
         std::cout << "Failed to get pointer for glGenFramebuffers " << std::endl;
      }
      if (!convertPointer(glBindFramebuffer, (void*)wglGetProcAddress("glBindFramebuffer")))
      {
         std::cout << "Failed to get pointer for glBindFramebuffer " << std::endl;
      }
      if (!convertPointer(glDeleteFramebuffers, (void*)wglGetProcAddress("glDeleteFramebuffers")))
      {
         std::cout << "Failed to get pointer for glDeleteFramebuffers " << std::endl;
      }
      if (!convertPointer(glDrawBuffers, (void*)wglGetProcAddress("glDrawBuffers")))
      {
         std::cout << "Failed to get pointer for glDrawBuffers " << std::endl;
      }
      if (!convertPointer(glCheckFramebufferStatus, (void*)wglGetProcAddress("glCheckFramebufferStatus")))
      {
         std::cout << "Failed to get pointer for glCheckFramebufferStatus " << std::endl;
      }
      if (!convertPointer(glActiveTexture, (void*)wglGetProcAddress("glActiveTexture")))
      {
         std::cout << "Failed to get pointer for glActiveTexture " << std::endl;
      }
      if (!convertPointer(glDeleteProgram, (void*)wglGetProcAddress("glDeleteProgram")))
      {
         std::cout << "Failed to get pointer for glDeleteProgram " << std::endl;
      }
      if (!convertPointer(glGetProgramiv, (void*)wglGetProcAddress("glGetProgramiv")))
      {
         std::cout << "Failed to get pointer for glGetProgramiv " << std::endl;
      }
      if (!convertPointer(glGetProgramInfoLog, (void*)wglGetProcAddress("glGetProgramInfoLog")))
      {
         std::cout << "Failed to get pointer for glGetProgramInfoLog " << std::endl;
      }
      if (!convertPointer(glUseProgram, (void*)wglGetProcAddress("glUseProgram")))
      {
         std::cout << "Failed to get pointer for glUseProgram " << std::endl;
      }
      if (!convertPointer(glGetUniformBlockIndex, (void*)wglGetProcAddress("glGetUniformBlockIndex")))
      {
         std::cout << "Failed to get pointer for glGetUniformBlockIndex " << std::endl;
      }
      if (!convertPointer(glUniformBlockBinding, (void*)wglGetProcAddress("glUniformBlockBinding")))
      {
         std::cout << "Failed to get pointer for glUniformBlockBinding " << std::endl;
      }
      if (!convertPointer(glUniformBlockBinding, (void*)wglGetProcAddress("glUniformBlockBinding")))
      {
         std::cout << "Failed to get pointer for glUniformBlockBinding " << std::endl;
      }
      if (!convertPointer(glCreateProgram, (void*)wglGetProcAddress("glCreateProgram")))
      {
         std::cout << "Failed to get pointer for glCreateProgram " << std::endl;
      }
      if (!convertPointer(glAttachShader, (void*)wglGetProcAddress("glAttachShader")))
      {
         std::cout << "Failed to get pointer for glAttachShader " << std::endl;
      }
      if (!convertPointer(glLinkProgram, (void*)wglGetProcAddress("glLinkProgram")))
      {
         std::cout << "Failed to get pointer for glLinkProgram " << std::endl;
      }
      if (!convertPointer(glGetActiveUniform, (void*)wglGetProcAddress("glGetActiveUniform")))
      {
         std::cout << "Failed to get pointer for glGetActiveUniform " << std::endl;
      }
      if (!convertPointer(glGetUniformLocation, (void*)wglGetProcAddress("glGetUniformLocation")))
      {
         std::cout << "Failed to get pointer for glGetUniformLocation " << std::endl;
      }
      if (!convertPointer(glCreateShader, (void*)wglGetProcAddress("glCreateShader")))
      {
         std::cout << "Failed to get pointer for glCreateShader " << std::endl;
      }
      if (!convertPointer(glShaderSource, (void*)wglGetProcAddress("glShaderSource")))
      {
         std::cout << "Failed to get pointer for glShaderSource " << std::endl;
      }
      if (!convertPointer(glCompileShader, (void*)wglGetProcAddress("glCompileShader")))
      {
         std::cout << "Failed to get pointer for glCompileShader " << std::endl;
      }
      if (!convertPointer(glGetShaderiv, (void*)wglGetProcAddress("glGetShaderiv")))
      {
         std::cout << "Failed to get pointer for glGetShaderiv " << std::endl;
      }
      if (!convertPointer(glGetShaderInfoLog, (void*)wglGetProcAddress("glGetShaderInfoLog")))
      {
         std::cout << "Failed to get pointer for glGetShaderInfoLog " << std::endl;
      }
      if (!convertPointer(glActiveTexture, (void*)wglGetProcAddress("glActiveTexture")))
      {
         std::cout << "Failed to get pointer for glActiveTexture " << std::endl;
      }
      if (!convertPointer(glGenerateMipmap, (void*)wglGetProcAddress("glGenerateMipmap")))
      {
         std::cout << "Failed to get pointer for glGenerateMipmap " << std::endl;
      }
      if (!convertPointer(glUniform1i, (void*)wglGetProcAddress("glUniform1i")))
      {
         std::cout << "Failed to get pointer for glUniform1i " << std::endl;
      }
      if (!convertPointer(glUniform1f, (void*)wglGetProcAddress("glUniform1f")))
      {
         std::cout << "Failed to get pointer for glUniform1f " << std::endl;
      }
      if (!convertPointer(glUniform2f, (void*)wglGetProcAddress("glUniform2f")))
      {
         std::cout << "Failed to get pointer for glUniform2f " << std::endl;
      }
      if (!convertPointer(glUniform3f, (void*)wglGetProcAddress("glUniform3f")))
      {
         std::cout << "Failed to get pointer for glUniform3f " << std::endl;
      }
      if (!convertPointer(glUniform4f, (void*)wglGetProcAddress("glUniform4f")))
      {
         std::cout << "Failed to get pointer for glUniform4f " << std::endl;
      }
      if (!convertPointer(glUniformMatrix3fv, (void*)wglGetProcAddress("glUniformMatrix3fv")))
      {
         std::cout << "Failed to get pointer for glUniformMatrix3fv " << std::endl;
      }
      if (!convertPointer(glUniformMatrix4fv, (void*)wglGetProcAddress("glUniformMatrix4fv")))
      {
         std::cout << "Failed to get pointer for glUniformMatrix4fv " << std::endl;
      }
      if (!convertPointer(glBindBufferBase, (void*)wglGetProcAddress("glBindBufferBase")))
      {
         std::cout << "Failed to get pointer for glBindBufferBase " << std::endl;
      }
      if (!convertPointer(glGenVertexArrays, (void*)wglGetProcAddress("glGenVertexArrays")))
      {
         std::cout << "Failed to get pointer for glGenVertexArrays " << std::endl;
      }
      if (!convertPointer(glBindVertexArray, (void*)wglGetProcAddress("glBindVertexArray")))
      {
         std::cout << "Failed to get pointer for glBindVertexArray " << std::endl;
      }
      if (!convertPointer(glVertexAttribPointer, (void*)wglGetProcAddress("glVertexAttribPointer")))
      {
         std::cout << "Failed to get pointer for glVertexAttribPointer " << std::endl;
      }
      if (!convertPointer(glEnableVertexAttribArray, (void*)wglGetProcAddress("glEnableVertexAttribArray")))
      {
         std::cout << "Failed to get pointer for glEnableVertexAttribArray " << std::endl;
      }
      if (!convertPointer(glDisableVertexAttribArray, (void*)wglGetProcAddress("glDisableVertexAttribArray")))
      {
         std::cout << "Failed to get pointer for glDisableVertexAttribArray " << std::endl;
      }
   }
}