
������ʼ¼��5��

�������


�˿�3022��0x0A��β��������:

get_md5
	��õ�ǰ¼���ļ�md5�ִ���32�ֽ�Сд����0x0A��β��
	���û���ļ�������¼����blockס
	

del
	ɾ����ǰ�ļ�
	�������¼����blockס


�˿�3023��������:
	ֱ�ӷ����ļ����ر����ӡ�
	
	

�˿�3024��������
	����д���wav��Ȼ��ر����ӣ�����һ�Ρ�




sudo amixer sset PCM 100% 
sudo aplay test2.wav
sudo aplay test.wav	
sudo aplay -D plughw:1 test.wav	
sudo aplay -D plughw:1 test2.wav
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
sudo arecord -d 5 -D plughw:1 -f S16_LE -c1 -r16000 test3.wav
sudo aplay -D plughw:1 test.wav
sudo aplay -D plughw:1 test2.wav
sudo aplay -D plughw:1 test3.wav
python3 t02post.py

sudo avconv -i test3.wav test3.mp3


