#Search:

		}

		self.serverCommander=stringCommander.Analyzer()

#Add on:

			"ItemLock"					: self.itemlock,
			"CreateItemLock"			: self.createitemlock,

#Add to end:

	def itemlock(self, source_pos, target_pos):
		if self.interface:
			self.interface.itemlock(int(source_pos), int(target_pos))

	def createitemlock(self, source_pos, target_pos):
		if self.interface:
			self.interface.createitemlock(int(source_pos), int(target_pos))