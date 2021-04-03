#Search:

		elif item.IsMetin(srcItemVID):
			self.AttachMetinToItem(srcItemSlotPos, dstItemSlotPos)

#Add below:

		elif player.GetItemIndex(srcItemSlotPos) == 50263 or player.GetItemIndex(srcItemSlotPos) == 50264:
			self.ItemLocked(srcItemSlotPos, dstItemSlotPos)

#Search:

		self.attachBonusDialog.Open(sourceSlotPos, targetSlotPos)

#Add below:

	def ItemLocked(self, sourceSlotPos, targetSlotPos):
		net.SendItemLockedPacket(sourceSlotPos, targetSlotPos)