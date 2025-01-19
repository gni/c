#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

static int __init hello_init(void) {
    printk(KERN_INFO "Hello, Kernel!\n");
    return 0;
}

static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye, Kernel!\n");
}

module_init(hello_init);
module_exit(hello_exit);

// compile
// make -C /lib/modules/$(uname -r)/build M=$(pwd) modules
// sudo insmod hello_kernel_module.ko
// dmesg | tail
// sudo rmmod hello_kernel_module