#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/timer.h>
#include <linux/proc_fs.h>

#define DRIVER_AUTHOR	"Maxime PI CHE RIT- Martina VAN DE MOUCHE DICK - Fredo RODIER"
#define DRIVER_DESC		"Chenillard Module"
#define DRIVER_LICENSE	"GPL or SP or Diesel"

#define PROC_NAME		"Chennilard TP2"
#define PROC_PAR_NAME	"MBM (Men Between Mouse)"
struct file_operations proc_fops = {};
struct proc_dir_entry* proc_parent;

// Paramètre du timer pour la fréquence du chennillard
// Il modifie l'index de la led et print dans le Kernel
#define TIM1_PERIOD		200
static struct timer_list tim1;
static int led_index = 0;

static void tim1_callback(unsigned long data) {
	mod_timer(&tim1, jiffies + TIM1_PERIOD);
	if (led_index < 10){
		printk(KERN_INFO "Led index %d  : ON\n", led_index);
		led_index ++;
	}
	else {
		led_index = 0;
	}
}

// Paramètre de notre module
static int param_val;

module_param(param_val, int ,0);
MODULE_PARM_DESC(param_val, "LE paramètre");

int chenillard_init(void)
{
	proc_parent = proc_mkdir(PROC_PAR_NAME, NULL);
	proc_create(PROC_NAME, 0, proc_parent, &proc_fops);

	// Configuration du timer
	setup_timer(&tim1, tim1_callback, 0);
	mod_timer(&tim1, jiffies + TIM1_PERIOD);

	printk(KERN_INFO "Hello world !\n");
	printk(KERN_DEBUG "Tu as choisie : %d\n", param_val);
	return 0;
}

void chenillard_exit(void)
{
	// Suppression des processus et timer
	remove_proc_entry(PROC_NAME, proc_parent);
	remove_proc_entry(PROC_PAR_NAME, NULL);
	del_timer(&tim1);

	printk(KERN_ALERT "Bye bye...\n");
}

module_init(chenillard_init);
module_exit(chenillard_exit);

MODULE_LICENSE(DRIVER_LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);