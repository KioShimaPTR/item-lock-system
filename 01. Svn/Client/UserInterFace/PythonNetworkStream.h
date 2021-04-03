//Search:

	bool SendPointResetPacket();

//Add on:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
	bool SendItemLockedPacket(TItemPos source_pos, TItemPos target_pos);
#endif