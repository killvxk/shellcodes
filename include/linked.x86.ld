ENTRY(_WindowsEntrypoint)
SECTIONS
{
	text : 
	{
		*(.text.WindowsEntrypoint)
		*(.text.GetPeBase)
		*(.text.GetPeFunc)
		*(.text.GetStringHashDjb2)
	}
}
