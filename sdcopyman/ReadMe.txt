
sdcopyman

copy sd card 

sudo dd if=/dev/mmcblk0 of=/dev/sda bs=15123123

if output is 32G, use 
sudo raspi-config afterward.


ifconfig wlan0 |grep "inet addr"| cut -f 2 -d ":"|cut -f 1 -d " ">1.txt



ATBK	ON/OFF	�ϵ��Ĭ������	��ATBK+ON;
��ATBK+OFF;


ATS	row (0��1)
col��0��15)	
string
��ATS+1,0,abcd;
��ATS+0,0, %2B%25%3B;
��ʾ��+%;��

