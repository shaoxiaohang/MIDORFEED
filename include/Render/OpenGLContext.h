#pragma once

#include <windows.h>
#include <gl/GL.h>
#include <Render/OpenGLDefines.h>

namespace vrv
{
   class OpenGLContext
   {
   public:

      static OpenGLContext& instance();


      OpenGLContext(HWND hWnd);

      bool makeCurrent();

      void initialize();


   public:

      void (APIENTRY* glGenBuffers) (GLsizei n, GLuint *buffers);
      void (APIENTRY* glBindBuffer) (GLenum target, GLuint buffer);
      void (APIENTRY* glBufferData) (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
      void (APIENTRY* glDeleteBuffers) (GLsizei n, const GLuint *buffers);
      void (APIENTRY* glBufferSubData) (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
      void (APIENTRY* glDrawArraysInstanced)(GLenum mode, GLint first, GLsizei count, GLsizei primcount);
      void (APIENTRY* glDrawElementsInstanced)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei primcount);
      void (APIENTRY* glFramebufferTexture2D) (GLenum, GLenum, GLenum, GLuint, GLint);
      void (APIENTRY* glFramebufferRenderbuffer) (GLenum, GLenum, GLenum, GLuint);
      void (APIENTRY* glBindRenderbuffer) (GLenum, GLuint);
      void (APIENTRY* glGenRenderbuffers) (GLsizei, GLuint *);
      void (APIENTRY* glRenderbufferStorage) (GLenum, GLenum, GLsizei, GLsizei);
      void (APIENTRY* glGenFramebuffers) (GLsizei, GLuint *);
      void (APIENTRY* glBindFramebuffer) (GLenum, GLuint);
      void (APIENTRY* glDeleteFramebuffers) (GLsizei n, const GLuint *framebuffers);
      void (APIENTRY* glDrawBuffers)(GLsizei n, const GLenum *bufs);
      GLenum(APIENTRY* glCheckFramebufferStatus) (GLenum);
      void (APIENTRY* glVertexAttribDivisor)(GLuint index, GLuint divisor);
      void (APIENTRY* glActiveTexture) (GLenum texture);
      void (APIENTRY* glDeleteProgram)(GLuint program);
      void (APIENTRY* glGetProgramiv)(GLuint program, GLenum pname, GLint *params);
      void (APIENTRY* glGetProgramInfoLog)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
      void (APIENTRY* glUseProgram)(GLuint program);
      GLuint(APIENTRY * glGetUniformBlockIndex)(GLuint program, const GLchar *uniformBlockName);
      void (APIENTRY* glUniformBlockBinding)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
      GLuint(APIENTRY* glCreateProgram)(void);
      void (APIENTRY* glAttachShader)(GLuint program, GLuint shader);
      void (APIENTRY* glLinkProgram)(GLuint program);
      void (APIENTRY* glGetActiveUniform)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
      GLint(APIENTRY* glGetUniformLocation)(GLuint program, const GLchar *name);
      GLuint(APIENTRY* glCreateShader)(GLenum type);
      void (APIENTRY* glShaderSource)(GLuint shader, GLsizei count, const GLchar* *string, const GLint *length);
      void (APIENTRY* glCompileShader)(GLuint shader);
      void (APIENTRY* glGetShaderiv)(GLuint shader, GLenum pname, GLint *params);
      void (APIENTRY* glGetShaderInfoLog)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
      void (APIENTRY* glGenerateMipmap) (GLenum);
      void (APIENTRY* glUniform1i)(GLint location, GLint v0);
      void (APIENTRY* glUniform1f)(GLint location, GLfloat v0);
      void (APIENTRY* glUniform2f)(GLint location, GLfloat v0, GLfloat v1);
      void (APIENTRY* glUniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
      void (APIENTRY* glUniform4f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
      void (APIENTRY* glUniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
      void (APIENTRY* glUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
      void (APIENTRY* glBindBufferBase) (GLenum target, GLuint index, GLuint buffer);
      void (APIENTRY* glGenVertexArrays) (GLsizei size, GLuint *handles);
      void (APIENTRY* glBindVertexArray) (GLuint handle);
      void (APIENTRY* glVertexAttribPointer) (unsigned int, GLint, GLenum, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
      void (APIENTRY* glEnableVertexAttribArray)(GLuint index);
      void (APIENTRY* glDisableVertexAttribArray)(GLuint index);

   protected:
      bool createContext();

      bool setPixelFormat();

      void destroy();

      bool makeSampleContextCurrent();

      void destorySampleContext();

      void retrieveOpenGLFunctions();

   protected:

      HWND myWindowHandle;
      HGLRC myContextHandle;
      HDC myDeviceContext;

      HWND mySampleWindowHandle;
      HGLRC mySampleContextHandle;
      HDC mySampleDeviceHandle;

      int myMajorVersion;
      int myMinorVersion;

      static OpenGLContext* myInstance;
   };
}