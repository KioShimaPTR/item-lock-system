//Search:

		void			SetLastAttacked(DWORD time);

//Add below:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
		void			SetLastItemLockLastTime(int time) { m_dwItemLockLastTime = time; }
		int				GetLastItemLockLastTime() const	{ return m_dwItemLockLastTime; }
#endif

//Search:

		bool			m_bStaminaConsume;

//Add below:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
		int				m_dwItemLockLastTime;
#endif

//Search:

		bool			IsRefineThroughGuild() const;

//Add on:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
		void			SetItemLockPassword(int password);
		int				GetItemLockPassword() const;
		bool			IsItemLocked(TItemPos source_pos, TItemPos target_pos);
#endif