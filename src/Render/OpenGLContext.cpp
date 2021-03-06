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
         (PFNWGLCREATECONTEXTATTRIBSARBPROC)getAnyGLFuncAddress("wglCreateContextAttribsARB");
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
         WGLChoosePixelFormatARB wglChoosePixelFormatARB = (WGLChoosePixelFormatARB)getAnyGLFuncAddress("wglChoosePixelFormatARB");
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

   void* OpenGLContext::getAnyGLFuncAddress(const char *name)
   {
      void *p = (void *)wglGetProcAddress(name);
      if (p == 0 ||
         (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
         (p == (void*)-1))
      {
         HMODULE module = LoadLibraryA("opengl32.dll");
         p = (void *)GetProcAddress(module, name);
      }

      return p;
   }

   void OpenGLContext::retrieveOpenGLFunctions()
   {
      if (!convertPointer(glGenBuffers, (void*)getAnyGLFuncAddress("glGenBuffers")))
      {
         std::cout << "Failed to get pointer for glGenBuffers " << std::endl;
      }
      if (!convertPointer(glBindBuffer, (void*)getAnyGLFuncAddress("glBindBuffer")))
      {
         std::cout << "Failed to get pointer for glBindBuffer " << std::endl;
      }
      if (!convertPointer(glBufferData, (void*)getAnyGLFuncAddress("glBufferData")))
      {
         std::cout << "Failed to get pointer for glBufferData " << std::endl;
      }
      if (!convertPointer(glDeleteBuffers, (void*)getAnyGLFuncAddress("glDeleteBuffers")))
      {
         std::cout << "Failed to get pointer for glDeleteBuffers " << std::endl;
      }
      if (!convertPointer(glBufferSubData, (void*)getAnyGLFuncAddress("glBufferSubData")))
      {
         std::cout << "Failed to get pointer for glBufferSubData " << std::endl;
      }
      if (!convertPointer(glDrawArraysInstanced, (void*)getAnyGLFuncAddress("glDrawArraysInstanced")))
      {
         std::cout << "Failed to get pointer for glDrawArraysInstanced " << std::endl;
      }
      if (!convertPointer(glDrawElementsInstanced, (void*)getAnyGLFuncAddress("glDrawElementsInstanced")))
      {
         std::cout << "Failed to get pointer for glDrawElementsInstanced " << std::endl;
      }
      if (!convertPointer(glFramebufferTexture2D, (void*)getAnyGLFuncAddress("glFramebufferTexture2D")))
      {
         std::cout << "Failed to get pointer for glFramebufferTexture2D " << std::endl;
      }
      if (!convertPointer(glFramebufferRenderbuffer, (void*)getAnyGLFuncAddress("glFramebufferRenderbuffer")))
      {
         std::cout << "Failed to get pointer for glFramebufferRenderbuffer " << std::endl;
      }
      if (!convertPointer(glBindRenderbuffer, (void*)getAnyGLFuncAddress("glBindRenderbuffer")))
      {
         std::cout << "Failed to get pointer for glBindRenderbuffer " << std::endl;
      }
      if (!convertPointer(glGenRenderbuffers, (void*)getAnyGLFuncAddress("glGenRenderbuffers")))
      {
         std::cout << "Failed to get pointer for glGenRenderbuffers " << std::endl;
      }
      if (!convertPointer(glRenderbufferStorage, (void*)getAnyGLFuncAddress("glRenderbufferStorage")))
      {
         std::cout << "Failed to get pointer for glRenderbufferStorage " << std::endl;
      }
      if (!convertPointer(glGenFramebuffers, (void*)getAnyGLFuncAddress("glGenFramebuffers")))
      {
         std::cout << "Failed to get pointer for glGenFramebuffers " << std::endl;
      }
      if (!convertPointer(glBindFramebuffer, (void*)getAnyGLFuncAddress("glBindFramebuffer")))
      {
         std::cout << "Failed to get pointer for glBindFramebuffer " << std::endl;
      }
      if (!convertPointer(glDeleteFramebuffers, (void*)getAnyGLFuncAddress("glDeleteFramebuffers")))
      {
         std::cout << "Failed to get pointer for glDeleteFramebuffers " << std::endl;
      }
      if (!convertPointer(glDrawBuffers, (void*)getAnyGLFuncAddress("glDrawBuffers")))
      {
         std::cout << "Failed to get pointer for glDrawBuffers " << std::endl;
      }
      if (!convertPointer(glCheckFramebufferStatus, (void*)getAnyGLFuncAddress("glCheckFramebufferStatus")))
      {
         std::cout << "Failed to get pointer for glCheckFramebufferStatus " << std::endl;
      }
      if (!convertPointer(glActiveTexture, (void*)getAnyGLFuncAddress("glActiveTexture")))
      {
         std::cout << "Failed to get pointer for glActiveTexture " << std::endl;
      }
      if (!convertPointer(glDeleteProgram, (void*)getAnyGLFuncAddress("glDeleteProgram")))
      {
         std::cout << "Failed to get pointer for glDeleteProgram " << std::endl;
      }
      if (!convertPointer(glGetProgramiv, (void*)getAnyGLFuncAddress("glGetProgramiv")))
      {
         std::cout << "Failed to get pointer for glGetProgramiv " << std::endl;
      }
      if (!convertPointer(glGetProgramInfoLog, (void*)getAnyGLFuncAddress("glGetProgramInfoLog")))
      {
         std::cout << "Failed to get pointer for glGetProgramInfoLog " << std::endl;
      }
      if (!convertPointer(glUseProgram, (void*)getAnyGLFuncAddress("glUseProgram")))
      {
         std::cout << "Failed to get pointer for glUseProgram " << std::endl;
      }
      if (!convertPointer(glGetUniformBlockIndex, (void*)getAnyGLFuncAddress("glGetUniformBlockIndex")))
      {
         std::cout << "Failed to get pointer for glGetUniformBlockIndex " << std::endl;
      }
      if (!convertPointer(glUniformBlockBinding, (void*)getAnyGLFuncAddress("glUniformBlockBinding")))
      {
         std::cout << "Failed to get pointer for glUniformBlockBinding " << std::endl;
      }
      if (!convertPointer(glUniformBlockBinding, (void*)getAnyGLFuncAddress("glUniformBlockBinding")))
      {
         std::cout << "Failed to get pointer for glUniformBlockBinding " << std::endl;
      }
      if (!convertPointer(glCreateProgram, (void*)getAnyGLFuncAddress("glCreateProgram")))
      {
         std::cout << "Failed to get pointer for glCreateProgram " << std::endl;
      }
      if (!convertPointer(glAttachShader, (void*)getAnyGLFuncAddress("glAttachShader")))
      {
         std::cout << "Failed to get pointer for glAttachShader " << std::endl;
      }
      if (!convertPointer(glLinkProgram, (void*)getAnyGLFuncAddress("glLinkProgram")))
      {
         std::cout << "Failed to get pointer for glLinkProgram " << std::endl;
      }
      if (!convertPointer(glGetActiveUniform, (void*)getAnyGLFuncAddress("glGetActiveUniform")))
      {
         std::cout << "Failed to get pointer for glGetActiveUniform " << std::endl;
      }
      if (!convertPointer(glGetUniformLocation, (void*)getAnyGLFuncAddress("glGetUniformLocation")))
      {
         std::cout << "Failed to get pointer for glGetUniformLocation " << std::endl;
      }
      if (!convertPointer(glCreateShader, (void*)getAnyGLFuncAddress("glCreateShader")))
      {
         std::cout << "Failed to get pointer for glCreateShader " << std::endl;
      }
      if (!convertPointer(glShaderSource, (void*)getAnyGLFuncAddress("glShaderSource")))
      {
         std::cout << "Failed to get pointer for glShaderSource " << std::endl;
      }
      if (!convertPointer(glCompileShader, (void*)getAnyGLFuncAddress("glCompileShader")))
      {
         std::cout << "Failed to get pointer for glCompileShader " << std::endl;
      }
      if (!convertPointer(glGetShaderiv, (void*)getAnyGLFuncAddress("glGetShaderiv")))
      {
         std::cout << "Failed to get pointer for glGetShaderiv " << std::endl;
      }
      if (!convertPointer(glGetShaderInfoLog, (void*)getAnyGLFuncAddress("glGetShaderInfoLog")))
      {
         std::cout << "Failed to get pointer for glGetShaderInfoLog " << std::endl;
      }
      if (!convertPointer(glActiveTexture, (void*)getAnyGLFuncAddress("glActiveTexture")))
      {
         std::cout << "Failed to get pointer for glActiveTexture " << std::endl;
      }
      if (!convertPointer(glGenerateMipmap, (void*)getAnyGLFuncAddress("glGenerateMipmap")))
      {
         std::cout << "Failed to get pointer for glGenerateMipmap " << std::endl;
      }
      if (!convertPointer(glUniform1i, (void*)getAnyGLFuncAddress("glUniform1i")))
      {
         std::cout << "Failed to get pointer for glUniform1i " << std::endl;
      }
      if (!convertPointer(glUniform1f, (void*)getAnyGLFuncAddress("glUniform1f")))
      {
         std::cout << "Failed to get pointer for glUniform1f " << std::endl;
      }
      if (!convertPointer(glUniform2f, (void*)getAnyGLFuncAddress("glUniform2f")))
      {
         std::cout << "Failed to get pointer for glUniform2f " << std::endl;
      }
      if (!convertPointer(glUniform3f, (void*)getAnyGLFuncAddress("glUniform3f")))
      {
         std::cout << "Failed to get pointer for glUniform3f " << std::endl;
      }
      if (!convertPointer(glUniform4f, (void*)getAnyGLFuncAddress("glUniform4f")))
      {
         std::cout << "Failed to get pointer for glUniform4f " << std::endl;
      }
      if (!convertPointer(glUniformMatrix3fv, (void*)getAnyGLFuncAddress("glUniformMatrix3fv")))
      {
         std::cout << "Failed to get pointer for glUniformMatrix3fv " << std::endl;
      }
      if (!convertPointer(glUniformMatrix4fv, (void*)getAnyGLFuncAddress("glUniformMatrix4fv")))
      {
         std::cout << "Failed to get pointer for glUniformMatrix4fv " << std::endl;
      }
      if (!convertPointer(glBindBufferBase, (void*)getAnyGLFuncAddress("glBindBufferBase")))
      {
         std::cout << "Failed to get pointer for glBindBufferBase " << std::endl;
      }
      if (!convertPointer(glGenVertexArrays, (void*)getAnyGLFuncAddress("glGenVertexArrays")))
      {
         std::cout << "Failed to get pointer for glGenVertexArrays " << std::endl;
      }
      if (!convertPointer(glBindVertexArray, (void*)getAnyGLFuncAddress("glBindVertexArray")))
      {
         std::cout << "Failed to get pointer for glBindVertexArray " << std::endl;
      }
      if (!convertPointer(glVertexAttribPointer, (void*)getAnyGLFuncAddress("glVertexAttribPointer")))
      {
         std::cout << "Failed to get pointer for glVertexAttribPointer " << std::endl;
      }
      if (!convertPointer(glEnableVertexAttribArray, (void*)getAnyGLFuncAddress("glEnableVertexAttribArray")))
      {
         std::cout << "Failed to get pointer for glEnableVertexAttribArray " << std::endl;
      }
      if (!convertPointer(glDisableVertexAttribArray, (void*)getAnyGLFuncAddress("glDisableVertexAttribArray")))
      {
         std::cout << "Failed to get pointer for glDisableVertexAttribArray " << std::endl;
      }
      if (!convertPointer(glTexImage2D, (void*)getAnyGLFuncAddress("glTexImage2D")))
      {
         std::cout << "Failed to get pointer for glTexImage2D " << std::endl;
      }
      if (!convertPointer(glTexParameteri, (void*)getAnyGLFuncAddress("glTexParameteri")))
      {
         std::cout << "Failed to get pointer for glTexParameteri " << std::endl;
      }
      if (!convertPointer(glBindTexture, (void*)getAnyGLFuncAddress("glBindTexture")))
      {
         std::cout << "Failed to get pointer for glBindTexture " << std::endl;
      }
   }
}