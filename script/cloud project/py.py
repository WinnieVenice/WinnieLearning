# 原文：https://blog.csdn.net/zhuisui_woxin/article/details/84400439

# 基于FLANN的匹配器(FLANN based Matcher)定位图片
import numpy as np
import cv2
#from matplotlib import pyplot as plt
#import PyHook3
import os
#import win32gui
import time
import sys
import random
import subprocess as sp
import numpy
from matplotlib import pyplot as plt
py_path = os.path.split(sys.argv[0])[0]
order_path = ''
print('当前文件目录: ', py_path)
_floor_1 = [ py_path + '\\10_1.png', py_path + '\\20_1.png', py_path + '\\30_1.png', py_path + '\\40_1.png', py_path + '\\50_1.png', py_path + '\\60_1.png', py_path + '\\70_1.png', py_path + '\\80_1.png', py_path + '\\90_1.png', py_path + '\\100_1.png', 
py_path + '\\110_1.png', py_path + '\\120_1.png', py_path + '\\130_1.png', py_path + '\\140_1.png', py_path + '\\150_1.png', py_path + '\\160_1.png', py_path + '\\170_1.png', py_path + '\\180_1.png', py_path + '\\190_1.png', py_path + '\\200_1.png', py_path + '\\210_1.png', py_path + '\\220_1.png', py_path + '\\230_1.png', py_path + '\\240_1.png', py_path + '\\250_1.png', py_path + '\\260_1.png', py_path + '\\270_1.png', py_path + '\\280_1.png', py_path + '\\290_1.png', py_path + '\\300_1.png', py_path 
+ '\\310_1.png', py_path + '\\320_1.png', py_path + '\\330_1.png', py_path + '\\340_1.png', py_path + '\\350_1.png', py_path + 
'\\360_1.png', py_path + '\\370_1.png', py_path + '\\380_1.png', py_path + '\\390_1.png', py_path + '\\400_1.png']
_floor_2 = [ py_path + '\\10_2.png', py_path + '\\20_2.png', py_path + '\\30_2.png', py_path + '\\40_2.png', py_path + '\\50_2.png', py_path + '\\60_2.png', py_path + '\\70_2.png', py_path + '\\80_2.png', py_path + '\\90_2.png', py_path + '\\100_2.png', 
py_path + '\\110_2.png', py_path + '\\120_2.png', py_path + '\\130_2.png', py_path + '\\140_2.png', py_path + '\\150_2.png', py_path + '\\160_2.png', py_path + '\\170_2.png', py_path + '\\180_2.png', py_path + '\\190_2.png', py_path + '\\200_2.png', py_path + '\\210_2.png', py_path + '\\220_2.png', py_path + '\\230_2.png', py_path + '\\240_2.png', py_path + '\\250_2.png', py_path + '\\260_2.png', py_path + '\\270_2.png', py_path + '\\280_2.png', py_path + '\\290_2.png', py_path + '\\300_2.png', py_path 
+ '\\310_2.png', py_path + '\\320_2.png', py_path + '\\330_2.png', py_path + '\\340_2.png', py_path + '\\350_2.png', py_path + 
'\\360_2.png', py_path + '\\370_2.png', py_path + '\\380_2.png', py_path + '\\390_2.png', py_path + '\\400_2.png']
_reward = [py_path + '\\shuhe.png', py_path + '\\skill_point.png', py_path + '\\xp.png']
temp_path = py_path + '\\temp_path.png'

_configuration_path = py_path + '\\configuration.txt'

