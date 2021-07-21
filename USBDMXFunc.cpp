// USBFunc.cpp: исходный файл, содержащий только USB включаемые модули
#include "stdafx.h"


static int  usbGetStringAscii(usb_dev_handle *dev, int index, int langid, char *buf, int buflen)
{
char    buffer[256];
int     rval, i;

    if((rval = usb_control_msg(dev, USB_ENDPOINT_IN, USB_REQ_GET_DESCRIPTOR, (USB_DT_STRING << 8) + index, langid, buffer, sizeof(buffer), 1000)) < 0)
        return rval;
    if(buffer[1] != USB_DT_STRING)
        return 0;
    if((unsigned char)buffer[0] < rval)
        rval = (unsigned char)buffer[0];
    rval /= 2;
    /* lossy conversion to ISO Latin1 */
    for(i=1;i<rval;i++){
        if(i > buflen)  /* destination buffer overflow */
            break;
        buf[i-1] = buffer[2 * i];
        if(buffer[2 * i + 1] != 0)  /* outside of ISO Latin1 range */
            buf[i-1] = '?';
    }
    buf[i-1] = 0;
    return i-1;
}


/* PowerSwitch uses the free shared default VID/PID. If you want to see an
 * example device lookup where an individually reserved PID is used, see our
 * RemoteSensor reference implementation.
 */
static usb_dev_handle   *findDevice(void)
{
struct usb_bus      *bus;
struct usb_device   *dev;
usb_dev_handle      *handle = 0;

    usb_find_busses();
    usb_find_devices();
    for(bus=usb_busses; bus; bus=bus->next){
        for(dev=bus->devices; dev; dev=dev->next){
            if(dev->descriptor.idVendor == USBDEV_SHARED_VENDOR && dev->descriptor.idProduct == USBDEV_SHARED_PRODUCT){
                char    string[256];
                int     len;
                handle = usb_open(dev); /* we need to open the device in order to query strings */
                if(!handle){
                    if(USB_DEBUG) fprintf(stderr, "Warning: cannot open USB device: %s\n", usb_strerror());
                    continue;
                }
                len = usbGetStringAscii(handle, dev->descriptor.iManufacturer, 0x0409, string, sizeof(string));
                if(len < 0){
                    if(USB_DEBUG) fprintf(stderr, "warning: cannot query manufacturer for device: %s\n", usb_strerror());
                    goto skipDevice;
                }
                if(strcmp(string, USBDEV_SHARED_MANUFACTURER_STRING) != 0)
                    goto skipDevice;
                len = usbGetStringAscii(handle, dev->descriptor.iProduct, 0x0409, string, sizeof(string));
                if(len < 0){
                    if(USB_DEBUG) fprintf(stderr, "warning: cannot query product for device: %s\n", usb_strerror());
                    goto skipDevice;
                }
                if(strcmp(string, USBDEV_SHARED_PRODUCT_STRING) == 0)
                    break;
skipDevice:
                usb_close(handle);
                handle = NULL;
            }
        }
        if(handle)
            break;
    }
    if(!handle)
	{
        if(USB_DEBUG) fprintf(stderr, "Could not find USB device %s/%s\n",USBDEV_SHARED_MANUFACTURER_STRING,USBDEV_SHARED_PRODUCT_STRING);
	}
    return handle;
}

static void DMX_Open(void)
{
	if(USB_DEBUG) usb_set_debug(1);
   
    usb_init();
    if((DMXHandle = findDevice()) == NULL)
	{
        if(USB_DEBUG) fprintf(stderr, "Could not find USB device \"%s\" with vid=0x%x pid=0x%x\n",USBDEV_SHARED_PRODUCT_STRING, USBDEV_SHARED_VENDOR, USBDEV_SHARED_PRODUCT);
    }
}

static void DMX_Close(void)
{
	if(DMXHandle)
	{
		usb_close(DMXHandle);
		DMXHandle=NULL;
	}
}

static int DMX_Send( int CC /* Channel Count */,int FC /* From Channel */, char *DMX_B /* DMX Buffer */ ){

	return usb_control_msg(DMXHandle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, cmd_SetChannelRange,
	 CC /* Lenth */, FC-1 /* From Channel */, DMX_B /* Buffer with Chanells */, CC /* Channel count */, 1000 /* Usb wait Time */);
}