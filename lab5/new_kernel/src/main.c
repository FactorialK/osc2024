#include "mini_uart.h"
#include "exception.h"
#include "shell.h"
#include "timer.h"
#include "memory.h"
#include "sched.h"

extern char *__boot_loader_addr;
extern unsigned long long __code_size;
extern unsigned long long __begin;
extern void set_for_el_switch(void);
char *_dtb;
char *exceptionLevel;
static int EL2_to_EL1_flag = 1;

extern thread_t *curr_thread;
extern thread_t *threads[];
// x0 is for the parameter
void main(char *arg)
{

    exceptionLevel = arg;
    // put_int(exceptionLevel);
    // uart_puts("\n");
    // el1_interrupt_enable();
    // timer_init(); //這會跳去EL0
    
    uart_init();
    uart_interrupt_enable();
    uart_flush_FIFO();
    init_memory_space();
    irqtask_list_init();
    timer_list_init();

    el1_interrupt_enable();  // enable interrupt in EL1 -> EL1
    char input_buffer[10];
    shell_cmd_read(input_buffer);
    shell_banner();
//  core_timer_enable();

    init_thread_sched();
    set_current_thread_context(&curr_thread->context);
    load_context(&curr_thread->context); // jump to idle thread and unlock interrupt

}
void code_relocate(char *addr)
{
    unsigned long long size = (unsigned long long)&__code_size;
    char *start = (char *)&__begin;
    for (unsigned long long i = 0; i < size; i++)
    {
        addr[i] = start[i];
    }

    ((void (*)(char *))addr)(_dtb);
}