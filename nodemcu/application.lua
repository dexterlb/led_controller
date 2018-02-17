dofile("credentials.lua")

main = function()
  connect_mqtt()
end

subscriptions = {
  ["/leddy"]=1
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
  print(topic .. ":" )
  if data ~= nil then
    print(data)
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
      client:subscribe(subscriptions, connected)
    end,
    function(client, reason)
      print("failed to connect to MQTT: " .. reason)
      mqtt_offline_callback(client)
    end
  )
end

-- mqtt_client:close();

main()