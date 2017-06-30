
触发开始录音5秒

可用命令：


端口3022，0x0A结尾，短连接:

get_md5
	获得当前录音文件md5字串，32字节小写，以0x0A结尾。
	如果没有文件或正在录音就block住
	

del
	删除当前文件
	如果正在录音就block住


端口3023，短连接:
	直接发出文件并关闭连接。
	
	

端口3024，短连接
	接收写入的wav，然后关闭连接，播放一次。




sudo amixer sset PCM 100% 
sudo aplay test2.wav
sudo aplay test.wav	
sudo aplay -D plughw:1 test4.wav	
sudo mpv test3.wav

sudo arecord -d 3 -D plughw:1 -f S16_LE -c1 -r16000 test.wav
sudo opusenc test3.wav test3.opus
sudo mpv test3.opus

python3 beep_on.py
python3 beep_off.py
python3 led_on.py
python3 led_off.py
python3 get_button.py
python3 get_miclevel.py

sudo amixer cset numid=1 31
 amixer cset numid=4 31
amixer controls
amixer -c 0
amixer -c 1

sudo amixer -c 1 controls
sudo amixer -c 1 cget numid=4
sudo amixer -c 1 cset numid=4 31
sudo amixer -c 1 cset numid=6 37


pi@raspberrypi:~ $ sudo amixer -c 1 controls
numid=3,iface=MIXER,name='Mic Playback Switch'
numid=4,iface=MIXER,name='Mic Playback Volume'
numid=7,iface=MIXER,name='Mic Capture Switch'
numid=8,iface=MIXER,name='Mic Capture Volume'
numid=9,iface=MIXER,name='Auto Gain Control'
numid=5,iface=MIXER,name='Speaker Playback Switch'
numid=6,iface=MIXER,name='Speaker Playback Volume'
numid=2,iface=PCM,name='Capture Channel Map'
numid=1,iface=PCM,name='Playback Channel Map'
pi@raspberrypi:~ $

sudo amixer -c 1 cget numid=8
//	sudo amixer -c 1 cset numid=8 35
sudo amixer -c 1 cset numid=8 20
sudo amixer -c 1 cget numid=5
sudo amixer -c 1 cget numid=6
sudo amixer -c 1 cset numid=6 37
sudo arecord -d 3 -D plughw:1 -f S16_LE -c1 -r16000 test.wav
sudo aplay -D plughw:1 test.wav
sudo aplay -D plughw:1 test3.wav
python3 t02post.py

sudo avconv -i test3.wav test3.mp3


