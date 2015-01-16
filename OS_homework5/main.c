#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>

MODULE_LICENSE("Dual BSD/GPL");

#define EXAMPLE_MAJOR 60
#define EXAMPLE_NAME "example"

static int drv_open(struct inode *inode, struct file *filp){
	printk("OS_HW5:%s():device open\n",__FUNCTION__);
	return 0;
}

static int drv_release(struct inode *inode, struct file *flip){
	printk("OS_HW5:%s():device release\n",__FUNCTION__);
	return 0;
}

static ssize_t drv_read(struct file *flip, char *buf, size_t size, loff_t *f_pos){
	int i;
	printk("OS_HW5:%s():device release\n",__FUNCTION__);
	for(i = 0; i < 10; ++i)
		buf[i] = '2';
	
	return 0;
}

static ssize_t drv_write(struct file *flip, const char *buf, size_t size, loff_t *f_pos){
	printk("<1>EXAMPLE: write (size=%zu)\n", size);
	return size;
}

static struct file_operations drv_fops = {
	open:		drv_open,
	release:	drv_release,
	read:		drv_read,
	write:		drv_write,
};

static int init_modules(void){
	int result;
	printk("OS_HW5:%s():.................Start................\n",__FUNCTION__);
	
	/* Register character device */
	result = register_chrdev(EXAMPLE_MAJOR, EXAMPLE_NAME, &drv_fops);
	if( result < 0 ){
		printk("OS_HW5:%s(): Failed to register character device\n",__FUNCTION__);
		return result;
	}

	return 0;
}

static void exit_modules(void){
	printk("OS_HW5:%s():unregister chrdev\n",__FUNCTION__);
	/*  Unregister character device */
	unregister_chrdev(EXAMPLE_MAJOR, EXAMPLE_NAME);

	printk("OS_HW5:%s():..................End.................\n",__FUNCTION__);
}

module_init(init_modules);
module_exit(exit_modules);
