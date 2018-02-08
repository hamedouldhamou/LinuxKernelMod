#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/list_sort.h>

struct birthday 
{	
	
	int day;
	int month;
	int year;
	char *name;
	struct list_head list;
	
	
};

/**
 * The following defines and initializes a list_head object named birthday_list
 */
static LIST_HEAD(birthday_list);

// START OF THE simple_init
int simple_init(void)
{
 /**
 * Declaring my structs
 */
	struct birthday *person;
	struct birthday *ptr;
	struct birthday *next;
        struct birthday *ptrvalue1;
	struct birthday *ptrvalue2;	

	

	/*Creating person 1*/
	person = kmalloc(sizeof(*person),GFP_KERNEL);// allocating memory for a person.
	person->month = 8;
	person->day = 20;
	person->year = 1993;
	person->name = "Hamed";
	INIT_LIST_HEAD(&person->list);//intializing the list member in the struct.
	list_add_tail(&person->list,&birthday_list);//adding a person to the end of the linkedlist.

	/*Creating person 2*/
	person = kmalloc(sizeof(*person),GFP_KERNEL);
	person->month = 9;
	person->day = 6;
	person->year = 1990;
	person->name = "Emilly";
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list,&birthday_list);

	/*Creating person 3*/
	person = kmalloc(sizeof(*person),GFP_KERNEL);
	person->month = 9;
	person->day = 3;
	person->year = 1995;
	person->name = "Chandler";
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list,&birthday_list);

	/*Creating person 4*/
	person = kmalloc(sizeof(*person),GFP_KERNEL);
	person->month = 3;
	person->day = 1;
	person->year = 1989;
	person->name = "Jim";
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list,&birthday_list);
	
	/*Creating person 5*/
	person = kmalloc(sizeof(*person),GFP_KERNEL);
	person->month = 12;
	person->day = 2;
	person->year = 1998;
	person->name = "Britney";
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list,&birthday_list);

	/*Creating person 6*/
	person = kmalloc(sizeof(*person),GFP_KERNEL);
	person->month = 4;
	person->day = 1;
	person->year = 1992;
	person->name = "Jack";
	INIT_LIST_HEAD(&person->list);
	list_add_tail(&person->list,&birthday_list);
      
	
	/*traverse through linked list and output its content*/
	list_for_each_entry(ptr, &birthday_list, list){
	printk(KERN_INFO "Birthday: Name: %s, Day: %d, Month: %d, Year: %d\n", ptr->name,ptr->day,ptr->month,ptr->year);

}

 /*traverse through linked list using entery_safe to get the ptr and next as parameters
 * and using and if and else if to compare the year of two person*/
 list_for_each_entry_safe(ptr,next,&birthday_list,list)
{
	if ((ptr->year)>(next->year))//if current year of birth is bigger than next
{
    ptrvalue1 = ptr;// then we save ptr value in ptrvalue1
    	
}
    else if ((ptr->year)<(next->year)) {// if the opposite
    ptrvalue2 = next;// we save next in ptrvalue2
    
}
   else// else continue
{
   continue;
}
  }// end of loop

/* Comparing the two values we recieved from the previous traverse through the list
*(ptrvalue1,ptrvalue2) and we pick the biggest year of birth witch means the youngest person 
and make our pointer ptr point to it */

   if ((ptrvalue1->year) < (ptrvalue2->year)) 
{
  ptr = ptrvalue2;
}
else if ((ptrvalue2->year) > (ptrvalue1->year))
{
 ptr = ptrvalue1; 
}// end if statment.

   /*Outputting the youngest person*/	
   printk(KERN_INFO"THIS IS THE YOUNGEST.");
   printk(KERN_INFO "Youngest: Name: %s, Day: %d, Month: %d, Year: %d\n", ptr->name,ptr->day,ptr->month,ptr->year);
 	
	list_del(&ptr->list);// remove the Youngest from the list.
        printk(KERN_INFO"THE YOUNGEST STUDENT WAS REMOVED");
	
	/*Going through the list and outputting the updated list without the youngest person. */
	printk(KERN_INFO"THIS IS THE UPDATED LIST.");
	list_for_each_entry(ptr, &birthday_list, list){
	printk(KERN_INFO "Birthday: Name: %s, Day: %d, Month: %d, Year: %d\n", ptr->name,ptr->day,ptr->month,ptr->year);

}



   return 0;
}//END OF THE simple_init


//START OF THE simple_exit
void simple_exit(void) {
	
	struct birthday *ptr, *next;

     
      /**Going through the list and removing the persons from the list*/
	list_for_each_entry_safe(ptr,next, &birthday_list,list)
{
	printk(KERN_INFO "Removing: Name: %s,Day:%d, Month:%d, Year: %d\n", ptr->name, ptr->day, ptr->month, ptr->year);
list_del(&ptr->list);
kfree(ptr);
}
	 
	
	

}

module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel Data Structures");
MODULE_AUTHOR("SGG");
