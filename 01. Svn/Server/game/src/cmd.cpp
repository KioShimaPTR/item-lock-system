//Search:

struct command_info cmd_info[] =

//Add on:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
ACMD(do_item_lock);
ACMD(do_item_lock_passwd_change);
#endif

//Search:

	{ "\n",		NULL,			0,			POS_DEAD,	GM_IMPLEMENTOR	}

//Add on:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
	{ "item_lock",	do_item_lock,	0,	POS_DEAD,	GM_PLAYER	},
	{ "item_lock_passwd_change",	do_item_lock_passwd_change,	0,	POS_DEAD,	GM_PLAYER },
#endif