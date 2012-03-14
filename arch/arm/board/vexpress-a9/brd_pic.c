/**
 * Copyright (c) 2012 Anup Patel.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * @file brd_pic.c
 * @author Anup Patel (anup@brainfault.org)
 * @brief board specific progammable interrupt contoller
 */

#include <vmm_error.h>
#include <vmm_host_aspace.h>
#include <arch_board.h>
#include <ca9x4_board.h>
#include <gic.h>

u32 arch_pic_irq_count(void)
{
	return GIC_NR_IRQS;
}

u32 arch_pic_irq_active(u32 cpu_irq_no)
{
	return gic_active_irq(0);
}

void arch_pic_irq_ack(u32 host_irq_no)
{
	gic_ack_irq(0, host_irq_no);
}

void arch_pic_irq_eoi(u32 host_irq_no)
{
}

void arch_pic_irq_unmask(u32 host_irq_no)
{
	gic_unmask(0, host_irq_no);
}

void arch_pic_irq_mask(u32 host_irq_no)
{
	gic_mask(0, host_irq_no);
}

int __init arch_pic_init(void)
{
	int ret;
	virtual_addr_t dist_base, cpu_base;

	dist_base = vmm_host_iomap(A9_MPCORE_GIC_DIST, 0x1000);
	ret = gic_dist_init(0, dist_base, IRQ_CA9X4_GIC_START);
	if (ret) {
		return ret;
	}

	cpu_base = vmm_host_iomap(A9_MPCORE_GIC_CPU, 0x1000);
	ret = gic_cpu_init(0, cpu_base);
	if (ret) {
		return ret;
	}

	return VMM_OK;
}
