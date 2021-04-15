#!/usr/bin/python3
import argparse
import dbus
import gatt
import struct

DWM_SERVICE_UUID = 'de258bcd-1d7c-48db-a7e3-4759ac040000'
DWM_LOCATION_CHARACTERISTIC_ID = 'de258bcd-1d7c-48db-a7e3-4759ac040002'

class DwmDeviceManager(gatt.DeviceManager):
    def __init__(self, adapter_name='hci0', discovery_callback=None):
        self.discovery_callback = discovery_callback
        super(DwmDeviceManager, self).__init__(adapter_name=adapter_name)

    def set_discovery_callback(self, discovery_callback):
        self.discovery_callback = discovery_callback

    def device_discovered(self, device):
        if self.discovery_callback != None:
            self.discovery_callback(self, device)

class DwmDevice(gatt.Device):
    def __init__(self, mac_address, manager, location_callback=None, subscribe=False):
        self.subscribe = subscribe
        self.location_callback = location_callback
        super(DwmDevice, self).__init__(mac_address=mac_address, manager=manager)

    def services_resolved(self):
        super().services_resolved()
        self._read_location()

    def characteristic_value_updated(self, characteristic, value):
        self._decode_location(value)

    def _read_location(self):
        device_information_service = next(
            s for s in self.services
            if s.uuid == DWM_SERVICE_UUID)
        
        location_data_characteristic = next(
            c for c in device_information_service.characteristics
            if c.uuid == DWM_LOCATION_CHARACTERISTIC_ID)
        
        if self.subscribe == True:
            location_data_characteristic.enable_notifications()

        location_data_characteristic.read_value()
    
    def _decode_location(self, location_data):
        encoded_bytes = [v for v in location_data]

        # LOCATION ENCODING: <1 byte - Type><4 bytes-x pos><4 bytes-y pos><4 bytes-z pos><1 byte-quality>
        if len(encoded_bytes) == 6:
            data1 = (encoded_bytes[0] * 100 + encoded_bytes[1]) / 100.0
            data2 = (encoded_bytes[2] * 100 + encoded_bytes[3]) / 100.0
            data3 = (encoded_bytes[4] * 100 + encoded_bytes[5]) / 100.0
            
            if self.location_callback != None:
                self.location_callback(self.manager, self, data1, data2, data3)
        else:
            print("Invalid location data received: length={0}".format(len(encoded_bytes)))

    def _get_pos(self, encoded_location):
        pos_bytes = bytearray(encoded_location)
        pos, = struct.unpack('<i', pos_bytes)
        return pos


def dwm_node_discovered(device_manager, device):
    print("Discovered [%s] %s" % (device.mac_address, device.alias()))

def dwm_location_received(device_manager, device, pos1, pos2, pos3):
    print("Anc1 = {0}m , Anc2 = {1}m, Anc3= {2}, mac={3}".format(pos1, pos2, pos3, device.mac_address))
    if device.subscribe != True:
        device_manager.stop()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("--discover", action="store_true", help="Discover active DWM bluetooth devices")
    parser.add_argument("--adapter", type=str, default= "hci0", help="Bluetooth adapter to use")
    parser.add_argument("--readlocation", action="store_true", help="Read location from the dwm device")
    parser.add_argument("--continous", action="store_true", help="Continously read location from the device")
    parser.add_argument("--mac", type=str, help="Target device mac address")

    args = parser.parse_args()

    if args.readlocation == True:
        mac_address='e3:ec:26:c3:38:45'
        print("Reading location data from: {0}".format(mac_address))
        manager = DwmDeviceManager(adapter_name=args.adapter)

        device = DwmDevice(mac_address=mac_address, manager=manager, location_callback=dwm_location_received, subscribe=True)
        device.connect()
        manager.run()
    
