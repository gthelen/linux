#undef TRACE_SYSTEM
#define TRACE_SYSTEM memcontrol

#if !defined(_TRACE_MEMCONTROL_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_MEMCONTROL_H

#include <linux/types.h>
#include <linux/tracepoint.h>

TRACE_EVENT(mem_cgroup_mark_inode_dirty,
	TP_PROTO(struct inode *inode),

	TP_ARGS(inode),

	TP_STRUCT__entry(
		__field(int, dev_major)
		__field(int, dev_minor)
		__field(unsigned long, ino)
		__field(unsigned short, css_id)
		),

	TP_fast_assign(
		__entry->dev_major = MAJOR(inode->i_sb->s_dev);
		__entry->dev_minor = MINOR(inode->i_sb->s_dev);
		__entry->ino = inode->i_ino;
		__entry->css_id =
			inode->i_mapping ? inode->i_mapping->i_memcg : 0;
		),

	TP_printk("dev=%d,%d ino=%ld css_id=%d",
		  __entry->dev_major, __entry->dev_minor,
		  __entry->ino, __entry->css_id)
)

#endif /* _TRACE_MEMCONTROL_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
