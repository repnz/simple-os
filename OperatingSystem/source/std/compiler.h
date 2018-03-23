#pragma once

#if defined(__GNUC__)
#define PACKED __attribute__((packed))
#define ASM __asm__
#define ASM_VOLATILE __asm__ __volatile__
#define GLOBAL extern "C"
#else
#define PACKED 
#define ASM
#define ASM_VOLATILE 
#define GLOBAL extern "C"
#endif