_jiesuan_1 = py_path + '\\jiesuan_1.png'
_jiesuan_2 = py_path + '\\jiesuan_2.png'
#_shuhe = py_path + '\\shuhe.png'
#_skill_point = py_path + '\\skill_point.png'
_not_choose = py_path + '\\not_choose.png'
_buy = py_path + '\\buy.png'
_quit = py_path + '\\quit.png'
_back1 = py_path + '\\back1.png'
_back2 = py_path + '\\back2.png'
_start = py_path + '\\start.png'
_start_fight_1 = py_path + '\\start_fight_1.png'
_start_fight_2 = py_path + '\\start_fight_2.png'
_continue = py_path + '\\continue.png'
_xieyi = py_path + '\\xieyi.png'
_ai_mode = py_path + '\\ai_mode.png'
_ai_start = py_path + '\\ai_start.png'
_confirm_quit = py_path + '\\confirm_quit.png'
_confirm = py_path + '\\confirm.png'
_cancel = py_path + '\\cancel.png'
_no_money = py_path + '\\no_money.png'
_re_fight_1 = py_path +'\\re_fight_1.png'
_re_fight_2 = py_path + '\\re_fight_2.png'
_fight_fail = py_path + '\\fight_fail.png'
_run = py_path + '\\run.png'
_width = 0
_height = 0
#_rect_windows = [0, 0, _w, _h]
BUTTON_MIN_MATCH_COUNT = 10
ITEM_MIN_MATCH_COUNT = 10
ONE_MINITE = 60
SLEEP_TIME = 5
D_FIND_REWARD = 1
cur_choose_reward = []
cur_floor = 150
fight_time = 9
SWIPE_TIME = 1000
def init_configuration(_T):
    if _T == False:
        return
    try:
        f = open(_configuration_path, 'r')
        _list = f.readlines()
        for i in range(0, len(_list)):
            _list[i] = _list[i].rstrip('\n')
        print(_list)
        global BUTTON_MIN_MATCH_COUNT
        BUTTON_MIN_MATCH_COUNT = int(_list[0])
        global ITEM_MIN_MATCH_COUNT
        ITEM_MIN_MATCH_COUNT = int(_list[1])
        global SLEEP_TIME 
        SLEEP_TIME  = int(_list[2])
        global D_FIND_REWARD 
        D_FIND_REWARD = int(_list[3])
        global idx_choose_reward 
        idx_choose_reward = _list[4].split(',', -1)
        global cur_floor 
        cur_floor = int(_list[5])
        global adb_port 
        adb_port = _list[6]
        global SWIPE_TIME 
        SWIPE_TIME = int(_list[7])
        global fight_time
        fight_time = 9
        global order_path
        order_path = _list[8]
        for x in _list[4].split(',', -1):
            cur_choose_reward.append(_reward[int(x)])    
        print('BUTTON_MIN_MATCH_COUNT: ', BUTTON_MIN_MATCH_COUNT)
        print('ITEM_MIN_MATCH_COUNT: ', ITEM_MIN_MATCH_COUNT)
        print('SLEEP_TIME: ', SLEEP_TIME)
        print('D_FIND_REWARD: ', D_FIND_REWARD)
        print('所选奖品: ', cur_choose_reward)
        print('所选楼层: ', cur_floor)
        print('预估战斗时间: ', fight_time, '分钟')
        print('当前adb地址端口: ', adb_port)
        print('当前滑动时常:', SWIPE_TIME)
        print('adb所在地址: ', order_path)
    finally:
        f.close()
