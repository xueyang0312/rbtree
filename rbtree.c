#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("National Cheng Kung University, xueyang");
MODULE_DESCRIPTION("RB tree example");
MODULE_VERSION("1.0");

static int __init rbtree_init(void)
{

}

static void __exit rbtree_exit(void)
{

}


module_init(rbtree_init);
module_exit(rbtree_exit);