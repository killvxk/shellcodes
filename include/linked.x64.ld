ENTRY(StackAlign)
SECTIONS
{
	.text :
	{
		*(.text.StackAlign)
		*(.text.WindowsEntrypoint)
		*(.text.GetPeBase)
		*(.text.GetPeFunc)
		*(.text.GetStringHashDjb2)
	}
}
