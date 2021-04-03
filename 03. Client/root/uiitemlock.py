# Author: Bahadýr Bozdað or Cosby or KioShima
# File name: uiitemlock.py

import app
import net
import player
import item
import ui
import chat
import uiToolTip
import mousemodule
import localeInfo
import uicommon
import constInfo
import grp

class ItemLockDialog(ui.ScriptWindow):
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.children = []
		self.__LoadScript()
		self.targetItemPos = 0
		self.sourceItemPos = 0
		self.dialogHeight = 0
		self.isCreate = False

	def __LoadScript(self):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, "uiscript/itemlockdialog.py")
		except:
			import exception
			exception.Abort("ItemLockDialog.__LoadScript.LoadObject")
		try:
			self.board = self.GetChild("Board")
			self.titleBar = self.GetChild("TitleBar")
			self.lockText = self.GetChild("lockText")
			self.lockText2 = self.GetChild("lockText2")
			self.GetChild("change_pw_button").SetEvent(self.ChangePW)
			self.item_lock_pw_value = self.GetChild("item_lock_pw_value")
			self.item_lock_pw_value.OnIMEReturn = self.Accept
			self.GetChild("accept_button").SetEvent(self.Accept)
		except:
			import exception
			exception.Abort("ItemLockDialog.__LoadScript.BindObject")

		toolTip = uiToolTip.ItemToolTip()
		toolTip.SetParent(self)
		toolTip.SetPosition(15, 38)
		toolTip.SetFollow(False)
		toolTip.Show()
		self.toolTip = toolTip
		self.slotList = []
		self.slotList2 = []
		for i in xrange(3):
			slot = self.__MakeSlot()
			slot.SetParent(self)
			slot.SetWindowVerticalAlignCenter()
			self.slotList.append(slot)
			slot2 = self.__MakeSlot2()
			slot2.SetParent(self)
			slot2.SetWindowVerticalAlignCenter()
			self.slotList2.append(slot2)

		itemImage = self.__MakeItemImage()
		itemImage.SetParent(self)
		itemImage.SetWindowVerticalAlignCenter()
		itemImage.SetPosition(20, 20)
		self.itemImage = itemImage

		itemImage2 = self.__MakeItemImage2()
		itemImage2.SetParent(self)
		itemImage2.SetWindowVerticalAlignCenter()
		itemImage2.SetPosition(266, 20)
		self.itemImage2 = itemImage2

		self.titleBar.SetCloseEvent(ui.__mem_func__(self.Close))
		self.wndChangePassword = ItemLockChangePasswd()

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def __MakeSlot(self):
		slot = ui.ImageBox()
		slot.LoadImage("d:/ymir work/ui/public/slot_base.sub")
		slot.Show()
		self.children.append(slot)
		return slot

	def __MakeSlot2(self):
		slot2 = ui.ImageBox()
		slot2.LoadImage("d:/ymir work/ui/public/slot_base.sub")
		slot2.Show()
		self.children.append(slot2)
		return slot2

	def __MakeItemImage(self):
		itemImage = ui.ImageBox()
		itemImage.Show()
		self.children.append(itemImage)
		return itemImage

	def __MakeItemImage2(self):
		itemImage2 = ui.ImageBox()
		itemImage2.Show()
		self.children.append(itemImage2)
		return itemImage2

	def Destroy(self):
		self.ClearDictionary()
		self.board = 0
		self.titleBar = 0
		self.lockText = 0
		self.lockText2 = 0
		item_lock_pw_value = 0
		self.toolTip = 0
		self.slotList = []
		self.slotList2 = []
		self.children = []

	def Open(self, isCreate, sourceItemPos, targetItemPos):
		self.item_lock_pw_value.SetText("")
		self.sourceItemPos = sourceItemPos
		self.targetItemPos = targetItemPos

		itemIndex = player.GetItemIndex(targetItemPos)
		item.SelectItem(itemIndex)

		attrSlot = [player.GetItemAttribute(targetItemPos, i) for i in xrange(player.ATTRIBUTE_SLOT_MAX_NUM)]

		if isCreate == True:
			if attrSlot[6][1] == 0:
				self.lockText.SetText("%s isimli eþyayý kilitlemek istediðine emin misin ?" % (item.GetItemName()))
				self.lockText2.SetText("Ýtem kilit þifrenizi giriniz:")
				self.isCreate = True
			else:
				self.lockText.SetText("%s isimli eþyanýn kilidini açmak istediðine emin misin ?" %(item.GetItemName()))
				self.lockText2.SetText("Ýtem kilit þifrenizi giriniz:")
				self.isCreate = True
		else:
			self.lockText.SetText("%s isimli eþyayý kilitlemek istediðine emin misin ?" %(item.GetItemName()))
			self.lockText2.SetText("|cffff0000Þifre bulunamadý!|r item kilit þifrenizi belirleyiniz:")

		constInfo.ITEM_LOCK = 1

		self.itemImage.OnMouseOverIn = lambda arg = targetItemPos : self.OverInItem(arg)
		self.itemImage.OnMouseOverOut = lambda arg = self.toolTip : self.OverOutItem(arg)
		self.itemImage2.OnMouseOverIn = lambda arg = targetItemPos : self.OverInItemRight(arg)
		self.itemImage2.OnMouseOverOut = lambda arg = self.toolTip : self.OverOutItem(arg)
		self.itemImage.LoadImage(item.GetIconImageFileName())
		self.itemImage2.LoadImage(item.GetIconImageFileName())
		xSlotCount, ySlotCount = item.GetItemSize()
		for slot in self.slotList:
			slot.Hide()
		for slot2 in self.slotList2:
			slot2.Hide()
		for i in xrange(min(3, ySlotCount)):
			self.slotList[i].SetPosition(20, i*32 - (ySlotCount-1)*16+20)
			self.slotList[i].Show()
			self.slotList2[i].SetPosition(266, i*32 - (ySlotCount-1)*16+20)
			self.slotList2[i].Show()

		self.SetTop()
		self.Show()

	def OverInItem (self, targetItemPos):
		itemIndex = player.GetItemIndex(targetItemPos)
		metinSlot = []
		for i in xrange(player.METIN_SOCKET_MAX_NUM):
			metinSlot.append(player.GetItemMetinSocket(targetItemPos, i))
		attrSlot = []
		for i in xrange(player.ATTRIBUTE_SLOT_MAX_NUM):
			attrSlot.append(player.GetItemAttribute(targetItemPos, i))
		evolution = player.GetItemEvolution(targetItemPos)
		self.toolTip.AddItemData(itemIndex, metinSlot, attrSlot, 0, 0, 0, evolution)
		if attrSlot[6][1] == 1:
			self.toolTip.AppendTextLine("[Kilitli]", grp.GenerateColor(1.0, 0.7843, 0.0, 1.0))

	def OverInItemRight (self, targetItemPos):
		itemIndex = player.GetItemIndex(targetItemPos)
		metinSlot = []
		for i in xrange(player.METIN_SOCKET_MAX_NUM):
			metinSlot.append(player.GetItemMetinSocket(targetItemPos, i))
		attrSlot = []
		for i in xrange(player.ATTRIBUTE_SLOT_MAX_NUM):
			attrSlot.append(player.GetItemAttribute(targetItemPos, i))
		evolution = player.GetItemEvolution(targetItemPos)
		self.toolTip.AddItemData(itemIndex, metinSlot, attrSlot, 0, 0, 0, evolution)
		if attrSlot[6][1] == 0:
			self.toolTip.AppendTextLine("[Kilitli]", grp.GenerateColor(1.0, 0.7843, 0.0, 1.0))

	def OverOutItem (self, toolTip):
		if None != toolTip :
			self.toolTip.HideToolTip()
			self.toolTip.ClearToolTip()

	def ChangePW(self):
		if self.isCreate == True:
			self.wndChangePassword.Open()

	def Accept(self):
		self.isCreate = True
		pw = self.item_lock_pw_value.GetText()
		net.SendChatPacket("/item_lock %s %d %d" % (pw, self.sourceItemPos, self.targetItemPos))

		self.Close()
		return True

	def Close(self):
		self.item_lock_pw_value.KillFocus()
		constInfo.ITEM_LOCK = 0
		self.Hide()

	def OnPressEscapeKey(self):
		self.Close()
		return True

