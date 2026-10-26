/* SPDX-License-Identifier: GPL-2.0 */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM fork

#if !defined(_TRACE_FORK_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_FORK_H

#include <linux/sched/task.h>
#include <linux/tracepoint.h>

/*
 * fork 打桩学习实验（级 2）：自定义 TRACE_EVENT，
 * 挂点在 kernel_clone() 入口。照抄 drivers/android/binder_trace.h 模式。
 */
TRACE_EVENT(fork_entry,
	TP_PROTO(const struct kernel_clone_args *args),
	TP_ARGS(args),
	TP_STRUCT__entry(
		__field(u64, flags)
		__field(int, exit_signal)
		__field(unsigned long, stack)
	),
	TP_fast_assign(
		__entry->flags = args->flags;
		__entry->exit_signal = args->exit_signal;
		__entry->stack = args->stack;
	),
	TP_printk("flags=%#llx exit_signal=%d stack=%#lx",
		  (unsigned long long)__entry->flags,
		  __entry->exit_signal, __entry->stack)
);

#endif /* _TRACE_FORK_H */

#undef TRACE_INCLUDE_PATH
#undef TRACE_INCLUDE_FILE
#define TRACE_INCLUDE_PATH .
#define TRACE_INCLUDE_FILE fork_trace
#include <trace/define_trace.h>
