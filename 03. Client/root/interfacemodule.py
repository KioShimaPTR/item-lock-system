#Add imports

import uiitemlock

#Search:

	def __MakeCubeResultWindow(self):
		self.wndCubeResult = uiCube.CubeResultWindow()
		self.wndCubeResult.LoadWindow()
		self.wndCubeResult.Hide()

#Add below:

	def __MakeItemLockWindow(self):
		self.wndItemLockWindow = uiitemlock.ItemLockDialog()
		self.wndItemLockWindow.Hide()

#Search:

		self.__MakeCubeResultWindow()

#Add below:

		self.__MakeItemLockWindow()

#Search:

		if self.wndItemSelect:
			self.wndItemSelect.Destroy()

#Add below:

		if self.wndItemLockWindow:
			self.wndItemLockWindow.Destroy()

#Search:

		del self.wndItemSelect

#Add below:

		del self.wndItemLockWindow

#Search:

	def __HideWindows(self):

#Add on:

	def itemlock(self, source_pos, target_pos):
		self.wndItemLockWindow.Open(True, source_pos, target_pos)

	def createitemlock(self, source_pos, target_pos):
		self.wndItemLockWindow.Open(False, source_pos, target_pos)