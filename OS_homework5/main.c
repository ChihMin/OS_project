#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/workqueue.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include "ioc_hw5.h"

MODULE_LICENSE("Dual BSD/GPL");

#define EXAMPLE_NAME "mydev"
#define OS_HW5 "OS_HW5"

#define DMA_BUFSIZE 64

#define DMASTUIDADDR 0x0    // Student ID
#define DMARWOKADDR 0x4     // RW function complete 
#define DMAIOCOKADDR 0x8	// ioctl function complete 
#define DMAIRQOKADDR 0xc    // ISR function complete 
#define DMACOUNTADDR 0x10   // interrupt count function complete
#define DMAANSADDR 0x14     // Computation answer 
#define DMAREADABLEADDR 0x18	// READABLE variable for synchronize
#define DMABLOCKADDR 0x1c		// Blocking or Non-Blocking IO 
#define DMAOPCODEADDR 0x20      // data.a opcode
#define DMAOPERANDBADDR 0x21    // data.b opcode
#define DMAOPERANDCADDR 0x25    // data.c opcode

struct dataIn{
	char a;
	int b;
	short c;
};

void *dma_buf;
static int Major, Minor;
static int hw5_num = 0;
struct cdev *dev_cdevp = NULL;
static struct work_struct *math_work = NULL;

static int drv_open(struct inode *inode, struct file *flip);
static int drv_release(struct inode *inode, struct file *flip);
static ssize_t drv_read(struct file *flip, char *buf, size_t size, loff_t *f_pos);
static ssize_t drv_write(struct file *flip, const char *buf, size_t size, loff_t *f_pos);
static ssize_t drv_ioctl(struct file*, unsigned int, unsigned long);

static void arithmetic_routine(struct work_struct *ws);

void myoutb(unsigned char data, unsigned short int port);
void myoutw(unsigned short data, unsigned short int port);
void myoutl(unsigned long data, unsigned short int port);
unsigned char myinb(unsigned short port);
unsigned short myinw(unsigned short port);
unsigned long myinl(unsigned short port);


static struct file_operations drv_fops = {
	owner:			THIS_MODULE,
	open:			drv_open,
	release:		drv_release,
	read:			drv_read,
	write:			drv_write,
	unlocked_ioctl:	drv_ioctl,
};

int prime(int base, short nth)
{
    int fnd=0;
    int i, num, isPrime;

    num = base;
    while(fnd != nth) {
        isPrime=1;
        num++;
        for(i=2;i<=num/2;i++) {
            if(num%i == 0) {
                isPrime=0;
                break;
            }
        }
        
        if(isPrime) {
            fnd++;
        }
    }
    return num;
}

static void arithmetic_routine(struct work_struct *ws ){
    struct dataIn data;
    int ans;

    data.a = myinb(DMAOPCODEADDR);
    data.b = myinl(DMAOPERANDBADDR);
    data.c = myinw(DMAOPERANDCADDR);

    switch(data.a) {
        case '+':
            ans = data.b + data.c;
            break;
			
        case '-':
            ans = data.b - data.c;
            break;

        case '*':
            ans = data.b * data.c;
            break;

        case '/':
            ans = data.b / data.c;
            break;

        case 'p':
            ans = prime(data.b, data.c);
            break;

        default:
            ans = 0;
    }
	printk("%s:%s(): %d %c %d = %d\n", OS_HW5, __FUNCTION__, data.b, data.a, data.c, ans);
	myoutl(ans, DMAANSADDR );
	myoutl(1, DMAREADABLEADDR);
}

void myoutb(unsigned char data, unsigned short int port){
	*(volatile unsigned char*)(dma_buf + port) = data;
}

void myoutw(unsigned short data, unsigned short int port){
	*(volatile unsigned short*)(dma_buf + port) = data;
}

void myoutl(unsigned long data, unsigned short int port){
	*(volatile unsigned long*)(dma_buf + port) = data;
}

unsigned char myinb(unsigned short port){
	return *( volatile unsigned char *)(dma_buf + port);
}

unsigned short myinw(unsigned short port){
	return *( volatile unsigned short *)(dma_buf + port);
}

unsigned long myinl(unsigned short port){
	return *( volatile unsigned long *)(dma_buf + port);
}

static int drv_open(struct inode *inode, struct file *filp){
	try_module_get(THIS_MODULE);
	printk("OS_HW5:%s():device open\n",__FUNCTION__);
	return 0;
}

static int drv_release(struct inode *inode, struct file *flip){
	module_put(THIS_MODULE);
	printk("OS_HW5:%s():device release\n",__FUNCTION__);
	return 0;
}

