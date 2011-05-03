/*
 * Copyright (C) 2006 by Latchesar Ionkov <lucho@ionkov.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

typedef struct Npcpool Npcpool;

struct Npcpool {
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
	u32		maxid;
	int		msize;
	u8*		map;
};

struct Npcfsys {
	pthread_mutex_t	lock;
	u32		msize;
	Nptrans*	trans;

	int		refcount;
	Npcpool*	tagpool;
	Npcpool*	fidpool;
};

Npcfsys *npc_create_fsys(int fd, int msize);
void npc_disconnect_fsys(Npcfsys *fs);
void npc_incref_fsys(Npcfsys *fs);
void npc_decref_fsys(Npcfsys *fs);

Npcpool *npc_create_pool(u32 maxid);
void npc_destroy_pool(Npcpool *p);
u32 npc_get_id(Npcpool *p);
void npc_put_id(Npcpool *p, u32 id);

Npcfid *npc_fid_alloc(Npcfsys *fs);
void npc_fid_free(Npcfid *fid);

int npc_rpc(Npcfsys *fs, Npfcall *tc, Npfcall **rc);
