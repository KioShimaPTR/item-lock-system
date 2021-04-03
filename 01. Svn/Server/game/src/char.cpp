//Search:

	m_iSyncHackCount = 0;

//Add below:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
	m_dwItemLockLastTime = 0;
#endif

//Search:

			if (pkItem->GetOwner() != this)
				return;

//Add below:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
			if (pkItem->GetItemLock() == true)
			{
				ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Kilitli itemi pazara koyamazsýn.");
				return;
			}
#endif