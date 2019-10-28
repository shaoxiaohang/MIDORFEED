#pragma once

#if defined(_WIN64)
typedef __int64 GLintptr;
typedef __int64 GLsizeiptr;
#endif

typedef char GLchar;
typedef unsigned int GLuint;
typedef unsigned int GLenum;
typedef void GLvoid;

#define GL_ARRAY_BUFFER               0x8892
#define GL_ELEMENT_ARRAY_BUFFER       0x8893
#define GL_UNIFORM_BUFFER             0x8A11
#define GL_STATIC_DRAW                0x88E4
#define GL_DYNAMIC_DRAW               0x88E8
#define GL_STREAM_DRAW                0x88E0
#define GL_FRAMEBUFFER                0x8D40
#define GL_COLOR_ATTACHMENT0          0x8CE0
#define GL_RENDERBUFFER               0x8D41
#define GL_DEPTH_ATTACHMENT           0x8D00
#define GL_DEPTH_STENCIL_ATTACHMENT   0x821A
#define GL_DEPTH24_STENCIL8           0x88F0
#define GL_FRAMEBUFFER_COMPLETE       0x8CD5
#define GL_SRGB                       0x8C40
#define GL_BGR                        0x80E0
#define GL_SRGB_ALPHA                 0x8C42
#define GL_BGRA                       0x80E1
#define GL_TEXTURE0                   0x84C0
#define GL_LINK_STATUS                0x8B82
#define GL_INFO_LOG_LENGTH            0x8B84
#define GL_ACTIVE_UNIFORMS            0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH  0x8B87
#define GL_COMPILE_STATUS             0x8B81
#define GL_VERTEX_SHADER              0x8B31
#define GL_FRAGMENT_SHADER            0x8B30
#define GL_GEOMETRY_SHADER            0x8DD9
#define GL_CLAMP_TO_EDGE              0x812F
#define GL_CLAMP_TO_BORDER            0x812D
#define GL_RGBA16F                    0x881A
#define GL_RGBA32F                    0x8814
#define GL_TEXTURE_CUBE_MAP           0x8513
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X    0x8515
#define GL_TEXTURE_WRAP_R             0x8072
#define GL_FLOAT_VEC2                 0x8B50
#define GL_FLOAT_VEC3                 0x8B51
#define GL_FLOAT_VEC4                 0x8B52
#define GL_BOOL                       0x8B56
#define GL_FLOAT_MAT3                 0x8B5B
#define GL_FLOAT_MAT4                 0x8B5C
#define GL_SAMPLER_2D                 0x8B5E
#define GL_SAMPLER_CUBE               0x8B60