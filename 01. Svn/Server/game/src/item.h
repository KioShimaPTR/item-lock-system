//Search:

	protected:
		bool		EquipEx(bool is_equip);

//Add on:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
		void		SetItemLock(bool lockstatus);
		bool		GetItemLock();
#endif