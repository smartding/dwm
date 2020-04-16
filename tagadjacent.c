void
tagtoleft(const Arg *arg) {
	if(selmon->sel != NULL
	&& __builtin_popcount(selmon->tagset[selmon->seltags] & TAGMASK) == 1){
		if(selmon->tagset[selmon->seltags] > 1) { /* if not on the first(left most) tag */
			selmon->sel->tags >>= 1;
			unsigned int newtagset = selmon->tagset[selmon->seltags] >> 1;
			selmon->seltags ^= 1; /* toggle sel tagset */
			selmon->tagset[selmon->seltags] = newtagset;
		}else{/* if on the first tag */
			selmon->sel->tags = 1 << LENGTH(tags) -1;
			selmon->seltags ^= 1; /* toggle sel tagset */
			selmon->tagset[selmon->seltags] = 1 << LENGTH(tags) -1;
		}
		focus(NULL);
		arrange(selmon);
	}
}

void
tagtoright(const Arg *arg) {
	if(selmon->sel != NULL
	&& __builtin_popcount(selmon->tagset[selmon->seltags] & TAGMASK) == 1){
		if(selmon->tagset[selmon->seltags] & (TAGMASK >> 1)) {/* if not on the last(right most) tag */
			selmon->sel->tags <<= 1;
			unsigned int newtagset = selmon->tagset[selmon->seltags] << 1;
			selmon->seltags ^= 1; /* toggle sel tagset */
			selmon->tagset[selmon->seltags] = newtagset;
		}else{
			selmon->sel->tags = 1;
			selmon->seltags ^= 1; /* toggle sel tagset */
			selmon->tagset[selmon->seltags] = 1;
		}
		focus(NULL);
		arrange(selmon);
	}
}