static ssize_t drv_ioctl(struct file *flip, unsigned int cmd, unsigned long args){
	int ret = 0;
	int getValue = 0;
	switch(cmd){
		case HW5_IOCSETSTUID:
			ret = __get_user(hw5_num, (int __user *)args);
			myoutl( hw5_num, DMASTUIDADDR); 
			printk("OS_HW5:%s(): My STUID is %d\n",__FUNCTION__, hw5_num);
			break;

		case HW5_IOCSETRWOK:
			ret = __get_user(getValue, (int __user *)args);
			myoutl(getValue, DMARWOKADDR); 
			printk("OS_HW5:%s(): RW OK\n", __FUNCTION__);
			break;
		
		case HW5_IOCSETIOCOK:
			ret = __get_user(getValue, (int __user *)args);
			myoutl(getValue, DMAIOCOKADDR); 
			printk("OS_HW5:%s(): IOC OK\n", __FUNCTION__);
			break;

		case HW5_IOCSETIRQOK:
			ret = __get_user(getValue, (int __user *)args);
			//myoutl(getValue, DMAIRQOKADDR); 	
			// printk("OS_HW5:%s(): IRQ OK\n", __FUNCTION__);
			break;
		
		case HW5_IOCSETBLOCK:
			ret = __get_user(getValue, (int __user *)args);
			myoutl(getValue, DMABLOCKADDR);
			if( getValue ){	
				// Set block mode
				printk("%s:%s(): Blocking IO\n", OS_HW5, __FUNCTION__);
			}
			else{	
				// Set non-block mode
				printk("%s:%s(): Non-Blocking IO\n", OS_HW5, __FUNCTION__);
			}
			break;

		case HW5_IOCWAITREADABLE:
			while( !myinl(DMAREADABLEADDR) )
				msleep( 500 );
			ret = __put_user(1, (int __user *)args);
			printk("%s:%s(): wait readable 1\n", OS_HW5, __FUNCTION__);
			break;

		default :
			printk("OS_HW5:%s(): (ERROR)NO METHOD TO PROCESS\n", __FUNCTION__);
			return -1;
	}
	return 0;
}

static ssize_t drv_read(struct file *flip, char *buf, size_t size, loff_t *f_pos){
	int ans = myinl(DMAANSADDR);
	printk("OS_HW5:%s(): ans = %d\n",__FUNCTION__, ans);
	
	copy_to_user( buf, &ans, sizeof( int ) );	
	myoutl( 0, DMAANSADDR);
	myoutl( 0, DMAREADABLEADDR); 

	return 0;
}

static ssize_t drv_write(struct file *flip, const char *buf, size_t size, loff_t *f_pos){
	char a = 0;
	int b;
	short c;
	struct dataIn data;
	int blockStatus = 0;
	
	printk("%s:%s():queue work\n", OS_HW5, __FUNCTION__);
	copy_from_user( &data, buf, sizeof( struct dataIn ) );	
		
	a = data.a;
	b = data.b;
	c = data.c;
	
	blockStatus = myinl(DMABLOCKADDR);
    myoutb(a, DMAOPCODEADDR);
    myoutl(b, DMAOPERANDBADDR);
    myoutw(c, DMAOPERANDCADDR);
	
	INIT_WORK( math_work, arithmetic_routine );

	schedule_work( math_work );
	if( blockStatus ){
		// If now is Block mode, hold and wait for running
		printk("%s:%s():block\n", OS_HW5, __FUNCTION__);
		flush_scheduled_work();		
	}
	//printk("%s:%s(): %c %d %d vs status %d\n", OS_HW5, __FUNCTION__, a, b, c, blockStatus); 
	 
	return size;
}


static int init_modules(void){
	int ret;
	dev_t dev;
	

	printk("OS_HW5:%s():.................Start................\n",__FUNCTION__);
	

	ret = alloc_chrdev_region(&dev, 0, 1, EXAMPLE_NAME); 	
	if( ret ){
		printk("OS_HW5:%s(): Can't alloc chrdev\n",__FUNCTION__);
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
	
	dma_buf = kzalloc(DMA_BUFSIZE, GFP_KERNEL);
	if( dma_buf )	
		printk("%s:%s():allocate dma buffer\n", OS_HW5, __FUNCTION__);
	else
		printk("%s:%s():allocate dma buffer FAILED !!\n", OS_HW5, __FUNCTION__);

	math_work = kzalloc(sizeof(struct work_struct), GFP_KERNEL);
	if( math_work ){
		printk("----------> SUCCESS allocate math_work structure <--------\n");
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
	dev_t dev;
	/*  Unregister character device */

	dev = MKDEV(Major, Minor);
	if(dev_cdevp){
		cdev_del(dev_cdevp);
		kfree(dev_cdevp);
	}
	kfree( dma_buf );
	printk("%s:%s():free dma buffer\n", OS_HW5, __FUNCTION__ );


	unregister_chrdev(Major, EXAMPLE_NAME);
	printk("OS_HW5:%s():unregister chrdev\n",__FUNCTION__);
	
	kfree( math_work );

	printk("OS_HW5:%s():..................End.................\n",__FUNCTION__);
}

module_init(init_modules);
module_exit(exit_modules);
