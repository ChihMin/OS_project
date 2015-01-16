#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

MODULE_LICENSE("Dual BSD/GPL");

#define EXAMPLE_MAJOR 60
#define EXAMPLE_NAME "mydev"

static int Major, Minor;
struct cdev *dev_cdevp = NULL;


static int drv_open(struct inode *inode, struct file *filp){
	printk("OS_HW5:%s():device open\n",__FUNCTION__);
	return 0;
}

static int drv_release(struct inode *inode, struct file *flip){
	printk("OS_HW5:%s():device release\n",__FUNCTION__);
	return 0;
}

static ssize_t drv_read(struct file *flip, char *buf, size_t size, loff_t *f_pos){
	printk("OS_HW5:%s():device release\n",__FUNCTION__);
			
	return 0;
}

static ssize_t drv_write(struct file *flip, const char *buf, size_t size, loff_t *f_pos){
	printk("<1>EXAMPLE: write (size=%zu)\n", size);
	return size;
}

static struct file_operations drv_fops = {
	owner:		THIS_MODULE,
	open:		drv_open,
	release:	drv_release,
	read:		drv_read,
	write:		drv_write
};

static int init_modules(void){
	int ret;
	dev_t dev;
	

	printk("OS_HW5:%s():.................Start................\n",__FUNCTION__);
	

	ret = alloc_chrdev_region(&dev, 0, 1, EXAMPLE_NAME); 	
	if( ret ){
		printk("OS_HW5:%s(): Can;t alloc chrdev\n",__FUNCTION__);
		return ret;
	}
	Major = MAJOR(dev);
	Minor = MINOR(dev);
	/* Register character device */
	
	printk("OS_HW5:%s(): register chrdev(%d,%d)\n", __FUNCTION__, Major, Minor);
	//result = register_chrdev(Major, EXAMPLE_NAME, &drv_fops);
	dev_cdevp = kzalloc(sizeof(struct cdev), GFP_KERNEL );
	if( dev_cdevp == NULL ){
		printk("OS_HW5:%s(): kzalloc failed\n", __FUNCTION__);
		goto failed;
	}
	
	cdev_init(dev_cdevp, &drv_fops);
	dev_cdevp->owner = THIS_MODULE;
	ret = cdev_add(dev_cdevp, MKDEV(Major, Minor), 1);
	if( ret < 0){
		printk("OS_HW5:%s():add chr dev failed\n", __FUNCTION__);
		goto failed;
	}

	return 0;

failed:

	if(dev_cdevp) {
		kfree(dev_cdevp);
		dev_cdevp = NULL;
	}

	return 0;
}

static void exit_modules(void){
	printk("OS_HW5:%s():unregister chrdev\n",__FUNCTION__);
	/*  Unregister character device */
	dev_t dev;

	dev = MKDEV(Major, Minor);
	if(dev_cdevp){
		cdev_del(dev_cdevp);
		kfree(dev_cdevp);
	}
	unregister_chrdev(Major, EXAMPLE_NAME);

	printk("OS_HW5:%s():..................End.................\n",__FUNCTION__);
}

module_init(init_modules);
module_exit(exit_modules);