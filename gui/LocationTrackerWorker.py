from enum import Enum
from dwm1001 import DwmDeviceManager
import threading
import wx

class DeviceType(Enum):
    ANCHOR = 1
    TAG = 2

LOC_RECEIVED_EVNT_TYPE = wx.NewEventType()
LOC_RECEIVED_EVNT = wx.PyEventBinder(LOC_RECEIVED_EVNT_TYPE, 1)
class LocationReceivedEvent(wx.PyCommandEvent):
    def __init__(self, etype, eid, alias, data1, data2, data3):
        wx.PyCommandEvent.__init__(self, etype, eid)
        self._alias = alias
        self.data1 = data1
        self.data2 = data2
        self.data3 = data3

    def get_location(self):
        return (self.data1, self.data2, self.data3)

    def get_alias(self):
        return self._alias


class LocationTrackerWorker(threading.Thread):
    def __init__(self, parent, device_manager):
        threading.Thread.__init__(self)
        self._parent = parent
        self._device_manager = device_manager

    def run(self):
        port= "/dev/ttyACM0"
        print("Reading location data from: {0}".format(port))
        self.manager = DwmDeviceManager(port)
        while 1:
            self.manager.run()

            self.dwm_tag_location_received(float(self.manager.data[0]), float(self.manager.data[1]), float(self.manager.data[2]))
    
    def dwm_tag_location_received(self, x_pos, y_pos, quality):
        if self._parent != None:
            evt = LocationReceivedEvent(LOC_RECEIVED_EVNT_TYPE, -1, "tag", x_pos, y_pos, quality)
            wx.PostEvent(self._parent, evt)
        else:
            print("ERR:Parent object not available")

    
