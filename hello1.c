#include <linux/module.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/printk.h>
#include "hello1.h"

struct event_list {
    struct list_head list;
    ktime_t start_time;
    ktime_t end_time;
};

static LIST_HEAD(event_list_head);

void print_hello(void) {
    struct event_list *event = kmalloc(sizeof(struct event_list), GFP_KERNEL);
    if (!event) {
        pr_err("Failed to allocate memory for event\n");
        return;
    }

    event->start_time = ktime_get();
    pr_info("Hello, World!\n");
    event->end_time = ktime_get();

    list_add_tail(&event->list, &event_list_head);
}
EXPORT_SYMBOL(print_hello);

static void cleanup_events(void) {
    struct event_list *event, *tmp;
    list_for_each_entry_safe(event, tmp, &event_list_head, list) {
        pr_info("Start time: %lld, End time: %lld\n", event->start_time, event->end_time);
        list_del(&event->list);
        kfree(event);
    }
}

static int __init hello1_init(void) {
    pr_info("hello1 module loaded\n");
    return 0;
}

static void __exit hello1_exit(void) {
    cleanup_events();
    pr_info("hello1 module unloaded\n");
}

module_init(hello1_init);
module_exit(hello1_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Maksim Kochenkov");
MODULE_DESCRIPTION("Hello1 module");

