connection = require 'connection'

noauto = function()
    if file.open("no_auto_connect.txt", "w") then
        file.close("no_auto_connect.txt")
    end
end

nouart = function()
    file.remove("uart_settings.lua")
    change_uart_settings = false
end

begin = function()
    print("hi :)")
    if file.open("uart_settings.lua") ~= nil then
        file.close("uart_settings.lua")
        print("UART SETTINGS WILL CHANGE AFTER 7 SECONDS! CANCEL WITH nouart().")
        change_uart_settings = true
    else
        change_uart_settings = false
    end

    tmr.create():alarm(7000, tmr.ALARM_SINGLE, function()
        if change_uart_settings then
            dofile("uart_settings.lua")
        end

        if file.open("no_auto_connect.txt") == nil then
            connection.connect()
        else
            print("not connecting automatically.")
            file.close("no_auto_connect.txt")
        end
    end)
end
