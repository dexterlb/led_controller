dofile('credentials.lua')

local function connect(subscriptions, connected, disconnected, lwt)
    local mqtt_client = nil;
    if MQTT_AUTH then
        mqtt_client = mqtt.Client(MQTT_CLIENT_ID, MQTT_KEEPALIVE, MQTT_USERNAME, MQTT_PASSWORD)
    else
        mqtt_client = mqtt.Client(MQTT_CLIENT_ID, MQTT_KEEPALIVE)
    end

    local obj = {
        publish = function(self, topic, msg, qos, retain)
            if not self:is_online() then
                print("cannot publish because MQTT is offline")
                return
            end
            self.current_mqtt_client:publish(topic, msg, qos, retain)
        end,
        is_online = function(self)
            return self.current_mqtt_client ~= nil
        end,
        current_mqtt_client = nil
    }

    local subscription_qoses = {}
    local subscription_callbacks = {}
    for topic,sub in pairs(subscriptions) do
        local full_topic = topic
        subscription_qoses[full_topic] = sub[1]
        subscription_callbacks[full_topic] = sub[2]
    end

    -- unset connected state when we die
    if lwt ~= nil then
        mqtt_client:lwt(lwt[1], lwt[2], 1, 1)
    end

    -- on publish message receive event
    mqtt_client:on("message", function(client, topic, data)
        local callback = subscription_callbacks[topic]
        if callback ~= nil then
            callback(client, data)
        else
            print("received [" .. topic .. "]: " .. data)
        end
    end)

    local connect_mqtt = function()
        print("Connecting to MQTT...")
        local ok = mqtt_client:connect(MQTT_HOST, MQTT_PORT, MQTT_TLS,
            function(client)
                print("MQTT connected!")
                client:subscribe(subscription_qoses, function()
                    obj.current_mqtt_client = mqtt_client
                    if connected ~= nil then
                        connected(obj)
                    end
                end)
            end,
            function(client, reason)
                print("failed to connect to MQTT: " .. reason)
                mqtt_offline_callback(client)
            end
        )

        if not ok then
            mqtt_offline_callback(mqtt_client)
        end
    end

    local mqtt_offline_callback = function(client)
        obj.current_mqtt_client = nil
        if disconnected  ~= nil then
            disconnected(obj)
        end
        print("MQTT went offline. Will connect again in 3 seconds")
        tmr.create():alarm(3000, tmr.ALARM_SINGLE, connect_mqtt)
    end

    mqtt_client:on("offline", mqtt_offline_callback)

    connect_mqtt()

    return obj
end

return {
    connect = connect
}
