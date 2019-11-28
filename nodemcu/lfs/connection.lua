-- load credentials, 'SSID' and 'PASSWORD' declared and initialize in there
dofile("credentials.lua")
application = require 'application'
telnet = require 'telnet'

local function startup()
    if file.open("no_telnet.txt") == nil then
        print('starting telnet server on port 2345.')
        telnet:open(nil, nil, 2345)
    else
        file.close("no_telnet.txt")
    end

    if file.open("run.txt") == nil then
        print("run.txt deleted or renamed")
    else
        print("Running")
        file.close("run.txt")

        application.main()
    end
end

-- Define WiFi station event callbacks
local wifi_connect_event = function(T)
    print("Connection to AP("..T.SSID..") established!")
    print("Waiting for IP address...")
    if disconnect_ct ~= nil then disconnect_ct = nil end
end

local app_started = false

local wifi_got_ip_event = function(T)
    print("Wifi connection is ready! IP address is: "..T.IP)
    if not app_started then
        app_started = true
        print("Will start in 3sec...")
        tmr.create():alarm(3000, tmr.ALARM_SINGLE, startup)
    end
end

local wifi_disconnect_event = function(T)
    if T.reason == wifi.eventmon.reason.ASSOC_LEAVE then
        --the station has disassociated from a previously connected AP
        return
    end
    -- total_tries: how many times the station will attempt to connect to the AP. Should consider AP reboot duration.
    local total_tries = 75
    print("\nWiFi connection to AP("..T.SSID..") has failed!")

    --There are many possible disconnect reasons, the following iterates through
    --the list and returns the string corresponding to the disconnect reason.
    for key,val in pairs(wifi.eventmon.reason) do
        if val == T.reason then
            print("Disconnect reason: "..val.."("..key..")")
            break
        end
    end

    telnet:close()

    if disconnect_ct == nil then
        disconnect_ct = 1
    else
        disconnect_ct = disconnect_ct + 1
    end
    if disconnect_ct < total_tries or total_tries == -1 then
        print("Retrying connection...(attempt "..(disconnect_ct+1).." of "..total_tries..")")
    else
        wifi.sta.disconnect()
        print("Aborting connection to AP!")
        print("Will restart.")
        node.restart()
        disconnect_ct = nil
    end
end

local function connect()
    wifi.eventmon.register(wifi.eventmon.STA_CONNECTED, wifi_connect_event)
    wifi.eventmon.register(wifi.eventmon.STA_GOT_IP, wifi_got_ip_event)
    wifi.eventmon.register(wifi.eventmon.STA_DISCONNECTED, wifi_disconnect_event)

    print("Connecting to WiFi access point...")
    wifi.setmode(wifi.STATION)
    wifi.sta.config({ssid=SSID, pwd=PASSWORD})
    -- wifi.sta.connect() not necessary because config() uses auto-connect=true by default
end

return {
    connect = connect
}