def _match(_tpl, _target, _T, MIN_MATCH_COUNT):
    try:
        template = cv2.imread(_tpl, 0)
        target = cv2.imdecode(_target, 0)
        #target = cv2.imread(_target, 0) # trainImage
        # Initiate SIFT detector创建sift检测器
        sift = cv2.xfeatures2d.SIFT_create()
        # find the keypoints and descriptors with SIFT
        kp1, des1 = sift.detectAndCompute(template,None)
        kp2, des2 = sift.detectAndCompute(target,None)
        #创建设置FLANN匹配
        FLANN_INDEX_KDTREE = 0
        index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 5)
        search_params = dict(checks = 50)
        flann = cv2.FlannBasedMatcher(index_params, search_params)
        matches = flann.knnMatch(des1,des2,k=2)
        # store all the good matches as per Lowe's ratio test.
        good = []
        #舍弃大于0.7的匹配
        for m,n in matches:
            if m.distance < 0.4*n.distance:
                good.append(m)
        _x = []
        _y = []
        if len(good)>=MIN_MATCH_COUNT:
            # 获取关键点的坐标
            src_pts = np.float32([ kp1[m.queryIdx].pt for m in good ]).reshape(-1,1,2)
            dst_pts = np.float32([ kp2[m.trainIdx].pt for m in good ]).reshape(-1,1,2)
            #print(dst_pts)
            for _p in dst_pts:
                _x.append(_p[0][0])
                _y.append(_p[0][1])
            _x.sort()
            _y.sort()
            if _T:
                time.sleep(1)
                print([int(_x[len(_x) // 2]), int(_y[len(_y) // 2])])
                mouse_click(int(_x[len(_x) // 2]), int(_y[len(_y) // 2]))
            '''
            #计算变换矩阵和MASK
            M, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC, 5.0)
            matchesMask = mask.ravel().tolist()
            h,w = template.shape
            # 使用得到的变换矩阵对原图像的四个角进行变换，获得在目标图像上对应的坐标
            pts = np.float32([ [0,0],[0,h-1],[w-1,h-1],[w-1,0] ]).reshape(-1,1,2)
            dst = cv2.perspectiveTransform(pts,M)
            cv2.polylines(target,[np.int32(dst)],True,0,2, cv2.LINE_AA)
            '''
        else:
            print( "Not enough matches are found - %d/%d" % (len(good),MIN_MATCH_COUNT))
            matchesMask = None
            return True
        '''
        draw_params = dict(matchColor=(0,255,0), 
                        singlePointColor=None,
                        matchesMask=matchesMask, 
                        flags=2)
        result = cv2.drawMatches(template,kp1,target,kp2,good,None,**draw_params)
        plt.imshow(result, 'gray')
        plt.show()
        '''
        return False
    except Exception as e:
        print('except')
        return True
def _match_pct(_tpl, _target, MIN_MATCH_COUNT):
    try:
        template = cv2.imread(_tpl, 0)
        target = _target
        #target = cv2.imdecode(_target, 0)
        #target = cv2.imread(_target, 0) # trainImage
        # Initiate SIFT detector创建sift检测器
        sift = cv2.xfeatures2d.SIFT_create()
        # find the keypoints and descriptors with SIFT
        kp1, des1 = sift.detectAndCompute(template,None)
        kp2, des2 = sift.detectAndCompute(target,None)
        #创建设置FLANN匹配
        FLANN_INDEX_KDTREE = 0
        index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 5)
        search_params = dict(checks = 50)
        flann = cv2.FlannBasedMatcher(index_params, search_params)
        matches = flann.knnMatch(des1,des2,k=2)
        # store all the good matches as per Lowe's ratio test.
        good = []
        #舍弃大于0.7的匹配
        for m,n in matches:
            if m.distance < 0.3*n.distance:
                good.append(m)
        if len(good) < MIN_MATCH_COUNT:
            print( "Not enough matches are found - %d/%d" % (len(good),MIN_MATCH_COUNT))
            return False
        return True
    except Exception as e:
        print('except')
        return False
def _screenshot():
    pp = sp.Popen(order_path + ' exec-out screencap -p', shell = True, stdout = sp.PIPE)
    byteImg = pp.stdout.read().replace(b'\r\n', b'\n')
    pp.communicate()
    return numpy.asarray(bytearray(byteImg), dtype = numpy.uint8)
def mouse_swipe(_x1, _y1, _x2, _y2, _time):
    order = order_path + ' shell input swipe ' + str(_x1) + ' ' + str(_y1 + random.randrange(0, 11, 1)) + ' ' + str(_x2) + ' ' + str(_time + random.randrange(0, _time, 1))
    pp = sp.Popen(order, shell = True, stdout = sp.PIPE)
    pp.communicate()
def mouse_click(_x, _y):
    order = order_path + ' shell input tap ' + str(_x + random.randrange(0, 6, 1)) + ' ' + str(_y + random.randrange(0, 6, 1))
    pp = sp.Popen(order, shell = True, stdout = sp.PIPE)
    pp.communicate()
def adb_init(_adb_port):
    pp = sp.Popen(order_path + ' connect ' + _adb_port, shell = True, stdout = sp.PIPE)
    print(pp.stdout.read())
    pp.communicate()
    pp = sp.Popen(order_path + ' shell wm size', shell = True, stdout = sp.PIPE)
    str = bytes.decode(pp.stdout.read())
    pp.communicate()
    str = str.lstrip('Physical size: ')
    str = str.rstrip('\r\r\n')
    global _width
    _width = int(str.split('x')[0])
    global _height
    _height = int(str.split('x')[1])
    print('初始化窗口大小为: ', _width, 'x', _height)
def find_floor(_floor, _sleep_time):
    print('寻找', _floor, '楼层')
    cur_floor_path_1 = _floor_1[_floor // 10 - 1]
    cur_floor_path_2 = _floor_2[_floor // 10 - 1]
    time.sleep(_sleep_time)
    arr = _screenshot()
    #gui.screenshot(temp_path, _rect_windows)
    swipe_cnt = 0
    _direction = 1
    while _match(cur_floor_path_1, arr, True, BUTTON_MIN_MATCH_COUNT) and _match(cur_floor_path_2, arr, True, BUTTON_MIN_MATCH_COUNT):
        print('寻找', _floor, '楼层')
        if _direction == 1 :
            swipe_cnt += 1
        else:
            swipe_cnt -= 1
        if swipe_cnt > (_width + 200 - 1) // 200:
            _direction = 0
        elif swipe_cnt < 0:
            _direction = 1
        mouse_swipe(_width // 2, _height // 2, _width // 2, _height // 2 + 200 * _direction, SWIPE_TIME)
        time.sleep(1)
        arr = _screenshot()
    print('完成寻找', _floor, '楼层')
def start_mission(_sleep_time):
    print('点击开始任务按钮')
    time.sleep(_sleep_time)
    arr = _screenshot()
    while _match(_start, arr, True, BUTTON_MIN_MATCH_COUNT):
        print('点击开始任务按钮')
        arr = _screenshot()
    print('完成点击开始任务按钮')
def start_fight_2(_sleep_time):
    print('点击开始作战按钮')
    time.sleep(_sleep_time)
    arr = _screenshot()
    while _match(_start_fight_2, arr, True, BUTTON_MIN_MATCH_COUNT):
        print('点击开始作战按钮')
        #os.remove(temp_path)
        arr = _screenshot()
    print('完成点击开始作战按钮')
def click_agreement(_sleep_time):
    print('点击地图协议')
    time.sleep(_sleep_time)
    arr = _screenshot()
    while _match(_xieyi, arr, True, BUTTON_MIN_MATCH_COUNT):
        print('点击地图协议')
        arr = _screenshot()
    print('完成点击地图协议')
def click_ai_mode(_sleep_time):
    print('点击ai模式')
    time.sleep(_sleep_time)
    arr = _screenshot()
    while _match(_ai_mode, arr, True, BUTTON_MIN_MATCH_COUNT):
        print('点击ai模式')
        arr = _screenshot()
    print('完成点击ai模式')
def click_ai_start(_sleep_time):
    print('点击开始ai作战')
    time.sleep(_sleep_time)
    arr = _screenshot()
    while _match(_ai_start, arr, True, BUTTON_MIN_MATCH_COUNT):
        print('点击开始ai作战')
        arr = _screenshot()
    print('完成点击开始ai作战')
def sleep_fight(_sleep_time):
    print('作战开始,进入休眠')
    x= _sleep_time
    while x > 0:
        time.sleep(ONE_MINITE)
        print('第', x + 1, '分钟过去了')
        arr = _screenshot()
        if _match(_re_fight_1, arr, False, BUTTON_MIN_MATCH_COUNT) == False and _match(_cancel, arr, False, BUTTON_MIN_MATCH_COUNT) == False:
            print('检测到损失过大,重新作战')
            _match(_cancel, arr, True, BUTTON_MIN_MATCH_COUNT)
            x += 1
        if _match(_fight_fail, arr, False, BUTTON_MIN_MATCH_COUNT) == False and _match(_run, arr, False, BUTTON_MIN_MATCH_COUNT) == False:
            print('检测到作战失败,重新作战')
            _match(_run, arr, True, BUTTON_MIN_MATCH_COUNT)
            time.sleep(1)
            _match(_continue, arr, True, BUTTON_MIN_MATCH_COUNT)
            x = 0
        x -= 1
    print('拟定作战结束,唤醒')
def choose_reward(_sleep_time):
    print('捕获结算界面')
    time.sleep(_sleep_time)
    arr = _screenshot()
    while _match(_jiesuan_1, arr, False, BUTTON_MIN_MATCH_COUNT) or _match(_jiesuan_2, arr, False, BUTTON_MIN_MATCH_COUNT):
        print('捕获结算界面')
        arr = _screenshot()
    print('完成捕获结算界面')
def not_choose(_sleep_time):
    print('点击全部取消选择按钮')
    time.sleep(_sleep_time)
    arr = _screenshot()
    while _match(_not_choose, arr, True, BUTTON_MIN_MATCH_COUNT):
        print('点击全部取消选择按钮')
        arr = _screenshot()
    print('完成点击全部取消选择按钮')
def find_reward(_sleep_time_st, _sleep_time, _choose_reward):
    print('开始选择所需奖品')
    __x = 250
    __y = 290
    __dx = 244
    __w = 214
    __h = 260
    __sh = 45
    cnt_choose = 0
    time.sleep(_sleep_time_st)
    _times = (_width - 2 * __dx + __dx - 1) // __dx
    arr = _screenshot()
    _target = cv2.imdecode(arr, 0)
    for times in range(0, _times):
        print('检测奖励品1层', times + 1, '个')
        time.sleep(_sleep_time)
        target = _target[__y:(__y + __h), __x:(__x + __w)]
        for cur_reward in _choose_reward:
            if _match_pct(cur_reward, target, ITEM_MIN_MATCH_COUNT):
                mouse_click(__x + __w // 2, __y + __h - __sh // 2)
                cnt_choose += 1
        __x += __dx
    __x = 250
    __y = 580
    arr = _screenshot()
    _target = cv2.imdecode(arr, 0)
    for times in range(0, _times):
        print('检测奖励品2层', times + 1, '个')
        time.sleep(_sleep_time)
        target = _target[__y:(__y + __h), __x:(__x + __w)]
        for cur_reward in _choose_reward:
            if _match_pct(cur_reward, target, ITEM_MIN_MATCH_COUNT):
                mouse_click(__x + __w // 2, __y + __h - __sh // 2)
                cnt_choose += 1
        __x += __dx
    print('完成选择所需奖品')
    return cnt_choose
def buy_reward(_sleep_time):
    print('点击购买所选奖品')
    time.sleep(_sleep_time)
    arr = _screenshot()
    while _match(_buy, arr, True, BUTTON_MIN_MATCH_COUNT):
        print('点击购买所选奖品')
        arr = _screenshot()
    print('完成点击购买所选奖品')
def click_quit(_sleep_time):
    print('点击离开')
    time.sleep(_sleep_time)
    arr = _screenshot()
    while _match(_quit, arr, True, BUTTON_MIN_MATCH_COUNT):
        print('点击离开')
        arr = _screenshot()
    print('完成点击离开')
def click_confirm(_sleep_time):
    print('点击确认按钮')
    time.sleep(_sleep_time)
    arr = _screenshot()
    while _match(_confirm, arr, True, BUTTON_MIN_MATCH_COUNT):
        print('点击确认按钮')
        arr = _screenshot()
    print('完成点击确认按钮')
def confirm_quit(_sleep_time):
    print('点击确认离开')
    time.sleep(_sleep_time)
    arr = _screenshot()
    while _match(_confirm_quit, arr, False, BUTTON_MIN_MATCH_COUNT):
        print('点击确认离开')
        arr = _screenshot()
    click_confirm(_sleep_time)
    print('完成点击确认离开')
def click_back(_sleep_time):
    print('点击返回按钮')
    time.sleep(_sleep_time)
    arr = _screenshot()
    while _match(_back1, arr, True, BUTTON_MIN_MATCH_COUNT) and _match(_back2, arr, True, BUTTON_MIN_MATCH_COUNT):
        print('点击返回按钮')
        arr = _screenshot()
    print('完成点击返回按钮')
def click_continue(_sleep_time):
    print('点击继续')
    time.sleep(_sleep_time)
    arr = _screenshot()
    while _match(_continue, arr, True, BUTTON_MIN_MATCH_COUNT):
        print('点击继续')
        arr = _screenshot()
    print('完成点击继续')
'''
def wait_money(_sleep_time):
    print('检测是否缺少体力')
    time.sleep(_sleep_time)
    gui.screenshot(temp_path, _rect_windows)
    if _match(_no_money, temp_path, False, BUTTON_MIN_MATCH_COUNT) == False:
        print('等待体力恢复')
        
    os.remove(temp_path)
    print('完成等待体力恢复')
'''
cv2.matchTemplate
def _rand_time(_sleep_time):
    return _sleep_time + (1 if random.random() < 0.5 else -1) * random.random()
if __name__ == '__main__':
    init_configuration(True)
    adb_init(adb_port)
    find = True
    cnt_reward = 0
    cnt_round = 0
    while find:
        
        cnt_round += 1
        
        find_floor(cur_floor, _rand_time(SLEEP_TIME))
        
        start_mission(_rand_time(SLEEP_TIME))
        
        start_fight_2(_rand_time(SLEEP_TIME))
        
        click_agreement(_rand_time(SLEEP_TIME))

        click_ai_mode(_rand_time(SLEEP_TIME))

        click_ai_start(_rand_time(SLEEP_TIME))

        sleep_fight(fight_time)

        choose_reward(_rand_time(SLEEP_TIME))
        
        not_choose(_rand_time(SLEEP_TIME))
        
        cnt_choose = find_reward(SLEEP_TIME, D_FIND_REWARD, cur_choose_reward)
        
        cnt_reward += cnt_choose

        if cnt_choose > 0:
            buy_reward(_rand_time(SLEEP_TIME))
        else:
            click_quit(_rand_time(SLEEP_TIME))
            confirm_quit(_rand_time(SLEEP_TIME))

        click_back(_rand_time(SLEEP_TIME))
        
        click_continue(_rand_time(SLEEP_TIME))
        
    print('总共获得:', cnt_reward, '个,总共打了:', cnt_round, '轮')

