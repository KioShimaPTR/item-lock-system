//Search:

								case USE_CHANGE_ATTRIBUTE :

//Add below:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
									if (item2->GetItemLock() == true)
									{
										ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Kilitli iteme efsun basamazsýn.");
										return false;
									}
#endif

//Search:

								case USE_ADD_ATTRIBUTE :

//Add below:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
									if (item2->GetItemLock() == true)
									{
										ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Kilitli iteme efsun ekleyemezsin.");
										return false;
									}
#endif

//Search:

								case USE_ADD_ATTRIBUTE2 :
									if (item2->GetAttributeSetIndex() == -1)
									{
										ChatPacket(CHAT_TYPE_INFO, LC_TEXT("¼Ó¼ºÀ» º¯°æÇÒ ¼ö ¾ø´Â ¾ÆÀÌÅÛÀÔ´Ï´Ù."));
										return false;
									}

//Add below:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
									if (item2->GetItemLock() == true)
									{
										ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Kilitli iteme efsun basamazsýn.");
										return false;
									}
#endif

//Search:

		case ITEM_METIN:
			{
				LPITEM item2;

				if (!IsValidItemPosition(DestCell) || !(item2 = GetItem(DestCell)))
					return false;

//Add below:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
				if (item2->GetItemLock() == true)
				{
					ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Kilitli iteme taþ ekleyemezsin.");
					return false;
				}
#endif

//Search:

	if (quest::CQuestManager::instance().GetPCForce(GetPlayerID())->IsRunning() == true)
		return false;

//Add below:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
	if (item->GetItemLock() == true)
	{
		ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Kilitli itemi silemezsin.");
		return false;
	}
#endif

//Search:

	if (IS_SET(item->GetAntiFlag(), ITEM_ANTIFLAG_SELL))
		return false;

//Add below:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
	if (item->GetItemLock() == true)
	{
		ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Kilitli itemi satamazsýn.");
		return false;
	}
#endif

//Search:

	if (DISTANCE_APPROX(GetX() - from->GetX(), GetY() - from->GetY()) > 2000)
		return false;

//Add below:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
	if (item->GetItemLock() == true)
	{
		from->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Kilitli itemi yükseltemezsin.");
		return false;
	}
#endif

//Add to end:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
void CHARACTER::SetItemLockPassword(int password)
{
	DBManager::instance().DirectQuery("UPDATE account.account SET itemlockpassword = '%d' WHERE id = '%d';", password, GetDesc()->GetAccountTable().id);
}

int CHARACTER::GetItemLockPassword() const
{
	std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT itemlockpassword FROM account.account WHERE id = '%d';", GetDesc()->GetAccountTable().id));
	if (pMsg->Get()->uiNumRows == 0)
		return 0;

	MYSQL_ROW row = mysql_fetch_row(pMsg->Get()->pSQLResult);
	return atoi(row[0]);
}

bool CHARACTER::IsItemLocked(TItemPos source_pos, TItemPos target_pos)
{
	LPITEM item;
	LPITEM item_target;

	if (!IsValidItemPosition(source_pos) || !(item = GetItem(source_pos)))
		return false;

	if (!IsValidItemPosition(target_pos) || !(item_target = GetItem(target_pos)))
		return false;

	int iPulse = thecore_pulse();

	if (iPulse - GetLastItemLockLastTime() < passes_per_sec * 2)
	{
		ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Bu kadar hýzlý iþlem yapamazsýn.");
		return false;
	}

	SetLastItemLockLastTime(iPulse);

	if (item->GetVnum() != 50263 && item->GetVnum() != 50264)
		return false;

	if (item->IsExchanging())
		return false;

	if (!CanHandleItem())
		return false;

	if (item_target->IsExchanging())
		return false;

	if (item_target->IsEquipped())
		return false;

	if (item_target->GetType() != ITEM_WEAPON && item_target->GetType() != ITEM_ARMOR && item_target->GetType() != ITEM_BELT)
	{
		ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Sadece silah, zýrh ve iç itemlerini kilitleyebilirsin.");
		return false;
	}

	if (item->GetVnum() == 50263 && item_target->GetItemLock() == true)
	{
		ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Zaten itemin kilitli durumda.");
		return false;
	}

	if (item->GetVnum() == 50264 && item_target->GetItemLock() != true)
	{
		ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Zaten itemin kilitli deðil.");
		return false;
	}

	if (GetItemLockPassword() != 0)
		ChatPacket(CHAT_TYPE_COMMAND, "ItemLock %d %d", source_pos.cell, target_pos.cell);
	else
		ChatPacket(CHAT_TYPE_COMMAND, "CreateItemLock %d %d", source_pos.cell, target_pos.cell);

	return true;
}
#endif