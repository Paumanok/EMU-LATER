

def blank_mem(size):
    array = []
    for i in range(size):
        array.append(0)
    return array


c_string = "uint8_t mock_ram[] = { \n"
array = blank_mem(0x40)

#indexed indirect
array[0x18] = 0x20
array[0x19] = 0x10

array[0x10] = 0x26
array[0x11] = 0x10

array[0x2e] = 0xc4



for i in range(len(array)):
    c_string += (str(hex(array[i])))

    if i != 0x40 -1:
        c_string += ','
    else:
        c_string += '};'

    if i % 8 == 0 and i != 0:
        c_string += '\n'

print(c_string)
