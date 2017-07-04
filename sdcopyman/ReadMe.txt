
sdcopyman

copy sd card 

sudo dd if=/dev/mmcblk0 of=/dev/sda bs=15123123

if output is 32G, use 
sudo raspi-config afterward.


ifconfig wlan0 |grep "inet addr"| cut -f 2 -d ":"|cut -f 1 -d " ">1.txt



ATBK	ON/OFF	上电后默认是亮	发ATBK+ON;
发ATBK+OFF;


ATS	row (0～1)
col（0～15)	
string
发ATS+1,0,abcd;
发ATS+0,0, %2B%25%3B;
显示“+%;”

