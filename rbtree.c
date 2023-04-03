#include <linux/init.h>
#include <linux/module.h>
/* for kmalloc */
#include <linux/slab.h>
#include <linux/rbtree.h>

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("National Cheng Kung University, xueyang");
MODULE_DESCRIPTION("RB tree example");
MODULE_VERSION("1.0");

struct rbtree {
    struct rb_node node;
    int key;
};

/* Declare a root of rb tree */
struct rb_root mytree = RB_ROOT;

/* search key of rb tree*/
static struct rbtree *search(struct rb_root *root, int new) 
{
    struct rb_node *node = root->rb_node;

    while (node) {
        struct rbtree *data = container_of(node, struct rbtree, node);
        if (data->key > new)
            node = node->rb_left;
        else if (data->key < new)
            node = node->rb_right;
        else
            return data;
    }

    return NULL;
}

/* insert data to rb tree */
static int insert(struct rb_root *root, struct rbtree *data)
{
    struct rb_node **new = &(root->rb_node) , *parent = NULL;
    while (*new) {
        struct rbtree *this = container_of(*new, struct rbtree, node);

        parent = *new;
        if (this->key > data->key) 
            new = &((*new)->rb_left);
        else if (this->key < data->key)
            new = &((*new)->rb_right);
        else
            return -1;
    }

    rb_link_node(&data->node, parent, new);
    rb_insert_color(&data->node, root);

    return 0;
}

static int __init rbtree_init(void)
{
    struct rbtree *data;
    struct rb_node *node;

    for (int i = 0; i < 20 ; i += 2) {
        data = kmalloc(sizeof(struct rbtree), GFP_KERNEL);
        data->key = i;
        insert(&mytree, data);
    }

    /* traverse all rb tree and print it on console. */
    for (node = rb_first(&mytree); node; node = rb_next(node)) {
        printk("key=%d\r\n", rb_entry(node, struct rbtree, node)->key);
    }

    return 0;
}

static void __exit rbtree_exit(void)
{

}


module_init(rbtree_init);
module_exit(rbtree_exit);