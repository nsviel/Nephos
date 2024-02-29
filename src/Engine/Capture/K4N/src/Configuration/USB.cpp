#include "USB.h"

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/usbdevice_fs.h>


namespace k4n::config{

//Constructor / Destructor
USB::USB(){
  //---------------------------


  //---------------------------
}
USB::~USB(){}

//Main function
void USB::reset_usb_port(string filename){
  //---------------------------

  int fd = open(filename.c_str(), O_WRONLY);
  if (fd < 0) {
    cout<<"[error] USB opening output file failed"<<endl;
    return;
  }

  printf("Resetting USB device %s\n", filename.c_str());
  int rc = ioctl(fd, USBDEVFS_RESET, 0);
  if (rc < 0) {
    cout<<"[error] USB ioctl failed"<<endl;
    return;
  }
  printf("Reset successful\n");

  close(fd);

  //---------------------------
}

}
