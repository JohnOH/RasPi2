https://wiki.ubuntu.com/ARM/RaspberryPi#Download

Kernel Headers:
  apt-get install linux-headers-$(uname -r)

http://raspberrypi.stackexchange.com/questions/8851/setting-up-wifi-and-ethernet
  
Transfer .img file as usual to micro SD card.

Initial login must be via keyboard & HDMI connected display.
You should have a (resized) SD card at least 4GB, because by default it will want to create a ~2GB swapfile.

Disable swap file:
  sudo chmod -x /etc/init.d/dphys-swapfile
  sudo swapoff -a
  sudo rm /var/swap

This is a minimal ubuntu-standard image. If you want a full desktop, go ahead and do so:

  sudo apt-get install xubuntu-desktop

http://scruss.com/blog/2013/06/07/well-that-was-unexpected-the-raspberry-pis-hardware-random-number-generator/
sudo modprobe bcm2708-rng
sudo apt-get install rng-tools

cat /proc/sys/kernel/random/entropy_avail
sudo cat /dev/hwrng | rngtest -c 1000

ssh is not installed/enabled by default.
  sudo apt-get install ssh

Once installed remote login is fine using Putty etc.
Default login is ubuntu with password ubuntu

Add a user:
  adduser john
  ..password
  ..password
  ..full name etc.

If appropriate add the user to the sudo group:
  adduser john sudo

Allow use of FTDI type connections etc:  
  adduser john dialout
  

Change password to secure the default account
  passwd
  ..ubuntu
  ..asrequired
  ..asrequired
  exit
  
Login with the appropriate user name and then:

  sudo apt-get install build-essential gcc-arm-none-eabi
  sudo apt-get install git
  sudo apt-get install curl
  
Set git defaults:
  git config --global push.default current
  git config --global user.name "Full name"
  git config --global user.email "user@domain"

Install Go:  
  sudo -s
  cd /usr/local
  curl http://dave.cheney.net/paste/go1.4.linux-arm~multiarch-armv7-1.tar.gz | tar zxf -
  echo "export PATH=$PATH:/usr/local/go/bin" >>/etc/profile.d/go.sh
  exit
  echo 'export GOPATH=$HOME/go' >>~/.profile
  echo 'export PATH=$PATH:$GOPATH/bin' >>~/.profile
  mkdir $HOME/go
Logout
  exit
and then back in again.
  go env 
should display:
john@ubuntu:~$ go env
GOARCH="arm"
GOBIN=""
GOCHAR="5"
GOEXE=""
GOHOSTARCH="arm"
GOHOSTOS="linux"
GOOS="linux"
GOPATH="/home/john/go"
GORACE=""
GOROOT="/usr/local/go"
GOTOOLDIR="/usr/local/go/pkg/tool/linux_arm"
CC="gcc"
GOGCCFLAGS="-fPIC -marm -pthread -fmessage-length=0"
CXX="g++"
CGO_ENABLED="1"

Now install the uploader package:
  go get -u github.com/jeelabs/embello/tools/uploader
  
  cd
  mkdir github
  cd github
  
  git clone https://github.com/jeelabs/embello.git
  cd embello/lib/test-lpc8xx-none/
  make clean

Connect your FTDI card and Pico to USB

john@ubuntu:~/github/embello/lib/test-lpc8xx-none$ make
uploader -s /dev/ttyUSB0 build/firmware.bin #build/firmware.bin
found: 8242 - LPC824: 32 KB flash, 8 KB RAM, TSSOP20
hwuid: 07800307679C61AEB98AA053870200F5
flash: 0880 done, 2120 bytes
entering terminal mode, press <ESC> to quit:


[rf_ping] dev 8242 node 24
 > 1
 > 2
 > 3
 > 4
 > 5

Edit your .bashrc file to shorten the system prompt by changing the 'w' below:
----------------------------------
if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
----------------------------------

to: 'W'

----------------------------------
if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\W\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\W\$ '
fi
----------------------------------

                               
Links:
http://www.finnie.org/2015/02/14/ubuntu-14-04-trusty-tahr-on-the-raspberry-pi-2/#comment-670818
http://sjoerd.luon.net/posts/2015/02/debian-jessie-on-rpi2/
