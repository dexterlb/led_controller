if file.open("_reflash.txt") ~= nil then
    file.remove("_reflash.txt")
    print("Reflashing LFS...")
    local result = node.flashreload("lfs.img")
    print(result)
end

function reflash()
    file.open("_reflash.txt", "w")
    file.close()
    node.restart()
end

if pcall(node.flashindex("_init")) then
    require('begin')
    begin()
else
    print('No LFS found.')
end
