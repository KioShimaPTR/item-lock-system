//Search:

void CInputMain::ItemToItem(LPCHARACTER ch, const char * pcData)
{
	TPacketCGItemUseToItem * p = (TPacketCGItemUseToItem *) pcData;
	if (ch)
		ch->UseItem(p->Cell, p->TargetCell);
}

//Add below:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
void CInputMain::ItemLocked(LPCHARACTER ch, const char * pcData)
{
	TPacketCGItemLock * p = (TPacketCGItemLock *) pcData;

	if (ch)
		ch->IsItemLocked(p->source_pos, p->target_pos);
}
#endif

//Search:

	}
	return (iExtraLen);

//Add on:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
		case HEADER_CG_ITEM_LOCK:
			ItemLocked(ch, c_pData);
			break;
#endif