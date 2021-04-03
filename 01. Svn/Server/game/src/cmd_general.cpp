//Add to end:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
ACMD(do_item_lock)
{
	char arg1[256];
	char arg2[256];
	char arg3[256];

	three_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2), arg3, sizeof(arg3));

	if (!*arg1 || !*arg2 || !*arg3)
		return;

	int iPulse = thecore_pulse();

	if (iPulse - ch->GetLastItemLockLastTime() < passes_per_sec * 2)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Bu kadar h�zl� i�lem yapamazs�n.");
		return;
	}

	ch->SetLastItemLockLastTime(iPulse);

	if (ch->IsDead() || ch->GetExchange() || ch->GetMyShop() || ch->IsOpenSafebox() || ch->IsCubeOpen() || ch->GetOfflineShopOwner())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�ٸ� �ŷ���(â��,��ȯ,����)���� ���λ����� ����� �� �����ϴ�."));
		return;
	}

	int password = 0;
	str_to_number(password, arg1);

	DWORD dwVnum = 0;
	str_to_number(dwVnum, arg2);

	DWORD dwVnum2 = 0;
	str_to_number(dwVnum2, arg3);

	if (dwVnum < 0 || dwVnum >= INVENTORY_MAX_NUM)
		return;

	if (dwVnum2 < 0 || dwVnum2 >= INVENTORY_MAX_NUM)
		return;

	LPITEM item = ch->GetInventoryItem(dwVnum);
	LPITEM item2 = ch->GetInventoryItem(dwVnum2);

	if (!item || item->IsExchanging() || item->GetCount() <= 0)
		return;

	if (item->GetVnum() != 50263 && item->GetVnum() != 50264)
		return;

	if (!item2 || item2->IsExchanging())
		return;

	if (item2->GetItemLock() == false)
	{
		if (ch->GetItemLockPassword() != 0)
		{
			if (std::to_string(password).length() < 4 || std::to_string(password).length() > 6)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifreniz 4-6 karakter aras� olabilir.");
				return;
			}

			if(!sadece_rakam(std::to_string(password)))
			{
				ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifreniz sadece rakamdan olu�abilir.");
				return;
			}

			if (ch->GetItemLockPassword() == password)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifre do�ru, iteminiz ba�ar�yla kilitlendi.");
				item2->SetItemLock(true);
				item->SetCount(item->GetCount() - 1);
			}
			else
			{
				ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifre yanl��, iteminiz kilitlenemedi.");
				return;
			}
		}
		else
		{
			if (std::to_string(password).length() < 4 || std::to_string(password).length() > 6)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifreniz 4-6 karakter aras� olabilir.");
				return;
			}
			if(!sadece_rakam(std::to_string(password)))
			{
				ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifreniz sadece rakamdan olu�abilir.");
				return;
			}

			ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �tem kilit �ifreniz ba�ar�yla olu�turuldu, iteminiz kilitlendi.");
			ch->SetItemLockPassword(password);
			item2->SetItemLock(true);
			item->SetCount(item->GetCount() - 1);
		}
	}
	else
	{
		if (std::to_string(password).length() < 4 || std::to_string(password).length() > 6)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifreniz 4-6 karakter aras� olabilir.");
			return;
		}

		if(!sadece_rakam(std::to_string(password)))
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifreniz sadece rakamdan olu�abilir.");
			return;
		}

		if (ch->GetItemLockPassword() == password)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifre do�ru, iteminizin kilidi kald�r�ld�.");
			item2->SetItemLock(false);
			item->SetCount(item->GetCount() - 1);
		}
		else
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifre yanl��, iteminizin kilidi kald�r�lmad�.");
			return;
		}
	}
}

ACMD(do_item_lock_passwd_change)
{
	char arg1[256];
	char arg2[256];
	char arg3[256];

	three_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2), arg3, sizeof(arg3));

	if (!*arg1 || !*arg2 || !*arg3)
		return;

	int iPulse = thecore_pulse();

	if (iPulse - ch->GetLastItemLockLastTime() < passes_per_sec * 2)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Bu kadar h�zl� i�lem yapamazs�n.");
		return;
	}

	ch->SetLastItemLockLastTime(iPulse);

	int password = 0;
	str_to_number(password, arg1);

	int newpassword = 0;
	str_to_number(newpassword, arg2);

	int newpassword2 = 0;
	str_to_number(newpassword2, arg3);

	if (std::to_string(password).length() < 4 || std::to_string(password).length() > 6)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifreniz 4-6 karakter aras� olabilir.");
		return;
	}

	if (std::to_string(newpassword).length() < 4 || std::to_string(newpassword).length() > 6)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifreniz 4-6 karakter aras� olabilir.");
		return;
	}

	if (std::to_string(newpassword2).length() < 4 || std::to_string(newpassword2).length() > 6)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifreniz 4-6 karakter aras� olabilir.");
		return;
	}

	if (!sadece_rakam(std::to_string(password)))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifreniz sadece rakamdan olu�abilir.");
		return;
	}

	if (!sadece_rakam(std::to_string(newpassword)))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifreniz sadece rakamdan olu�abilir.");
		return;
	}

	if (!sadece_rakam(std::to_string(newpassword2)))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifreniz sadece rakamdan olu�abilir.");
		return;
	}

	if (newpassword == newpassword2)
	{
		if (ch->GetItemLockPassword() == password)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �tem kilit �ifreniz ba�ar�yla de�i�tirildi.");
			ch->SetItemLockPassword(newpassword);
		}
		else
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifreler birbiriyle uyu�mamaktad�r.");
			return;
		}
	}
	else
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] �ifreler birbiriyle uyu�mamaktad�r.");
		return;
	}
}
#endif