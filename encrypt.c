//encrypt.c
/* Necessary includes for device drivers */
#include <linux/init.h>
#include <generated/autoconf.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
#include <asm/system.h> /* cli(), *_flags */
#include <asm/uaccess.h> /* copy_from/to_user */


MODULE_LICENSE("Dual BSD/GPL");

/* Declaration of encrypt.c functions */
int encrypt_open(struct inode *inode, struct file *filp);
int encrypt_release(struct inode *inode, struct file *filp);
ssize_t encrypt_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
ssize_t encrypt_write(struct file *filp, char *buf, size_t count, loff_t *f_pos);
void encrypt_exit(void);
int encrypt_init(void);

/* Structure that declares the usual file */
/* access functions */
struct file_operations encrypt_fops = {
  read: encrypt_read,
  write: encrypt_write,
  open: encrypt_open,
  release: encrypt_release
};


/* Declaration of the init and exit functions */
module_init(encrypt_init);
module_exit(encrypt_exit);

/* Global variables of the driver */
/* Major number */
int encrypt_major = 60;
/* Buffer to store data */
char *encrypt_buffer;

char *encrypted_data;


// The encrypt method.
char* encrypt_ROT_47(const char* inputString, int size){
	
	//printf("%s\n", inputString);
	printk("| Encrypting");
	int strLeng = strlen(inputString);

	char* ca = kmalloc(strLeng, GFP_KERNEL); 
	int i = 0;
	for (i = 0; i < strLeng; i++)
	{
		char c = inputString[i];

		if (c >= 33 && c <= 126)
		{
			int j = c + 47;
			if (j > 126) 
			{
				j -= 94;
			}
				
			ca[i] = (char)j;
				
		}
		else
		{
			ca[i] = c;	
		}
	} 
  printk("| Encrypted");
	return ca;

}




int encrypt_init(void) {
  int result;

  /* Registering device */
  result = register_chrdev(encrypt_major, "encrypt", &encrypt_fops);
  if (result < 0) {
    printk(
      "<1>encrypt: cannot obtain major number %d\n", encrypt_major);
    return result;
  }

  /* Allocating encrypt for the buffer */
  //encrypt_buffer = kmalloc(1, GFP_KERNEL); 
//  if (!encrypt_buffer) { 
//    result = -ENOMEM;
//    goto fail; 
//  } 
//  memset(encrypt_buffer, 0, 1);
//
  printk("<1>Inserting encrypt module\n"); 
  return 0;

  fail: 
    encrypt_exit(); 
    return result;
}



void encrypt_exit(void) {
  /* Freeing the major number */
  unregister_chrdev(encrypt_major, "encrypt");

  /* Freeing buffer encrypt */
  if (encrypt_buffer) {
    kfree(encrypt_buffer);
  }

  printk("<1>Removing encrypt module\n");

}

int encrypt_open(struct inode *inode, struct file *filp) {

  /* Success */
  return 0;
}

int encrypt_release(struct inode *inode, struct file *filp) {
 
  /* Success */
  return 0;
}

// gets the data and gives it to the user
ssize_t encrypt_read(struct file *filp, char *buf, size_t count, loff_t *f_pos) { 
     
  //int datasize = strlen(filp->private_data);
  printk("| reading");
  copy_to_user(buf,filp->private_data,count);
  printk("| read\n");
  return count; 
}


//Encrypts the input information!
ssize_t encrypt_write( struct file *filp, char *buf, size_t count, loff_t *f_pos) {

  if (filp->private_data != NULL)
  {
    /* code */
    kfree(filp->private_data);
  }
  printk("| Writing");
  char* data_to_encrypt = kmalloc(count + 1, GFP_KERNEL); 
  copy_from_user(data_to_encrypt, buf, count);
  filp->private_data = encrypt_ROT_47(data_to_encrypt, count);
  printk("| Written");
  return count;
}
