//Search:

	HEADER_CG_KEY_AGREEMENT = 0xfb,

//Add on:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
	HEADER_CG_ITEM_LOCK = 78,
#endif

//Add to end:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
typedef struct command_item_lock
{
	BYTE  header;
	TItemPos source_pos;
	TItemPos target_pos;
} TPacketCGItemLock;
#endif