class ItemLockChangePasswd(ui.ScriptWindow):
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.LoadDialog()

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def LoadDialog(self):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, "uiscript/changepassworddialog2.py")
		except:
			import exception
			exception.Abort("ItemLockChangePasswd.__LoadScript.LoadObject")
		try:
			self.titleBar = self.GetChild("titlebar")
			self.GetChild("accept_button").SetEvent(ui.__mem_func__(self.OnAccept))
			self.GetChild("cancel_button").SetEvent(ui.__mem_func__(self.OnCancel))
			self.GetChild("titlebar").SetCloseEvent(ui.__mem_func__(self.OnCancel))
			oldPassword = self.GetChild("old_password_value")
			newPassword = self.GetChild("new_password_value")
			newPasswordCheck = self.GetChild("new_password_check_value")
		except:
			import exception
			exception.Abort("ItemLockChangePasswd.__LoadScript.BindObject")

		oldPassword.SetTabEvent(lambda arg=1: self.OnNextFocus(arg))
		newPassword.SetTabEvent(lambda arg=2: self.OnNextFocus(arg))
		newPasswordCheck.SetTabEvent(lambda arg=3: self.OnNextFocus(arg))
		oldPassword.SetReturnEvent(lambda arg=1: self.OnNextFocus(arg))
		newPassword.SetReturnEvent(lambda arg=2: self.OnNextFocus(arg))
		newPasswordCheck.SetReturnEvent(ui.__mem_func__(self.OnAccept))
		oldPassword.OnPressEscapeKey = self.OnCancel
		newPassword.OnPressEscapeKey = self.OnCancel
		newPasswordCheck.OnPressEscapeKey = self.OnCancel

		self.oldPassword = oldPassword
		self.newPassword = newPassword
		self.newPasswordCheck = newPasswordCheck

	def OnNextFocus(self, arg):
		if 1 == arg:
			self.oldPassword.KillFocus()
			self.newPassword.SetFocus()
		elif 2 == arg:
			self.newPassword.KillFocus()
			self.newPasswordCheck.SetFocus()
		elif 3 == arg:
			self.newPasswordCheck.KillFocus()
			self.oldPassword.SetFocus()

	def Destroy(self):
		self.ClearDictionary()
		self.dlgMessage.ClearDictionary()
		self.oldPassword = None
		self.newPassword = None
		self.newPasswordCheck = None

	def Open(self):
		self.oldPassword.SetText("")
		self.newPassword.SetText("")
		self.newPasswordCheck.SetText("")
		self.oldPassword.SetFocus()
		self.SetCenterPosition()
		self.SetTop()
		self.Show()

	def Close(self):
		self.oldPassword.SetText("")
		self.newPassword.SetText("")
		self.newPasswordCheck.SetText("")
		self.oldPassword.KillFocus()
		self.newPassword.KillFocus()
		self.newPasswordCheck.KillFocus()
		self.Hide()

	def OnAccept(self):
		oldPasswordText = self.oldPassword.GetText()
		newPasswordText = self.newPassword.GetText()
		newPasswordCheckText = self.newPasswordCheck.GetText()
		net.SendChatPacket("/item_lock_passwd_change %s %s %s" % (oldPasswordText, newPasswordText, newPasswordCheckText))
		self.Close()
		return True

	def OnCancel(self):
		self.Close()
		return True