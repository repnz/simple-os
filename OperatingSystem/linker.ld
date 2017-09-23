OUTPUT_FORMAT("binary")
ENTRY(start)
phys = 0x00007c00;
SECTIONS
{		
	.bootloader phys : AT(phys) {
	__bootloader__start__ = .;
	*boot.*(.text);
	*boot.*(.data);
	__bootloader_code_end__ = .;
	. += 510 - (__bootloader_code_end__ - __bootloader__start__);
	BYTE(0x55);
	BYTE(0xAA);
	__bootloader__end__ = .;
	} 
	
	__kernel_start_sector__ = 2;
	
	.text :
	{
    __kernel_code_start__ = .;
    *(.text)
    *(.rodata)
	. = ALIGN(512);
	__kernel_code_end__ = .;
	} 
	
  .data :
  {
    __data_start__ = .;
    *(.data)
	. = ALIGN(512);
	__data_end__ = .;
  }

  __kernel_sectors_length__ = ((. - __kernel_code_start__) / 512);

  __kernel_stack_start__ = . + 0x2000;
  __threads_stack_start__ = . + 0x10000;
  __dynamic_memory_start__ = . + 0x4;
  __dynamic_memory_end = . + 0x10000;
  
  .bss :
  {
	
    __bss_start__ = .;
    *(.bss)
	. = ALIGN(512);
	__bss_end__ = .;
  }

}