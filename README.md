# Cellmate

Cellmate is a Sailfish OS app for monitoring and logging the local radio network

### Untested on 5G/NR 

I don't have a 5G test device so no testing has been done on a 5G network

## Serving Cell

The opening screen shows the available details about the current serving cell. The fields shown change depending on which technology the device is connected to. 
## Monitored Signals

Ofino makes available the full set of radio measurements for neighbouring cells measured by the device. These measurements can be accessed using the pull down drawer menu. For each reported measurement the identifier fields (BSIC / BCCH/ (e)ARFCN, PCI, PSC) are shown depeneding on the technology, along with available signal strength / quality indicators. 

In most circumstances the device will only make measurements for the technology it is currently served by (so a device camped on a LTE cell will mostly make LTE measurements). Measurements for other radio technologies are sometimes made when the device is preparing for an inter-RAT handover. 

## Recordings 

Recordings to a file can be started using 'Start Recording' from the pull down menu, and stopped using 'Stop Recording' from the same menu. When a recording is running the radio conditions are sampled every second and written to a log along with the timestamp and current location from the GPS if available. 

When stopping a recording the location and filename can be specified, with a unique filename being generated by default. Note that if the save path is changed it must be set to a location the application has access to (if running inside SailJail it only has access to the Documents folder).

## Log Format 

Logs are written in a JSONL format. Each line of the log file is a JSON object containing the available fields for one detected radio signal. Writing to a JSONL format reduces the memory required compared to writing a pure JSON object.

## Field Descriptions 

TODO

## Attributions

Thanks to Slava for the example implementation of the CellWatcher class on the forums:
https://forum.sailfishos.org/t/cell-id-info-no-longer-returned-via-dbus-calls-in-sfos-4-2/8254/23?page=2