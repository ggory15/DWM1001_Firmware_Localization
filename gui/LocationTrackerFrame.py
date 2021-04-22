import wx
from dwm1001 import DwmDeviceManager
from LocationTrackerWorker import DeviceType, LocationTrackerWorker, LocationTrackerWorker, LOC_RECEIVED_EVNT
import math
import numpy as np
import threading

FLOOR_PLAN_IMAGE = 'demo/demo-floor-plan.png'
WINDOW_WIDTH = 890
WINDOW_HEIGHT = 1000

ANCHOR_IMAGE = 'demo/anchor.png'
TAG_IMAGE = 'demo/tag.png'
ICON_IMG_WIDTH = 32
ICON_IMG_HEIGHT = 32

X_UI_RANGE = (-400, 400)
Y_UI_RANGE = (-400, 400)

X_PHYSICAL_RANGE = (-1000, 1000)
Y_PHYSICAL_RANGE = (-1000, 1000)

QUALITY_THRESHOLD = 0

MAX_PREVIOUS_LOCATION_UPDATES = 10 # look at previous 'n' updates to calculated avg position
SKIP_LOCATION_UPDATES = 0 # ui updates after every 'n' loc update

class LocationTrackerFame(wx.Frame):
    def __init__(self, device_manager):
        super().__init__(parent=None, title='Location Tracker')

        self.SetSize((WINDOW_WIDTH, WINDOW_HEIGHT))
        self.SetTitle('DWM1001 Location Tracker Demo')
        self.Centre()

        img = wx.Image(FLOOR_PLAN_IMAGE, wx.BITMAP_TYPE_ANY)
        self.bitmap_img = img.ConvertToBitmap()
        
        self.floor_plan_img = wx.StaticBitmap(self, -1, self.bitmap_img, (10, 5), (self.bitmap_img.GetWidth(), self.bitmap_img.GetHeight()))
        self.floor_plan_img.Bind(wx.EVT_MOTION, self.imgctrl_on_mousemove)

        self.status_bar = wx.StatusBar(self, -1, wx.STB_ELLIPSIZE_END, "defaultstatusbar");
        self.status_bar.SetStatusText("X={0}, Y={1}".format(0,0))
        self.SetStatusBar(self.status_bar)

        self.anchors = dict()
        self.tag = None
        self.overlay = wx.Overlay()
        self.previous_loc_updates = list()
        self.loc_update_index = 0

        worker = LocationTrackerWorker(self, device_manager)
        worker.start()

        self.Show()
        self.Bind(LOC_RECEIVED_EVNT, self.on_location_received)
        self.anc1_pos = [0, 0]
        self.anc2_pos = [-0.5, 0.0]
        self.anc3_pos = [-0.25, 0.5]
    
    def on_location_received(self, evt):
        data1, data2, data3 = evt.get_location()
        device_name = evt.get_alias()
        print(data1, data2, data3)
        pos_x, pos_y = self.get_location(data1, data2, data3)

        x_pixel, y_pixel = self.convert_to_ui_coordinates(self.anc1_pos[0], self.anc1_pos[1])
        self.anchors["anc1"] = (x_pixel, y_pixel, self.anc1_pos[0], self.anc1_pos[1])
        
        x_pixel, y_pixel = self.convert_to_ui_coordinates(self.anc2_pos[0], self.anc2_pos[1])
        self.anchors["anc2"] = (x_pixel, y_pixel, self.anc2_pos[0], self.anc2_pos[1])
        
        x_pixel, y_pixel = self.convert_to_ui_coordinates(self.anc3_pos[0], self.anc3_pos[1])
        self.anchors["anc3"] = (x_pixel, y_pixel, self.anc3_pos[0], self.anc3_pos[1])
        
        x_pixel, y_pixel = self.convert_to_ui_coordinates(pos_x, pos_y)
        self.tag = (x_pixel, y_pixel, pos_x, pos_y)
        self.draw_tracking_overlay()


    def get_location(self, data1, data2, data3):
        if (data1 >0 and data2 >0 and data3 >0):
            #2D-TRIA Algorithm
            tmp = (self.anc2_pos[1] - self.anc1_pos[1]) * (pow(data1, 2) - pow(data3, 2) - pow(self.anc1_pos[1], 2) + pow(self.anc3_pos[0], 2) + pow(self.anc3_pos[1], 2) - pow(self.anc1_pos[0], 2))
            lam = pow(self.anc1_pos[0], 2) + pow(self.anc1_pos[1], 2) - pow(data1, 2) - pow(self.anc2_pos[0], 2) - pow(self.anc2_pos[1], 2) + pow(data2, 2) + tmp / (self.anc3_pos[1] - self.anc1_pos[1]) 
            delta = 2. * (  (self.anc2_pos[1] - self.anc1_pos[1]) * (self.anc3_pos[0] - self.anc1_pos[0]) -  (self.anc2_pos[0] - self.anc1_pos[0]) * (self.anc3_pos[1] - self.anc1_pos[1]))

            Mx = lam * (self.anc3_pos[1] - self.anc1_pos[1]) / delta
            tmp2 = pow(data1, 2) - pow(data3, 2) - pow(self.anc1_pos[1], 2) + pow(self.anc3_pos[0], 2) + pow(self.anc3_pos[1], 2) - pow(self.anc1_pos[0], 2) - 2. * (self.anc3_pos[0] - self.anc1_pos[0]) * Mx
            My = tmp2 / (2 * (self.anc3_pos[1] -self.anc1_pos[1]))
            self.pos = np.array([ Mx, My])
            print ("2D position is :", self.pos)

            #3D-TRIA Algorithm
            # Da = data1
            # Db = data2
            # Dc = data3
            # Ax = self.anc1_pos[0]
            # Ay = self.anc1_pos[1]
            # Bx = self.anc2_pos[0]
            # By = self.anc2_pos[1]
            # Cx = self.anc3_pos[0]
            # Cy = self.anc3_pos[1]

            # Mx = (pow(Da, 2) - pow(Db, 2) + pow(Bx, 2)) / 2.0 / Bx
            # My = (pow(Cx, 2) + pow(Cy, 2) + pow(Da, 2) - pow(Dc, 2) - 2*Mx *Cx)/ 2.0 / Cy
            # Mz = np.sqrt(np.fabs(pow(Da, 2) - pow(Mx, 2) - pow(My, 2)))

            # self.pos = np.array([Mx, My, Mz]) 
            # print ("3D position is :", self.pos)

            # A = -2.*self.anc1_pos[0] + 2. * self.anc2_pos[0]
            # B = -2.*self.anc1_pos[1] + 2. * self.anc2_pos[1]
            # D = -2.*self.anc2_pos[0] + 2. * self.anc3_pos[0]
            # E = -2.*self.anc2_pos[1] + 2. * self.anc3_pos[1]
            # C = pow(data1, 2) - pow(data2, 2) - pow(self.anc1_pos[0], 2) + pow(self.anc2_pos[0], 2) - pow(self.anc1_pos[1], 2) + pow(self.anc2_pos[1], 2)
            # F = pow(data2, 2) - pow(data3, 2) - pow(self.anc2_pos[0], 2) + pow(self.anc3_pos[0], 2) - pow(self.anc2_pos[1], 2) + pow(self.anc3_pos[1], 2)
            # self.pos = np.array([(C*E - F*B)/(E*A -B*D), (C*D-A*F)/(B*D-A*E)])

        if (data1 == 0.0):
            self.pos = self.anc1_pos
        if (data2 == 0.0):
            self.pos = self.anc2_pos
        if (data3 == 0.0):
            self.pos = self.anc3_pos

        return (self.pos[0], self.pos[1])

    def convert_to_ui_coordinates(self, physical_x, physical_y):
        gain = 50.0
        x_pixel_coord = 450 + physical_x * gain
        y_pixel_coord = 500 + physical_y * gain

        return (x_pixel_coord, y_pixel_coord)

    def imgctrl_on_mousemove(self, event):
        ctrl_pos = event.GetPosition()
        pos = self.floor_plan_img.ScreenToClient(ctrl_pos)
        screen_pos = self.GetScreenPosition()
        relative_pos_x = pos[0] + screen_pos[0]
        relative_pos_y = pos[1] + screen_pos[1]
        self.status_bar.SetStatusText("X={0}, Y={1}".format(relative_pos_x,relative_pos_y))
        self.draw_tracking_overlay()

    def draw_tracking_overlay(self):
        mdc = wx.ClientDC(self)
        dc = wx.BufferedDC(mdc)
        # Draw floor plan
        dc.DrawBitmap(self.bitmap_img, 10, 5)
        
        font = wx.Font(pointSize = 9, family = wx.DEFAULT,
               style = wx.NORMAL, weight = wx.NORMAL,
               faceName = 'Consolas')
        dc.SetFont(font)

        odc = wx.DCOverlay(self.overlay, dc)
        odc.Clear()
        
        # draw anchors
        if self.anchors != None:
            for name in self.anchors:
                x, y, x_mm, y_mm = self.anchors[name]
                self._draw_anchor(dc, name, x, y, x_mm, y_mm)

        # draw tag
        if self.tag != None:
            x , y, x_mm, y_mm = self.tag
            self._draw_tag(dc, x, y, x_mm, y_mm)

    def _draw_tag(self, dc, x, y, x_mm, y_mm):
        # Draw icon: tag image
        icon_img = wx.Image(TAG_IMAGE, wx.BITMAP_TYPE_ANY).Scale(ICON_IMG_WIDTH, ICON_IMG_HEIGHT, wx.IMAGE_QUALITY_HIGH)
        icon_bitmap = icon_img.ConvertToBitmap()
        img_x = x-(ICON_IMG_WIDTH/2)
        img_y = y-(ICON_IMG_HEIGHT)
        dc.DrawBitmap(icon_bitmap, img_x, img_y)
        dc.DrawCircle(x, y, 3)

        # Draw text: position
        label = "x={0} m, y={0} m".format(x_mm, y_mm)
        tw, th = dc.GetTextExtent(label)
        dc.DrawText(label, img_x + (ICON_IMG_WIDTH - tw)/2, img_y+ICON_IMG_HEIGHT)

        # Draw lines to all anchors
        dc.SetPen(wx.Pen("gray", 1, style=wx.PENSTYLE_DOT))
        if self.anchors != None:
            for name in self.anchors:
                anchor_x, anchor_y, x_mm, y_mm = self.anchors[name]
                dc.DrawLine(x, y, anchor_x, anchor_y)

    def _draw_anchor(self, dc, name, x, y, x_mm, y_mm):
        # Draw icon: Anchor image
        icon_img = wx.Image('demo/anchor.png', wx.BITMAP_TYPE_ANY).Scale(ICON_IMG_WIDTH, ICON_IMG_HEIGHT, wx.IMAGE_QUALITY_HIGH)
        icon_bitmap = icon_img.ConvertToBitmap()
        x_pixel_start, x_pixel_end = X_UI_RANGE
        img_x = x-(ICON_IMG_WIDTH/2)
        # img_x = x_pixel_start if img_x < x_pixel_start else img_x
        # img_x = x_pixel_end if img_x > x_pixel_end else img_x

        img_y = y-(ICON_IMG_HEIGHT/2)
        dc.DrawBitmap(icon_bitmap, img_x , img_y)

        # Draw text: Name and position
        label = "{0} (x={1} m, y={2} m)".format(name, x_mm, y_mm)
        tw, th = dc.GetTextExtent(label)
        lbl_x = img_x + ICON_IMG_WIDTH if img_x < (x_pixel_end + x_pixel_start)/2 else img_x - tw
        lbl_y = img_y+ICON_IMG_HEIGHT
        dc.DrawText(label, lbl_x, lbl_y)