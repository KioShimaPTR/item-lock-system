//Add to end:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
bool CPythonNetworkStream::SendItemLockedPacket(TItemPos source_pos, TItemPos target_pos)
{
	if (!__CanActMainInstance())
		return true;

	TPacketCGItemLock itemLockedPacket;
	itemLockedPacket.header = HEADER_CG_ITEM_LOCK;
	itemLockedPacket.source_pos = source_pos;
	itemLockedPacket.target_pos = target_pos;

	if (!Send(sizeof(TPacketCGItemLock), &itemLockedPacket))
	{
		Tracen("SendItemLockedPacket Error");
		return false;
	}

#ifdef _DEBUG
	Tracef(" << SendItemLockedPacket(source_pos=%d, target_pos=%d)\n", source_pos, target_pos);
#endif

	return SendSequence();
}
#endif