#include <linux/module.h>
#include <linux/printk.h>
#include "hello1.h"

static unsigned int repeat_count = 1;
module_param(repeat_count, uint, 0444);
MODULE_PARM_DESC(repeat_count, "Number of 'Hello, World!' messages to print");

static int __init hello2_init(void) {
    unsigned int i;
    if (repeat_count == 0 || (repeat_count >= 5 && repeat_count <= 10)) {
        pr_warn("Parameter is either 0 or in range 5-10\n");
    }

    if (repeat_count > 10) {
        pr_err("Parameter cannot be larger than 10\n");
        return -EINVAL;
    }

    for (i = 0; i < repeat_count; i++) {
        print_hello();
    }

    return 0;
}

static void __exit hello2_exit(void) {
    pr_info("hello2 module unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Maksim Kochenkov");
MODULE_DESCRIPTION("Hello2 module");

