#ifndef BASEDEFINE_PLATFORM_H
#define BASEDEFINE_PLATFORM_H

#if defined (__GNUC__)
#define SGE_GCC
#elif defined _MSC_VER
#define SGE_MSVC
#endif

#ifdef SGE_GCC
#if defined __amd64__
#define SGE_64
#define SGE_INTEL
#elif defined __i386__
#define SGE_32
#define SGE_INTEL
#endif
#endif

#ifdef SGE_MSVC
#if defined (_M_AMD64) || defined (_M_X64)
#define SGE_64
#define SGE_INTEL
#elif defined (_M_IX86)
#define SGE_32
#define SGE_INTEL
#endif
#endif

#if defined SGE_GCC
#define sge_align(aligntype) __attribute__((aligned(aligntype)))
#define sge_export
#define sge_import
#define sge_inline static __inline __attribute__((always_inline))
#define sge_template_inst_inline
#define sge_thread_local __thread
#elif defined SGE_MSVC
#define sge_align(aligntype) __declspec(align(aligntype))
#define sge_export __declspec(dllexport)
#define sge_import __declspec(dllimport)
#define sge_inline __forceinline
#define sge_template_inst_inline __forceinline
#define sge_thread_local __declspec(thread)
#endif

//C function declearation must be enclosed in extern "C"
#ifdef __cplusplus
#define SGE_EXTERN_C_START extern "C" {
#define SGE_EXTERN_C_END }
#else
#define SGE_EXTERN_C_START
#define SGE_EXTERN_C_END
#endif

#define UNUSED(x) ((void)x)
#endif

