import random

len_of_b = 20
len_of_c = 20 
len_of_d = 20

value_min = 1.0
value_max = 1000.0


f = open('inputs.txt', 'w')

def generate_inputs(param):
    
    iter_count = 0
    i = 0
    j = 0

    if (param == 'b'):
        iter_count = len_of_b
    if (param == 'c'):
        iter_count = len_of_c
    if (param == 'd'):
        iter_count = len_of_d

    for x in range (iter_count):

        value = round(random.uniform(value_min, value_max),2)

        text = str(param)
        text += r".insert({std::make_pair("
        text += str(i)
        text += ','
        text += str(j)
        text += '), '
        text += str(value)
        text += r"});"

        f.write(text)
        f.write('\n')

        # Increase i or j 
        # j's increase probability is 4 times higher
        rand_num = random.randrange(5)

        if rand_num == 0: # increase i
            i = i + 1
            j = 0
        else: # increase j
            j = j + 1


generate_inputs('b')            
generate_inputs('c')    
generate_inputs('d')    
