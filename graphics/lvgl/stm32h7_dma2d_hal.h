/**
 * Minimal CMSIS-compatible HAL header for LVGL DMA2D draw backend on NuttX.
 *
 * Provides only the register definitions, typedefs, and intrinsics required
 * by the LVGL DMA2D backend (src/draw/dma2d/).  This avoids pulling in the
 * full STM32CubeH7 HAL / CMSIS-Device headers which would conflict with
 * NuttX's own peripheral definitions.
 *
 * Reference: stm32h753xx.h + core_cm7.h from CMSIS 5 / STM32CubeH7.
 */

#ifndef STM32H7_DMA2D_HAL_H
#define STM32H7_DMA2D_HAL_H

#include <stdint.h>

/* ---- STM32 family identification (selects RCC register in DMA2D backend) */
#ifndef STM32H7
#define STM32H7
#endif

/* ---- Cortex-M core identification (enables D-cache management) ---------- */
#ifndef __CORTEX_M
#define __CORTEX_M 7U
#endif

/* ---- Volatile qualifiers (CMSIS style) --------------------------------- */
#ifndef __IO
#define __IO  volatile
#endif
#ifndef __IM
#define __IM  volatile const
#endif
#ifndef __OM
#define __OM  volatile
#endif
#ifndef __IOM
#define __IOM volatile
#endif

/* ---- Compiler helpers --------------------------------------------------- */
#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline __attribute__((always_inline))
#endif

#ifndef __COMPILER_BARRIER
#define __COMPILER_BARRIER() __asm volatile ("" ::: "memory")
#endif

/* ---- ARM memory barrier intrinsics -------------------------------------- */
#ifndef __DSB
#define __DSB() __asm volatile ("dsb 0xF" ::: "memory")
#endif

#ifndef __ISB
#define __ISB() __asm volatile ("isb 0xF" ::: "memory")
#endif

/* ---- D-Cache line size (Cortex-M7 = 32 bytes) -------------------------- */
#ifndef __SCB_DCACHE_LINE_SIZE
#define __SCB_DCACHE_LINE_SIZE 32U
#endif

/* ======================================================================== */
/*                      IRQ number (DMA2D = 90 on STM32H753)                */
/* ======================================================================== */

typedef enum {
    DMA2D_IRQn = 90
} IRQn_Type;

/* ======================================================================== */
/*                              NVIC registers                              */
/* ======================================================================== */

typedef struct {
    __IOM uint32_t ISER[8U];    /* Offset: 0x000  Interrupt Set Enable Register     */
          uint32_t RESERVED0[24U];
    __IOM uint32_t ICER[8U];    /* Offset: 0x080  Interrupt Clear Enable Register   */
          uint32_t RESERVED1[24U];
    __IOM uint32_t ISPR[8U];    /* Offset: 0x100  Interrupt Set Pending Register    */
          uint32_t RESERVED2[24U];
    __IOM uint32_t ICPR[8U];    /* Offset: 0x180  Interrupt Clear Pending Register  */
          uint32_t RESERVED3[24U];
    __IOM uint32_t IABR[8U];    /* Offset: 0x200  Interrupt Active Bit Register     */
          uint32_t RESERVED4[56U];
    __IOM uint8_t  IP[240U];    /* Offset: 0x300  Interrupt Priority Register       */
          uint32_t RESERVED5[644U];
    __OM  uint32_t STIR;        /* Offset: 0xE00  Software Trigger Interrupt Reg    */
} NVIC_Type;

#define NVIC_BASE  (0xE000E100UL)
#define NVIC       ((NVIC_Type *) NVIC_BASE)

__STATIC_INLINE void NVIC_EnableIRQ(IRQn_Type IRQn)
{
    if ((int32_t)(IRQn) >= 0) {
        __COMPILER_BARRIER();
        NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] =
            (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
        __COMPILER_BARRIER();
    }
}

