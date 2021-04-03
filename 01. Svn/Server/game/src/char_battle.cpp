//Search:

				pkItem = GetInventoryItem(vec_bSlots[i]);

				if (IS_SET(pkItem->GetAntiFlag(), ITEM_ANTIFLAG_GIVE | ITEM_ANTIFLAG_PKDROP))
					continue;

//Add below:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
				if (pkItem->GetItemLock() == true)
					continue;
#endif

//Search:

				pkItem = GetWear(vec_bSlots[i]);

				if (IS_SET(pkItem->GetAntiFlag(), ITEM_ANTIFLAG_GIVE | ITEM_ANTIFLAG_PKDROP))
					continue;

//Add below:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
				if (pkItem->GetItemLock() == true)
					continue;
#endif