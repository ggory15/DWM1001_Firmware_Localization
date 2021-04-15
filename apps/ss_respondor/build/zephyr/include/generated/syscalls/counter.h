
/* auto-generated by gen_syscalls.py, don't edit */
#ifndef Z_INCLUDE_SYSCALLS_COUNTER_H
#define Z_INCLUDE_SYSCALLS_COUNTER_H


#ifndef _ASMLANGUAGE

#include <syscall_list.h>
#include <syscall.h>

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic push
#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern bool z_impl_counter_is_counting_up(const struct device * dev);
static inline bool counter_is_counting_up(const struct device * dev)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (bool) arch_syscall_invoke1(*(uintptr_t *)&dev, K_SYSCALL_COUNTER_IS_COUNTING_UP);
	}
#endif
	compiler_barrier();
	return z_impl_counter_is_counting_up(dev);
}


extern uint8_t z_impl_counter_get_num_of_channels(const struct device * dev);
static inline uint8_t counter_get_num_of_channels(const struct device * dev)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (uint8_t) arch_syscall_invoke1(*(uintptr_t *)&dev, K_SYSCALL_COUNTER_GET_NUM_OF_CHANNELS);
	}
#endif
	compiler_barrier();
	return z_impl_counter_get_num_of_channels(dev);
}


extern uint32_t z_impl_counter_get_frequency(const struct device * dev);
static inline uint32_t counter_get_frequency(const struct device * dev)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (uint32_t) arch_syscall_invoke1(*(uintptr_t *)&dev, K_SYSCALL_COUNTER_GET_FREQUENCY);
	}
#endif
	compiler_barrier();
	return z_impl_counter_get_frequency(dev);
}


extern uint32_t z_impl_counter_us_to_ticks(const struct device * dev, uint64_t us);
static inline uint32_t counter_us_to_ticks(const struct device * dev, uint64_t us)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		union { struct { uintptr_t lo, hi; } split; uint64_t val; } parm0;
		parm0.val = us;
		return (uint32_t) arch_syscall_invoke3(*(uintptr_t *)&dev, parm0.split.lo, parm0.split.hi, K_SYSCALL_COUNTER_US_TO_TICKS);
	}
#endif
	compiler_barrier();
	return z_impl_counter_us_to_ticks(dev, us);
}


extern uint64_t z_impl_counter_ticks_to_us(const struct device * dev, uint32_t ticks);
static inline uint64_t counter_ticks_to_us(const struct device * dev, uint32_t ticks)
{
#ifdef CONFIG_USERSPACE
	uint64_t ret64;
	if (z_syscall_trap()) {
		(void)arch_syscall_invoke3(*(uintptr_t *)&dev, *(uintptr_t *)&ticks, (uintptr_t)&ret64, K_SYSCALL_COUNTER_TICKS_TO_US);
		return (uint64_t)ret64;
	}
#endif
	compiler_barrier();
	return z_impl_counter_ticks_to_us(dev, ticks);
}


extern uint32_t z_impl_counter_get_max_top_value(const struct device * dev);
static inline uint32_t counter_get_max_top_value(const struct device * dev)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (uint32_t) arch_syscall_invoke1(*(uintptr_t *)&dev, K_SYSCALL_COUNTER_GET_MAX_TOP_VALUE);
	}
#endif
	compiler_barrier();
	return z_impl_counter_get_max_top_value(dev);
}


extern int z_impl_counter_start(const struct device * dev);
static inline int counter_start(const struct device * dev)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (int) arch_syscall_invoke1(*(uintptr_t *)&dev, K_SYSCALL_COUNTER_START);
	}
#endif
	compiler_barrier();
	return z_impl_counter_start(dev);
}


extern int z_impl_counter_stop(const struct device * dev);
static inline int counter_stop(const struct device * dev)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (int) arch_syscall_invoke1(*(uintptr_t *)&dev, K_SYSCALL_COUNTER_STOP);
	}
#endif
	compiler_barrier();
	return z_impl_counter_stop(dev);
}


