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
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Bu kadar hýzlý iþlem yapamazsýn.");
		return;
	}

	ch->SetLastItemLockLastTime(iPulse);

	if (ch->IsDead() || ch->GetExchange() || ch->GetMyShop() || ch->IsOpenSafebox() || ch->IsCubeOpen() || ch->GetOfflineShopOwner())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("´Ù¸¥ °Å·¡Áß(Ã¢°í,±³È¯,»óÁ¡)¿¡´Â °³ÀÎ»óÁ¡À» »ç¿ëÇÒ ¼ö ¾ø½À´Ï´Ù."));
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
				ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifreniz 4-6 karakter arasý olabilir.");
				return;
			}

			if(!sadece_rakam(std::to_string(password)))
			{
				ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifreniz sadece rakamdan oluþabilir.");
				return;
			}

			if (ch->GetItemLockPassword() == password)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifre doðru, iteminiz baþarýyla kilitlendi.");
				item2->SetItemLock(true);
				item->SetCount(item->GetCount() - 1);
			}
			else
			{
				ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifre yanlýþ, iteminiz kilitlenemedi.");
				return;
			}
		}
		else
		{
			if (std::to_string(password).length() < 4 || std::to_string(password).length() > 6)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifreniz 4-6 karakter arasý olabilir.");
				return;
			}
			if(!sadece_rakam(std::to_string(password)))
			{
				ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifreniz sadece rakamdan oluþabilir.");
				return;
			}

			ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Ýtem kilit þifreniz baþarýyla oluþturuldu, iteminiz kilitlendi.");
			ch->SetItemLockPassword(password);
			item2->SetItemLock(true);
			item->SetCount(item->GetCount() - 1);
		}
	}
	else
	{
		if (std::to_string(password).length() < 4 || std::to_string(password).length() > 6)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifreniz 4-6 karakter arasý olabilir.");
			return;
		}

		if(!sadece_rakam(std::to_string(password)))
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifreniz sadece rakamdan oluþabilir.");
			return;
		}

		if (ch->GetItemLockPassword() == password)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifre doðru, iteminizin kilidi kaldýrýldý.");
			item2->SetItemLock(false);
			item->SetCount(item->GetCount() - 1);
		}
		else
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifre yanlýþ, iteminizin kilidi kaldýrýlmadý.");
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
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Bu kadar hýzlý iþlem yapamazsýn.");
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
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifreniz 4-6 karakter arasý olabilir.");
		return;
	}

	if (std::to_string(newpassword).length() < 4 || std::to_string(newpassword).length() > 6)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifreniz 4-6 karakter arasý olabilir.");
		return;
	}

	if (std::to_string(newpassword2).length() < 4 || std::to_string(newpassword2).length() > 6)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifreniz 4-6 karakter arasý olabilir.");
		return;
	}

	if (!sadece_rakam(std::to_string(password)))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifreniz sadece rakamdan oluþabilir.");
		return;
	}

	if (!sadece_rakam(std::to_string(newpassword)))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifreniz sadece rakamdan oluþabilir.");
		return;
	}

	if (!sadece_rakam(std::to_string(newpassword2)))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifreniz sadece rakamdan oluþabilir.");
		return;
	}

	if (newpassword == newpassword2)
	{
		if (ch->GetItemLockPassword() == password)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Ýtem kilit þifreniz baþarýyla deðiþtirildi.");
			ch->SetItemLockPassword(newpassword);
		}
		else
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifreler birbiriyle uyuþmamaktadýr.");
			return;
		}
	}
	else
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "[Bilgi] Þifreler birbiriyle uyuþmamaktadýr.");
		return;
	}
}
#endif