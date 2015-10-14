/*
 * This file is part of the coreboot project.
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _RULES_H
#define _RULES_H

/* Useful helpers to tell whether the code is executing in bootblock,
 * romstage, ramstage or SMM.
 */

#if defined(__BOOTBLOCK__)
#define ENV_BOOTBLOCK 1
#define ENV_ROMSTAGE 0
#define ENV_RAMSTAGE 0
#define ENV_SMM 0
#define ENV_VERSTAGE 0
#define ENV_RMODULE 0

#elif defined(__ROMSTAGE__)
#define ENV_BOOTBLOCK 0
#define ENV_ROMSTAGE 1
#define ENV_RAMSTAGE 0
#define ENV_SMM 0
#define ENV_VERSTAGE 0
#define ENV_RMODULE 0

#elif defined(__SMM__)
#define ENV_BOOTBLOCK 0
#define ENV_ROMSTAGE 0
#define ENV_RAMSTAGE 0
#define ENV_SMM 1
#define ENV_VERSTAGE 0
#define ENV_RMODULE 0

#elif defined(__VERSTAGE__)
#define ENV_BOOTBLOCK 0
#define ENV_ROMSTAGE 0
#define ENV_RAMSTAGE 0
#define ENV_SMM 0
#define ENV_VERSTAGE 1
#define ENV_RMODULE 0

#elif defined(__RAMSTAGE__)
#define ENV_BOOTBLOCK 0
#define ENV_ROMSTAGE 0
#define ENV_RAMSTAGE 1
#define ENV_SMM 0
#define ENV_VERSTAGE 0
#define ENV_RMODULE 0

#elif defined(__RMODULE__)
#define ENV_BOOTBLOCK 0
#define ENV_ROMSTAGE 0
#define ENV_RAMSTAGE 0
#define ENV_SMM 0
#define ENV_VERSTAGE 0
#define ENV_RMODULE 1

#else
/*
 * Default case of nothing set for random blob generation using
 * create_class_compiler that isn't bound to a stage. Also AGESA
 * apparently builds things compeletely separate from coreboot's
 * build infrastructure -- hardcoding its own rules.
 */
#define ENV_BOOTBLOCK 0
#define ENV_ROMSTAGE 0
#define ENV_RAMSTAGE 0
#define ENV_SMM 0
#define ENV_VERSTAGE 0
#define ENV_RMODULE 0
#endif

/* For romstage and ramstage always build with simple device model, ie.
 * PCI, PNP and CPU functions operate without use of devicetree.
 *
 * For ramstage individual source file may define __SIMPLE_DEVICE__
 * before including any header files to force that particular source
 * be built with simple device model.
 */

#if defined(__PRE_RAM__) || defined(__SMM__)
#define __SIMPLE_DEVICE__
#endif

#endif /* _RULES_H */
