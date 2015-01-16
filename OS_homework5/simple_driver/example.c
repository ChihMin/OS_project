#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>

MODULE_LICENSE("Dual BSD/GPL");

#define EXAMPLE_MAJOR 60
#define EXAMPLE_NAME "example"

static int example_open(struct inode *inode, struct file *filp){
	printk("<1>EXAMPLE: open\n");
	return 0;
}

static int example_close(struct inode *inode, struct file *flip){
	printk("<1>EXAMPLE: close\n");
	return 0;
}

static ssize_t example_read(struct file *flip, char *buf, size_t size, loff_t *f_pos){
	int i;
	printk("<1>EXAMPLE: read (size=%zu)\n", size);
	for(i = 0; i < 10; ++i)
		buf[i] = '2';
	
	return 0;
}

static ssize_t example_write(struct file *flip, const char *buf, size_t size, loff_t *f_pos){
	printk("<1>EXAMPLE: write (size=%zu)\n", size);
	return size;
}

static struct file_operations example_fops = {
	.open = example_open,
	.release = example_close,
	.read = example_read,
	.write = example_write,
};

static int example_init(void){
	int result;
	printk("<1>EXAMPLE:init\n");
	
	/* Register character device */
	result = register_chrdev(EXAMPLE_MAJOR, EXAMPLE_NAME, &example_fops);
	if( result < 0 ){
		printk("<1>EXAMPLE: Failed to register character device\n");
		return result;
	}

	return 0;
}

static void example_exit(void){
	printk("<1>EXAMPLE:exit\n");
	/*  Unregister character device */
	unregister_chrdev(EXAMPLE_MAJOR, EXAMPLE_NAME);

}

module_init(example_init);
module_exit(example_exit);
