go = function()
  dofile("connection.lua")
end

noauto = function()
  file.remove("auto_run.txt")
end

nouart = function()
  file.remove("uart_settings.lua")
  change_uart_settings = false
end

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

  if file.open("auto_run.txt") == nil then
    print("auto_run.txt not present.")
  else
    print("go go go")
    file.close("auto_run.txt")

    go()
  end
end)
