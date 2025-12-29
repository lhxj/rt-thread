#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* ===== 任务优先级定义 ===== */
#define THREAD_PRIORITY         20
#define THREAD_STACK_SIZE       2048
#define THREAD_TIMESLICE        10

/* ===== 任务函数声明 ===== */
static void idle_thread_entry(void *parameter);

/* ===== 空闲任务线程 ===== */
static rt_thread_t idle_tid = RT_NULL;
static char idle_thread_stack[THREAD_STACK_SIZE];
static struct rt_thread idle_thread;

/* ===== 空闲任务函数 ===== */
static void idle_thread_entry(void *parameter)
{
    rt_uint32_t counter = 0;
    
    while (1)
    {
        /* 每 1000 次迭代打印一次日志 */
        counter++;
        if (counter % 1000 == 0)
        {
            LOG_I("Idle thread running... [%u]", counter / 1000);
        }
        
        /* 在这里可以进行一些低优先级的后台任务 */
    }
}

/* ===== 主函数（如启用 RT_USING_USER_MAIN）===== */
int main(void)
{
    LOG_I("RT-Thread RISC-V + K1 Learning BSP");
    LOG_I("=====================================");
    LOG_I("Creating idle thread...");
    
    /* 创建一个空闲线程（低优先级任务）*/
    idle_tid = rt_thread_init(&idle_thread,
                               "idle_task",
                               idle_thread_entry,
                               RT_NULL,
                               &idle_thread_stack[0],
                               THREAD_STACK_SIZE,
                               THREAD_PRIORITY,
                               THREAD_TIMESLICE);
    
    /* 启动线程 */
    if (idle_tid != RT_NULL)
    {
        rt_thread_startup(idle_tid);
        LOG_I("Idle thread started!");
    }
    else
    {
        LOG_E("Failed to create idle thread!");
    }
    
    return 0;
}

