//Add to end:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
void CItem::SetItemLock(bool lockstatus)
{
	if (lockstatus == true)
		SetForceAttribute(6, 0, 1);
	else
		SetForceAttribute(6, 0, 0);
}

bool CItem::GetItemLock()
{
	if (GetAttributeValue(6) == 1)
		return true;
	else
		return false;
}
#endif