extern int z_impl_counter_get_value(const struct device * dev, uint32_t * ticks);
static inline int counter_get_value(const struct device * dev, uint32_t * ticks)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (int) arch_syscall_invoke2(*(uintptr_t *)&dev, *(uintptr_t *)&ticks, K_SYSCALL_COUNTER_GET_VALUE);
	}
#endif
	compiler_barrier();
	return z_impl_counter_get_value(dev, ticks);
}


extern int z_impl_counter_set_channel_alarm(const struct device * dev, uint8_t chan_id, const struct counter_alarm_cfg * alarm_cfg);
static inline int counter_set_channel_alarm(const struct device * dev, uint8_t chan_id, const struct counter_alarm_cfg * alarm_cfg)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (int) arch_syscall_invoke3(*(uintptr_t *)&dev, *(uintptr_t *)&chan_id, *(uintptr_t *)&alarm_cfg, K_SYSCALL_COUNTER_SET_CHANNEL_ALARM);
	}
#endif
	compiler_barrier();
	return z_impl_counter_set_channel_alarm(dev, chan_id, alarm_cfg);
}


extern int z_impl_counter_cancel_channel_alarm(const struct device * dev, uint8_t chan_id);
static inline int counter_cancel_channel_alarm(const struct device * dev, uint8_t chan_id)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (int) arch_syscall_invoke2(*(uintptr_t *)&dev, *(uintptr_t *)&chan_id, K_SYSCALL_COUNTER_CANCEL_CHANNEL_ALARM);
	}
#endif
	compiler_barrier();
	return z_impl_counter_cancel_channel_alarm(dev, chan_id);
}


extern int z_impl_counter_set_top_value(const struct device * dev, const struct counter_top_cfg * cfg);
static inline int counter_set_top_value(const struct device * dev, const struct counter_top_cfg * cfg)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (int) arch_syscall_invoke2(*(uintptr_t *)&dev, *(uintptr_t *)&cfg, K_SYSCALL_COUNTER_SET_TOP_VALUE);
	}
#endif
	compiler_barrier();
	return z_impl_counter_set_top_value(dev, cfg);
}


extern int z_impl_counter_get_pending_int(const struct device * dev);
static inline int counter_get_pending_int(const struct device * dev)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (int) arch_syscall_invoke1(*(uintptr_t *)&dev, K_SYSCALL_COUNTER_GET_PENDING_INT);
	}
#endif
	compiler_barrier();
	return z_impl_counter_get_pending_int(dev);
}


extern uint32_t z_impl_counter_get_top_value(const struct device * dev);
static inline uint32_t counter_get_top_value(const struct device * dev)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (uint32_t) arch_syscall_invoke1(*(uintptr_t *)&dev, K_SYSCALL_COUNTER_GET_TOP_VALUE);
	}
#endif
	compiler_barrier();
	return z_impl_counter_get_top_value(dev);
}


extern int z_impl_counter_set_guard_period(const struct device * dev, uint32_t ticks, uint32_t flags);
static inline int counter_set_guard_period(const struct device * dev, uint32_t ticks, uint32_t flags)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (int) arch_syscall_invoke3(*(uintptr_t *)&dev, *(uintptr_t *)&ticks, *(uintptr_t *)&flags, K_SYSCALL_COUNTER_SET_GUARD_PERIOD);
	}
#endif
	compiler_barrier();
	return z_impl_counter_set_guard_period(dev, ticks, flags);
}


extern uint32_t z_impl_counter_get_guard_period(const struct device * dev, uint32_t flags);
static inline uint32_t counter_get_guard_period(const struct device * dev, uint32_t flags)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (uint32_t) arch_syscall_invoke2(*(uintptr_t *)&dev, *(uintptr_t *)&flags, K_SYSCALL_COUNTER_GET_GUARD_PERIOD);
	}
#endif
	compiler_barrier();
	return z_impl_counter_get_guard_period(dev, flags);
}


#ifdef __cplusplus
}
#endif

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic pop
#endif

#endif
#endif /* include guard */
