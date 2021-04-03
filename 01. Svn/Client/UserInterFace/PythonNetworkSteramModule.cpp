//Search:

void initnet()

//Add on:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
PyObject* netSendItemLockedPacket(PyObject* poSelf, PyObject* poArgs)
{
	TItemPos source_pos;
	TItemPos target_pos;

	if (!PyTuple_GetInteger(poArgs, 0, &source_pos.cell))
		return Py_BuildException();

	if (!PyTuple_GetInteger(poArgs, 1, &target_pos.cell))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendItemLockedPacket(source_pos, target_pos);
	return Py_BuildNone();
}
#endif

//Search:

		{ NULL,										NULL,										NULL },

//Add on:

#ifdef ENABLE_ITEM_LOCK_SYSTEM
		{ "SendItemLockedPacket",					netSendItemLockedPacket,					METH_VARARGS },
#endif