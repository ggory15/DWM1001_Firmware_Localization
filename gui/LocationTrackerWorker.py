from enum import Enum
from dwm1001 import DwmDevice
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
        self.mac_address='e3:ec:26:c3:38:45'
        print("Reading location data from: {0}".format(self.mac_address))
        self.manager = self._device_manager
        self.device = DwmDevice(mac_address=self.mac_address, manager=self.manager, location_callback=self.dwm_tag_location_received, subscribe=True)
        self.device.connect()
        self.manager.run()
    
    def dwm_tag_location_received(self, device_manager, device, x_pos, y_pos, quality):
        if self._parent != None:
            evt = LocationReceivedEvent(LOC_RECEIVED_EVNT_TYPE, -1, device.alias(), x_pos, y_pos, quality)
            wx.PostEvent(self._parent, evt)
        else:
            print("ERR:Parent object not available")

