
# -*- coding: utf-8 -*-
'''
说明：
窗体design V02，
4列表格方式
'''    

import sys
sys.path.append('/home/pi')

import threading, time, random
import w1thrd
import w2crsclck
import w3crscmgr
import w4window
import w5window
import allconfig
import waitingtaken
import waitingtakenlist
import takenarrived
import takenarrivedlist
import takenwaitarrived
import takenwaitarrivedlist
import sortedtitle
import sortedlist
import senttitle
import sentlist

 

global w
global conf
w = None
w = w5window.w5window()
conf = allconfig.allconfig(w.screen_width, w.screen_height)
conf.m_window = w


#//
def win_init(): #//窗体初始化
    pass;
    w.m_x = 0
    w.m_y = 0
    w.m_width = conf.m_screen_width
    w.m_height = conf.m_screen_height
    w.m_title = "自刷显示"
    w.updatedata()
    #//w.m_root.state("zoomed")
    w.m_root.attributes("-alpha", 0.99)
    #//w.m_root.attributes("-topmost", 1)
    pass


#//
def add_labels():
    pass;
    a = waitingtaken.waitingtaken()
    a.m_conf = conf
    a.init()
    #//a.openx()
    conf.m_n00b0 = a
    pass;
    pass
    a = waitingtakenlist.waitingtakenlist()
    a.m_conf = conf
    a.init()
    a.openx()
    conf.m_n00b1 = a
    pass;
    pass

    a = takenarrived.takenarrived()
    a.m_conf = conf
    a.init()
    a.openx()
    conf.m_n10b0 = a
    pass;
    pass
    a = takenarrivedlist.takenarrivedlist()
    a.m_conf = conf
    a.init()
    a.openx()
    conf.m_n10b1 = a
    pass;
    pass

    a = takenwaitarrived.takenwaitarrived()
    a.m_conf = conf
    a.init()
    a.openx()
    conf.m_n11b0 = a
    pass;
    pass
    a = takenwaitarrivedlist.takenwaitarrivedlist()
    a.m_conf = conf
    a.init()
    a.openx()
    conf.m_n11b1 = a
    pass;
    pass

    a = sortedtitle.sortedtitle()
    a.m_conf = conf
    a.init()
    a.openx()
    conf.m_n20b0 = a
    pass;
    pass
    a = sortedlist.sortedlist()
    a.m_conf = conf
    a.init()
    a.openx()
    conf.m_n20b1 = a
    pass;
    pass

    a = senttitle.senttitle()
    a.m_conf = conf
    a.init()
    a.openx()
    conf.m_n30b0 = a
    pass;
    pass
    a = sentlist.sentlist()
    a.m_conf = conf
    a.init()
    a.openx()
    conf.m_n30b1 = a
    pass;
    pass

#//
class AA(w1thrd.w1thrd):

    #//
    def __init__(self):
        pass
        w1thrd.w1thrd.__init__(self)
        pass
    
    
    #//
     #virtual
    def on_user_run(self):
        pass;
        w.wait_done()
        w.send_task( win_init )
        w.send_task( add_labels )
    
        while True:
            conf.GetData()
            conf.m_n00b0.Show()
            conf.m_n00b1.Show()
            conf.m_n10b0.Show()
            conf.m_n10b1.Show()
            conf.m_n11b0.Show()
            conf.m_n11b1.Show()
            conf.m_n20b0.Show()
            conf.m_n20b1.Show()
            conf.m_n30b0.Show()
            conf.m_n30b1.Show()
            
            if w1thrd.w1osinfo().iswin():
                time.sleep( random.uniform(3, 5) )
            else:
                time.sleep( random.uniform(9, 15) )

        pass;
        return 0;
 
print("a1")           
a = AA()
a.openx()
print("a2")       
 

w.loopwindow()  

    


