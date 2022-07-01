// event结构体的定义
// 封装了句柄,实践类型,回调函数以及其他必要的标志和数据

/*
 * Copyright (c) 2000-2007 Niels Provos <provos@citi.umich.edu>
 * Copyright (c) 2007-2012 Niels Provos and Nick Mathewson
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _EVENT2_EVENT_STRUCT_H_
#define _EVENT2_EVENT_STRUCT_H_

/** @file event2/event_struct.h

  Structures used by event.h.  Using these structures directly WILL harm
  forward compatibility: be careful.

  No field declared in this file should be used directly in user code.  Except
  for historical reasons, these fields would not be exposed at all.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <event2/event-config.h>
#ifdef _EVENT_HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef _EVENT_HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

/* For int types. */
#include <event2/util.h>

/* For evkeyvalq */
#include <event2/keyvalq_struct.h>
// 事件标志:
#define EVLIST_TIMEOUT	0x01
#define EVLIST_INSERTED	0x02
#define EVLIST_SIGNAL	0x04
#define EVLIST_ACTIVE	0x08
#define EVLIST_INTERNAL	0x10
#define EVLIST_INIT	0x80

/* EVLIST_X_ Private space: 0x1000-0xf000 */
#define EVLIST_ALL	(0xf000 | 0x9f)

/* Fix so that people don't have to run with <sys/queue.h> */
#ifndef TAILQ_ENTRY
#define _EVENT_DEFINED_TQENTRY
#define TAILQ_ENTRY(type)						\
struct {								\
	struct type *tqe_next;	/* next element */			\
	struct type **tqe_prev;	/* address of previous next element */	\
}
#endif /* !TAILQ_ENTRY */

#ifndef TAILQ_HEAD
#define _EVENT_DEFINED_TQHEAD
#define TAILQ_HEAD(name, type)			\
struct name {					\
	struct type *tqh_first;			\
	struct type **tqh_last;			\
}
#endif

struct event_base;
struct event {
	TAILQ_ENTRY(event) ev_active_next;	// 活动事件队列,尾队列(一种双向队列)实现
	TAILQ_ENTRY(event) ev_next;		// 注册事件队列
									// 包含I/O事件处理器,信号事件处理器
	/* for managing timeouts */
	union {
		// 定时器事件分为两类:通用的,其他的
		// 通用定时器存储在尾队列中,其他定时器存储在时间堆中
		TAILQ_ENTRY(event) ev_next_with_common_timeout;	// 用于通用定时器,指出该定时器在通用定时器队列中的位置
		int min_heap_idx;	// 用于其他定时器,指出定时器在时间堆中的位置
	} ev_timeout_pos;	// 用于定时事件处理器
	evutil_socket_t ev_fd;	// 文件描述符值(对于I/O事件处理器)或
							// 信号值(对于信号事件处理器)

	struct event_base *ev_base;	// 该事件处理器从属的event_base实例

	union {
		/* used for io events */
		struct {
			TAILQ_ENTRY(event) ev_io_next;	// 具有相同文件描述符的I/O事件处理器队列
			struct timeval ev_timeout;
		} ev_io;

		/* used by signal events */
		struct {
			TAILQ_ENTRY(event) ev_signal_next;	// 具有相同信号值的信号事件处理器队列
			short ev_ncalls;	// 指定信号事件发生时,执行回调函数多少次
			/* Allows deletes in callback */
			short *ev_pncalls;	// NULL或者指向ev_ncalls
		} ev_signal;
	} _ev;

	short ev_events;	// 事件类型,可以按位或,除非是互斥事件
	short ev_res;		/* result passed to event callback */
						// 当前激活事件的类型
	short ev_flags;		// 事件标志
	ev_uint8_t ev_pri;	/* smaller numbers are higher priority */	// 事件优先级
	ev_uint8_t ev_closure;	// 指定执行事件处理器的回调函数时的行为
	struct timeval ev_timeout;	// 仅对定时器,指定定时器的超时值

	/* allows us to adopt for different types of events */
	void (*ev_callback)(evutil_socket_t, short, void *arg);	// 事件处理器的回调函数
	void *ev_arg;	// 回调函数的参数
};

TAILQ_HEAD (event_list, event);

#ifdef _EVENT_DEFINED_TQENTRY
#undef TAILQ_ENTRY
#endif

#ifdef _EVENT_DEFINED_TQHEAD
#undef TAILQ_HEAD
#endif

#ifdef __cplusplus
}
#endif

#endif /* _EVENT2_EVENT_STRUCT_H_ */
