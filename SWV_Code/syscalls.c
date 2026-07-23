//paste it below the macros in core/Src/syscalls.c


#define DEMCR           (*(volatile uint32_t *)0xE000EDFC)
#define ITM_TER         (*(volatile uint32_t *)0xE0000E00)
#define ITM_TCR         (*(volatile uint32_t *)0xE0000E80)
#define ITM_PORT0       (*(volatile uint32_t *)0xE0000000)

void ITM_SendChar(uint8_t ch)
{
    /* Check whether trace and ITM are enabled */
    if ((DEMCR & (1U << 24)) &&
        (ITM_TCR & 1U) &&
        (ITM_TER & 1U))
    {
        while ((ITM_PORT0 & 1U) == 0U);

        ITM_PORT0 = ch;
    }
}



// modify the _write function in syscalls.c 
int _write(int file, char *ptr, int len)
{
  (void)file;
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
	  ITM_SendChar(*ptr++);
  }
  return len;
}