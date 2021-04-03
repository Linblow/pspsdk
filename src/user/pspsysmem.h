/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspsysmem.h - Interface to the system memory manager.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 *
 */

/* Note: Some of the structures, types, and definitions in this file were
   extrapolated from symbolic debugging information found in the Japanese
   version of Puzzle Bobble. */

#ifndef PSPSYSMEM_H
#define PSPSYSMEM_H

#include <pspkerneltypes.h>

/** @defgroup SysMem System Memory Manager
  * This module contains routines to manage heaps of memory.
  */

/** @addtogroup SysMem System Memory Manager */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/** Specifies the type of allocation used for memory blocks. */
enum PspSysMemBlockTypes {
	/** Allocate from the lowest available address. */
	PSP_SMEM_Low = 0,
	/** Allocate from the highest available address. */
	PSP_SMEM_High,
	/** Allocate from the specified address. */
	PSP_SMEM_Addr
};

typedef int SceKernelSysMemAlloc_t;

/** Additional options for ::sceKernelAllocMemoryBlock */
typedef struct SceKernelMemoryBlockOptParam {
	/** Size of the ::SceKernelMemoryBlockOptParam structure. */
	SceSize size;
} SceKernelMemoryBlockOptParam;

/**
 * Allocate a memory block from a memory partition.
 *
 * @param partitionid - The UID of the partition to allocate from.
 * @param name - Name assigned to the new block.
 * @param type - Specifies how the block is allocated within the partition.  One of ::PspSysMemBlockTypes.
 * @param size - Size of the memory block, in bytes.
 * @param addr - If type is PSP_SMEM_Addr, then addr specifies the lowest address allocate the block from.
 *
 * @return The UID of the new block, or if less than 0 an error.
 */
SceUID sceKernelAllocPartitionMemory(SceUID partitionid, const char *name, int type, SceSize size, void *addr);

/**
 * Free a memory block allocated with ::sceKernelAllocPartitionMemory.
 *
 * @param blockid - UID of the block to free.
 *
 * @return ? on success, less than 0 on error.
 */
int sceKernelFreePartitionMemory(SceUID blockid);

/**
 * Get the address of a memory block.
 *
 * @param blockid - UID of the memory block.
 *
 * @return The lowest address belonging to the memory block.
 */
void * sceKernelGetBlockHeadAddr(SceUID blockid);

/**
 * Allocate a memory block from the user memory partition.
 *
 * @note Only available in PSP firmware >= 3.5.0
 *
 * @param name - Name assigned to the new block. Not checked for uniqueness. Cannot be NULL.
 * @param type - Specifies how the block is allocated within the user partition.
 *               Specify PSP_SMEM_Low or PSP_SMEM_High. The other types are illegal.
 * @param size - Size of the memory block, in bytes.
 * @param opt  - Additional options. Unused, pass NULL.
 *
 * @return > 0 memory block ID
 *         < 0 on error:
 *         SCE_KERNEL_ERROR_ERROR
 *         SCE_KERNEL_ERROR_ILLEGAL_ARGUMENT
 *         SCE_KERNEL_ERROR_ILLEGAL_MEMBLOCKTYPE
 *         SCE_KERNEL_ERROR_MEMBLOCK_ALLOC_FAILED
 */
SceUID sceKernelAllocMemoryBlock(const char *name, SceKernelSysMemAlloc_t type, SceSize size, const SceKernelMemoryBlockOptParam *opt);

/**
 * Free a memory block allocated with ::sceKernelAllocMemoryBlock.
 *
 * @note Only available in PSP firmware >= 3.5.0
 *
 * @param mbid - Memory block ID
 *
 * @return ? on success, < 0 on error (eg. SCE_KERNEL_ERROR_UNKNOWN_UID)
 */
int sceKernelFreeMemoryBlock(SceUID mbid);

/**
 * Get the address of a memory block allocated with ::sceKernelAllocMemoryBlock.
 *
 * @note Only available in PSP firmware >= 3.5.0
 *
 * @param mbid - Memory block ID.
 * @param pBlock - Pointer to receive the block address.
 *
 * @return ? on success, < 0 on error:
 *         SCE_KERNEL_ERROR_UNKNOWN_UID
 *         SCE_KERNEL_ERROR_ILLEGAL_ADDR
 */
int sceKernelGetMemoryBlockAddr(SceUID mbid, void **pBlock);

/**
 * Get the total amount of free memory.
 *
 * @return The total amount of free memory, in bytes.
 */
SceSize sceKernelTotalFreeMemSize(void);

/**
 * Get the size of the largest free memory block.
 *
 * @return The size of the largest free memory block, in bytes.
 */
SceSize sceKernelMaxFreeMemSize(void);

/**
 * Get the firmware version.
 * 
 * @return The firmware version.
 * 0x01000300 on v1.00 unit,
 * 0x01050001 on v1.50 unit,
 * 0x01050100 on v1.51 unit,
 * 0x01050200 on v1.52 unit,
 * 0x02000010 on v2.00/v2.01 unit,
 * 0x02050010 on v2.50 unit,
 * 0x02060010 on v2.60 unit,
 * 0x02070010 on v2.70 unit,
 * 0x02070110 on v2.71 unit.
 */
int sceKernelDevkitVersion(void);

#if _PSP_FW_VERSION >= 150

/**
 * Kernel printf function.
 *
 * @param format - The format string.
 * @param ... - Arguments for the format string.
 */
void sceKernelPrintf(const char *format, ...) __attribute__((format(printf, 1, 2)));

#endif

/**
 * Set the version of the SDK with which the caller was compiled.
 * Version numbers are as for sceKernelDevkitVersion().
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelSetCompiledSdkVersion(int version);

/**
 * Get the SDK version set with sceKernelSetCompiledSdkVersion().
 *
 * @return Version number, or 0 if unset.
 */
int sceKernelGetCompiledSdkVersion(void);

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /* PSPSYSMEM_H */
