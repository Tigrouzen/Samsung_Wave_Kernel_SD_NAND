/* drivers/misc/fsync_control.c
 *
 * Copyright 2012  Ezekeel
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/device.h>
#include <linux/miscdevice.h>

#define DEVIL_TWEAKS_VERSION 1

static bool smooth_ui_enabled = true;
static bool smooth_governors_enabled = false;
static bool powersave_governors_enabled = false;
static int governors_profile = 0;

bool smooth_ui()
{
    return smooth_ui_enabled;
}
EXPORT_SYMBOL(smooth_ui);


static ssize_t smooth_ui_status_read(struct device * dev, struct device_attribute * attr, char * buf)
{
    return sprintf(buf, "%u\n", (smooth_ui_enabled ? 1 : 0));
}

static ssize_t smooth_ui_status_write(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
    unsigned int data;

    if(sscanf(buf, "%u\n", &data) == 1) 
	{
	    if (data == 1) 
		{
		    pr_info("%s: smooth_ui enabled\n", __FUNCTION__);
		    smooth_ui_enabled = true;
		} 
	    else if (data == 0) 
		{
		    pr_info("%s: smooth_ui disabled\n", __FUNCTION__);
		    smooth_ui_enabled = false;
		} 
	    else 
		{
		    pr_info("%s: invalid input range %u\n", __FUNCTION__, data);
		}
	} 
    else 
	{
	    pr_info("%s: invalid input\n", __FUNCTION__);
	}

    return size;
}



bool smooth_governors()
{
    return smooth_governors_enabled;
}
EXPORT_SYMBOL(smooth_governors);


static ssize_t governors_profile_read(struct device * dev, struct device_attribute * attr, char * buf)
{
    return sprintf(buf, "%u\n", governors_profile);
}


static ssize_t governors_profile_write(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
    unsigned int data;

    if(sscanf(buf, "%u\n", &data) == 1) 
	{
	    if (data == 1) 
		{
		    pr_info("%s: smooth_governors enabled\n", __FUNCTION__);

		    smooth_governors_enabled = true;
		    powersave_governors_enabled = false;
		    governors_profile = data;
		} 
	    else if (data == 2) 
		{
		    pr_info("%s: powersave_governors enabled\n", __FUNCTION__);

		    smooth_governors_enabled = false;
		    powersave_governors_enabled = true;
		    governors_profile = data;
		} 
	    else 
		{
		    pr_info("%s: governors_profile disabled \n", __FUNCTION__);
		    smooth_governors_enabled = false;
		    powersave_governors_enabled = false;
		    governors_profile = 0;
		}
	} 
    else 
	{
	    pr_info("%s: invalid input\n", __FUNCTION__);
	}

    return size;
}
/*
static ssize_t smooth_governors_status_read(struct device * dev, struct device_attribute * attr, char * buf)
{
    return sprintf(buf, "%u\n", (smooth_governors_enabled ? 1 : 0));
}

static ssize_t smooth_governors_status_write(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
    unsigned int data;

    if(sscanf(buf, "%u\n", &data) == 1) 
	{
	    if (data == 1) 
		{
		    pr_info("%s: smooth_governors enabled\n", __FUNCTION__);

		    smooth_governors_enabled = true;
		    powersave_governors_enabled = false;
		} 
	    else if (data == 0) 
		{
		    pr_info("%s: smooth_governors disabled\n", __FUNCTION__);

		    smooth_governors_enabled = false;
		} 
	    else 
		{
		    pr_info("%s: invalid input range %u\n", __FUNCTION__, data);
		}
	} 
    else 
	{
	    pr_info("%s: invalid input\n", __FUNCTION__);
	}

    return size;
}
*/


bool powersave_governors()
{
    return powersave_governors_enabled;
}
EXPORT_SYMBOL(powersave_governors);
/*
static ssize_t powersave_governors_status_read(struct device * dev, struct device_attribute * attr, char * buf)
{
    return sprintf(buf, "%u\n", (powersave_governors_enabled ? 1 : 0));
}

static ssize_t powersave_governors_status_write(struct device * dev, struct device_attribute * attr, const char * buf, size_t size)
{
    unsigned int data;

    if(sscanf(buf, "%u\n", &data) == 1) 
	{
	    if (data == 1) 
		{
		    pr_info("%s: powersave_governors enabled\n", __FUNCTION__);

		    powersave_governors_enabled = true;
		    smooth_governors_enabled = false;	
		} 
	    else if (data == 0) 
		{
		    pr_info("%s: powersave_governors disabled\n", __FUNCTION__);

		    powersave_governors_enabled = false;
		} 
	    else 
		{
		    pr_info("%s: invalid input range %u\n", __FUNCTION__, data);
		}
	} 
    else 
	{
	    pr_info("%s: invalid input\n", __FUNCTION__);
	}

    return size;
}
*/

static ssize_t devil_tweaks_version(struct device * dev, struct device_attribute * attr, char * buf)
{
    return sprintf(buf, "%u\n", DEVIL_TWEAKS_VERSION);
}

static DEVICE_ATTR(smooth_ui_enabled, S_IRUGO | S_IWUGO, smooth_ui_status_read, smooth_ui_status_write);
static DEVICE_ATTR(governors_profile, S_IRUGO | S_IWUGO, governors_profile_read, governors_profile_write);
//static DEVICE_ATTR(smooth_governors_enabled, S_IRUGO | S_IWUGO, smooth_governors_status_read, smooth_governors_status_write);
//static DEVICE_ATTR(powersave_governors_enabled, S_IRUGO | S_IWUGO, powersave_governors_status_read, powersave_governors_status_write);
static DEVICE_ATTR(version, S_IRUGO , devil_tweaks_version, NULL);

static struct attribute *devil_tweaks_attributes[] = 
    {
	&dev_attr_smooth_ui_enabled.attr,
//	&dev_attr_smooth_governors_enabled.attr,
//	&dev_attr_powersave_governors_enabled.attr,
	&dev_attr_governors_profile.attr,
	&dev_attr_version.attr,
	NULL
    };

static struct attribute_group devil_tweaks_group = 
    {
	.attrs  = devil_tweaks_attributes,
    };

static struct miscdevice devil_tweaks_device = 
    {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "devil_tweaks",
    };

static int __init devil_tweaks_init(void)
{
    int ret;

    pr_info("%s misc_register(%s)\n", __FUNCTION__, devil_tweaks_device.name);

    ret = misc_register(&devil_tweaks_device);

    if (ret) 
	{
	    pr_err("%s misc_register(%s) fail\n", __FUNCTION__, devil_tweaks_device.name);
	    return 1;
	}

    if (sysfs_create_group(&devil_tweaks_device.this_device->kobj, &devil_tweaks_group) < 0) 
	{
	    pr_err("%s sysfs_create_group fail\n", __FUNCTION__);
	    pr_err("Failed to create sysfs group for device (%s)!\n", devil_tweaks_device.name);
	}

    return 0;
}

device_initcall(devil_tweaks_init);
