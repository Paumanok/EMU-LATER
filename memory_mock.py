

def blank_mem(size):
    array = []
    for i in range(size):
        array.append(0)
    return array


c_string = "uint8_t cust_ram = { \n"
array = blank_mem(40)
for i in range(len(array)):
    c_string += (str(hex(array[i])))
    if i % 8 == 0:
        c_string += '\n'

    if i != 40 -1:
        c_string += ','
    else:
        c_string += '};'

print(c_string)
