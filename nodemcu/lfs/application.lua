mqtt_persistent = require 'mqtt_persistent'

max_brightness = 0xffff
current_mqtt_client = nil

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

local function process_data(key, raw_value)
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
        if value == true or value == false or value == 0 or value == 1 then
            value_string = tostring(value)
        else
            value_string = string.format("%.5f", value)
        end
        succ = current_mqtt_client:publish("_value/" .. POTOO_ROOT .. "/" .. long_name, value_string, 1, 1)
    end
end

local function uart_callback(data)
    if string.sub(data, 1, 8) == "%restart" then
        node.restart()
        return
    end

    local key, raw_value = string.match(data, '%%status ([bs][0-9])=([0-9]+)')
    if key ~= nil then
        process_data(key, raw_value)
    else
        print("unknown key.")
    end
end

local function process_set(name, data)
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

local function process_get(name)
    uart.write(0, "\n", "%get ", name, "\n")
end

local function set_led(led_id, state)
    local state_value = nil
    if state then
        state_value = 1
    else
        state_value = 0
    end

    uart.write(0, "\n", "%set l", tostring(led_id), "=", tostring(state_value), "\n")
end

local function make_subscriptions()
    local subscriptions = {
        [POTOO_ROOT .. "/foo"] = {0, function(client, data)
            print("foo: ", data)
        end},
        [POTOO_ROOT .. "/terminal/start"] = {0, function(client, data)
            node.output(function(s)
                client:publish("/terminal/out", s, 0, 0)
            end, 0)
        end},
        [POTOO_ROOT .. "/terminal/in"] = {0, function(client, data)
            node.input(data)
        end},
    }

    for short, long in pairs(long_names) do
        subscriptions["_call/" .. POTOO_ROOT .. "/" .. long .. "/set"] = {
            0, function(client, data)
                local arg = data:gmatch("[^ ]*$")()
                process_set(short, arg)
            end
        }
    end

    return subscriptions
end

local function send_defaults()
    for short, long in pairs(long_names) do
        process_data(short, "0")
    end
end

local function make_contract()
    local ss = {}
    local add = function(...)
        for _, s in ipairs(arg) do
            ss[#ss + 1] = s
        end
    end

    add("{")
    for short, long in pairs(long_names) do
        local tt = {}
        tt[#tt + 1] = '{"t":{"kind":"type-basic",'
        if string.sub(short, 1, 1) == "s" then
            tt[#tt + 1] = '"sub":"bool"'
        else
            tt[#tt + 1] = '"sub":"float","meta":{"min":0,"max":1}'
        end
        tt[#tt + 1] = '},"meta":{},"version":"0","encoding":"json"}'

        add('"')
        add(long)
        add('":{', '"_t":"value","type":')
        add(unpack(tt))
        add(",")
        add('"subcontract":{')
        add('"set":{"_t":"callable","argument":')
        add(unpack(tt))
        add(',"retval":{"t":{"kind":"type-basic","sub":"void"},')
        add('"meta":{},"version":"0","encoding":"json"},"subcontract":{}}')
        add('}')
        add('}')
        add(',')
    end
    ss[#ss] = "" -- remove the last comma
    add("}")

    return table.concat(ss, "")
end

local function connected(client)
    current_mqtt_client = client
    client:publish("_contract/" .. POTOO_ROOT, make_contract(), 1, 1)
    send_defaults()
    set_led(0, true)
    print("started service")
end

local function disconnected(client)
    current_mqtt_client = nil
    set_led(0, false)
    print("suspended service")
end

local function main()
    local client = mqtt_persistent.connect(
        make_subscriptions(), connected, disconnected,
        {"_contract/" .. POTOO_ROOT, "null"}
        )

    tmr.create():alarm(3000, tmr.ALARM_SINGLE, function()
        print("NOW EXITING LUA SHELL. USE \"\\n%restart\\n\" TO RESTART.")
        uart.on("data", "\n", uart_callback, 0)
    end)
end

return {
    main = main
}
