/* SPDX-License-Identifier: GPL-2.0 */

#include <linux/slab.h>
#include <linux/vmalloc.h>

static inline bool sb_rdonly(const struct super_block *sb) {
	return sb->s_flags & MS_RDONLY;
}

#define bio_set_dev(bio, bdev)	((bio)->bi_bdev = (bdev))

static inline void *erofs_kvmalloc(size_t size, gfp_t flags)
{
	void *ret;

	ret = kmalloc(size, flags | __GFP_NOWARN);
	if (!ret)
		ret = __vmalloc(size, flags, PAGE_KERNEL);
	return ret;
}

static inline void *erofs_kvzalloc(size_t size, gfp_t flags)
{
	void *ret;

	ret = kzalloc(size, flags | __GFP_NOWARN);
	if (!ret)
		ret = __vmalloc(size, flags | __GFP_ZERO, PAGE_KERNEL);
	return ret;
}
