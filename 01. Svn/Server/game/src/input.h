//Search:

		void		Refine(LPCHARACTER ch, const char* c_pData);

//Add below:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
		void		ItemLocked(LPCHARACTER ch, const char * pcData);
#endif