#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/device.h>
#include<linux/semaphore.h>
#include<linux/delay.h>
#include<linux/wait.h>
#include<linux/sched.h>

#define LOCK 0
#define UNLOCK 1

#define DELAY 2000

struct semaphore sample_sem;
struct cdev sync_semaphore_cdev;
struct class *sync_semaphore_class;
struct device *sync_semaphore_device;
static wait_queue_head_t mywait;

char gbuff[50]; 
int flag = 1;
char buff[100];

dev_t mydev;
int mychar_open(struct inode *inode, struct file *flip);
int mychar_release(struct inode *inode, struct file *flip);
ssize_t mychar_read(struct file *flip, char __user *Ubuff, size_t count, loff_t *offp);
ssize_t mychar_write(struct file *flip, const char __user *Ubuff, size_t count, loff_t *offp);

struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = mychar_open,
	.release = mychar_release,
	.read = mychar_read,
	.write = mychar_write,
};

DECLARE_WAIT_QUEUE_HEAD(mywait);
struct cdev *my_cdev;

static int __init char_init(void)
{
	int r;
	int MAJOR,MINOR;
	r = alloc_chrdev_region(&mydev,0,1,"mychar");
	if(r<0)
	{
		printk("Region requested is not available\n");
		return -1;
	}
	MAJOR = MAJOR(mydev);
	MINOR = MINOR(mydev);
	printk("Major number %d\t Minor number %d\n",MAJOR,MINOR);
	my_cdev = cdev_alloc();
	my_cdev->ops = &fops;
	r = cdev_add(my_cdev,mydev,1);
	if(r<0)
	{
		printk("Device nor created\n");
		return -1;
	}
	cdev_init (&sync_semaphore_cdev,&fops);
	cdev_add(&sync_semaphore_cdev, mydev, 1);
	//create a node
	
	sync_semaphore_class= class_create(THIS_MODULE, "mychar");
	sync_semaphore_device = device_create(sync_semaphore_class, NULL, mydev, NULL, "mychar");
	return 0;
}

static void __exit char_exit(void)
{
	int MAJOR,MINOR;
	MAJOR = MAJOR(mydev);
	MINOR = MINOR(mydev);
	printk("Major number is %d\t Minor number is %d\n",MAJOR,MINOR);
	//delete node created
	
	device_destroy(sync_semaphore_class, mydev);
	class_destroy(sync_semaphore_class);
	unregister_chrdev_region(mydev,1);
	cdev_del(my_cdev);
	printk("Unregister\n");
}

int mychar_open(struct inode *inode,struct file *flip)
{
	printk("In open system call\n");
	return 0;
}

int mychar_release(struct inode *inode,struct file *flip)
{
	printk("In close system call\n");
	return 0;
}

ssize_t mychar_read(struct file *flip, char __user *Ubuff,size_t count,loff_t *offp)
{
	char kbuff[] = "Read data";
	int r;
	size_t ret;

	//Acquire semaphore
	
	if(down_interruptible(&sample_sem))
		return -ERESTARTSYS;
	//critical sectio
	
	msleep(DELAY);
	if(flag == 1)
	{
		wait_event_interruptible(mywait,flag==);
	}

	r = copy_to_user((char *)Ubuff, (const char *)kbuff, sizeof(kbuff));
	r = copy_to_user((char *)Ubuff, (const char *)gbuff, sizeof(gbuff));
	if(r==0)
	{
		printk("Read data successfully %d\n",sizeof(kbuff));
		ret = sizeof(kbuff);
		flag = 0;
		wake_up_interruptible(&mywait);
		return ret;
	}
	else if(r>0)
	{
		printk("Data available %d\n",count-r);
		ret = count-r;
		return ret;
	}
	else 
	{
		printk("Error\n");
		flag = 1;
		ret = -EFAULT;
		return ret;
	}
	//Release semaphore
	
	up(&sample_sem);
	return sizeof(gbuff);
}

ssize_t mychar_write(struct file *flip, const char __user *Ubuff, size_t count, loff_t *offp)
{
	char kbuff[100];
	unsigned long r;
	ssize_t ret;

	//Acquire semaphore
	
        if(down_interruptible(&sample_sem))
		return -ERESTARTSYS;
	msleep(DELAY);

	r = copy_from_user((char *)kbuff,(char *)Ubuff, count);
	r = copy_from_user((char *)gbuff,(char *)Ubuff, count);

	if(r == 0)
	{
		printk("User data %s\n", kbuff);
		ret = count;
		flag = 0;
		wake_up_interruptible(&mywait);
		return ret;
	}
	else if(r>0)
	{
		printk("User data %s\n",kbuff);
		printk("Data copied %d\n",count-r);
		ret = count-r;
		return ret;
	}
	else
	{
		printk("Error\n");
		ret = -EFAULT;
		return ret;
	}
	//Release semaphore
	
	up(&sample_sem);
	return sizeof(gbuff);
	

}

MODULE_LICENSE("GPL");
module_init(char_init);
module_exit(char_exit);
