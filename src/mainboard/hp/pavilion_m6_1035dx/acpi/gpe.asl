/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2013 Sage Electronic Engineering, LLC
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

Scope(\_GPE) {	/* Start Scope GPE */

	Method(_L00) {
		Store("L00 received", Debug)
	}

	Method(_L01) {
		Store("L01 received", Debug)
	}

	Method(_L02) {
		Store("L02 received", Debug)
	}

	Method(_L04) {
		Store("L04 received", Debug)
	}

	Method(_L05) {
		Store("L05 received", Debug)
	}

	Method(_L06) {
		Store("L06 received", Debug)
	}

	Method(_L07) {
		Store("L07 received", Debug)
	}

	/*  Legacy PM event  */
	Method(_L08) {
		Store("L08 received", Debug)
		/* DBGO("\\_GPE\\_L08\n") */
	}

	/*  Temp warning (TWarn) event  */
	Method(_L09) {
		Store("L09 received", Debug)
		/* DBGO("\\_GPE\\_L09\n") */
		/* Notify (\_TZ.TZ00, 0x80) */
	}

	/*  USB controller PME#  */
	Method(_L0B) {
		Store("USB PME", Debug)
		/* Notify devices of wake event */
		Notify(\_SB.PCI0.UOH1, 0x02)
		Notify(\_SB.PCI0.UOH2, 0x02)
		Notify(\_SB.PCI0.UOH3, 0x02)
		Notify(\_SB.PCI0.UOH4, 0x02)
		Notify(\_SB.PCI0.XHC0, 0x02)
		Notify(\_SB.PCI0.UEH1, 0x02)
		Notify(\_SB.PWRB, 0x02)
	}

	/*  ExtEvent0 SCI event  */
	Method(_L10) {
		Store("L10 received", Debug)
		/* DBGO("\\_GPE\\_L10\n") */
	}


	/*  ExtEvent1 SCI event  */
	Method(_L11) {
		Store("L11 received", Debug)
		/* DBGO("\\_GPE\\_L11\n") */
	}

	Method(_L12) {
		Store("L12 received", Debug)
	}

	//Method(_L13) {
	//	Store("L13 received", Debug)
	//}

	Method(_L14) {
		Store("L14 received", Debug)
	}

	Method(_L15) {
		Store("L15 received", Debug)
	}

	Method(_L17) {
		Store("L17 received (probably EC SMI)", Debug)
		/* DBGO("\\_GPE\\_L11\n") */
	}

	/* Lid switch opened or closed */
	Method(_L16) {
		Store("Lid status changed", Debug)
		/* Flip trigger polarity */
		Not(LPOL, LPOL)
		/* Notify lid object of status change */
		Notify(\_SB.LID, 0x80)
	}

	/*  GPIO0 or GEvent8 event  */
	Method(_L18) {
		Store("PCI bridge wake event", Debug)
		/* Notify PCI bridges of wake event */
		Notify(\_SB.PCI0.PBR4, 0x02)
		Notify(\_SB.PCI0.PBR5, 0x02)
	}

	/*  Azalia SCI event  */
	Method(_L1B) {
		Store("L1B received", Debug)
		/* DBGO("\\_GPE\\_L1B\n") */
		Notify(\_SB.PCI0.AZHD, 0x02) /* NOTIFY_DEVICE_WAKE */
		Notify(\_SB.PWRB, 0x02) /* NOTIFY_DEVICE_WAKE */
	}

	Method(_L1C) {
		Store("L1C received", Debug)
	}
} 	/* End Scope GPE */
