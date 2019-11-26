ENTRY(shellcode_start)
SECTIONS
{
	.text :
	{
		*(.text.shellcode_start)
		*(.text)
	}
}
