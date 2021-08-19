#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/device.h>
#include<linux/ioctl.h>

#define write_value _IOW('a','a',char*)
#define read_value _IOR('a','b',char*)

struct stats
{
	int size;
	char buff[100];
	int r_w;  //read = 0, write =1
};
dev_t mydev;
static int mychar_open(struct inode *inode, struct file *flip);
static int mychar_release(struct inode *inode, struct file *flip);
ssize_t mychar_read(struct file *flip, char __user *Ubuff, size_t count, loff_t *offp);
ssize_t mychar_write(struct file *flip, const char __user *Ubuff, size_t count, loff_t *offp);
static long mychar_ioctl(struct file *flip,unsigned int cmd, unsigned long arg);

struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = mychar_open,
	.release = mychar_release,
	.read = mychar_read,
	.write = mychar_write,
	.unlocked_ioctl = mychar_ioctl,
};

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
		printk("Device not created\n");
		return -1;
	}
	return 0;
}

static void __exit char_exit(void)
{
	int MAJOR,MINOR;
	MAJOR = MAJOR(mydev);
	MINOR = MINOR(mydev);
	printk("Major number is %d\t Minor number is %d\n",MAJOR,MINOR);

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


	r = copy_to_user((char *)Ubuff, (const char *)kbuff, sizeof(kbuff));
	if(r==0)
	{
		printk("Read data successfully %d\n",sizeof(kbuff));
		ret = sizeof(kbuff);
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
		ret = -EFAULT;
		return ret;
	}
	return ret;
	}

ssize_t mychar_write(struct file *flip, const char __user *Ubuff, size_t count, loff_t *offp)
{
	char kbuff[100];
	unsigned long r;
	ssize_t ret;


	r = copy_from_user((char *)kbuff,(char *)Ubuff, count);
	if(r == 0)
	{
		printk("User data %s\n", kbuff);
		ret = count;
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
	return ret;
	
}

static long mychar_ioctl(struct file *flip, unsigned int cmd, unsigned long arg)
{
	struct stats p;
	p.buff[100] = 'sr';
	switch(cmd)
	{
		case write_value:
			p.r_w = 0;
			p.size = sizeof(p.buff);
			copy_from_user(&(p.buff),(char *)arg,sizeof(p.buff));
			printk("Buff = %s\n",p.buff);
			printk("size = %d\n",p.size);
			printk("r_w = %d\n",p.r_w);
			break;
		
	        case read_value:
			p.r_w = 1;
			p.size = sizeof(p.buff);
			copy_to_user(&(p.buff), (char *)arg, sizeof(p.buff));
			printk("buff = %s\n",p.buff);
			printk("size = %d\n",p.size);
			printk("r_w = %d\n",p.r_w);
			break;
	}
	return 0;
}
					
MODULE_LICENSE("GPL");
module_init(char_init);
module_exit(char_exit);
