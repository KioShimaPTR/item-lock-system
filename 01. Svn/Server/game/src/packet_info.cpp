//Search:

	Set(HEADER_CG_STATE_CHECKER, sizeof(BYTE), "ServerStateCheck", false);

//Add below:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
	Set(HEADER_CG_ITEM_LOCK, sizeof(TPacketCGItemLock), "IsItemLock", false);
#endif