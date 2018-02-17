dofile("credentials.lua")

main = function()
  connect_mqtt()
end

uart_names = {
  ["block_0"] = "b0",
  ["block_1"] = "b1",
  ["switch_0"] = "s0",
  ["switch_1"] = "s1",
  ["switch_2"] = "s2",
  ["switch_3"] = "s3",
  ["switch_4"] = "s4",
  ["switch_5"] = "s5",
}

subscriptions = {
  [MQTT_ROOT .. "/set/block_0"] = {1, function(client, data)
      process_set("block_0", data)
    end}
}


connected = function(client)
  print("connected and subscribed")
  client:publish(MQTT_ROOT .. "/connected", "2", 1, 1)
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