__STATIC_INLINE void NVIC_DisableIRQ(IRQn_Type IRQn)
{
    if ((int32_t)(IRQn) >= 0) {
        NVIC->ICER[(((uint32_t)IRQn) >> 5UL)] =
            (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
        __DSB();
        __ISB();
    }
}

/* ======================================================================== */
/*              SCB (System Control Block) – Cortex-M7                      */
/* ======================================================================== */

typedef struct {
    __IM  uint32_t CPUID;       /* Offset: 0x000 */
    __IOM uint32_t ICSR;        /* Offset: 0x004 */
    __IOM uint32_t VTOR;        /* Offset: 0x008 */
    __IOM uint32_t AIRCR;       /* Offset: 0x00C */
    __IOM uint32_t SCR;         /* Offset: 0x010 */
    __IOM uint32_t CCR;         /* Offset: 0x014 */
    __IOM uint8_t  SHPR[12U];   /* Offset: 0x018 */
    __IOM uint32_t SHCSR;       /* Offset: 0x024 */
    __IOM uint32_t CFSR;        /* Offset: 0x028 */
    __IOM uint32_t HFSR;        /* Offset: 0x02C */
    __IOM uint32_t DFSR;        /* Offset: 0x030 */
    __IOM uint32_t MMFAR;       /* Offset: 0x034 */
    __IOM uint32_t BFAR;        /* Offset: 0x038 */
    __IOM uint32_t AFSR;        /* Offset: 0x03C */
    __IM  uint32_t ID_PFR[2U];  /* Offset: 0x040 */
    __IM  uint32_t ID_DFR;      /* Offset: 0x048 */
    __IM  uint32_t ID_AFR;      /* Offset: 0x04C */
    __IM  uint32_t ID_MFR[4U];  /* Offset: 0x050 */
    __IM  uint32_t ID_ISAR[5U]; /* Offset: 0x060 */
          uint32_t RESERVED0[1U];
    __IM  uint32_t CLIDR;       /* Offset: 0x078 */
    __IM  uint32_t CTR;         /* Offset: 0x07C */
    __IM  uint32_t CCSIDR;      /* Offset: 0x080 */
    __IOM uint32_t CSSELR;      /* Offset: 0x084 */
    __IOM uint32_t CPACR;       /* Offset: 0x088 */
          uint32_t RESERVED3[93U];
    __OM  uint32_t STIR;        /* Offset: 0x200 */
          uint32_t RESERVED4[15U];
    __IM  uint32_t MVFR0;       /* Offset: 0x240 */
    __IM  uint32_t MVFR1;       /* Offset: 0x244 */
    __IM  uint32_t MVFR2;       /* Offset: 0x248 */
          uint32_t RESERVED5[1U];
    __OM  uint32_t ICIALLU;     /* Offset: 0x250 */
          uint32_t RESERVED6[1U];
    __OM  uint32_t ICIMVAU;     /* Offset: 0x258 */
    __OM  uint32_t DCIMVAC;     /* Offset: 0x25C  D-Cache Invalidate by MVA to PoC */
    __OM  uint32_t DCISW;       /* Offset: 0x260 */
    __OM  uint32_t DCCMVAU;     /* Offset: 0x264 */
    __OM  uint32_t DCCMVAC;     /* Offset: 0x268  D-Cache Clean by MVA to PoC      */
    __OM  uint32_t DCCSW;       /* Offset: 0x26C */
    __OM  uint32_t DCCIMVAC;    /* Offset: 0x270 */
    __OM  uint32_t DCCISW;      /* Offset: 0x274 */
    __OM  uint32_t BPIALL;      /* Offset: 0x278 */
} SCB_Type;

#define SCB_BASE  (0xE000ED00UL)
#define SCB       ((SCB_Type *) SCB_BASE)

#define SCB_CCR_DC_Pos  16U
#define SCB_CCR_DC_Msk  (1UL << SCB_CCR_DC_Pos)

/* ======================================================================== */
/*                         DMA2D peripheral                                 */
/* ======================================================================== */

typedef struct {
    __IO uint32_t CR;           /* Offset: 0x00  Control Register                   */
    __IO uint32_t ISR;          /* Offset: 0x04  Interrupt Status Register           */
    __IO uint32_t IFCR;         /* Offset: 0x08  Interrupt Flag Clear Register       */
    __IO uint32_t FGMAR;        /* Offset: 0x0C  FG Memory Address Register          */
    __IO uint32_t FGOR;         /* Offset: 0x10  FG Offset Register                  */
    __IO uint32_t BGMAR;        /* Offset: 0x14  BG Memory Address Register          */
    __IO uint32_t BGOR;         /* Offset: 0x18  BG Offset Register                  */
    __IO uint32_t FGPFCCR;      /* Offset: 0x1C  FG PFC Control Register             */
    __IO uint32_t FGCOLR;       /* Offset: 0x20  FG Color Register                   */
    __IO uint32_t BGPFCCR;      /* Offset: 0x24  BG PFC Control Register             */
    __IO uint32_t BGCOLR;       /* Offset: 0x28  BG Color Register                   */
    __IO uint32_t FGCMAR;       /* Offset: 0x2C  FG CLUT Memory Address Register     */
    __IO uint32_t BGCMAR;       /* Offset: 0x30  BG CLUT Memory Address Register     */
    __IO uint32_t OPFCCR;       /* Offset: 0x34  Output PFC Control Register         */
    __IO uint32_t OCOLR;        /* Offset: 0x38  Output Color Register               */
    __IO uint32_t OMAR;         /* Offset: 0x3C  Output Memory Address Register      */
    __IO uint32_t OOR;          /* Offset: 0x40  Output Offset Register              */
    __IO uint32_t NLR;          /* Offset: 0x44  Number of Line Register             */
    __IO uint32_t LWR;          /* Offset: 0x48  Line Watermark Register             */
    __IO uint32_t AMTCR;        /* Offset: 0x4C  AHB Master Timer Config Register   */
         uint32_t RESERVED[236];
    __IO uint32_t FGCLUT[256];  /* Offset: 0x400  FG CLUT                           */
    __IO uint32_t BGCLUT[256];  /* Offset: 0x800  BG CLUT                           */
} DMA2D_TypeDef;

#define DMA2D_BASE  (0x52001000UL)
#define DMA2D       ((DMA2D_TypeDef *) DMA2D_BASE)

/* ---- DMA2D_CR (Control Register) ---------------------------------------- */
#define DMA2D_CR_START_Pos     0U
#define DMA2D_CR_START_Msk     (0x1UL << DMA2D_CR_START_Pos)
#define DMA2D_CR_START         DMA2D_CR_START_Msk

#define DMA2D_CR_TCIE_Pos      9U
#define DMA2D_CR_TCIE_Msk      (0x1UL << DMA2D_CR_TCIE_Pos)
#define DMA2D_CR_TCIE          DMA2D_CR_TCIE_Msk

#define DMA2D_CR_MODE_Pos      16U
#define DMA2D_CR_MODE_Msk      (0x7UL << DMA2D_CR_MODE_Pos)

/* ---- DMA2D_NLR (Number of Line Register) -------------------------------- */
#define DMA2D_NLR_NL_Pos       0U
#define DMA2D_NLR_NL_Msk       (0xFFFFUL << DMA2D_NLR_NL_Pos)

#define DMA2D_NLR_PL_Pos       16U
#define DMA2D_NLR_PL_Msk       (0x3FFFUL << DMA2D_NLR_PL_Pos)

/* ---- DMA2D_OPFCCR (Output PFC Control Register) ------------------------ */
#define DMA2D_OPFCCR_CM_Pos    0U
#define DMA2D_OPFCCR_CM_Msk    (0x7UL << DMA2D_OPFCCR_CM_Pos)

/* ---- DMA2D_FGPFCCR (FG PFC Control Register) --------------------------- */
#define DMA2D_FGPFCCR_CM_Pos      0U
#define DMA2D_FGPFCCR_CM_Msk      (0xFUL << DMA2D_FGPFCCR_CM_Pos)

#define DMA2D_FGPFCCR_AM_Pos      16U
#define DMA2D_FGPFCCR_AM_Msk      (0x3UL << DMA2D_FGPFCCR_AM_Pos)

#define DMA2D_FGPFCCR_ALPHA_Pos   24U
#define DMA2D_FGPFCCR_ALPHA_Msk   (0xFFUL << DMA2D_FGPFCCR_ALPHA_Pos)

/* ---- DMA2D_BGPFCCR (BG PFC Control Register) --------------------------- */
#define DMA2D_BGPFCCR_CM_Pos      0U
#define DMA2D_BGPFCCR_CM_Msk      (0xFUL << DMA2D_BGPFCCR_CM_Pos)

#define DMA2D_BGPFCCR_AM_Pos      16U
#define DMA2D_BGPFCCR_AM_Msk      (0x3UL << DMA2D_BGPFCCR_AM_Pos)

#define DMA2D_BGPFCCR_ALPHA_Pos   24U
#define DMA2D_BGPFCCR_ALPHA_Msk   (0xFFUL << DMA2D_BGPFCCR_ALPHA_Pos)

/* ======================================================================== */
/*                     RCC – only AHB3ENR needed                            */
/* ======================================================================== */

/*
 * RCC_TypeDef: we only need access up to AHB3ENR at offset 0xD4.
 * Pad with a uint32_t array to reach the correct offset.
 * RCC base on STM32H753: 0x58024400
 */
typedef struct {
    uint32_t _pad[0xD4 / 4];   /* padding: offsets 0x00 .. 0xD0 */
    __IO uint32_t AHB3ENR;     /* Offset: 0xD4 */
} RCC_TypeDef;

#define RCC_BASE  (0x58024400UL)
#define RCC       ((RCC_TypeDef *) RCC_BASE)

#define RCC_AHB3ENR_DMA2DEN_Pos  4U
#define RCC_AHB3ENR_DMA2DEN_Msk  (0x1UL << RCC_AHB3ENR_DMA2DEN_Pos)
#define RCC_AHB3ENR_DMA2DEN      RCC_AHB3ENR_DMA2DEN_Msk

#endif /* STM32H7_DMA2D_HAL_H */
