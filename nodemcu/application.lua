dofile("credentials.lua")

long_names = {
  ["b0"] = "block_0",
  ["b1"] = "block_1",
  ["s0"] = "switch_0",
  ["s1"] = "switch_1",
  ["s2"] = "switch_2",
  ["s3"] = "switch_3",
  ["s4"] = "switch_4",
  ["s5"] = "switch_5",
}

max_brightness = 0xffff

current_mqtt_client = nil

uart_callback = function(data)
  print("you said: " .. data)
  if string.sub(data, 1, 8) == "%restart" then
    node.restart()
    return
  end

  local key, raw_value = string.match(data, '%%status ([bs][0-9])=([0-9]+)')
  if key ~= nil then
    local long_name = long_names[key]
    if long_name == nil then
      print("unable to find key " .. key)
      return
    end

    local value = nil
    if string.sub(key, 1, 1) == "s" then
      value = (tonumber(raw_value) >= 0.5)
    else
      value = tonumber(raw_value) / max_brightness
      if value > 1 then
        value = 1
      elseif value < 0 then
        value = 0
      end
    end

    if value ~= nil and current_mqtt_client ~= nil then
      topic = MQTT_ROOT .. "/status/" .. long_name
      if value == true or value == false or value == 0 or value == 1 then
        value_string = tostring(value)
      else
        value_string = string.format("%.5f", value)
      end
      succ = current_mqtt_client:publish(topic, value_string, 1, 1)
      print("publish [" .. topic .. "] " .. value_string .. ": " .. tostring(succ))
    end
    return
  end

  print("unknown key.")
end

main = function()
  connect_mqtt()
  print("NOW EXITING LUA SHELL. USE \"\\n%restart\\n\" TO RESTART.")
  uart.on("data", "\n", uart_callback, 0)
end

process_set = function(name, data)
  local value = nil
  if data == "true" then
    value = 1
  elseif data == "false" then
    value = 0
  else
    value = tonumber(data)
  end

  if value ~= nil then
    if string.sub(name, 1, 1) == "s" and value ~= 0 then
      value = 1
    end
    if string.sub(name, 1, 1) == "b" then
      if value < 0 then
        value = 0
      elseif value > 1 then
        value = max_brightness
      else
        value = math.floor(value * max_brightness + 0.5)
      end
    end

    uart.write(0, "\n", "%set ", name, "=", tostring(value), "\n")
  else
    print("invalid value: " .. data)
  end
end

process_get = function(name)
  uart.write(0, "\n", "%get ", name, "\n")
end

subscriptions = {
  [MQTT_ROOT .. "/set/block_0"] = {1, function(client, data)
      process_set("b0", data)
    end},
  [MQTT_ROOT .. "/set/block_1"] = {1, function(client, data)
      process_set("b1", data)
    end},
  [MQTT_ROOT .. "/set/switch_0"] = {1, function(client, data)
      process_set("s0", data)
    end},
  [MQTT_ROOT .. "/set/switch_1"] = {1, function(client, data)
      process_set("s1", data)
    end},
  [MQTT_ROOT .. "/set/switch_2"] = {1, function(client, data)
      process_set("s2", data)
    end},
  [MQTT_ROOT .. "/set/switch_3"] = {1, function(client, data)
      process_set("s3", data)
    end},
  [MQTT_ROOT .. "/set/switch_4"] = {1, function(client, data)
      process_set("s4", data)
    end},
  [MQTT_ROOT .. "/set/switch_5"] = {1, function(client, data)
      process_set("s5", data)
    end},
  [MQTT_ROOT .. "/get/block_0"] = {1, function(client, data)
      process_get("b0")
    end},
  [MQTT_ROOT .. "/get/block_1"] = {1, function(client, data)
      process_get("b1")
    end},
  [MQTT_ROOT .. "/get/switch_0"] = {1, function(client, data)
      process_get("s0")
    end},
  [MQTT_ROOT .. "/get/switch_1"] = {1, function(client, data)
      process_get("s1")
    end},
  [MQTT_ROOT .. "/get/switch_2"] = {1, function(client, data)
      process_get("s2")
    end},
  [MQTT_ROOT .. "/get/switch_3"] = {1, function(client, data)
      process_get("s3")
    end},
  [MQTT_ROOT .. "/get/switch_4"] = {1, function(client, data)
      process_get("s4")
    end},
  [MQTT_ROOT .. "/get/switch_5"] = {1, function(client, data)
      process_get("s5")
    end},
}

connected = function(client)
  print("connected and subscribed")
  client:publish(MQTT_ROOT .. "/connected", "2", 1, 1)
  current_mqtt_client = client
end

-- init mqtt client without logins, keepalive timer 120s
if MQTT_AUTH then
  mqtt_client = mqtt.Client(MQTT_CLIENT_ID, MQTT_KEEPALIVE, MQTT_USERNAME, MQTT_PASSWORD)
else
  mqtt_client = mqtt.Client(MQTT_CLIENT_ID, MQTT_KEEPALIVE)
end

-- unset connected state when we die
mqtt_client:lwt(MQTT_ROOT .. "/connected", "0", 1, 1)

-- on publish message receive event
mqtt_client:on("message", function(client, topic, data)
  sub = subscriptions[topic]
  if sub ~= nil then
    sub[2](client, data)
  else
    print("received [" .. topic .. "]: " .. data)
  end
end)

mqtt_offline_callback = function(client)
  current_mqtt_client = nil
  print("MQTT went offline. Will connect again in 3 seconds")
  tmr.create():alarm(3000, tmr.ALARM_SINGLE, connect_mqtt)
end

mqtt_client:on("offline", mqtt_offline_callback)

connect_mqtt = function()
  print("Connecting to MQTT...")
  if MQTT_TLS then is_tls = 1 else is_tls = 0 end

  ok = mqtt_client:connect(MQTT_HOST, MQTT_PORT, is_tls,
    function(client)
      print("MQTT connected!")

      subscription_priorities = {}
      for topic,sub in pairs(subscriptions) do
        subscription_priorities[topic] = sub[1]
      end

      client:subscribe(subscription_priorities, connected)
    end,
    function(client, reason)
      print("failed to connect to MQTT: " .. reason)
      mqtt_offline_callback(client)
    end
  )
end

-- mqtt_client:close();

main()