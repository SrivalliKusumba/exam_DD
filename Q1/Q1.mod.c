#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x4766f3ab, "module_layout" },
	{ 0xadfb6ea0, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xe171d059, "class_destroy" },
	{ 0xb37ccf3d, "device_destroy" },
	{ 0x1b6c45b6, "device_create" },
	{ 0xd74cab92, "__class_create" },
	{ 0x60d951ec, "cdev_init" },
	{ 0x31ace3dd, "cdev_add" },
	{ 0xa8881d43, "cdev_alloc" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x5f754e5a, "memset" },
	{ 0x2cfde9a2, "warn_slowpath_fmt" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0xf9a482f9, "msleep" },
	{ 0xca5a7528, "down_interruptible" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xc5850110, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "C079B2768EF601621F63E94");
