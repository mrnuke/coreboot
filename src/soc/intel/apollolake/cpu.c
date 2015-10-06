#include <cpu/x86/msr.h>
#include <cpu/x86/tsc.h>
#include <soc/cpu.h>

unsigned long tsc_freq_mhz(void)
{
	msr_t msr = rdmsr(MSR_PLATFORM_INFO);
	return (BASE_CLOCK_MHZ * ((msr.lo >> 8) & 0xff));
}
