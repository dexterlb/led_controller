uart.setup(0, 9600, 8, uart.PARITY_NONE, uart.STOPBITS_1, 0)

reset_uart = function()
    uart.setup(0, 115200, 8, uart.PARITY_NONE, uart.STOPBITS_1, 1)
end

echo_on = function()
    uart.setup(0, 9600, 8, uart.PARITY_NONE, uart.STOPBITS_1, 1)
end