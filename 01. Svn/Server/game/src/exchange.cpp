//Search:

	if (IS_SET(item->GetAntiFlag(), ITEM_ANTIFLAG_GIVE))
	{
		m_pOwner->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�������� �ǳ��� �� �����ϴ�."));
		return false;
	}

//Add below:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
	if (item->GetItemLock() == true)
	{
		m_pOwner->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Kilitli itemle ticaret yapamazs�n.");
		return false;
	}
#endif